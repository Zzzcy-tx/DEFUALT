/*
 * main.c
 *
 *  Created on: 2022Äê7ÔÂ12ÈÕ
 *      Author: FeiDao
 */
#include <fd_demo.h>
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    set_clock();
    example();

}
