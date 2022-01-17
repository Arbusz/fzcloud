/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_CURLLIST_H
#define FZCLOUD_CURLLIST_H

#include "CurlBaseOp.h"

class CurlList
{
public:
    CurlList();
    ~CurlList();
    std::string Run(std::string remoteAddr, std::string userinfo);
};

#endif //FZCLOUD_CURLLIST_H
