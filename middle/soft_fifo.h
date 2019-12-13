#ifndef _SOFT_FIFO_H
#define _SOFT_FIFO_H


#include "stdbool.h"
#include "stdint.h"
#include "string.h"


#define FIFO_LENGTH     2048

typedef struct __SOFT_FIFO
{
    volatile uint8_t data[FIFO_LENGTH];
    volatile uint16_t addr_in;
    volatile uint16_t addr_out;
    volatile uint16_t deep_now;
}SOFT_FIFO;


void fifo_init(SOFT_FIFO *fifo);
uint8_t fifo_write(SOFT_FIFO *fifo,uint8_t *data,uint16_t length);
uint8_t fifo_read(SOFT_FIFO *fifo,uint8_t *data,uint16_t max_length);
bool fifo_empty(SOFT_FIFO *fifo);
    

#endif

