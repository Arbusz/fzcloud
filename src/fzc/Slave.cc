/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzrpc/RpcLib.h>
#include <protos/fzrpc.grpc.pb.h>
#include <fzc/DockerHandler.h>
#include <fzc/SyncFile.h>
#include <fzc/conf.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define MASTER_IP "172.18.194.116"

//get local uri
void getLocalURI(std::string &ip){

    const char* server_ip = MASTER_IP;
    int         server_port = 50001;

    //ip.resize(100);
    char buffer[100];
    bzero(buffer, 100);

    struct sockaddr_in serv;

    int sock = socket ( AF_INET, SOCK_DGRAM, 0);

    //Socket could not be created
    if(sock < 0)
    {
        perror("Socket error");
    }

    memset( &serv, 0, sizeof(serv) );
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(server_ip);
    serv.sin_port = htons(server_port);

    int err = connect( sock , (const struct sockaddr*) &serv , sizeof(serv) );

    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    err = getsockname(sock, (struct sockaddr*) &name, &namelen);

    const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, 100);

    std::string local_ip(buffer);
    ip = local_ip;

    if(p != NULL)
    {
        printf("Local ip is : %s \n" , ip.c_str());
    }
    else
    {
        //Some error
        printf ("Error number : %d . Error message : %s \n" , errno , strerror(errno));
    }
    close(sock);
};

class ServiceImpl final : public FzService::Service
{
    Status RemoteCall(ServerContext *context, const FzRequest *request,
                      FzResponse *response) override
    {
        std::string mCommand = request->cmd();
        response->set_jobid(request->jobid());
        response->set_cmd(mCommand);

        mCommand += "&&";
        switch (mCommand[0])
        {
            case '1':
            {
                //std::vector<std::string> paramLists = Split(mCommand, "&&");
                //std::string ret;
                //DockerHandler::ContainerExec(paramLists[1], "uname -n" ,ret);
                //SyncFile sync = SyncFile("ftp://172.18.194.116", "ftp:ftp",
                //                         ret, hosts);
                //response->set_flag(true);
                //sync.Run(ret);
                break;
            }
            case '2':
            {
                std::vector<std::string> paramLists = Split(mCommand, "&&");
                std::string ret;
                DockerHandler::ContainerRun(paramLists[1], ret);
                response->set_flag(true);
                response->set_ret("success");
                break;
            }
//            case '3':
//            {
//                std::vector<std::string> paramLists = Split(mCommand, "&&");
//                std::string ret;
//                DockerHandler::ContainerExec(paramLists[1], paramLists[2], ret);
//                response->set_flag(true);
//                response->set_ret(ret);
//                break;
//            }
            case '4':
            {
                std::vector<std::string> paramLists = Split(mCommand, "&&");
                std::string ret;
                DockerHandler::ContainerStart(paramLists[1], ret);
                response->set_flag(true);
                response->set_ret(ret);
                break;
            }
            case '5':
            {
                std::vector<std::string> paramLists = Split(mCommand, "&&");
                std::string ret;
                DockerHandler::ContainerStop(paramLists[1], ret);
                response->set_flag(true);
                response->set_ret("success");
                break;
            }
            case '6':
            {
                std::vector<std::string> paramLists = Split(mCommand, "&&");
                std::string ret;
                DockerHandler::ContainerRM(paramLists[1], ret);
                response->set_flag(true);
                response->set_ret("success");
                break;
            }
            case '7':
            {
                //param 1: local path
                //param 2: experience name
                std::vector<std::string> paramLists = Split(mCommand, "&&");
                std::string ret;
                char ftp[100] = "ftp://";
                paramLists[2] = "/" + paramLists[2] + "/sync/";
                SyncFile sync = SyncFile(std::strcat(ftp, MASTER_IP) + paramLists[2],
                                         "ftp:ftp", paramLists[1], myIP);
                sync.Sync_up(ret);
                response->set_flag(true);
                response->set_ret("success");
                break;
            }
            case '8':
            {
                //param 1: local path
                //param 2: experience name
                std::vector<std::string> paramLists = Split(mCommand, "&&");
                std::string ret;
                char ftp[100] = "ftp://";
                paramLists[2] = "/" + paramLists[2] + "/sync/";
                SyncFile sync = SyncFile(std::strcat(ftp, MASTER_IP) + paramLists[2],
                                         "ftp:ftp", paramLists[1], myIP);
                sync.Sync_down(ret);
                response->set_flag(true);
                response->set_ret("success");
                break;

            }
            case '9':
            {
                //param 1: local path
                //param 2: experience name
                std::vector<std::string> paramLists = Split(mCommand, "&&");
                std::string ret;
                char ftp[100] = "ftp://";
                paramLists[2] = "/" + paramLists[2] + "/result/";
                SyncFile sync = SyncFile(std::strcat(ftp, MASTER_IP) + paramLists[2],
                                         "ftp:ftp", paramLists[1], myIP);
                sync.Sync_res(ret);
                response->set_flag(true);
                response->set_ret("success");
                break;

            }
            default:
            {
                std::cout << "Not a valid command" << std::endl;
                break;
            }
        }
        return Status::OK;
    }

};

