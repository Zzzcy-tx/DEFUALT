/*
 * fd_demo.c
 *
 *  Created on: 2022年7月12日
 *      Author: FeiDao
 */

#include <fd_demo.h>


//-------------------------------------------------------------------------------------------------------------------
//  @brief      例程
//  @return     void
//  @note       基本函数用法见README.txt
//-------------------------------------------------------------------------------------------------------------------

int init_speed=200; //速度环平均速度

void example(void)
{
    init_all();
    encoder_init();
    pid_init();

    pwm_init(12,1000,0);
    pwm_init(13,1000,0);
    pwm_init(14,1000,0);
    pwm_init(15,1000,0);
    int once_flag=0;


    while(1)
    {
        if(edit_complete_flag==0) // content edit
        {
            keyboard_test();
            if(1)
            {
                page_changer();
                content_mouse();
                content_value_editor();
                feedback_page();
                if(current_page==1)
                {ground_sensor_get();}
                pages();
                value_update_from_code();
                start_checker();
            }

        }

        if(edit_complete_flag==1)
        {
//            keyboard_test();
//            start_checker();
            if(once_flag==0)
            {
                OLED_Clear();
                once_flag=1;
//                delay(1000);
                motor_speed_set(init_speed,init_speed);
            }

            pid_read();



        }
//        if(edit_stop_flag==1)
//        {
//            motor_speed_set(0,0);
//        }
    }
}



// Set CPU Clock to 25MHz
void set_clock(void)
{
  P1SEL &= ~BIT1;
  P1DIR |= BIT1;
  P1SEL |= BIT0; //ACLK
  P1DIR |= BIT0;
  P2SEL |= BIT2; //SMCLK
  P2DIR |= BIT2;
  P7SEL |= BIT7; //MCLK
  P7DIR |= BIT7;
  P5SEL |= BIT4|BIT5;

  UCSCTL6 |= XCAP_3;//开启  SMCLK时钟   选择电容
  UCSCTL6 &= ~XT1OFF;//打开 XT1，否则 XT1LFOFFG 可能报错
//  PMMCTL0_H = 0xA5;
//  PMMCTL0 |=PMMPW+ PMMCOREV_3;

      PMMCTL0_H = 0xA5;                                         //开PMM电源管理
       SVSMLCTL |= SVSMLRRL_1 + SVMLE;                            //配置SVML电压
       PMMCTL0 =  PMMPW + PMMCOREV_2;                             //配置内核电压
       while((PMMIFG & SVSMLDLYIFG ) == 0);                       //等待设置完成
       PMMIFG &= ~(SVMLVLRIFG + SVMLIFG + SVSMLDLYIFG);
       if((PMMIFG & SVMLIFG) == 1)                                //判断内核电压是否上升到VSVML
             while((PMMIFG & SVMLVLRIFG) == 0);                   //如果没有等待
  SVSMLCTL &= ~SVMLE;                                        //关掉SVML模块
  PMMCTL0_H = 0X00;                                          //锁存配置

  __bis_SR_register(SCG0);//该语法为固定格式，意为将括号内的变量置位，SCG0与系统工作模式有关，此时 MCLK 暂停工作
  UCSCTL0 = 0; //先清零，FLL 运行时，该寄存器系统会自动配置，不用管
  UCSCTL1 = DCORSEL_6;//自动修正
  UCSCTL2 = FLLD_1 | 380;//FLLD=1,FLLN=380,则频率为2*（380+1）*32.768=24.969MHZ
  __bic_SR_register(SCG0);
  __delay_cycles(782000);//系统自带的精确延时，单位 us
  while(SFRIFG1 & OFIFG)
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
    SFRIFG1 &= ~OFIFG;
  }
  UCSCTL4 = UCSCTL4&(~(SELS_7|SELM_7))|SELS_3|SELM_3;
  ///MCLK=24M   SMCLK=24MH   ACLK   32.768K
}





