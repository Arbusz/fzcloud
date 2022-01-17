/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <protos/fzrpc.grpc.pb.h>
#include <fzrpc/RpcLib.h>
#include <fzc/JobState.h>
#include <fzc/DockerHandler.h>
#include <fzc/util.h>
#include <fzrpc/RpcServer.h>
using namespace std;

#define MASTER_IP "172.18.194.116"
template<typename TSERVICE, typename TSERVICESUB>
class MyConnection : public RpcConnection<TSERVICE, TSERVICESUB>
{
public:

    MyConnection(const std::string& address, CompletionQueue* cq, std::shared_ptr<JobSet> jobset) :
            RpcConnection<TSERVICE, TSERVICESUB>(address, cq), jobset(jobset), alive(true) {}

    void sayHello(std::shared_ptr<Job> job)
    {
        if(job == nullptr){
            printf("empty job\n");
            return;
        }

        FzRequest request;

        request.set_jobid(job->id);
        request.set_cmd(job->cmd);
        AsyncClientCall <FzRequest, FzResponse> *call =
                new AsyncClientCall<FzRequest, FzResponse>(this, job->id + "_Request");
        call->ResponderReader() = this->mStub->AsyncRemoteCall(&call->Context(), request, this->mCompletionQueue);
        job->moveState(js_running);
        call->ResponderReader()->Finish(&call->Reply(), &call->RpcStatus(), (void *) call);

    }

public:

    //callback
    virtual void onMessage(ClientCallMethod *cm)
    {
        AsyncClientCall <FzRequest, FzResponse> *helloCd =
                dynamic_cast<AsyncClientCall <FzRequest, FzResponse> *>(cm);
        if (helloCd) {
            if (helloCd->RpcStatus().ok()) {
                auto resp = helloCd->Reply();
                std::cout << "Received from: " << jobset->client_uri << "\t" << resp.ret() << std::endl;

                if(resp.jobid() >= jobset->jobs.size()){
                    printf("onMessage : bad jobid %u\n", resp.jobid());
                    delete helloCd;
                    return;
                }

                auto cjob = jobset->jobs[resp.jobid()];

                if(cjob->state.getState() == js_running){
                    if(resp.flag())
                    {
                        cjob->moveState(js_success);
                    }
                    else if (!resp.flag() && resp.ret().length() > 0 )
                    {
                        //failed exec
                       cjob->moveState(js_hanging);
                    }else{
                        printf("wrong condition...\n");
                    }
                }
                else if (cjob->state.getState() == js_success)
                {
                   //do nothing
                } else{
                    printf("onMessage: wrong job state : %d\n", cjob->state.getState());
                }
            }
            else {
                std::cout << "RPC failed" << std::endl;
                jobset->end(false);
                jobset->jobs[jobset->currentJobID]->state.move(js_hanging);
            }
            delete helloCd;
            return;
        }else{
            jobset->end(false);
        }
    }

    //proceeding function
    //called in main thread
    void proceed(){

        uint32_t id = jobset->currentJobID;
        auto& cjob = jobset->jobs[id];
        switch (cjob->state.getState()) {

            case js_received : {
                if(id == 0){
                    jobset->start();
                }
                jobset->curJobtime_ms = MicroSecondNow();

                //todo: random delay for sync job ?
                if(jobset->syncIntvl_sec > 0 && (cjob->jbt == jbt_sync_result || cjob->jbt == jbt_sync_up)){
                    cjob->moveState(js_delayed);
                }else{
                    //first get the job, launch it
                    cjob->moveState(js_launched);
                    this->sayHello(cjob);
                }
                break;
            }
            case js_delayed : {
                //todo : check if we are due
                auto inter = MicroSecondNow() - jobset->curJobtime_ms;
                //printf("delayed timeout , schedule the job %lu %d\n", inter, jobset->syncIntvl_sec);

                if( (inter)/1000 > jobset->syncIntvl_sec ){
                    cjob->moveState(js_launched);
                    this->sayHello(cjob);
                }else{
                    //printf("job waiting to launch\n");
                }
                break;
            }
            case js_hanging : {
                //resend a hanging job!
                if (cjob->tries < 3) {
                    //printf("retrying\n");
                    cjob->tries++;
                    cjob->moveState(js_retry);
                }
                else {
                    cjob->moveState(js_failure);
                }
                break;
            }
            case js_retry : {
                cjob->moveState(js_launched);
                this->sayHello(cjob);
                break;
            }
            case js_failure : {
                jobset->end(false);
                break;
            }
            case js_success : {
                if (id < (jobset->jobs.size() - 1))
                    jobset->currentJobID++;
                else {
                    jobset->end(true);
                }
                break;
            }
            default: {
                //printf("error state %d\n",cjob->state.getState() );
            }
        }
    }

public:
    volatile bool           alive;
    MicroSecond             last_heartbit_time;

private:

