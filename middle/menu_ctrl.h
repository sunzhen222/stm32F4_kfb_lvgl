
#ifndef _MENU_CTRL_H
#define _MENU_CTRL_H

#include "stdint.h"
#include "menu_data.h"

/*
* 初始化菜单数据，为各个层级的菜单结构体赋值、注册回调函数。
*/
void MenuInit(void);

/*
* 进入子菜单，在屏幕绘制子菜单的UI界面。
* menuObj：子菜单的结构体指针。
* 返回值，0-成功，其它代表失败错误码，错误码待定。
*/
uint8_t EnterSubMenu(MenuObj *menuObj);

/*
* 返回上级菜单，在屏幕绘制上级菜单的UI界面
* 返回值，0-成功，其它代表失败错误码，错误码待定。
*/
uint8_t BackPreMenu(void);

/*
* 返回home目录，在屏幕绘制上级菜单的UI界面
* 返回值，0-成功，其它代表失败错误码，错误码待定。
*/
uint8_t GotoHomeMenu(void);


/*
* 注册绘制卡片的回调函数。
* 将回调函数地址存入menuObj结构体指针中，当DrawMenu时，如果menuObj类型为卡片时执行。
* menuObj：需注册绘制卡片的菜单结构体指针。
* DrawCardFunc：被注册的绘制回调函数。
* 注意：回调函数在显示层定义实现。
*/
void RegisterDrawCardFunc(MenuObj *menuObj,void (*DrawCardFunc)(void));


/*
* 注册 菜单UI滑动事件的回调函数。
* 将回调函数地址存入menuObj结构体指针中的SlidFunc。
* 当显示层通过littlevGL检测到滑动事件之后，会通过当前UI结构体指针调用已注册
* 的滑动回调函数。
* menuObj：需注册滑动事件的菜单结构体指针。
* SlidEvent：被注册的滑动事件回调函数，该函数的参数为滑动方向。
* 注意：回调函数在控制层定义实现。
*/
void RegisterMenuSlidEvent(MenuObj *menuObj, void (*SlidEvent)(SlidDir));


/*
* 注册 List里某个Item点击的回调函数。
* 将回调函数地址存入menuItem结构体指针中的clickFunc。
* 当显示层通过littlevGL检测到某个Item的点击事件之后，会通过当前UI结构体指针
* 调用已注册的Item点击的回调函数。
* menuItem：需注册点击事件的列表子项结构体。
* ItemClickEvent：被注册的点击事件回调函数。
* 注意：回调函数在控制层定义实现。
*/
void RegisterListItemClickEvent(MenuItem *menuItem, void (*ItemClickEvent)(void));


/*
* 注册 Card按键点击事件的回调函数
* 将回调函数地址存入menuItem结构体指针中的XXX
* 当显示层通过littlevGL检测到某个按键的点击事件之后，会通过当前UI结构体指针调用
* 已注册的Card按键点击的回调函数
*/
void RegisterCardEvent(MenuObj *menuObj, void (*CardEvent)(uint8_t));





#endif



