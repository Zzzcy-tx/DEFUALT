/*
 * keyboard.h
 *
 *  Created on: 2023Äê7ÔÂ8ÈÕ
 *      Author: Unusualroutetaker
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include <fd_demo.h>

void keyboard_init(void);
void keyboard_test(void);
extern int real_press_key;
extern int keyboard_press_flag;
extern int keyboard_scan;
extern int pressed_key[3];

#endif /* KEYBOARD_H_ */
