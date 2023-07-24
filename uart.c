/*
 * uart.c
 *
 *  Created on: 2022��7��13��
 *      Author: FeiDao
 */

#include <uart.h>

int Data_USCI_A0;               //USCI_A0��������ԭʼ
int Data_USCI_A1;               //USCI_A1��������ԭʼ
int Data_USCI_A0_int;           //USCI_A0��������int��ʽ
int Data_USCI_A1_int;           //USCI_A1��������int��ʽ
char Data_USCI_A0_char;         //USCI_A0��������char��ʽ
char Data_USCI_A1_char;         //USCI_A1��������char��ʽ


//-------------------------------------------------------------------------------------------------------------------
//  @brief      uart���ڳ�ʼ��
//  @param      uart_pin        USCI_A0��USCI_A1
//  @return     void
//  @note       P3.3,4 ΪA0
//              P4.4,5 ΪA1
//-------------------------------------------------------------------------------------------------------------------
void uart_init(unsigned int uart_pin)
{
    if (uart_pin == 10)//USCI_A0
    {
        P3SEL |= BIT3+BIT4; // P3.3,4 = USCI_A0 TXD/RXD
        UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
        UCA0CTL1 |= UCSSEL_2; // SMCLK
        UCA0BR0 = 9; // 1MHz 115200 (see User's Guide)
        UCA0BR1 = 0; // 1MHz 115200
        UCA0MCTL |= UCBRS_1 + UCBRF_0; // Modulation UCBRSx=1, UCBRFx=0
        UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
        UCA0IE |= UCRXIE; // Enable USCI_A0 RX interrupt
    }
    if (uart_pin == 11)//USCI_A1
    {
        P4SEL |= BIT4+BIT5; // P4.4,5 = USCI_A1 TXD/RXD
        UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
        UCA1CTL1 |= UCSSEL_2; // SMCLK
        UCA1BR0 = 9; // 1MHz 115200 (see User's Guide)
        UCA1BR1 = 0; // 1MHz 115200
        UCA1MCTL |= UCBRS_1 + UCBRF_0; // Modulation UCBRSx=1, UCBRFx=0
        UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
        UCA1IE |= UCRXIE; // Enable USCI_A1 RX interrupt
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      uart���ڽ���
//  @param      uart_pin        USCI_A0USCI_A1
//  @return     void
//  @note       P3.3,4 ΪA0
//              P4.4,5 ΪA1
//
//              ��ȡ��Ϊint���ͣ�Data_USCI_Ax_int
//              ��ȡ��Ϊchar���ͣ�Data_USCI_Ax_char
//-------------------------------------------------------------------------------------------------------------------
void uart_read(unsigned int uart_pin)
{
    if (uart_pin == 10)//USCI_A0
    {
        Data_USCI_A0=UCA0RXBUF;
        Data_USCI_A0_int = Data_USCI_A0-'0';
        Data_USCI_A0_char = Data_USCI_A0;
//        OLED_ShowNum(15,2,Data_USCI_A0_int,3,10);
//        OLED_ShowChar(15,3,Data_USCI_A0_char,10);
        Data_USCI_A0=UCA0RXBUF;
    }
    if (uart_pin == 11)//USCI_A1
    {
        Data_USCI_A1=UCA1RXBUF;
        Data_USCI_A1_int = Data_USCI_A1-'0';
        Data_USCI_A1_char = Data_USCI_A1;
//        OLED_ShowNum(15,2,Data_USCI_A1_int,3,10);
//        OLED_ShowChar(15,3,Data_USCI_A1_char,10);
        Data_USCI_A1=UCA1RXBUF;
    }

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      uart���ڷ���
//  @param      uart_pin        USCI_A0��USCI_A1
//  @param      text            ��������
//  @return     void
//  @note       P3.3,4 ΪA0
//              P4.4,5 ΪA1
//-------------------------------------------------------------------------------------------------------------------
void uart_sent(unsigned int uart_pin, unsigned char text)
{
    if (uart_pin == 10)//USCI_A0
    {
        UCA0TXBUF=text;
        while(!(UCA0IFG&UCTXIFG));
    }
    if (uart_pin == 11)//USCI_A1
    {
        UCA1TXBUF=text;
        while(!(UCA1IFG&UCTXIFG));
    }

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����ж�A0
//  @return     void
//  @note       P3.3,4 = USCI_A0 TXD/RXD
//              ��ȡ��Data_USCI_A0
//-------------------------------------------------------------------------------------------------------------------
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    switch(__even_in_range(UCA0IV,4))
    {
        case 0:
            break; // Vector 0 - no interrupt
        case 2: // Vector 2 - RXIFG
            Data_USCI_A0=UCA0RXBUF;
//            uart_read(10);
            gyroscope_read();
            break;

        case 4:
            break; // Vector 4 - TXIFG
        default:
            break;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����ж�A0
//  @return     void
//  @note       P4.4,5 = USCI_A0 TXD/RXD
//              ��ȡ��Data_USCI_A1
//-------------------------------------------------------------------------------------------------------------------
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{

    switch(__even_in_range(UCA1IV,4))
    {
        case 0:
            break; // Vector 0 - no interrupt
        case 2: // Vector 2 - RXIFG
            while (!(UCA1IFG&UCTXIFG)); // USCI_A1 TX buffer ready?
            uart_read(11);
            break;
        case 4:
            break; // Vector 4 - TXIFG
        default:
            break;
    }
}
