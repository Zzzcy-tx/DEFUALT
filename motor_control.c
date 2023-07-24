/*
 * motor_control.c
 *
 *  Created on: 2023Äê7ÔÂ11ÈÕ
 *      Author: Unusualroutetaker
 */

#include <fd_demo.h>

void pid_init(void)
{
    pid_left.target_val = 0;
    pid_left.kp = 0.19;
    pid_left.ki = 0.16;
    pid_left.kd = 0.00;
    pid_left.err = 0;
    pid_left.err_last = 0;
    pid_left.err_last_last = 0;

    pid_right.target_val = 0;
    pid_right.kp = 0.19;
    pid_right.ki = 0.16;
    pid_right.kd = 0.00;
    pid_right.err = 0;
    pid_right.err_last = 0;
    pid_right.err_last_last = 0;
}

void PID_realize(int actual_val_left, int actual_val_right)
{
    if (pid_left.target_val < 0)
    {
        pid_left.err = -pid_left.target_val - actual_val_left;
    }
    if (pid_left.target_val >= 0)
    {
        pid_left.err = pid_left.target_val - actual_val_left;
    }
    pid_left.integral += pid_left.err;
    //    pid.output_val = pid.Kp * pid.err +
    //                     pid.Ki * pid.integral +
    //                     pid.Kd * (pid.err - pid.err_last);
    pid_left.output_val += pid_left.kp * (pid_left.err - pid_left.err_last) + pid_left.ki * pid_left.err +
                           pid_left.kd * (pid_left.err - 2 * pid_left.err_last + pid_left.err_last_last);
    pid_left.err_last_last = pid_left.err_last;
    pid_left.err_last = pid_left.err;

    if (pid_right.target_val < 0)
    {
        pid_right.err = -pid_right.target_val - actual_val_right;
    }
    if (pid_right.target_val >= 0)
    {
        pid_right.err = pid_right.target_val - actual_val_right;
    }
    pid_right.integral += pid_right.err;
    //    pid.output_val = pid.Kp * pid.err +
    //                     pid.Ki * pid.integral +
    //                     pid.Kd * (pid.err - pid.err_last);
    pid_right.output_val += pid_right.kp * (pid_right.err - pid_right.err_last) + pid_right.ki * pid_right.err +
                            pid_right.kd * (pid_right.err - 2 * pid_right.err_last + pid_right.err_last_last);
    pid_right.err_last_last = pid_right.err_last;
    pid_right.err_last = pid_right.err;

    //    pid_left.output_val=limit_int(pid_left.output_val,0,95);
    //    pid_right.output_val=limit_float(pid_right.output_val,0,95);
    //    pid_left.output_val=pid_left.output_val/100;
    //    pid_right.output_val=pid_right.output_val/100;
    if (pid_left.output_val >= 95)
    {
        pid_left.output_val = 95;
    }
    if (pid_left.output_val <= 0)
    {
        pid_left.output_val = 0;
    }

    if (pid_right.output_val >= 95)
    {
        pid_right.output_val = 95;
    }
    if (pid_right.output_val <= 0)
    {
        pid_right.output_val = 0;
    }
}

void pid_read(void)
{
    //    OLED_ShowString(10,0," Real  Err  Output",12);
    //    OLED_ShowString(2,1,"R",12);
    //    OLED_ShowString(2,2,"L",12);

    encoder_read();

    OLED_ShowNum(50, 2, abs_int(pid_left.err), 4, 12);
    OLED_ShowNum(80, 2, pid_left.output_val, 4, 12);

    OLED_ShowNum(50, 1, abs_int(pid_right.err), 4, 12);
    OLED_ShowNum(80, 1, pid_right.output_val, 4, 12);

    OLED_ShowNum(80, 3, pid_right.target_val, 4, 12);
    OLED_ShowNum(80, 4, pid_left.target_val, 4, 12);
}

void motor_realise(void)
{
    if (pid_right.target_val >= 0)
    {
        pwm_duty(12, pid_right.output_val);
        pwm_duty(13, 0);
    }
    if (pid_right.target_val < 0)
    {
        pwm_duty(12, 0);
        pwm_duty(13, pid_right.output_val);
    }

    if (pid_left.target_val >= 0)
    {
        pwm_duty(15, pid_left.output_val);
        pwm_duty(14, 0);
    }
    if (pid_left.target_val < 0)
    {
        pwm_duty(15, 0);
        pwm_duty(14, pid_left.output_val);
    }
}

void motor_speed_set(int left_speed_set, int right_speed_set)
{
    pid_left.target_val = left_speed_set;
    pid_right.target_val = right_speed_set;
}
