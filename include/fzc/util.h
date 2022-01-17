/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_UTIL_H
#define FZCLOUD_UTIL_H

#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <sys/wait.h>
#include <errno.h>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <regex.h>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

vector<string> Split(string input, string pattern);

string RunCMD(string command);

//return oldest file name while flag = false
//return newsdt file name while flag = true  
string GetSpecialFileName(vector<string> files, string key, bool flag, int& count);

template <class T>
T ToNum(const string& str)
{
    istringstream iss(str);
    T num;
    iss >> num;
    return num;
}

template <class T>
int GetMaxOrMinPos(vector<T> list, bool flag)
{
    //flag = true  Max
    //flag = false Min
    int pos = 0;
    T temp = list[0];
    for(int i = 0 ; i < list.size(); i++)
    {
        if(!flag ^ (list[i] > temp))
        {
            pos = i;
            temp = list[i];
        }

    }
    return pos;
}

bool HasContainerId(string message, bool flag, string& ret);

vector<string> MapToList(unordered_map<string, string> map);

string& Replace_all(string& str, const string& old_value, const string& new_value);
#endif //FZCLOUD_UTIL_H
