/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzcurl/CurlDown.h>
#include <fzcurl/CurlUp.h>
#include <fzcurl/CurlList.h>
#include <fzcurl/CurlDel.h>
using namespace std;
int main()
{
    curl_global_init(CURL_GLOBAL_ALL);
    CurlDown curlDown;
    CurlUp curlUp;
    CurlDel curlDel;
    CurlList curlList;
    curlUp.Run("ftp://localhost/ubuntu9.tgz", "~/Desktop/download.txt", 1, 3, "ftp:ftp");
    curlUp.Run("ftp://localhost/ubuntu10.tgz", "~/Desktop/download.txt", 1, 3, "ftp:ftp");
    curlUp.Run("ftp://localhost/vsftpd.conf", "~/Desktop/download.txt", 1, 3, "ftp:ftp");
    curlDown.Run("ftp://localhost/vsftpd.conf", "~/Desktop/a1.txt", 1, 3, "ftp:ftp");
    curlDown.Run("ftp://localhost/vsftpd.conf", "~/Desktop/a2.txt", 1, 3, "ftp:ftp");
    curlDown.Run("ftp://localhost/vsftpd.conf", "~/Desktop/a3.txt", 1, 3, "ftp:ftp");
    string result = curlList.Run("ftp://localhost", "ftp:ftp");
    curlDel.Run("ftp://localhost/", "vsftpd.conf", "ftp:ftp");
    curl_global_cleanup();
}
