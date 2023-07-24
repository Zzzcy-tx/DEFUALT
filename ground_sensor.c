/*
 * ground_sensor.c
 *
 *  Created on: 2023年7月23日
 *      Author: Unusualroutetaker
 */


#include <fd_demo.h>
int ground_sensor_list[7]={0,0,0,0,0,0,0};  //灰度传感器，黑灭1，白亮0。

void ground_sensor_init(void)
{
    P2DIR &= ~BIT3;// Set P2.3 Output init
    P2OUT &= ~BIT3;
    P2REN |= BIT3;

    P2DIR &= ~BIT6;// Set P2.6 Output init
    P2OUT &= ~BIT6;
    P2REN |= BIT6;

    P4DIR &= ~BIT1;// Set P4.1 Output init
    P4OUT &= ~BIT1;
    P4REN |= BIT1;

    P4DIR &= ~BIT2;// Set P4.2 Output init
    P4OUT &= ~BIT2;
    P4REN |= BIT2;

    P6DIR &= ~BIT0;// Set P6.0 Output init
    P6OUT &= ~BIT0;
    P6REN |= BIT0;

    P6DIR &= ~BIT1;// Set P6.1 Output init
    P6OUT &= ~BIT1;
    P6REN |= BIT1;

    P6DIR &= ~BIT2;// Set P6.2 Output init
    P6OUT &= ~BIT2;
    P6REN |= BIT2;

}

void ground_sensor_get(void)
{
    if(Port0)
        {ground_sensor_list[0]=1;}
    if(Port1)
        {ground_sensor_list[1]=1;}
    if(Port2)
        {ground_sensor_list[2]=1;}
    if(Port3)
        {ground_sensor_list[3]=1;}
    if(Port4)
        {ground_sensor_list[4]=1;}
    if(Port5)
        {ground_sensor_list[5]=1;}
    if(Port6)
        {ground_sensor_list[6]=1;}


    if(!Port0)
        {ground_sensor_list[0]=0;}
    if(!Port1)
        {ground_sensor_list[1]=0;}
    if(!Port2)
        {ground_sensor_list[2]=0;}
    if(!Port3)
        {ground_sensor_list[3]=0;}
    if(!Port4)
        {ground_sensor_list[4]=0;}
    if(!Port5)
        {ground_sensor_list[5]=0;}
    if(!Port6)
        {ground_sensor_list[6]=0;}

}
