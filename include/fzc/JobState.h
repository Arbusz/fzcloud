/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_JOBSTATE_H
#define FZCLOUD_JOBSTATE_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include <fzc/time.h>
#include <chrono>
#include <ctime>

using namespace std;

typedef uint32_t jid_t;
/*
 * A simple state machine with max 64 states
 */
typedef uint32_t jid_t;
struct StateMachine64 {
    StateMachine64(int numofState = 10) {
        if(numofState > maxNumofState){
            printf("number of states set to %d , greater than %d\n", numofState, maxNumofState);
            //todo: throw some exceptions here ?
            exit(0);
        }
        for(int i = 0 ; i < 64; i++){
            states[i] = 0;
        }
    }

    inline bool set(uint8_t from, uint8_t to, bool val){
        if((from >> 6) || (to >> 6)){
            printf("state machine error setting\n");
            return false;
        } else{
            states[from] = (val ? states[from]| (0x00000001)<<to : states[from]&~((0x00000001)<<to));
            return true;
        }
    }

    inline bool get(uint8_t from, uint8_t to, bool* val){
        if((from >> 6) || (to >> 6)){
            printf("state machine error getting\n");
            return false;
        } else{
            //printf("from %d , to %d\n", from, to);
            *val = states[from] & (0x00000001)<<to ;
            return true;
        }
    }
    static int maxNumofState;
private:

    uint64_t states[64];
};

int StateMachine64::maxNumofState = 64;


/*
 * Job State Machine Definition
 */
enum job_state{
    js_received = 0
    , js_launched
    , js_running
    , js_success
    , js_failure
    , js_hanging
    , js_retry
    , js_delayed
};

struct JobStateMachine {
    JobStateMachine(): numofStates(6), sm64(6){
        sm64.set(js_received, js_launched, true);
        sm64.set(js_received, js_delayed, true);
        sm64.set(js_received, js_hanging, true);
        sm64.set(js_launched, js_hanging, true);
        sm64.set(js_launched, js_running, true);
        sm64.set(js_running, js_success, true);
        sm64.set(js_running, js_hanging, true);
        sm64.set(js_running, js_failure, true);
        sm64.set(js_hanging, js_failure, true);
        sm64.set(js_hanging, js_retry, true);
        sm64.set(js_retry,   js_launched, true);
        sm64.set(js_delayed, js_launched, true);
        sm64.set(js_delayed, js_hanging, true);

    }

    inline bool get(enum job_state from, enum job_state to, bool* val){
        return sm64.get(from, to, val);
    }

private:
    StateMachine64 sm64;
    int numofStates;
};

/*
 * Job state containing a JSM shared pointer
 */
struct JobState{
    JobState(std::shared_ptr<JobStateMachine> jsm, enum job_state js = js_received):jsm(jsm), state(js){ }

    inline const enum job_state getState() const { return state; }

    inline bool move(enum job_state to) {
        bool res = false;

        if(jsm->get(state, to, &res) && res){
            //printf("js move %d to %d succeed\n", state, to);
            state = to;
        }else{
            //printf("Error: js move %d to %d is illegal!!\n", state, to);
        }
        return res;
    }
private:
    std::shared_ptr<JobStateMachine> jsm;
    volatile enum job_state state;

};

enum job_type{
     jbt_sync_file = 1
    ,jbt_docker_run
    ,jbt_docker_exec
    ,jbt_docker_start
    ,jbt_docker_stop
    ,jbt_docker_remove
    ,jbt_sync_up
    ,jbt_sync_down
    ,jbt_sync_result
};
/*
 * Job context
 */
struct Job {
    Job(jid_t id, std::shared_ptr<JobStateMachine> jsm, string cmd, enum job_type jbt) :
    id(id), state(jsm), cmd(cmd), jbt(jbt), stt_ms(0), tries(0){ }


    inline bool moveState(enum job_state to) {
        stt_ms = MicroSecondNow();
        return state.move(to);
    }

    jid_t                   id;        //global job id
    JobState                state;     //state of the job
    string                  cmd;       //command name
    enum job_type           jbt;
    volatile MicroSecond    stt_ms;    //time at last state transition
    uint8_t                 tries;     //times the jobs will resend
};

struct JobSet{
    JobSet(string& curi, int duration = -1, int sync_time = -1):
            client_uri(curi),
            duration_sec(duration),
            syncIntvl_sec(sync_time),
            done(false),
            result(false),
            currentJobID(0){ }

    inline void start(){
        start_sec = SecondNow();
    }

    inline void end(bool res){
        result = res;
        done = true;
        end_sec = SecondNow();
    }

    inline void stat(){
        if(!done)
            return;

        cout << "__________JobSet Statistics________" << endl << endl;
        cout << "Num of Jobs : " << jobs.size() << endl;
        cout << "Runing Clinet : " << client_uri << endl;
        printf("Time Elapsed(sec) : %lu\n", (end_sec - start_sec));
        if(result){
            cout << "Running Result: Success" << endl << endl;
        }else{
            cout << "Running Result: Failure" << endl << endl;
        }
    }

    inline const bool isEnd() const { return done; }

    volatile jid_t               currentJobID;
    string                       client_uri;
    std::vector<shared_ptr<Job>> jobs;
    MicroSecond                  curJobtime_ms;
    int                          duration_sec;
    int                          syncIntvl_sec;
    Second                       start_sec;
    Second                       end_sec;
private:
    bool                         done;
    bool                         result;
};


#endif //FZCLOUD_JOBSTATE_H
