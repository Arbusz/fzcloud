/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <protos/fzrpc.grpc.pb.h>
#include <fzrpc/RpcLib.h>

template<typename TSERVICE, typename TSERVICESUB>
class MyConnection : public RpcConnection<TSERVICE, TSERVICESUB>
{
public:

    MyConnection(const std::string& address, CompletionQueue* cq) :
            RpcConnection<TSERVICE, TSERVICESUB>(address, cq) {}

    void sayHello(const std::string& command)
    {
        FzRequest request;
        request.set_cmd(command);
        AsyncClientCall <FzRequest, FzResponse> *call =
                new AsyncClientCall<FzRequest, FzResponse>(this,"HelloRequest");
        call->ResponderReader() = this->mStub->AsyncRemoteCall(&call->Context(), request, this->mCompletionQueue);
        call->ResponderReader()->Finish(&call->Reply(), &call->RpcStatus(), (void *) call);
    }

public:

    virtual void onMessage(ClientCallMethod *cm)
    {
        AsyncClientCall <FzRequest, FzResponse> *helloCd =
                dynamic_cast<AsyncClientCall <FzRequest, FzResponse> *>(cm);
        if (helloCd) {
            if (helloCd->RpcStatus().ok())
                std::cout << "Greeter received: " << helloCd->Reply().ret() << std::endl;
            else
                std::cout << "RPC failed" << std::endl;
            delete helloCd;
            return;
        }
    }
};

int main()
{
    RpcClient client;
    client.Run(5);
    MyConnection<FzService, FzService::Stub> conn1("0.0.0.0:50051", &(client.Cq()));
    conn1.sayHello("touch ~/Desktop/test1.txt");
    MyConnection<FzService, FzService::Stub> conn2("0.0.0.0:50051", &(client.Cq()));
    conn2.sayHello("touch ~/Desktop/test2.txt");

    std::cout << "Press any key to quit." << std::endl;
    std::cin.get();

    client.Shutdown();

    return 0;
}



