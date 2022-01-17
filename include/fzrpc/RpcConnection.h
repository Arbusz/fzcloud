/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_RPCCONNECTION_H
#define FZCLOUD_RPCCONNECTION_H

#include "CallbackHandler.h"

template <typename TSERVICE, typename TSERVICESTUB>
class RpcConnection : public CallbackHandler
{
public:
    RpcConnection(const std::string& address, CompletionQueue* cq) : mCompletionQueue(cq)
    {
        mStub = TSERVICE::NewStub(grpc::CreateChannel(
                address, grpc::InsecureChannelCredentials()));
    };

protected:
    CompletionQueue* mCompletionQueue;
    std::unique_ptr<TSERVICESTUB> mStub;
};
#endif //FZCLOUD_RPCCONNECTION_H
