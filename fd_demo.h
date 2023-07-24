/*
 * fd_demo.h
 *
 *  Created on: 2022Äê7ÔÂ12ÈÕ
 *      Author: FeiDao
 */

#ifndef FD_DEMO_H_
#define FD_DEMO_H_
#include <msp430f5529.h>

#include <Oled.h>
#include <delay.h>
#include <pwm.h>
#include <uart.h>
#include <timer.h>
#include <encoder.h>
#include <gyroscope.h>
#include <flash.h>
#include <keyboard.h>
#include <content.h>
#include <init_summary.h>
#include <motor_control.h>
#include <ground_sensor.h>
#include <track.h>

void example(void);
void set_clock(void);

extern int init_speed;


#endif /* FD_DEMO_H_ */
