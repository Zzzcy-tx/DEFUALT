/*
 * pwm.c
 *
 *  Created on: 2022��7��13��
 *      Author: FeiDao
 */
#include <pwm.h>

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM�����ʼ��
//  @param      pin         ѡ������ţ���ѡ��Χ��1_2��1_3��1_4��1_5��2_0��2_4��2_5����Ӧ12��13��14��15��20��24��25
//  @param      freq        ���Ƶ��Hz
//  @param      duty        PWM����ʼ��ռ�ձ�0~1000
//  @return     void
//  Sample usage:           pwm_init("1_2", 100, 0);//P1_2��ʼ��ΪPWM�����Ƶ��100Hz����ʼռ�ձ�0%
//  @note                   ����ͬһ����ʱ��������Ӧ������ͬƵ��
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(unsigned int pin, unsigned int freq, unsigned int duty)
{
    if(pin == 12)
    {
        P1DIR |=BIT2;
        P1SEL |=BIT2;
        TA0CCR0=1000/freq*32.89;
        TA0CCTL1=OUTMOD_7;
        TA0CCR1=duty*TA0CCR0/100;
        TA0CTL =TASSEL_1+MC_1+TACLR;
    }
    if(pin == 13)
    {
        P1DIR |=BIT3;
        P1SEL |=BIT3;
        TA0CCR0=1000/freq*32.89;
        TA0CCTL2=OUTMOD_7;
        TA0CCR2=duty*TA0CCR0/100;
        TA0CTL =TASSEL_1+MC_1+TACLR;
    }
    if(pin == 14)
    {
        P1DIR |=BIT4;
        P1SEL |=BIT4;
        TA0CCR0=1000/freq*32.89;
        TA0CCTL3=OUTMOD_7;
        TA0CCR3=duty*TA0CCR0/100;
        TA0CTL =TASSEL_1+MC_1+TACLR;
    }
    if(pin == 15)
    {
        P1DIR |=BIT5;
        P1SEL |=BIT5;
        TA0CCR0=1000/freq*32.89;
        TA0CCTL4=OUTMOD_7;
        TA0CCR4=duty*TA0CCR0/100;
        TA0CTL =TASSEL_1+MC_1+TACLR;
    }
    if(pin == 20)
    {
        P2DIR |=BIT0;
        P2SEL |=BIT0;
        TA1CCR0=1000/freq*32.89;
        TA1CCTL1=OUTMOD_7;
        TA1CCR1=duty*TA1CCR0/100;
        TA1CTL =TASSEL_1+MC_1+TACLR;
    }
    if(pin == 24)
    {
        P2DIR |=BIT4;
        P2SEL |=BIT4;
        TA2CCTL1=OUTMOD_7;
        TA2CCR0=1000/freq*32.89;
        TA2CCR1=duty*TA2CCR0/100;
        TA2CTL =TASSEL_1+MC_1+TACLR;
    }
    if(pin == 25)
    {
        P2DIR |=BIT5;
        P2SEL |=BIT5;
        TA2CCTL2=OUTMOD_7;
        TA2CCR0=1000/freq*32.89;
        TA2CCR2=duty*TA2CCR0/100;
        TA2CTL =TASSEL_1+MC_1+TACLR;
    }

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM�������
//  @param      pin         ѡ������ţ���ѡ��Χ��1_2, 1_3, 1_4, 1_5, 2_0, 2_4, 2_5
//  @param      duty        PWM��ռ�ձ�0~100
//  @return     void
//  Sample usage:           pwm_init("1_2", 50);//P1_2����PWM���ռ�ձ�50%
//-------------------------------------------------------------------------------------------------------------------
void pwm_duty(unsigned int pin, unsigned int duty)
{
    if(pin == 12)
    {
        TA0CCR1=duty*TA0CCR0/100;
    }
    if(pin == 13)
    {
        TA0CCR2=duty*TA0CCR0/100;
    }
    if(pin == 14)
    {
        TA0CCR3=duty*TA0CCR0/100;
    }
    if(pin == 15)
    {
        TA0CCR4=duty*TA0CCR0/100;
    }
    if(pin == 20)
    {
        TA1CCR1=duty*TA1CCR0/100;
    }
    if(pin == 24)
    {
        TA2CCR1=duty*TA2CCR0/100;
    }
    if(pin == 25)
    {
        TA2CCR2=duty*TA2CCR0/100;
    }
}


