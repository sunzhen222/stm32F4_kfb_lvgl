
#include "lvglTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_hal.h"
#include "DrvLCD.h"
#include "lvgl.h"
#include "lvgl_demo.h"

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];             /*Declare a buffer for 10 lines*/


void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    LCD_Draw(area->x1,area->y1,area->x2,area->y2,(uint16_t *)color_p);
    lv_disp_flush_ready(disp_drv); /* Indicate you are ready with the flushing*/
}


void drawTest(void)
{
    uint16_t temp_color[1200];
    
    for(uint32_t ii=0;ii<1200;ii++)
    {
        temp_color[ii] = LCD_COLOR_BLUE;
    }
    LCD_Draw(100,50,120,100,temp_color);
}

void LvglTask(void *pvParameters)
{
    vTaskDelay(500);
    lv_init();
    LCD_Init();
    LCD_Clear(LCD_COLOR_BLACK);
    
    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);
    lv_disp_drv_t disp_drv;                             /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                        /*Basic initialization*/
    disp_drv.flush_cb = my_disp_flush;                  /*Set your driver function*/
    disp_drv.buffer = &disp_buf;                        /*Assign the buffer to the display*/
    lv_disp_drv_register(&disp_drv);                    /*Finally register the driver*/
    
    
    demo_create();
    //drawTest();
    //lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
    //
    //lv_obj_set_pos(btn1, 100, 100);
    //lv_obj_set_size(btn1, 100, 50);
    //
    //lv_obj_t *label1 = lv_label_create(btn1, NULL);
    //lv_label_set_text(label1, "button");
    
    
    
    while(1) {
        lv_task_handler();
        lv_tick_inc(5);
        vTaskDelay(5);
    }
}






