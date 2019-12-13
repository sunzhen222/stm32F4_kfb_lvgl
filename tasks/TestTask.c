

#include "TestTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_hal.h"
#include "DrvLCD.h"

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
    
    
    while(1) {
        vTaskDelay(1000);
        HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);
    }
}

