/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#include <memory>
#include <iostream>
#include <fzc/JobState.h>

using namespace std;

int main(){
    auto sm = std::make_shared<StateMachine64>();
    bool res;

    sm->get(0,1,&res);

    cout << "res is " << res << endl;

    sm->set(0,1, true);
    sm->get(0,1, &res);

    cout<<"res is " << res << endl;

    sm->set(0,1, false);
    sm->get(0,1, &res);

    cout<<"res is " << res << endl;


    auto jsm = std::make_shared<JobStateMachine>();

    auto js = std::make_shared<JobState>(jsm);

    cout<<"from received to launch " << js->move(js_launched) << endl;
    cout<<"current state is " << js->getState() << endl;

    cout<<"from launch to received " << js->move(js_received) << endl;
    cout<<"current state is " << js->getState() << endl;


    return 1;
}