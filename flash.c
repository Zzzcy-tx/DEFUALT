/*
 * flash.c
 *
 *  Created on: 2023Äê7ÔÂ8ÈÕ
 *      Author: Unusualroutetaker
 */
#include <fd_demo.h>

#define ERASE                  (0x0002)
#define FWKEY                  (0xA500)

char * flash_add[6] = {0x1800,0x2000,0x2200,0x2600,0x2800,0x3000};
int content_write_list[6] = {0,0,0,0,0,0};
int content_read_list[6] = {0,0,0,0,0,0};

void flash_demo(void)
{
      unsigned long * Flash_ptrD1;
      unsigned long * Flash_ptrD2;
      unsigned long * Flash_ptrD3;
      unsigned long * Flash_ptrD4;
      unsigned long * Flash_ptrD5;
      unsigned long * Flash_ptrD6;
      int flash_write_digit;
      char * content_write_in[6] = {"0","0","0","0","0","0"};

      Flash_ptrD1 = (unsigned long *) flash_add[0];
      Flash_ptrD2 = (unsigned long *) flash_add[1];
      Flash_ptrD3 = (unsigned long *) flash_add[2];
      Flash_ptrD4 = (unsigned long *) flash_add[3];
      Flash_ptrD5 = (unsigned long *) flash_add[4];
      Flash_ptrD6 = (unsigned long *) flash_add[5];

      for (flash_write_digit=0;flash_write_digit<=5;flash_write_digit++)
      {
          content_write_in[flash_write_digit] = content_write_list[flash_write_digit];
      }

      FCTL3 = FWKEY;
      FCTL1 = FWKEY + ERASE;
      _DINT();

//      for (flash_write_digit=0;flash_write_digit<=5;flash_write_digit++)
//      {
//
//      }

      *Flash_ptrD1 = 0;
      *Flash_ptrD2 = 0;
      *Flash_ptrD3 = 0;
      *Flash_ptrD4 = 0;
      *Flash_ptrD5 = 0;
      *Flash_ptrD6 = 0;
      while(FCTL3 & BUSY);
      FCTL1 = FWKEY + BLKWRT;
      *Flash_ptrD1 = content_write_in[0];
      *Flash_ptrD2 = content_write_in[1];
      *Flash_ptrD3 = content_write_in[2];
      *Flash_ptrD4 = content_write_in[3];
      *Flash_ptrD5 = content_write_in[4];
//      *Flash_ptrD6 = content_write_in[0]+5;
      while(FCTL3 & BUSY);
      _EINT();
      FCTL1 = FWKEY;
      FCTL3 = FWKEY + LOCK;
}


void flash_read(void)
{
    char * read_content[6] = {"0","0","0","0","0","0"};
    int flash_read_digit;

    for (flash_read_digit=0;flash_read_digit<=4;flash_read_digit++)
    {
        read_content[flash_read_digit] = *flash_add[flash_read_digit];
        content_read_list[flash_read_digit] = ((int)read_content[flash_read_digit]);
//        OLED_ShowNum(16,(flash_read_digit+2),content_read_list[flash_read_digit],10,14);
    }
}



