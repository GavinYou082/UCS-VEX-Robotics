#pragma once
#include "api.h"
#include "robot.hpp"

#if 0
class auto_move {
    public:
        int32_t time;
        int state;
        double target_l;
        double target_r;
        float Kp = 0.5, Ki = 0, Kd = 0;
        void run();
        void reset();
        bool firstrun = true;
    private:
        uint32_t start_time;
};

enum state {
    MOV_FIRST_RUN,
    MOV_RUNNING,
    MOV_ALREADY_DONE
};
#endif

uint16_t movecnt = 0;
uint8_t move_state[64]  = {};
uint32_t move_start_time[64] = {};

#define MOV_FIRST_RUN 0
#define MOV_RUNNING 1
#define MOV_ALREADY_DONE 0

#define _set_movement(MOV_VELOCITY, MOV_LEFT, MOV_RIGHT, MOV_TIME)      \
    do {    \
    movecnt++;   \
    if(move_state[movecnt] == MOV_RUNNING)  \
    {  \
        if(move_start_time[movecnt] - millis() >= MOV_TIME)  \
            move_state[movecnt] = MOV_ALREADY_DONE; \
        goto __end; \
        }   \
    if(move_state[movecnt] == MOV_ALREADY_DONE) \
        goto __next;    \
    if(move_state[movecnt] == MOV_FIRST_RUN)\
    {   \
        move_state[movecnt] = MOV_RUNNING;  \
        move_start_time[movecnt] = millis();    \
        chassis.ClearEncoderL();    \
        chassis.ClearEncoderR();    \
        chassis.SetMotorsRelativeL(MOV_LEFT, MOV_VELOCITY); \
        chassis.SetMotorsRelativeR(MOV_LEFT, MOV_VELOCITY); \
    }   \
__next: \
    } while(0)
