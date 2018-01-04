/*
 * delay.c
 *
 *  Created on: Nov 6, 2017
 *      Author: REN
 */
#include "delay.h"
void delay_ms(int time_ms)
{
    volatile int counter = 0;

    while ( counter < (DELAY_COUNT*time_ms) )
    {
        counter++;
    }
}
void delay_us(int time_us)
{
    volatile int counter = 0;

    while ( counter < (DELAY_COUNT_us*time_us) )
    {
        counter++;
    }
}

