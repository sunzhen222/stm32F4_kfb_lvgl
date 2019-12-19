
#ifndef _MENU_VIEW_H
#define _MENU_VIEW_H

#include "menu_data.h"




/*
* ����menuObj�ṹ��ָ�����ݽ��в˵�������ƣ����Ϳ������б�Ҳ�����ǿ�Ƭ��
* �ɿ��Ʋ���á�
* ע�⣺��������ǿ�Ƭ�Ļ������ƿ�Ƭ�ĺ�����Ҫʹ��RegisterDrawCardFunc��ǰע�ᡣ
* ����ֵ��0-�ɹ�����������ʧ�ܴ����룬�����������
*/
uint8_t DrawMenu(MenuObj *menuObj);

/*
* ��ʾ����
* �ɿ��Ʋ���ã�������Ļ�ʹ������ؿ���
* sw��0����أ�1����
*/
void DisplaySwitch(uint8_t sw);


/*
* ��Ļ��������
* bright��0~10��0�������10����������UX���ԭʼRGBֵ����Ϊ����
*/
void SetBright(uint8_t bright);



void DrawList(MenuObj *menuObj);
void DrawCard(MenuObj *menuObj);

#endif



