/*
 * pwm.h
 *
 *  Created on: 2022Äê7ÔÂ13ÈÕ
 *      Author: FeiDao
 */

#ifndef PWM_H_
#define PWM_H_

#include <fd_demo.h>

void pwm_init(unsigned int pin, unsigned int freq, unsigned int duty);
void pwm_duty(unsigned int pin, unsigned int duty);

#endif /* PWM_H_ */