    std::shared_ptr<JobSet> jobset;
};

class MasterServiceImpl final : public FzService::Service
{

private:
    Status RemoteCall(ServerContext* context, const FzRequest* request,
                      FzResponse* response) override
    {
        std::string mCommand = request->cmd();
        response->set_jobid(request->jobid());
        response->set_cmd(mCommand);

        mCommand += "&&";
        switch (mCommand[0])
        {
            case '3':
            {
                std::vector<std::string> paramLists = Split(mCommand, "&&");
                //printf("recv reg from client : %s\n", paramLists[1].c_str());
                addconnection(paramLists[1]);
                //response->set_flag(true);
                //response->set_ret("success3");

                break;
            }
            default:
            {
                std::cout << "Not a valid command" << std::endl;
                break;
            }
        }
        return  Status::OK;
    }

public:
    function<void(std::string)> addconnection;
};

template <typename TSERVICEIMPL>
class MasterRPCServer : public RpcServer<TSERVICEIMPL>
{
public:
    MasterRPCServer(std::string& addr, function<void(std::string)> addconn) :
            RpcServer<TSERVICEIMPL>(addr){
        RpcServer<TSERVICEIMPL>::mService.addconnection = addconn;
    };
};

struct ServerPara{
    std::string uri;
    function<void(std::string)> addconn;
};

template <class T>
void* RunServer(void* args)
{
    auto para = *((ServerPara*)args);

    MasterRPCServer<T> server(para.uri, para.addconn);
    server.Run();
};

