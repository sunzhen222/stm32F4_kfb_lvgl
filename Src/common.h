
#ifndef _COMMON_H
#define _COMMON_H

#include "stdint.h"

//#define VERSION     "V0.10"
//#define BUILD       "V0.10_20190105_test"

#define __DEBUG

#ifdef __DEBUG
#define DBG_PRINTF(...)         (printf(__VA_ARGS__))
#else
#define DBG_PRINTF(...)
#endif


extern char CHECK_VALID[];
extern char VERSION[];
extern char BUILD[];

extern uint8_t version_major;
extern uint8_t version_minor;
extern uint8_t version_build;

typedef struct __DEV_INFO
{
    char device_id[100];

    

}DEV_INFO;


void print_main_message(void);
void printf_init(void);

void uart1_tx_callback(void);
void uart1_send_data(uint8_t *data,uint16_t length);

#endif

