
#ifndef _MENU_CTRL_H
#define _MENU_CTRL_H

#include "stdint.h"
#include "menu_data.h"

/*
* ��ʼ���˵����ݣ�Ϊ�����㼶�Ĳ˵��ṹ�帳ֵ��ע��ص�������
*/
void MenuInit(void);

/*
* �����Ӳ˵�������Ļ�����Ӳ˵���UI���档
* menuObj���Ӳ˵��Ľṹ��ָ�롣
* ����ֵ��0-�ɹ�����������ʧ�ܴ����룬�����������
*/
uint8_t EnterSubMenu(MenuObj *menuObj);

/*
* �����ϼ��˵�������Ļ�����ϼ��˵���UI����
* ����ֵ��0-�ɹ�����������ʧ�ܴ����룬�����������
*/
uint8_t BackPreMenu(void);

/*
* ����homeĿ¼������Ļ�����ϼ��˵���UI����
* ����ֵ��0-�ɹ�����������ʧ�ܴ����룬�����������
*/
uint8_t GotoHomeMenu(void);


/*
* ע����ƿ�Ƭ�Ļص�������
* ���ص�������ַ����menuObj�ṹ��ָ���У���DrawMenuʱ�����menuObj����Ϊ��Ƭʱִ�С�
* menuObj����ע����ƿ�Ƭ�Ĳ˵��ṹ��ָ�롣
* DrawCardFunc����ע��Ļ��ƻص�������
* ע�⣺�ص���������ʾ�㶨��ʵ�֡�
*/
void RegisterDrawCardFunc(MenuObj *menuObj,void (*DrawCardFunc)(void));


/*
* ע�� �˵�UI�����¼��Ļص�������
* ���ص�������ַ����menuObj�ṹ��ָ���е�SlidFunc��
* ����ʾ��ͨ��littlevGL��⵽�����¼�֮�󣬻�ͨ����ǰUI�ṹ��ָ�������ע��
* �Ļ����ص�������
* menuObj����ע�Ử���¼��Ĳ˵��ṹ��ָ�롣
* SlidEvent����ע��Ļ����¼��ص��������ú����Ĳ���Ϊ��������
* ע�⣺�ص������ڿ��Ʋ㶨��ʵ�֡�
*/
void RegisterMenuSlidEvent(MenuObj *menuObj, void (*SlidEvent)(SlidDir));


/*
* ע�� List��ĳ��Item����Ļص�������
* ���ص�������ַ����menuItem�ṹ��ָ���е�clickFunc��
* ����ʾ��ͨ��littlevGL��⵽ĳ��Item�ĵ���¼�֮�󣬻�ͨ����ǰUI�ṹ��ָ��
* ������ע���Item����Ļص�������
* menuItem����ע�����¼����б�����ṹ�塣
* ItemClickEvent����ע��ĵ���¼��ص�������
* ע�⣺�ص������ڿ��Ʋ㶨��ʵ�֡�
*/
void RegisterListItemClickEvent(MenuItem *menuItem, void (*ItemClickEvent)(void));


/*
* ע�� Card��������¼��Ļص�����
* ���ص�������ַ����menuItem�ṹ��ָ���е�XXX
* ����ʾ��ͨ��littlevGL��⵽ĳ�������ĵ���¼�֮�󣬻�ͨ����ǰUI�ṹ��ָ�����
* ��ע���Card��������Ļص�����
*/
void RegisterCardEvent(MenuObj *menuObj, void (*CardEvent)(uint8_t));





#endif



