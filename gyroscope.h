/*
 * Gyroscope.h
 *
 *  Created on: 2021��10��8��
 *      Author: FeiDao
 */

#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_
#include <fd_demo.h>

extern int angle_Gyroscope_value[4];

extern void gyroscope_init(void);
extern void gyroscope_read(void);

#endif /* GYROSCOPE_H_ */
