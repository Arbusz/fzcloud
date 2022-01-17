/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <fzc/util.h>
#include <regex.h>
#ifndef ERRORMSG
#define ERRORMSG "ERROR"
#endif

using namespace std;

vector<string> Split(string input, string pattern)
{
    //split a long string name @input to vector name by thr @pattern
    string::size_type pos;
    vector<string> result;
    int size = input.size();
    for(int i = 0; i < size; i++)
    {
        pos = input.find(pattern, i);
        if(pos < size)
        {
            string s = input.substr(i, pos-i);
            result.push_back(s);
            i = pos + pattern.size()-1;
        }
    }
    return result;
};

string RunCMD(string command)
{
    FILE *fp;
    char buffer[1024];
    command += " 2>&1";
    fp = popen(command.c_str(), "r");
    fread(buffer, 1, sizeof(buffer), fp);
    //string result(buffer);
    pclose(fp);
    return string(buffer);
};

string GetSpecialFileName(vector<string> files, string key, bool flag, int& count) {
    //format : ${hostname}_seq_${num}.tgz
    //flag = true     return the newest (return ERROR if no such a file )
    //flag = false    return the oldest (return ERROR if file less then 2)
    vector<string> ftpfile;
    count = 0;
    string final = key.substr(0, key.length() - 4) + "final";
    for (string str : files) {
        if ((str.find(key) != string::npos)&&(str.find(final) == string::npos)) {
            ftpfile.push_back(str);
            count++;
        }
    }

    if (count == 0)
        return ERRORMSG;

    if (count == 1) {
        if (flag)
            return ftpfile[0];
        return ERRORMSG;
    }

    vector<uint32_t> serialNum;
    uint64_t key_len = key.length();
    for (int i = 0; i < count; i++) {
        serialNum.push_back(ToNum<uint32_t>(ftpfile[i].substr(key_len, ftpfile[i].length() - key_len - 4)));
    }

    return ftpfile[GetMaxOrMinPos<uint32_t>(serialNum, flag)];
}


bool HasContainerId(string message, bool length, string& ret)
{
    int cflag = REG_EXTENDED;
    regex_t reg;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    char* pattern;
    if(length)
        pattern = strcpy(pattern, "[a-z0-9]{64}");
    else
        pattern = strcpy(pattern, "[a-z0-9]{12}");
    regcomp(&reg, pattern, cflag);
    int status = regexec(&reg, message.c_str(), nmatch, pmatch, 0);
    regfree(&reg);
    if(status == REG_NOMATCH)
        return false;
    else {
        ret = message.substr(pmatch->rm_so, pmatch->rm_eo);
        return true;
    }
}

vector<string> MapToList(unordered_map<string, string> map)
{
    vector<string> lists;
    for(unordered_map<string, string>::iterator it = map.begin() ;it!=map.end();it++)
    {
        lists.push_back(it->second);
    }
    return  lists;
}


string& Replace_all(string& str, const string& old_value, const string& new_value)
{
    while(true){
        string::size_type pos(0);
        if((pos=str.find(old_value))!=string::npos)
            str.replace(pos,old_value.length(),new_value);
        else
            break;
    }
    return str;
}