int main() {
    std::string expName;
    double exp_min;
    double sync_min;
    printf("Please input Experience Name:\n");
    std::cin>>expName;
    printf("Please input Experience Time(/min):\n");
    scanf("%lf", &exp_min);
    printf("Please input Sync Time(/min):\n");
    scanf("%lf", &sync_min);
    time_t currentTime = time(0);
    char c_time[64];
    strftime(c_time, sizeof(c_time), "_%Y_%m_%d_%H_%M_%S", localtime(&currentTime));
    expName += c_time;
    pthread_mutex_t state_lock;

    pthread_mutex_init(&state_lock, NULL);
    //set master server uri
    char ip[30] = MASTER_IP;
    std::string master_server_uri(std::strcat(ip, ":50001"));

    //init rpc client with 25 threads (can handle 25 jobset, connection pair)
    volatile int numjobsets = 0;
    int maxNumClients = 25;

    RpcClient client;
    client.Run(maxNumClients);
    Second    client_to = 5;

    std::vector<std::shared_ptr<JobSet>> jobsets;
    //std::vector<std::shared_ptr<MyConnection<FzService, FzService::Stub>>> connections;
    std::unordered_map<string, std::shared_ptr<MyConnection<FzService, FzService::Stub>>> connections;


    jobsets.reserve(maxNumClients);
    //connections.reserve(maxNumClients);

    //create job state machine
    auto jms = std::make_shared<JobStateMachine>();

    auto add_connection = [&](std::string client_uri){

        //critical area

        pthread_mutex_lock(&state_lock);
        auto find = connections.find(client_uri);
        if(find == connections.end()){

            printf("registrating a new slave\n");

            auto jobset = std::make_shared<JobSet>(client_uri, (int) (exp_min * 60), (int) (sync_min * 60));
            auto num_sync = sync_min > 0 ? (int) (exp_min / sync_min) : 1;
            int jid = 0;
            int numofFuzzer = 2; /* num of fuzzer per container */
            std::string containerName = "fuzzer";
            std::string imageName = "172.18.194.116:5000/fztest/fuzzer";
            int index = numjobsets++;

            if (numjobsets > maxNumClients) {
                printf("num of clients exceeds the limit\n");
                return;
            }
            string myIp = jobset->client_uri;
            uint64_t ip_pos = myIp.find(":");
            myIp = myIp.substr(0, ip_pos);
            Replace_all(myIp, ".", "_");
            std::string localPath = "/home/td_dev/docker/fuzzer";
            std::string runCmd = "2&&" + containerName + " -v " + localPath +
                    ":/home/fuzzer/fuzzing/output " + imageName + " " +
                    myIp + " " + to_string(numofFuzzer);
            jobset->jobs.push_back(std::make_shared<Job>(jid++, jms, runCmd, jbt_docker_run));
            for (int j = 0; j < num_sync; j++) {
                jobset->jobs.push_back(
                        std::make_shared<Job>(jid++, jms, "7&&" + localPath +
                                "&&" + expName, jbt_sync_up));
                jobset->jobs.push_back(
                        std::make_shared<Job>(jid++, jms, "8&&" + localPath +
                                "&&" + expName, jbt_sync_down));
            }
            jobset->jobs.push_back(std::make_shared<Job>(jid, jms, "5&&" + containerName,
                                                         jbt_docker_stop));
            jobset->jobs.push_back(std::make_shared<Job>(jid++, jms, "9&&" + localPath + "&&" + expName,
                                                         jbt_sync_result));

            //jobsets[index] = jobset;
            jobsets.push_back(jobset);
            printf("jobset index is %d\n", index);

            auto conn = std::make_shared<MyConnection<FzService, FzService::Stub>>(
                    jobset->client_uri, &(client.Cq()), jobset);
            connections[jobset->client_uri] = conn;
            conn->last_heartbit_time = MicroSecondNow();
        }else{
            //todo : update heartbit..
            find->second->last_heartbit_time = MicroSecondNow();
            find->second->alive = true;
        }
        pthread_mutex_unlock(&state_lock);
        //end critical areq
    };

    //starting master server
    pthread_t master_server;
    //auto server = MasterRPCServer<MasterServiceImpl>(master_server_uri, add_connection);
    //RpcServer<MasterServiceImpl> server = RpcServer<MasterServiceImpl>(master_server_uri);
    auto para = ServerPara();
    para.addconn = add_connection;
    para.uri = master_server_uri;
    pthread_create(&master_server, NULL, RunServer<MasterServiceImpl>, (void*)&para);

    bool exp_run = true;

    while (exp_run){

        //input param
        //1 : sync
        //2 : docker run
        //3 : register(was docker exec)
        //4 : docker start
        //5 : docker stop
        //6 : docker remove
        //7 : sync_up
        //8 : sync_down
        //traverse the jobset and see what we should do

        pthread_mutex_lock(&state_lock);

        bool still_run = false;
        if(numjobsets > 0 ){
            for(int i = 0 ; i < numjobsets; i++){
                if(!jobsets[i]->isEnd()){

                    auto find = connections.find(jobsets[i]->client_uri);
                    if(find == connections.end()) {
                        jobsets[i]->end(false);
                        printf("could not find a connetion for job set %d, numjobsets %d\n", i, numjobsets);
                    }else if(find->second->alive){

                        if(MicroSecondNow() - find->second->last_heartbit_time < client_to*1000) {
                            still_run = true;
                            find->second->proceed();
                        }else{
                            //client times out..
                            printf("client %d times out\n", i);
                            find->second->alive = false;
                        }

                    }
                }
            }
        }else{
            still_run = true;
        }
        exp_run = still_run;
        pthread_mutex_unlock(&state_lock);

    }

    std::cout << "Press any key to see statistics." << std::endl;
    std::cin.get();

    client.Shutdown();

    for (auto it : jobsets) {
        it->stat();
    }

    pthread_mutex_destroy(&state_lock);
    return 0;
}



