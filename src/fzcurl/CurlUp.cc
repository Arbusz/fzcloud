/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzcurl/CurlUp.h>

CurlUp::CurlUp()
{

}

CurlUp::~CurlUp()
{
}

bool CurlUp::Run(std::string remoteAddr, std::string localAddr,
                 long timeout, long tries, std::string userinfo)
{
    CURL *curl;
    curl = curl_easy_init();
    FILE *file;
    long uploaded_len = 0;
    CURLcode code = CURLE_GOT_NOTHING;
    int c;
    file = fopen(localAddr.c_str(), "rb");
    if (file == NULL)
    {
        perror(NULL);
        return 0;
    }
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, remoteAddr.c_str());
    curl_easy_setopt(curl, CURLOPT_USERPWD, userinfo.c_str());
    if(timeout)
    {
        curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);
    }
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, CurlBaseOp::GetLength);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &uploaded_len);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlBaseOp::Discard);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, CurlBaseOp::Read);
    curl_easy_setopt(curl, CURLOPT_READDATA, file);
    //curl_easy_setopt(curl, CURLOPT_FTPPORT, "-");
    curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    
    for(c = 0; (code != CURLE_OK) && (c < tries); c++)
    {
        if(c)
        {
            curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
            curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
            code = curl_easy_perform(curl);
            if(code != CURLE_OK) continue;
            curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
            curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
            fseek(file, uploaded_len, SEEK_SET);
            curl_easy_setopt(curl, CURLOPT_APPEND, 1L);
        } 
        else
        {
            curl_easy_setopt(curl, CURLOPT_APPEND, 0L);
        }
        code = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    fclose(file);
    if(code == CURLE_OK) return 1;
    else 
    {
        std::cout<< curl_easy_strerror(code) << std::endl;
        return 0;
    }
                     
}

