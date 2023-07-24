/*
 * content.h
 *
 *  Created on: 2023Äê7ÔÂ8ÈÕ
 *      Author: Unusualroutetaker
 */

#ifndef CONTENT_H_
#define CONTENT_H_

#include <fd_demo.h>

void feedback_page(void);
void content_mouse(void);
void content_init(void);
void content_value_editor(void);
void page_changer(void);
void start_checker(void);
void value_update_from_code(void);
void flash_read_to_content(void);
void pages(void);
void page_0(void);
void page_1(void);

extern int mouse_select_flag;
extern int mouse_posi[3];
extern int content_start_flag;
extern int content_page0_data[10];
extern int edit_complete_flag;
extern int edit_stop_flag;
extern int current_page;

#endif /* CONTENT_H_ */
