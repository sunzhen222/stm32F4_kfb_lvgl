
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
void TouchGetXY_Pos(uint16_t *ValueX,uint16_t *ValueY);
bool touchpadIsPressed(void);

#endif


