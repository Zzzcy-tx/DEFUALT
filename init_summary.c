/*
 * init_summary.c
 *
 *  Created on: 2023Äê7ÔÂ9ÈÕ
 *      Author: Unusualroutetaker
 */

#include <fd_demo.h>

void init_all(void)
{
    OLED_Init();// OLED init
    delay(50);
    OLED_Init();
    OLED_Clear();

    P1DIR |= BIT0;// Set P1.0 Output init
    P1OUT &= ~BIT0;

    P6DIR |= BIT5;// Set P6.5 Output init
    P6OUT &= ~BIT5;




    P1DIR |= BIT6;// Set P1.6 Output init
    P1OUT &= ~BIT6;
    P6DIR |= BIT6;// Set P6.6 Output init
    P6OUT &= ~BIT6;
    P3DIR |= BIT2;// Set P3.2 Output init
    P3OUT &= ~BIT2;
    P2DIR |= BIT7;// Set P2.7 Output init
    P2OUT &= ~BIT7;


    ground_sensor_init();// ground sensor init
    content_init();// content init
    keyboard_init();// keyboard pins init
    timer_init(20,20); // the timer A2, scan keyboard

    __bis_SR_register(GIE); // Enter LPM0, interrupts enabled
    _EINT();


}
