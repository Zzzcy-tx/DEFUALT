/*
 * ground_sensor.h
 *
 *  Created on: 2023Äê7ÔÂ23ÈÕ
 *      Author: Unusualroutetaker
 */

#ifndef GROUND_SENSOR_H_
#define GROUND_SENSOR_H_

#include <fd_demo.h>

#define Port0   (P2IN&BIT3)
#define Port1   (P2IN&BIT6)
#define Port2   (P4IN&BIT1)
#define Port3   (P4IN&BIT2)
#define Port4   (P6IN&BIT1)
#define Port5   (P6IN&BIT0)
#define Port6   (P6IN&BIT2)


void ground_sensor_init(void);
void ground_sensor_get(void);

extern int ground_sensor_list[7];


#endif /* GROUND_SENSOR_H_ */
