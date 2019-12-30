
#ifndef _DRV_TOUCHSCREEN_H
#define _DRV_TOUCHSCREEN_H

#include "stdint.h"
#include "stdbool.h"

void TouchScreenIdle(void);
uint32_t TouchScreenSpiWrite(uint8_t *buf, uint32_t len);
uint32_t TouchScreenSpiRead(uint8_t *buf, uint32_t len);
void TouchScreenSpiSel(void);
void TouchScreenSpiDesel(void);
uint16_t TouchGetX_Value(void);
uint16_t TouchGetY_Value(void);
void TouchGetXY_ADC(uint16_t *ValueX,uint16_t *ValueY);




/*
* Touch pad初始化
*/
void TouchPadInit(void);



/*
* 获取touch pad的按下坐标。
* *ValueX：存入按下的X坐标。
* *ValueY：存入按下的Y坐标。
* 返回值，0-无按下，1-正常按下。
*/
uint8_t TouchPadGetPos(uint16_t *ValueX,uint16_t *ValueY);




/*
* Touch key初始化
*/
void TouchKeyInit(void);


/*
* Touch key初始化
*/
void TouchKeyInit(void);







void TouchGetXY_Pos(uint16_t *ValueX,uint16_t *ValueY);



bool touchpadIsPressed(void);



#endif