class MockServiceImpl final : public FzService::Service
{
    Status RemoteCall(ServerContext* context, const FzRequest* request,
                  FzResponse* response) override
    {
        response->set_jobid(request->jobid());
        response->set_cmd(request->cmd());
        switch (response->cmd()[0])
        {
            case '1':
            {
                response->set_flag(true);
                response->set_ret("success1");
                break;
            }
            case '2':
            {
                response->set_flag(true);
                response->set_ret("success2");
                break;
            }
//            case '3':
//            {
//                response->set_flag(true);
//                response->set_ret("success3");
//                break;
//            }
            case '4':
            {
                response->set_flag(true);
                response->set_ret("success4");
                break;
            }
            case '5':
            {

                srand((uint32_t)time(0));
                int random = rand() % 3;
                if(random == 0)
                {
                    response->set_flag(true);
                    response->set_ret("success5");
                }
                else
                {
                    response->set_flag(false);
                    response->set_ret("failed");
                }
                break;
            }
            case '6':
            {
                response->set_flag(true);
                response->set_ret("success6");
                break;
            }
            case '7':
            {
                response->set_flag(true);
                response->set_ret("success7");
                break;
            }
            case '8':
            {
                response->set_flag(true);
                response->set_ret("success8");
                break;
            }
            case '9':
            {
                response->set_flag(true);
                response->set_ret("success9");
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
};

template <class T>
void* RunServer(void* args)
{
    std::string url = *((std::string*)args);
    std::string address = url;
    RpcServer<T> server(address);
    server.Run();
};


template<typename TSERVICE, typename TSERVICESUB>
class RegConnection : public RpcConnection<TSERVICE, TSERVICESUB>
{
public:

    RegConnection(const std::string& address, CompletionQueue* cq) :
            RpcConnection<TSERVICE, TSERVICESUB>(address, cq){}

    void sayHello(std::string &uri)
    {

        FzRequest request;

        request.set_jobid(0);

        request.set_cmd("3&&"+ uri);

        AsyncClientCall <FzRequest, FzResponse> *call =
                new AsyncClientCall<FzRequest, FzResponse>(this, 0 + "_Request");
        call->ResponderReader() = this->mStub->AsyncRemoteCall(&call->Context(), request, this->mCompletionQueue);
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
                //std::cout << "client registration succeeed " << std::endl;

            }
            else {
                //std::cout << "register failed" << std::endl;
            }
            delete helloCd;
            return;
        }else{

        }
    }
};

int main()
{
    int serverNum = 1;
    std::vector<std::string> urls;
    //std::string master_uri = "172.17.0.3:50001";
    char remoteIp[30] = MASTER_IP;
    std::string master_uri = std::strcat(remoteIp, ":50001");
    int local_port = 40000;

    //get local IP address, port is default
    getLocalURI(myIP);
    for(int i = 0; i < serverNum; i++)
    {
        //printf("local ip %s , size %d\n", local_ip.c_str(), local_ip.length());
        urls.push_back(myIP + ":" + to_string(local_port+i));
    }
    Replace_all(myIP, ".", "_");
    //starting local slave server
    pthread_t id[serverNum];
    for(int i = 0; i < serverNum; i++)
    {
        pthread_create(&id[i], NULL, RunServer<ServiceImpl>, (void*)&urls[i]);
        //pthread_create(&id[i], NULL, RunServer<MockServiceImpl>, (void*)&urls[i]);
        sleep(1);
    }

    //start client
    RpcClient client;
    client.Run(1);
    auto regconn = std::make_shared<RegConnection<FzService, FzService::Stub>>(master_uri, &(client.Cq()));

    //main loop doing heartbit
    while(1){

        //sending reg message periodically..
        for(int i = 0; i < serverNum; i++)
        {
            regconn->sayHello(urls[i]);
        }
        sleep(1);
    };
    //pthread_exit(NULL);
}
