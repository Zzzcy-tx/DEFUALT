/*
 * main.c
 *
 *  Created on: 2022��7��12��
 *      Author: FeiDao
 */
#include <fd_demo.h>
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    set_clock();
    example();

}
