/*
 * oled.c
 *
 *  Created on: 2021Äê9ÔÂ6ÈÕ
 *      Author: feidao
 */


//	SCL connects to P6.3
//	SDA connects to P6.4
#include <msp430f5529.h>
#include "Oled.h"
#include "Oled_font.h"
#include "Oled_type.h"

void IIC_Start()
{

    OLED_SCLK_Set();
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}


void IIC_Stop()
{
OLED_SCLK_Set() ;
//  OLED_SCLK_Clr();
    OLED_SDIN_Clr();
    OLED_SDIN_Set();

}

void IIC_Wait_Ack()
{
    OLED_SCLK_Set() ;
    OLED_SCLK_Clr();
}

void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    unsigned char m,da;
    da=IIC_Byte;
    OLED_SCLK_Clr();
    for(i=0;i<8;i++)
    {
            m=da;

        m=m&0x80;
        if(m==0x80)
        {OLED_SDIN_Set();}
        else OLED_SDIN_Clr();
            da=da<<1;
        OLED_SCLK_Set();
        OLED_SCLK_Clr();
        }


}

void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);
    IIC_Wait_Ack();
   Write_IIC_Byte(0x00);
    IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Command);
    IIC_Wait_Ack();
   IIC_Stop();
}

void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);
    IIC_Wait_Ack();
   Write_IIC_Byte(0x40);
    IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Data);
    IIC_Wait_Ack();
   IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
    if(cmd)
            {

   Write_IIC_Data(dat);

        }
    else {
   Write_IIC_Command(dat);

    }


}


void fill_picture(unsigned char fill_Data)
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        OLED_WR_Byte(0xb0+m,0);
        OLED_WR_Byte(0x00,0);
        OLED_WR_Byte(0x10,0);
        for(n=0;n<128;n++)
            {
                OLED_WR_Byte(fill_Data,1);
            }
    }
}

void Delay_1ms(unsigned int Del_1ms)
{
    unsigned char j;
    while(Del_1ms--)
    {
        for(j=0;j<123;j++);
    }
}


void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}

void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X14,OLED_CMD);
    OLED_WR_Byte(0XAF,OLED_CMD);
}

void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X10,OLED_CMD);
    OLED_WR_Byte(0XAE,OLED_CMD);
}

void OLED_Clear(void)
{
    u8 i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);
    }
}
void OLED_On(void)
{
    u8 i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA);
    }
}

void OLED_ShowChar(u8 x2,u8 y2,u8 chr,u8 Char_Size)
{
    unsigned char c=0,i=0;
    c=chr-' ';
    if(x2>Max_Column-1){x2=0;y2=y2+2;}
    if(Char_Size ==16)
        {
        OLED_Set_Pos(x2,y2);
        for(i=0;i<8;i++)
        OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
        OLED_Set_Pos(x2,y2+1);
        for(i=0;i<8;i++)
        OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
        }
        else {
            OLED_Set_Pos(x2,y2);
            for(i=0;i<6;i++)
            OLED_WR_Byte(F6x8[c][i],OLED_DATA);
        }
}

u32 oled_pow(u8 m,u8 n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}

void OLED_ShowNum(u8 x1,u8 y1,u32 num,u8 len,u8 size2)
{
    u8 t,temp;
    u8 enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x1+(size2/2)*t,y1,' ',size2);
                continue;
            }else enshow=1;

        }
        OLED_ShowChar(x1+(size2/2)*t,y1,temp+'0',size2);
    }
}
void OLED_ShowVI(u8 x,u8 y,u32 num,u8 size2)
{
    OLED_ShowNum(x+size2*4-1,y,num%10,1,size2);
    OLED_ShowNum(x+size2*3-1,y,num/10%10,1,size2);
    OLED_ShowNum(x+size2*2-1,y,num/100%10,1,size2);
    OLED_ShowString(x+size2*1-1,y,".",size2);
    OLED_ShowNum(x-1,y,num/1000,1,size2);
}

void OLED_ShowString(u8 x3,u8 y3,u8 *chr,u8 Char_Size)
{
    unsigned char j=0;
    while (chr[j]!='\0')
    {       OLED_ShowChar(x3,y3,chr[j],Char_Size);
            x3+=6;
        if(x3>120){x3=0;y3+=2;}
            j++;
    }
}

void OLED_Init(void)
{
    P6DIR |= BIT3+BIT4;
    OLED_WR_Byte(0xAE,OLED_CMD);
    OLED_WR_Byte(0x00,OLED_CMD);
    OLED_WR_Byte(0x10,OLED_CMD);
    OLED_WR_Byte(0x40,OLED_CMD);
    OLED_WR_Byte(0xB0,OLED_CMD);
    OLED_WR_Byte(0x81,OLED_CMD);
    OLED_WR_Byte(0xFF,OLED_CMD);
    OLED_WR_Byte(0xA1,OLED_CMD);
    OLED_WR_Byte(0xA6,OLED_CMD);
    OLED_WR_Byte(0xA8,OLED_CMD);
    OLED_WR_Byte(0x3F,OLED_CMD);
    OLED_WR_Byte(0xC8,OLED_CMD);
    OLED_WR_Byte(0xD3,OLED_CMD);
    OLED_WR_Byte(0x00,OLED_CMD);

    OLED_WR_Byte(0xD5,OLED_CMD);
    OLED_WR_Byte(0x80,OLED_CMD);

    OLED_WR_Byte(0xD8,OLED_CMD);
    OLED_WR_Byte(0x05,OLED_CMD);

    OLED_WR_Byte(0xD9,OLED_CMD);
    OLED_WR_Byte(0xF1,OLED_CMD);

    OLED_WR_Byte(0xDA,OLED_CMD);
    OLED_WR_Byte(0x12,OLED_CMD);

    OLED_WR_Byte(0xDB,OLED_CMD);
    OLED_WR_Byte(0x30,OLED_CMD);

    OLED_WR_Byte(0x8D,OLED_CMD);
    OLED_WR_Byte(0x14,OLED_CMD);

    OLED_WR_Byte(0xAF,OLED_CMD);
}




