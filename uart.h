/*
 * uart.h
 *
 *  Created on: 2022Äê7ÔÂ13ÈÕ
 *      Author: FeiDao
 */

#ifndef UART_H_
#define UART_H_

#include <fd_demo.h>

extern int Data_USCI_A0;
extern int Data_USCI_A1;
extern int Data_USCI_A0_int;
extern int Data_USCI_A1_int;
extern char Data_USCI_A0_char;
extern char Data_USCI_A1_char;

void uart_init(unsigned int uart_pin);
void uart_sent(unsigned int uart_pin, unsigned char text);
void uart_read(unsigned int uart_pin);



#endif /* UART_H_ */
