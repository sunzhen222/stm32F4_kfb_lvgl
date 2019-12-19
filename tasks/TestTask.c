

#include "TestTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_hal.h"
#include "DrvLCD.h"
#include "stdio.h"
#include "lvglTask.h"
#include "DrvTouchScreen.h"

void TestTask(void *pvParameters)
{
    //vTaskDelay(500);
    //LCD_Init();
    //
    //while(1) {
    //    LCD_Clear(LCD_COLOR_RED);
    //    vTaskDelay(1000);
    //    LCD_Clear(LCD_COLOR_GREEN);
    //    vTaskDelay(1000);
    //    LCD_Clear(LCD_COLOR_BLUE);
    //    vTaskDelay(1000);
    //    HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);
    //}
    
    
    uint32_t count = 0;
    char testStr[30];
    uint16_t touchX,touchY;
    
    TouchScreenIdle();
    
    while(1) {
        vTaskDelay(100);
        HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7|GPIO_PIN_8);
        //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);
        
        
        //touchX = TouchGetX_Value();
        //touchY = TouchGetY_Value();
        
        //TouchGetXY_Pos(&touchX, &touchY);
        //
        //sprintf(testStr,"touchX=%d\r\ntouchY=%d",touchX,touchY);
        //count++;
        //SetTestText(testStr);
        
        
        //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7));
        
        //if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7) == GPIO_PIN_RESET)
        //{
        //    TouchGetXY_Pos(&touchX, &touchY);
        //    
        //    sprintf(testStr,"touchX=%d\r\ntouchY=%d",touchX,touchY);
        //    SetTestText(testStr);
        //    
        //    //count++;
        //    //sprintf(testStr,"count=%d",count);
        //    //SetTestText(testStr);
        //}
    }
}

