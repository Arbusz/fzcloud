/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_RPCCLIENT_H
#define FZCLOUD_RPCCLIENT_H

#include "ClientCallMethod.h"

class RpcClient
{
public:
    RpcClient();
    ~RpcClient();
    void Shutdown();
    bool Run(uint32_t threads);
    CompletionQueue& Cq();
    void AsyncCompleteRpc();
    virtual void process(ClientCallMethod* cm)
    {
        CallbackHandler* cb = cm->CbHandler();
        cb->onMessage(cm);
    }
protected:
    CompletionQueue mCompletionQueue;

private:
    bool mShutdown;
    std::list<std::shared_ptr<std::thread>> mThreads;
};


#endif //FZCLOUD_RPCCLIENT_H
