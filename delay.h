/*
 * delay.h
 *
 *  Created on: 2022Äê7ÔÂ12ÈÕ
 *      Author: FeiDao
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <fd_demo.h>

extern void delay(unsigned int ms);
float abs_float(float input_val);
int abs_int(int input_val);
float limit_float(float input_val,float low,float high);
int limit_int(int input_val,int low,int high);
void beeb_ring(int ring_time);

#endif /* DELAY_H_ */
