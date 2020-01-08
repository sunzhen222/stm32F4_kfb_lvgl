

#include "IdleTask.h"
#include "FreeRTOS.h"
#include "lvgl.h"

extern uint8_t lv_init_ok;

void vApplicationIdleHook(void)
{
    if(lv_init_ok)
    {
        //lv_task_handler();
    }
}

