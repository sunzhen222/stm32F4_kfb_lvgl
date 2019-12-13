#include "soft_fifo.h"


void fifo_init(SOFT_FIFO *fifo)
{
    memset(fifo,0,sizeof(SOFT_FIFO));
}

uint8_t fifo_write(SOFT_FIFO *fifo,uint8_t *data,uint16_t length)
{
    uint16_t ii = 0;
    
    __disable_irq();

    if((fifo->deep_now + length) > FIFO_LENGTH)
    {
        __enable_irq();
        return 0;
    }
    fifo->deep_now += length;

    for(ii=0;ii<length;ii++)
    {
        fifo->data[fifo->addr_in] = data[ii];
        fifo->addr_in = fifo->addr_in + 1;
        if(fifo->addr_in >= FIFO_LENGTH)
        {
            fifo->addr_in = 0;
        }
    }
    __enable_irq();
    return ii;
}


uint8_t fifo_read(SOFT_FIFO *fifo,uint8_t *data,uint16_t max_length)
{
    uint16_t ii = 0;

    __disable_irq();
    //if(fifo->deep_now < max_length)
    //{
    //    return 0;
    //}
    //fifo->deep_now -= max_length;
    
    memset(data,0,max_length);
    
    for(ii=0;ii<max_length;ii++)
    {
        //if(fifo->addr_in == fifo->addr_out)
        //{
        //    break;
        //}
        if(fifo->deep_now == 0)
        {
            //fifo->addr_in = 0;
            //fifo->addr_out = 0;
            break;
        }
        data[ii] = fifo->data[fifo->addr_out];
        fifo->addr_out = fifo->addr_out + 1;
        fifo->deep_now--;
        if(fifo->addr_out >= FIFO_LENGTH)
        {
            fifo->addr_out = 0;
        }
    }
    __enable_irq();
    return ii;
}


bool fifo_empty(SOFT_FIFO *fifo)
{
    if(fifo->addr_in == fifo->addr_out)
        return true;
    else
        return false;
}


