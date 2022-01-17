/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_CURLDEL_H
#define FZCLOUD_CURLDEL_H

#include "CurlBaseOp.h"

class CurlDel
{
public:
    CurlDel();
    ~CurlDel();
    bool Run(std::string fileName, std::string remoteAddr, std::string userinfo);
};

#endif //FZCLOUD_CURLDEL_H
