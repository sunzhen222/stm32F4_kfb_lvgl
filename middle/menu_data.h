
#ifndef _MENU_DATA_H
#define _MENU_DATA_H

#include "stdint.h"
#include "stdbool.h"


typedef enum __MenuType
{
    LIST = 0,
    CARD
}MenuType;


typedef enum __SlidDirection
{
    SLID_RIGHT = 0,
    SLID_DOWN,
    SLID_LEFT,
    SLID_UP
}SlidDir;


//列表子项描述结构体
typedef struct __MenuItem
{
    char *text;                             //文本内容
    uint8_t hanSize;                        //文本字体大小
    bool showImg;                           //是否显示图片
    uint32_t imgAddr;                       //是否显示图片
    void (*clickFunc)(void);                //子项点击回调函数
}MenuItem;


//菜单描述结构体
typedef struct __MenuObj
{
    MenuType type;                          //菜单类型(是列表还是卡片)
    void (*DrawCardFunc)(void);             //卡片绘制函数(当卡片有效)
    void (*SlidFunc)(SlidDir dir);          //滑动操作回调函数(当卡片有效)
    uint8_t itemNum;                        //列表子项数量(当列表有效)
    MenuItem *items;                        //列表子项数组(当列表有效)
    struct __MenuObj *pre;                  //上级菜单，用于返回键返回上级菜单(列表卡片通用)
}MenuObj;



#endif

