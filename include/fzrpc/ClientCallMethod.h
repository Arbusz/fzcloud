/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_RPC_CLIENTCALLMETHOD_H
#define FZCLOUD_RPC_CLIENTCALLMETHOD_H

#include "CallbackHandler.h"

class ClientCallMethod
{
private:
    std::string mMethodName;
    CallbackHandler* mCallbackHandler;
public:
        ClientCallMethod(CallbackHandler* handler, const std::string& methodName)
                :mCallbackHandler(handler), mMethodName(methodName){}
        virtual ~ClientCallMethod(){}
        const std::string& CallMethodName();
        CallbackHandler* CbHandler();
};

#endif //FZCLOUD_RPC_CLIENTCALLMETHOD_H
