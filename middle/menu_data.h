
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


typedef struct __MenuItem
{
    char *text;
    uint8_t textSize;
    bool showImg;
    uint32_t imgAddr;
    void (*clickFunc)(SlidDir dir);
}MenuItem;


typedef struct __MenuObj
{
    MenuType type;
    void (*DrawCardFunc)(void);
    void (*SlidFunc)(void);
    uint8_t itemNum;
    MenuItem items[];
}MenuObj;



#endif

