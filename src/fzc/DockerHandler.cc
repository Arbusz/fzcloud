/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <iostream>
#include <fzc/DockerHandler.h>
#include <exception>

using namespace std;

DockerHandler::DockerHandler()
{

}

DockerHandler::~DockerHandler()
{

}

bool DockerHandler::ContainerRun(string params, string& msg)
{
    string command = "docker run --privileged --name " + params +" &";
    msg = system(command.c_str());
    return true;
}

bool DockerHandler::ContainerStart(string container_Name, string& msg)
{
    string command = "docker start " + container_Name;
    msg = RunCMD(command);
    if(msg.find(container_Name) != string::npos)
    {
        msg = container_Name;
        return true;
    }
    return false;
}

bool DockerHandler::ContainerStop(string container_Name, string& msg)
{
    string command = "docker stop " + container_Name;
    msg = RunCMD(command);
    if(msg.find(container_Name) != string::npos)
    {
        msg = msg.substr(0, msg.length() - 1);
        return true;
    }
    return false;
}

bool DockerHandler::ContainerRM(string container_Name, string &msg)
{
    string command = "docker rm " + container_Name;
    msg = RunCMD(command);
    if(msg.find(container_Name) != string::npos)
    {
        msg = msg.substr(0, msg.length() - 1);
        return true;
    }
    return false;
}

bool DockerHandler::ContainerExec(string container_Name, string cmd, string& msg)
{
    string baseCMD = "docker exec " + container_Name + " " + cmd;
    msg = RunCMD(baseCMD);
    cout<<msg;
    return true;
}