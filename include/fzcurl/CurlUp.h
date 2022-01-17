/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_CURLUP_H
#define FZCLOUD_CURLUP_H

#include "CurlBaseOp.h"

class CurlUp
{
public:
    CurlUp();
    ~CurlUp();
    bool Run(std::string remoteAddr, std::string localAddr,
             long timeout, long tries, std::string userinfo);
};

#endif //FZCLOUD_CURLUP_H
