/*
 * encoder.h
 *
 *  Created on: 2022Äê7ÔÂ13ÈÕ
 *      Author: FeiDao
 */

#ifndef ENCODER_H_
#define ENCODER_H_
#include <fd_demo.h>

extern int speed_1;
extern int speed_2;
extern int encoder_count2;
extern int encoder_count1;

void encoder_init(void);
void encoder_read(void);


#endif /* ENCODER_H_ */
