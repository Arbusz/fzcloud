/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzrpc/ClientCallMethod.h>



const std::string& ClientCallMethod::CallMethodName()
{
    return this->mMethodName;
}

CallbackHandler* ClientCallMethod::CbHandler()
{
    return this->mCallbackHandler;
}


