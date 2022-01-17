/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzcurl/CurlDown.h>

CurlDown::CurlDown()
{

}

CurlDown::~CurlDown()
{
    
}

bool CurlDown::Run(std::string remoteAddr, std::string localAddr,
                 long timeout, long tries, std::string userinfo)
{
    CURL* curl;
    curl = curl_easy_init();
    FILE *mFile;
    curl_off_t mLocalLen = -1;   //local file length
    long filesize = 0;           // target file length
    CURLcode code = CURLE_GOT_NOTHING;
    struct stat file_info;
    int use_resume = 0;          //resume mark
    //Get local file info
    if(stat(localAddr.c_str(), &file_info) == 0)
    {
        mLocalLen = file_info.st_size;
        use_resume = 1;
    }
    //Append mode
    mFile = fopen(localAddr.c_str(), "ab+");
    if(mFile == NULL)
    {
        perror(NULL);
        return 0;
    }
    curl_easy_setopt(curl, CURLOPT_URL, remoteAddr.c_str());
    curl_easy_setopt(curl, CURLOPT_USERPWD, userinfo.c_str());
    curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, CurlBaseOp::GetLength);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &filesize);
    curl_easy_setopt(curl, CURLOPT_RESUME_FROM_LARGE, use_resume?mLocalLen:0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlBaseOp::Write);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, mFile);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    code = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(mFile);

    if(code == CURLE_OK) return 1;
    else 
    {
        std::cout<<curl_easy_strerror(code)<<std::endl;
        return 0;
    }
}