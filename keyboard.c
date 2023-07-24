/*
 * keyboard.c
 *
 *  Created on: 2023年7月8日
 *      Author: Unusualroutetaker
 */


/*
 * |返回|向上|    |增加|
 * |向左|选中|向右|减少|
 * |    |向下|    |    |
 * |    |    |确定|开始|
 */
#include <fd_demo.h>

int real_press_key;
int keyboard_press_flag;
int keyboard_scan;
int pressed_key[3];

void keyboard_init(void)
{
    P4DIR &= ~BIT3;
    P4REN |= BIT3;
    P4OUT &=~ BIT3;
    P4SEL &= ~BIT3;

    P4DIR &= ~BIT0;
    P4REN |= BIT0;
    P4OUT &=~ BIT0;
    P4SEL &= ~BIT0;

    P3DIR &= ~BIT7;
    P3REN |= BIT7;
    P3OUT &=~ BIT7;
    P3SEL &= ~BIT7;

    P8DIR &= ~BIT2;
    P8REN |= BIT2;
    P8OUT &=~ BIT2;
    P8SEL &= ~BIT2;

    P7DIR |= BIT4;
    P7OUT |= BIT4;

    P8DIR |= BIT1;
    P8OUT |= BIT1;

    P3DIR |= BIT5;
    P3OUT |= BIT5;

    P3DIR |= BIT6;
    P3OUT |= BIT6;
}


void keyboard_test(void)
{
    unsigned int keyboard_row;
    if(1)
    {
        keyboard_scan+=1;
        real_press_key=0;
        if(keyboard_scan>2)
        {
            keyboard_scan=0;
            pressed_key[0]=0;
            pressed_key[1]=0;
            pressed_key[2]=0;
        }
        for (keyboard_row=0;keyboard_row<=3;keyboard_row++)
        {
            P7OUT &= ~BIT4;
            P8OUT &= ~BIT1;
            P3OUT &= ~BIT5;
            P3OUT &= ~BIT6;

            if (keyboard_row==0)
            {P7OUT |= BIT4;}
            if (keyboard_row==1)
            {P8OUT |= BIT1;}
            if (keyboard_row==2)
            {P3OUT |= BIT5;}
            if (keyboard_row==3)
            {P3OUT |= BIT6;}


            if(P8IN&BIT2)
            {pressed_key[keyboard_scan]=4*keyboard_row+1;}
            if(P3IN&BIT7)
            {pressed_key[keyboard_scan]=4*keyboard_row+2;}
            if(P4IN&BIT0)
            {pressed_key[keyboard_scan]=4*keyboard_row+3;}
            if(P4IN&BIT3)
            {pressed_key[keyboard_scan]=4*keyboard_row+4;}
        }
        delay(10);
    }
    keyboard_press_flag=0;
    if ((pressed_key[0]==pressed_key[1]) && (pressed_key[1]==pressed_key[2]))
    {
        real_press_key = pressed_key[2];
        if(pressed_key[0]!=0)
        {
            keyboard_press_flag = 1;
            beeb_ring(8);
        }
    }
}
