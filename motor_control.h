/*
 * motor_control.h
 *
 *  Created on: 2023Äê7ÔÂ11ÈÕ
 *      Author: Unusualroutetaker
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <fd_demo.h>

struct PID_para_left
{
    int target_val;
    int err;
    int err_last;
    int err_last_last;
    float kp,ki,kd;
    int integral;
    int output_val;
}pid_left;


struct PID_para_right
{
    int target_val;
    int err;
    int err_last;
    int err_last_last;
    float kp,ki,kd;
    int integral;
    int output_val;
}pid_right;


void pid_init(void);
void PID_realize(int actual_val_left, int actual_val_right);
void motor_realise(void);
void motor_speed_set(int left_speed_set,int right_speed_set);
void pid_read(void);


#endif /* MOTOR_CONTROL_H_ */
