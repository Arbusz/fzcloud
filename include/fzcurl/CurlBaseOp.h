/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_CURLBASEOP_H
#define FZCLOUD_CURLBASEOP_H

#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

class CurlBaseOp
{
public:
    static size_t GetLength(void* ptr, size_t size, size_t nmemb, void* stream);
    static size_t Discard(void* ptr, size_t size, size_t nmemb, void* stream);
    static size_t Write(void* ptr, size_t size, size_t nmemb, void* stream);
    static size_t Read(void* ptr, size_t size, size_t nmemb, void* stream);
    static size_t List(void *ptr, size_t size, size_t nmemb, void *stream);
};



#endif //FZCLOUD_CURLBASEOP_H
