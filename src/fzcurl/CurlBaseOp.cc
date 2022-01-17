/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzcurl/CurlBaseOp.h>

//parse headers for Content-Length
size_t CurlBaseOp::GetLength(void* ptr, size_t size, size_t nmemb, void* stream)
{
    int result_len;
    long len = 0;
    result_len = sscanf((const char*)ptr, "Content-Length: %ld\n", &len);
    if(result_len)
    {
        *((long*) stream) = len;
    }
    return size * nmemb;
}

//Discard download data
size_t CurlBaseOp::Discard(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    return size * nmemb;
}

//Write data
size_t CurlBaseOp::Write(void *ptr, size_t size, size_t nmemb, void *stream)
{
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

//Read data
size_t CurlBaseOp::Read(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    FILE *f = (FILE*)stream;
    size_t result;
    if(ferror(f)) return CURL_READFUNC_ABORT;
    result = fread(ptr, size, nmemb, f) * size;
    return result;
}
size_t  CurlBaseOp::List(void *ptr, size_t size, size_t nmemb, void *stream)
{
    FILE *f = (FILE *)stream;
    return fwrite(ptr, size, nmemb, f);
}