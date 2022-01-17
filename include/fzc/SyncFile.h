/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_SYNCFILE_H
#define FZCLOUD_SYNCFILE_H

#include <string>
#include <memory>
#include <vector>

#include <fzcurl/CurlDown.h>
#include <fzcurl/CurlUp.h>
#include <fzcurl/CurlList.h>
#include <fzcurl/CurlDel.h>

using namespace std;

class SyncFile
{
public:
    explicit SyncFile(string addr, string userInfo, string localPath, string myName);
    ~SyncFile();
    void SetConfig();
    bool Run(string& msg);
    bool Sync_up(string& msg);
    bool Sync_down(string& msg);
    bool Sync_res(string& msg);
private:
    int sync_id;                //current serialize number of upload
    string mFTPAddress;         //FTP server address
    string mUser;               //FTP server userinfo ((format as)username:password)
    string mLocalPath;          //fuzzer output local path
    string mHostName;           //local host name
};


#endif //FZCLOUD_SYNCFILE_H
