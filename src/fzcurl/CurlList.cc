/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzcurl/CurlList.h>

CurlList::CurlList()
{

}

CurlList::~CurlList()
{

}

std::string CurlList::Run(std::string remoteAddr, std::string userinfo)
{
    CURL* mCurl;
    CURLcode code;
    FILE* mFile;
    char* mList;
    mFile = fopen("/tmp/ListFile", "wb+");
    std::string result = "";
    mCurl = curl_easy_init();
    if(mCurl)
    {
        curl_easy_setopt(mCurl, CURLOPT_URL, remoteAddr.c_str());
        curl_easy_setopt(mCurl, CURLOPT_USERPWD, userinfo.c_str());
        curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, CurlBaseOp::List);
        curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, mFile);
        curl_easy_setopt(mCurl, CURLOPT_DIRLISTONLY, 1);

        code = curl_easy_perform(mCurl);

        curl_easy_cleanup(mCurl);
    }
    if(mFile->_IO_read_base != nullptr)
    {
        mList = mFile->_IO_read_base;
        result = std::string(mList);
    }
    
    fclose(mFile);

    if(CURLE_OK != code) return "";
    return result;
}