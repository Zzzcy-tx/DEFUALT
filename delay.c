/*
 * delay.c
 *
 *  Created on: 2022ƒÍ7‘¬12»’
 *      Author: FeiDao
 */
#include <delay.h>
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ∫¡√Î—”≥Ÿ
//  @param      ms          —”≥Ÿ ±º‰£®∫¡√Î£©
//  @return     void
//  Sample usage:           delay(1000);//—”≥Ÿ1000∫¡√Î
//-------------------------------------------------------------------------------------------------------------------
void delay(unsigned int ms)
{
    int i,j;
    for(j=0;j<ms;j++)
    {
        for(i=0;i<207*25;i++);
    }
}


float abs_float(float input_val)
{
    if(input_val<0)
    {
        input_val = -input_val;
    }
    return input_val;
}


int abs_int(int input_val)
{
    if(input_val<0)
    {
        input_val = -input_val;
    }
    return input_val;
}


float limit_float(float input_val,float low,float high)
{
    if(input_val<=low)
    {input_val=low;}
    if(input_val>=high)
    {input_val=high;}
    return input_val;
}


int limit_int(int input_val,int low,int high)
{
    if(input_val<=low)
    {input_val=low;}
    if(input_val>=high)
    {input_val=high;}
    return input_val;
}


void beeb_ring(int ring_time)
{
    int ring_count=0;
    while(ring_count<=207*ring_time)
    {
        P6OUT |= BIT5;
        ring_count+=1;
    }
    P6OUT &= ~BIT5;
}
