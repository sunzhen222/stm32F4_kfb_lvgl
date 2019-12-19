


#include "DrvTouchScreen.h"
#include "stm32f4xx_hal.h"
#include "stdbool.h"

//#define	CHX     0x90
//#define	CHY     0xD0

#define	CHY     0x97
#define	CHX     0xD7

//#define	CHX     0xB8
//#define	CHY     0xC8

extern SPI_HandleTypeDef hspi2;


void TouchScreenIdle(void)
{
    uint8_t temp;
    TouchScreenSpiSel();
    temp = 0x80;
    TouchScreenSpiWrite(&temp, 1);
    TouchScreenSpiDesel();
}

uint32_t TouchScreenSpiWrite(uint8_t *buf, uint32_t len)
{
    
    if(HAL_SPI_Transmit(&hspi2,buf,len,100) == HAL_OK) {
        return 0;
    }
    else {
        return 1;
    }
}


uint32_t TouchScreenSpiRead(uint8_t *buf, uint32_t len)
{
    if(HAL_SPI_Receive(&hspi2,buf,len,100) == HAL_OK) {
        return 0;
    }
    else {
        return 1;
    }
}


void TouchScreenSpiSel(void)
{
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,GPIO_PIN_RESET);
}


void TouchScreenSpiDesel(void)
{
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,GPIO_PIN_SET);
}

uint16_t TouchGetX_Value(void)
{
    uint16_t value = 0;
    uint8_t temp = 0;
    
    TouchScreenSpiSel();
    temp = CHX;
    TouchScreenSpiWrite(&temp, 1);
    TouchScreenSpiRead(&temp, 1);
    value = temp;
    value <<= 8;
    TouchScreenSpiRead(&temp, 1);
    value += temp;
    //value >>= 3;
    
    TouchScreenSpiDesel();
    
    return value;
    
}


uint16_t TouchGetY_Value(void)
{
    uint16_t value = 0;
    uint8_t temp = 0;
    
    TouchScreenSpiSel();
    temp = CHY;
    TouchScreenSpiWrite(&temp, 1);
    TouchScreenSpiRead(&temp, 1);
    value = temp;
    value <<= 8;
    TouchScreenSpiRead(&temp, 1);
    value += temp;
    //value >>= 3;
    
    TouchScreenSpiDesel();
    
    return value;
}


#define TOUCH_GET_COUNT     4

void TouchGetXY_ADC(uint16_t *ValueX,uint16_t *ValueY)
{
	*ValueX = TouchGetX_Value();
	*ValueY = TouchGetY_Value();
}


uint16_t GetPosY(uint16_t ady) //240
{
    uint16_t posY;
    if(ady > 15620) {
        posY = (ady - 15620) / 100 + 120;
    }
    else {
        posY = (ady) / 99;
    }
    
    if(posY > 240) {
        posY = 240;
    }
    
    posY = 240 - posY;
    
    return posY;
}


uint16_t GetPosX(uint16_t adx) //320
{
    uint16_t posX;
    if(adx > 25600) {
        posX = ((adx - 25600) / 49 + 160);
    }
    else {
        posX = (adx) / 126;
    }
    
    if(posX > 320) {
        posX = 320;
    }
    
    return posX;
}


void TouchGetXY_Pos(uint16_t *ValueX,uint16_t *ValueY)
{
    uint16_t tempX,tempY;
    
    TouchGetXY_ADC(&tempX,&tempY);
    
    *ValueX = GetPosX(tempX);
    *ValueY = GetPosY(tempY);
    
    //*ValueX = (tempX);
    //*ValueY = (tempY);
    
    TouchScreenIdle();
}


bool touchpadIsPressed(void)
{
    if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7) == GPIO_PIN_RESET){
        return true;
    }
    else {
        return false;
    }
}

