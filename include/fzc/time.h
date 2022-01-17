/*
 * Copyright © 2018-2021 unifinicon LLC. All Rights Reserved
 * Licensed under the Academic Free License version 3.0
 * See the file "LICENSE" for more information
 */

#ifndef FZCLOUD_TIME_H
#define FZCLOUD_TIME_H

#include <time.h>

typedef unsigned long Second;

typedef unsigned long MicroSecond;

inline Second SecondNow(){
    timespec time;
    int res = clock_gettime(CLOCK_REALTIME, &time);
    if (res == -1)
        return 0;
    return time.tv_sec + time.tv_nsec * 0.000000001;
}

inline MicroSecond MicroSecondNow(){
    timespec time;
    int res = clock_gettime(CLOCK_REALTIME, &time);
    if (res == -1)
        return 0;
    return time.tv_sec * 1000 + time.tv_nsec * 0.000001;
}

inline double SecondNowD(){
    timespec time;
    int res = clock_gettime(CLOCK_REALTIME, &time);
    if (res == -1)
        return 0;
    return time.tv_sec + time.tv_nsec * 0.000000001;
}


#endif //FZCLOUD_TIME_H
