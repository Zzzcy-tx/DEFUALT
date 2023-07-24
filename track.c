/*
 * track.c
 *
 *  Created on: 2023Äê7ÔÂ23ÈÕ
 *      Author: Unusualroutetaker
 */


#include <fd_demo.h>
signed int wheel_error=0;
int sensor_error_list[7]={9,5,4,0,4,5,9};   
int sensor_error_sign[7]={1,1,1,0,-1,-1,-1};
signed int real_set_left=0;
signed int real_set_right=0;
int ground_sensor_count_num=0;
int last_sensor=3;
int this_sensor=3;
int average_speed;
int diff_speed=0;

void track_line(void)
{
    for(ground_sensor_count_num=0;ground_sensor_count_num<=6;ground_sensor_count_num++)
    {
        if(ground_sensor_list[ground_sensor_count_num]==1)
        {
            wheel_error = sensor_error_sign[ground_sensor_count_num]*sensor_error_list[ground_sensor_count_num];
        }
    }

//        average_speed=(real_set_left+real_set_right)/2;
//        motor_speed_set(average_speed,average_speed);

        diff_speed = limit_int(wheel_error, -init_speed*0.3, init_speed*0.3);

        // real_set_left=limit_int(init_speed+wheel_error,init_speed*0.3,init_speed*1.7);
        // real_set_right=limit_int(init_speed-wheel_error,init_speed*0.3,init_speed*1.7);

        motor_speed_set(pid_left.target_val -diff_speed,pid_right.target_val + diff_speed);
}
