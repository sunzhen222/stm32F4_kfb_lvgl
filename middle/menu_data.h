
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


//�б����������ṹ��
typedef struct __MenuItem
{
    char *text;                             //�ı�����
    uint8_t hanSize;                        //�ı������С
    bool showImg;                           //�Ƿ���ʾͼƬ
    uint32_t imgAddr;                       //�Ƿ���ʾͼƬ
    void (*clickFunc)(void);                //�������ص�����
}MenuItem;


//�˵������ṹ��
typedef struct __MenuObj
{
    MenuType type;                          //�˵�����(���б��ǿ�Ƭ)
    void (*DrawCardFunc)(void);             //��Ƭ���ƺ���(����Ƭ��Ч)
    void (*SlidFunc)(SlidDir dir);          //���������ص�����(����Ƭ��Ч)
    uint8_t itemNum;                        //�б���������(���б���Ч)
    MenuItem *items;                        //�б���������(���б���Ч)
    struct __MenuObj *pre;                  //�ϼ��˵������ڷ��ؼ������ϼ��˵�(�б�Ƭͨ��)
}MenuObj;



#endif

