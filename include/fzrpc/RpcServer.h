/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_RPCSERVER_H
#define FZCLOUD_RPCSERVER_H

#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

template <typename TSERVICEIMPL>
class RpcServer
{
public:
    RpcServer(std::string& addr) : mAddress(addr){};
    ~RpcServer(){};
    bool Run()
    {
        ServerBuilder builder;
        builder.AddListeningPort(mAddress, grpc::InsecureServerCredentials());
        builder.RegisterService(&mService);
        std::unique_ptr<Server> server(builder.BuildAndStart());
        std::cout<< "Server Listening on : " << mAddress << std::endl;
        server->Wait();
    };
    std::string mAddress;
    TSERVICEIMPL mService;
};


#endif //FZCLOUD_RPCSERVER_H
