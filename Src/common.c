
#include "common.h"
#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "soft_fifo.h"

char CHECK_VALID[] = "86705F2CE7E9DF6A6527327C9672E70D";
char VERSION[]  = "v0.10";
char BUILD[]    = "v0.10_20191008_1";


uint8_t version_major = 0;
uint8_t version_minor = 1;
uint8_t version_build = 5;

extern uint8_t uart1_rx_byte;
SOFT_FIFO uart1_fifo;
SOFT_FIFO uart3_fifo;


extern UART_HandleTypeDef huart1;


//void print_main_message(void)
//{
//    DBG_PRINTF("#---------------------------------\r\n");
//    DBG_PRINTF("#---------------------------------\r\n");
//    DBG_PRINTF("#version=%s,build=%s\r\n",VERSION,BUILD);
//    DBG_PRINTF("#build time:%s,%s\r\n",__DATE__,__TIME__);
//    DBG_PRINTF("#---------------------------------\r\n");
//
//}




void printf_init(void)
{
    fifo_init(&uart1_fifo);
}


int fputc(int c, FILE * f)
{
    uint8_t ch = c;
    uart1_send_data(&ch,1);//·¢ËÍ´®¿Ú
    return c;
}

void uart1_tx_callback(void)
{
    if(fifo_read(&uart1_fifo,&uart1_rx_byte,1) == 0)
        return;
    HAL_UART_Transmit_IT(&huart1,&uart1_rx_byte,1);
}



void uart1_send_data(uint8_t *data,uint16_t length)
{
    __disable_irq();
    fifo_write(&uart1_fifo,data,length);
    __enable_irq();
    if(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX_RX)
    {
        return ;
    }
    fifo_read(&uart1_fifo,&uart1_rx_byte,1);
    //__enable_irq();
    HAL_UART_Transmit_IT(&huart1,&uart1_rx_byte,1);
    //
}

