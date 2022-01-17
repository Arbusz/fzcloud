/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzrpc/RpcClient.h>

RpcClient::RpcClient()
{
    this->mShutdown = true;
}

RpcClient::~RpcClient()
{
    Shutdown();
    for(auto& it : mThreads)
    {
        it->join();
    }
}

void RpcClient::Shutdown()
{
    if(!mShutdown)
    {
        mCompletionQueue.Shutdown();
        mShutdown = true;
    }
}

bool RpcClient::Run(uint32_t threads)
{
    if(threads ==0)
    {
        return false;
    }
    mShutdown = false;
    for(int i =0; i < threads; ++i)
    {
        std::shared_ptr<std::thread> t = std::shared_ptr<std::thread>(
                new std::thread(&RpcClient::AsyncCompleteRpc, this));
        mThreads.push_back(t);
    }
    return true;
}

CompletionQueue& RpcClient::Cq()
{
    return mCompletionQueue;
}

void RpcClient::AsyncCompleteRpc()
{
    void* got_tag;
    bool ok = false;
    while (mCompletionQueue.Next(&got_tag, &ok))
    {
        if (!ok)
        {
            continue;
        }

        ClientCallMethod * cm = static_cast<ClientCallMethod*>(got_tag);
        process(cm);
    }
}