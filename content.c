/*
 * content.c
 *
 *  Created on: 2023Äê7ÔÂ8ÈÕ
 *      Author: Unusualroutetaker
 */

#include <fd_demo.h>
int current_page;
int current_page_last;
int content_start_flag;
int mouse_select_flag;
int mouse_posi[3]={2,0,0};
int mouse_posi_last[3]={2,0,0};
int clear_mouse_change_info_count=0;
int content_page0_data[10];
int edit_complete_flag;
int edit_stop_flag;

void content_init(void)
{
    edit_complete_flag=0;
    content_start_flag=1;
    current_page=0;
    mouse_select_flag=0;
    keyboard_scan=0;
    pressed_key[0]=0;
    pressed_key[1]=0;
    pressed_key[2]=0;
    flash_read_to_content();
    content_mouse();
    feedback_page();
    pages();

}


void flash_read_to_content(void)
{
    flash_read();
    content_page0_data[0]=content_read_list[0];
    content_page0_data[1]=content_read_list[1];
    content_page0_data[2]=content_read_list[2];
    content_page0_data[3]=content_read_list[3];
    content_page0_data[4]=content_read_list[4];
    content_page0_data[5]=100;
    content_page0_data[6]=100;
    content_page0_data[7]=100;
    content_page0_data[8]=100;
    content_page0_data[9]=100;
}


void feedback_page(void)
{
    if(content_start_flag==0)
    {OLED_ShowString(2,0,":S",14);}
    if(content_start_flag==1)
    {OLED_ShowString(2,0,":)",14);}
    if(content_start_flag==2)
    {OLED_ShowString(2,0,":(",14);}

//    if(real_press_key==1)
//    {OLED_ShowString(20,0,"Back",14);}
//    if(real_press_key==2)
//    {OLED_ShowString(20,0,"Up",14);}
//    if(real_press_key==4)
//    {OLED_ShowString(20,0,"++",14);}
//    if(real_press_key==5)
//
//    {OLED_ShowString(20,0,"Right",14);}
//    if(real_press_key==6)
//    {OLED_ShowString(20,0,"Select",14);}
//    if(real_press_key==7)
//    {OLED_ShowString(20,0,"Left",14);}
//    if(real_press_key==8)
//    {OLED_ShowString(20,0,"--",14);}
//
//    if(real_press_key==10)
//    {OLED_ShowString(20,0,"Down",14);}
//
//    if(real_press_key==13)
//    {OLED_ShowString(20,0,"Last_Page",14);}
//    if(real_press_key==14)
//    {OLED_ShowString(20,0,"Next_Page",14);}
//    if(real_press_key==15)
//    {OLED_ShowString(20,0,"OK",14);}
//    if(real_press_key==16)
//    {OLED_ShowString(20,0,"Start",14);}

    OLED_ShowString(85,0,"Page ",14);
    OLED_ShowNum(115,0,current_page,1,14);

    OLED_ShowString(0,1,"_____________________",14);
    OLED_ShowNum(115,0,current_page,1,14);

    OLED_ShowString(60,2,"!",14);
    OLED_ShowString(60,3,"!",14);
    OLED_ShowString(60,4,"!",14);
    OLED_ShowString(60,5,"!",14);
    OLED_ShowString(60,6,"!",14);
//    OLED_ShowString(20,0,"           ",14);
}


void content_mouse(void)
{
    unsigned char * mouse_shape[3]={"o","*"," "};
    if((real_press_key==2)&&(mouse_posi[0]>2))
    {
        mouse_posi[0]-=1;
    }
    if((real_press_key==10)&&(mouse_posi[0]<6))
    {
        mouse_posi[0]+=1;
    }

    if((real_press_key==5)&&(mouse_posi[1]==1))
    {
        mouse_posi[1]=0;
    }
    if((real_press_key==7)&&(mouse_posi[1]==0))
    {
        mouse_posi[1]=1;
    }

    if((real_press_key==6)&&(mouse_posi[2]==0))
    {
        mouse_posi[2]=1;
        content_start_flag=0;
    }
    if((real_press_key==1)&&(mouse_posi[2]==1))
    {
        mouse_posi[2]=0;
        content_start_flag=1;
    }

    if((mouse_posi_last[0]!=mouse_posi[0])||(mouse_posi_last[1]!=mouse_posi[1]))
    {
        OLED_ShowString((2+mouse_posi_last[1]*65),mouse_posi_last[0],mouse_shape[2],14);
        mouse_posi_last[0]=mouse_posi[0];
        mouse_posi_last[1]=mouse_posi[1];
        mouse_posi_last[2]=mouse_posi[2];
    }

    OLED_ShowString((2+mouse_posi[1]*65),mouse_posi[0],mouse_shape[mouse_posi[2]],14);
}


