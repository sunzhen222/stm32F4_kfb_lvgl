


#include "DrvTouchScreen.h"
#include "stm32f4xx_hal.h"


#define	CHX     0x90
#define	CHY     0xD0
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

	//uint16_t i,j,k,x_addata[TOUCH_GET_COUNT],y_addata[TOUCH_GET_COUNT];
    //
	//for(i=0;i<TOUCH_GET_COUNT;i++)					//采样4次.
	//{
	//	x_addata[i] = TouchGetX_Value();   //保存X坐标的数据
	//	y_addata[i] = TouchGetY_Value();   //保存X坐标的数据
	//}
    ////交换法排序的程序最清晰简单，每次用当前的元素同其后的元素比较并交换
	//for(i=0;i<TOUCH_GET_COUNT-1;i++)
	//{
    //	for(j=i+1;j<TOUCH_GET_COUNT;j++)
    //	{
    //       if(x_addata[j] > x_addata[i])
    //        {
    //            k = x_addata[j];
    //            x_addata[j] = x_addata[i];
    //            x_addata[i] = k;
    //        }
    //     }
    //}
    ////交换法排序的程序最清晰简单，每次用当前的元素同其后的元素比较并交换
	//for(i=0;i<TOUCH_GET_COUNT-1;i++)
	//{
    //	for(j=i+1;j<TOUCH_GET_COUNT;j++)
    //	{
    //       if(y_addata[j] > y_addata[i])
    //        {
    //            k = y_addata[j];
    //            y_addata[j] = y_addata[i];
    //            y_addata[i] = k;
    //        }
    //     }
    //}
    //
	//*ValueX=(x_addata[1] + x_addata[2]) >> 1;
	//*ValueY=(y_addata[1] + y_addata[2]) >> 1;
    
	*ValueX = TouchGetX_Value();
	*ValueY = TouchGetY_Value();
}


uint16_t GetPosY(uint16_t adx) //240
{
    uint16_t sx=0;
    int r = adx - 360;
    r *= 240;
    sx=r / (4096 - 800);
    if (sx<=0 || sx>240)
    return 0;
    return sx;
}

/*=====================================================================*/
uint16_t GetPosX(uint16_t ady) //320
{
    uint16_t sy = 0;
    int r = ady - 360;
    r *= 320;
    sy= r/(4096 - 680);
    if (sy<=0 || sy>320)
    return 0;
    return sy;
}


void TouchGetXY_Pos(uint16_t *ValueX,uint16_t *ValueY)
{
    uint16_t tempX,tempY;
    
    TouchGetXY_ADC(&tempX,&tempY);
    
    //*ValueX = GetPosX(tempX);
    //*ValueY = GetPosY(tempY);
    
    *ValueX = (tempX);
    *ValueY = (tempY);
    
    TouchScreenIdle();
}
