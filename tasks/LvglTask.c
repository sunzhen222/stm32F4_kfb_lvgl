
#include "lvglTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_hal.h"
#include "DrvLCD.h"
#include "lvgl.h"
#include "lvgl_demo.h"
#include "DrvTouchScreen.h"

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];             /*Declare a buffer for 10 lines*/

uint8_t lv_init_ok = 0;

void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    LCD_Draw(area->x1,area->y1,area->x2,area->y2,(uint16_t *)color_p);
    lv_disp_flush_ready(disp_drv); /* Indicate you are ready with the flushing*/
}

bool my_touchpad_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;
    /*Save the state and save the pressed coordinate*/
    data->state = touchpadIsPressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    if(data->state == LV_INDEV_STATE_PR) TouchGetXY_Pos(&last_x, &last_y);
    /*Set the coordinates (if released use the last pressed coordinates)*/
    data->point.x = last_x;
    data->point.y = last_y;
    return false; /*Return `false` because we are not buffering and no more data to?
    ,!read*/
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

lv_obj_t *testText = NULL;

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
    
    
    lv_indev_drv_t indev_drv; /*Descriptor of a input device driver*/
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER; /*Touch pad is a pointer-like device*/
    indev_drv.read_cb = my_touchpad_read; /*Set your driver function*/
    lv_indev_drv_register(&indev_drv); /*Finally register the driver*/
    
    
    demo_create();
    //drawTest();
    
    testText = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_pos(testText, 100, 100);
    lv_label_set_text(testText, "text");
    
    
    lv_obj_t *ul;
    ul = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_pos(ul, 20, 20);
    lv_label_set_text(ul, "0");

    lv_obj_t *ur;
    ur = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_pos(ur, 300, 20);
    lv_label_set_text(ur, "0");

    lv_obj_t *dl;
    dl = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_pos(dl, 20, 220);
    lv_label_set_text(dl, "0");

    lv_obj_t *dr;
    dr = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_pos(dr, 300, 220);
    lv_label_set_text(dr, "0");

    
    lv_init_ok = 1;
    while(1) {
        lv_task_handler();
        lv_tick_inc(5);
        vTaskDelay(5);
    }
}

void SetTestText(char* str)
{
    if(testText == NULL) {
        return ;
    }
    
    lv_label_set_text(testText, str);
}




