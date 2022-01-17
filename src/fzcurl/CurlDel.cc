/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzcurl/CurlDel.h>
#include <string.h>
CurlDel::CurlDel()
{

}

CurlDel::~CurlDel()
{

}

bool CurlDel::Run(std::string remoteAddr, std::string fileName, std::string userinfo)
{
    CURL* mCurl;
    CURLcode code;
    std::string delCommand = "DELE " + fileName;
    mCurl = curl_easy_init();
    curl_slist* headerlist;
    if(mCurl)
    {
        curl_easy_setopt(mCurl, CURLOPT_URL, remoteAddr.c_str());
        curl_easy_setopt(mCurl, CURLOPT_USERPWD, userinfo.c_str());
        struct curl_slist *list = NULL;
        list = curl_slist_append(list, delCommand.c_str());
        curl_easy_setopt(mCurl, CURLOPT_POSTQUOTE, list);
        code = curl_easy_perform(mCurl);
        curl_easy_cleanup(mCurl);
    }
    if(CURLE_OK != code)
        return  false;
    return  true;
}