void content_value_editor(void)
{
    int position_value;
    position_value=mouse_posi[0]+mouse_posi[1]*5 - 2;
    if(content_start_flag==0)
    {
        if((real_press_key==4)&&(content_page0_data[position_value]<255))
        {
            content_page0_data[position_value]+=1;
        }
        if((real_press_key==8)&&(content_page0_data[position_value]>0))
        {
            content_page0_data[position_value]-=1;
        }
    }
}


void start_checker(void)
{
    if((real_press_key==15)&&(content_start_flag==1))
    {
        content_write_list[0]=content_page0_data[0];
        content_write_list[1]=content_page0_data[1];
        content_write_list[2]=content_page0_data[2];
        content_write_list[3]=content_page0_data[3];
        content_write_list[4]=content_page0_data[4];
        flash_demo();
    }

    if((real_press_key==16)&&(content_start_flag==1))
    {
        if(edit_complete_flag==1)
        {
            edit_stop_flag=1;
        }
        if(edit_complete_flag==0)
        {
            edit_complete_flag=1;
        }
    }
}


void value_update_from_code(void)
{
    if((real_press_key==12)&&(content_start_flag==1))
    {
        content_write_list[0]=123;//edit to the user defined variable
        content_write_list[1]=123;
        content_write_list[2]=123;
        content_write_list[3]=123;
        content_write_list[4]=123;
        flash_demo();
        flash_read_to_content();
        OLED_Clear();
        page_changer();
        content_mouse();
        feedback_page();
        pages();
    }
}


void page_changer(void)
{
    current_page_last=current_page;
    if((real_press_key==13)&&(current_page>0))
    {
        current_page-=1;
    }
    if((real_press_key==14)&&(current_page<1))
    {
        current_page+=1;
    }
    if(current_page_last!=current_page)
    {OLED_Clear();}
}


void pages(void)
{
    if(current_page==0)
    {
        page_0();
    }
    if(current_page==1)
    {
        page_1();
    }
}


void page_0(void)
{
//    OLED_ShowString(2,2,"o",14);
//    OLED_ShowString(2,3,"*",14);

    OLED_ShowString(10,2,"Da0:",14);
    OLED_ShowString(10,3,"Da1:",14);
    OLED_ShowString(10,4,"Da2:",14);
    OLED_ShowString(10,5,"Da3:",14);
    OLED_ShowString(10,6,"Da4:",14);

    OLED_ShowNum(37,2,content_page0_data[0],3,14);
    OLED_ShowNum(37,3,content_page0_data[1],3,14);
    OLED_ShowNum(37,4,content_page0_data[2],3,14);
    OLED_ShowNum(37,5,content_page0_data[3],3,14);
    OLED_ShowNum(37,6,content_page0_data[4],3,14);


//    OLED_ShowString(67,2,"o",14);
//    OLED_ShowString(67,3,"*",14);

    OLED_ShowString(75,2,"Na",14);
    OLED_ShowString(75,3,"Na:",14);
    OLED_ShowString(75,4,"Na:",14);
    OLED_ShowString(75,5,"Na:",14);
    OLED_ShowString(75,6,"Na:",14);

    OLED_ShowNum(102,2,content_page0_data[5],3,14);
    OLED_ShowNum(102,3,content_page0_data[6],3,14);
    OLED_ShowNum(102,4,content_page0_data[7],3,14);
    OLED_ShowNum(102,5,content_page0_data[8],3,14);
    OLED_ShowNum(102,6,content_page0_data[9],3,14);
}

void page_1(void)
{
    OLED_ShowString(10,2,"P0:",14);
    OLED_ShowString(10,3,"P1:",14);
    OLED_ShowString(10,4,"P2:",14);
    OLED_ShowString(10,5,"P3:",14);
    OLED_ShowString(10,6,"P4:",14);

    OLED_ShowNum(37,2,ground_sensor_list[0],3,14);
    OLED_ShowNum(37,3,ground_sensor_list[1],3,14);
    OLED_ShowNum(37,4,ground_sensor_list[2],3,14);
    OLED_ShowNum(37,5,ground_sensor_list[3],3,14);
    OLED_ShowNum(37,6,ground_sensor_list[4],3,14);


    OLED_ShowString(75,2,"P5",14);
    OLED_ShowString(75,3,"P6",14);

    OLED_ShowNum(102,2,ground_sensor_list[5],3,14);
    OLED_ShowNum(102,3,ground_sensor_list[6],3,14);

}
