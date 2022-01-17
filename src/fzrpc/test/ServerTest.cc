/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzrpc/RpcLib.h>
#include <protos/fzrpc.grpc.pb.h>
#include <stdlib.h>

class ServiceImpl final : public FzService::Service
{
    Status RemoteCall(ServerContext* context, const FzRequest* request,
                  FzResponse* response) override
    {
        const char* mCommand = request->cmd().c_str();

        system(mCommand);
        response->set_ret("");
        return  Status::OK;
    }
};


int main()
{
    std::string address = "0.0.0.0:50051";
    RpcServer<ServiceImpl> server(address);
    server.Run();
}