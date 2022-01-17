/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzc/SyncFile.h>
#include <fzc/util.h>

#ifndef ERRORMSG
#define ERRORMSG "ERROR"
#endif

using namespace std;
SyncFile::SyncFile(string addr, string userInfo, string localPath, string myName) :
        mFTPAddress(addr), mUser(userInfo), mLocalPath(localPath), mHostName(myName)
{
    //current serialze number of the upload file
    sync_id = 0;
}

SyncFile::~SyncFile()
{

}

bool SyncFile::Run(string& msg)
{
    if(Sync_up(msg))
    {
        Sync_down(msg);
        return true;
    }
    return false;
}

bool SyncFile::Sync_up(string& msg)
{
    //init curl
    curl_global_init(CURL_GLOBAL_ALL);

    //remove tmp files
    RunCMD("docker exec -t fuzzer find /tmp/ -name magick* -exec rm -r {} \\;");

    //tar file
    RunCMD("chmod -R 4777 " + mLocalPath + "/../");
    string command = "cd "+ mLocalPath + " && tar -czf " + mHostName + ".tgz " + mHostName +
            "_fuzzer*/[qf]* --exclude=" + mHostName + "_fuzzer*/queue/*sync* | echo $?";
    string ret = RunCMD(command.c_str());

    bool flag;
    int count = 0;
    //upload
    //Get file list
    string fileName;
    vector<string> fileList;
    CurlList list;
    fileName = list.Run(mFTPAddress, mUser);
    string newest = ERRORMSG;
    fileList =Split(fileName, "\n");
    newest = GetSpecialFileName(fileList, mHostName + "_seq_", true, count);
    //get current id and increase the id
    if(newest != ERRORMSG)
    {
        sync_id = stoi(newest.substr(mHostName.length() + 5,
                                     newest.length() - mHostName.length() - 9));
        sync_id++;
        while(count > 1)
        {
            string oldest = ERRORMSG;
            CurlDel curlDel;
            oldest = GetSpecialFileName(fileList, mHostName + "_seq_", false, count);
            curlDel.Run(mFTPAddress, oldest, mUser);
            vector<string>::iterator it;
            for (it = fileList.begin(); it != fileList.end();) {
                if (*it == oldest) {
                    it = fileList.erase(it);
                    break;
                } else ++it;
            }
        }
    }

    CurlUp curlUp;
    flag = curlUp.Run(mFTPAddress + mHostName + "_seq_" +  to_string(sync_id) + ".tgz",
                      mLocalPath + "/" + mHostName + ".tgz", 1, 3, mUser);
    curl_global_cleanup();
    return flag;
}

bool SyncFile::Sync_down(string &msg)
{
    //init curl
    curl_global_init(CURL_GLOBAL_ALL);
    //Get file list
    string fileName;
    vector<string> fileList;
    CurlList list;
    fileName = list.Run(mFTPAddress, mUser);
    fileList = Split(fileName, "\n");
    int count = 0;
    vector<string> hosts;
    for(string fname : fileList)
    {
        if(fname.find(mHostName) == string::npos)
        {
            uint64_t mPos = fname.find("_seq_");
            fname = fname.substr(0, mPos);
            if (hosts.size() > 0) {
                bool isRepeat = false;
                for (string str : hosts) {
                    if (str == fname) {
                        isRepeat = true;
                        break;
                    }
                }
                if (!isRepeat)
                    hosts.push_back(fname);
            }
            else hosts.push_back(fname);
        }
        else
            continue;
    }

    for(string host : hosts)
    {
        if(host == mHostName)
            continue;
        else
        {
            string newest = ERRORMSG;
            newest = GetSpecialFileName(fileList, host + "_seq_", true, count);
            if(newest != ERRORMSG)
            {
                CurlDown curlDown;
                RunCMD("chmod -R 4777 " + mLocalPath + "/../");
                curlDown.Run(mFTPAddress + newest,
                             mLocalPath + "/" + host + ".tgz", 1, 3, mUser);
                string command = "cd " + mLocalPath + " && tar -xzf " +
                          host.c_str() + ".tgz | echo $?";
                string ret = RunCMD(command.c_str());
                try {
                    RunCMD("rm " + mLocalPath + "/" + host + ".tgz");
                }
                catch(exception ex) {
                    std::cout<<ex.what()<<std::endl;
                }
                if(ret == "")
                    msg = "No such a local path: " + mLocalPath;
                else if (ret != "0\n")
                    msg = "can't unpack tgz file";
                cout<<msg<<endl;
            }
        }
    }
    curl_global_cleanup();
    return true;
}

bool SyncFile::Sync_res(string& msg)
{
    //init curl
    curl_global_init(CURL_GLOBAL_ALL);
    bool flag;
    string finalName = mHostName + "_final.tgz";
    RunCMD("chmod -R 4777 " + mLocalPath + "/../");
    string command = "cd "+ mLocalPath + " && tar -czf " + finalName + " " + mHostName + "_fuzzer*/ " + " | echo $?";
    string ret = RunCMD(command.c_str());
    CurlUp curlUp;
    flag = curlUp.Run(mFTPAddress + finalName, mLocalPath + "/" + finalName, 1, 3, mUser);
    //RunCMD("rm " + mLocalPath + "/" + finalName);
    curl_global_cleanup();
    return flag;
}