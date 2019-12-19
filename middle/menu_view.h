
#ifndef _MENU_VIEW_H
#define _MENU_VIEW_H

#include "menu_data.h"




/*
* 根据menuObj结构体指针内容进行菜单界面绘制，类型可以是列表，也可以是卡片。
* 由控制层调用。
* 注意：如果类型是卡片的话，绘制卡片的函数需要使用RegisterDrawCardFunc提前注册。
* 返回值，0-成功，其它代表失败错误码，错误码待定。
*/
uint8_t DrawMenu(MenuObj *menuObj);

/*
* 显示开关
* 由控制层调用，用于屏幕和触屏开关控制
* sw：0代表关，1代表开
*/
void DisplaySwitch(uint8_t sw);


/*
* 屏幕亮度设置
* bright：0~10，0代表最暗，10代表最亮，UX设计原始RGB值定义为最亮
*/
void SetBright(uint8_t bright);



void DrawList(MenuObj *menuObj);
void DrawCard(MenuObj *menuObj);

#endif



