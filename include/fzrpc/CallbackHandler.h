/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_RPC_CALLBACKHANDLER_H
#define FZCLOUD_RPC_CALLBACKHANDLER_H

#include <iostream>
#include <memory>
#include <string>
#include <list>

#include <grpc++/grpc++.h>
#include <grpc/support/log.h>
#include <thread>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

class ClientCallMethod;

class CallbackHandler
{
    public:
        virtual void onMessage(ClientCallMethod* cm) = 0;
};


#endif //FZCLOUD_RPC_CALLBACKHANDLER_H
