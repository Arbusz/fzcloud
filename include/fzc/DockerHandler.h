/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_DOCKERHANDLER_H
#define FZCLOUD_DOCKERHANDLER_H

#include <string>
#include <memory>
#include <vector>
#include "util.h"

using namespace std;

class DockerHandler
{
public:
    DockerHandler();
    ~DockerHandler();
    static bool ContainerStart(string container_Name, string& msg);
    static bool ContainerStop(string container_Name, string& msg);
    static bool ContainerRM(string container_Name, string& msg);
    static bool ContainerExec(string container_Name, string cmd, string& msg);
    static bool ContainerRun(string params, string& msg);
};

#endif //FZCLOUD_DOCKERHANDLER_H
