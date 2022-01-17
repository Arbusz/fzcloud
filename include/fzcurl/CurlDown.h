/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_CURLDOWN_H
#define FZCLOUD_CURLDOWN_H

#include "CurlBaseOp.h"

class CurlDown
{
public:
    CurlDown();
    ~CurlDown();
    bool Run(std::string remoteAddr, std::string localAddr,
             long timeout, long tries, std::string userinfo);
};

#endif //FZCLOUD_CURLDOWN_H
