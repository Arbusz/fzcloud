/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_RPC_ASYNCCLIENTCALL_H
#define FZCLOUD_RPC_ASYNCCLIENTCALL_H

#include "ClientCallMethod.h"

template <typename TREQUEST, typename TREPLY>
class AsyncClientCall : public ClientCallMethod
{
private:
    TREPLY mReply;
    ClientContext mContext;
    Status mRpcStatus;
    std::unique_ptr<ClientAsyncResponseReader<TREPLY>> mResponseReader;
public:
    AsyncClientCall(CallbackHandler* handler, const std::string& methodName)
            : ClientCallMethod(handler, methodName){}
    Status& RpcStatus() { return this->mRpcStatus; }
    TREPLY& Reply() { return this->mReply; }
    ClientContext& Context() { return this->mContext; }
    std::unique_ptr<ClientAsyncResponseReader<TREPLY>>& ResponderReader()
    {
        return this->mResponseReader;
    }
};
#endif //FZCLOUD_RPC_ASYNCCLIENTCALL_H