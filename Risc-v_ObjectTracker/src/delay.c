/*
 * delay.c
 *
 *  Created on: Nov 6, 2017
 *      Author: Yutian Ren
 * Descriptions available in delay.h file
 */
#include "delay.h"
void delay_ms(float time_ms)
{
    volatile int counter = 0;

    while ( counter < (DELAY_COUNT*time_ms) )
    {
        counter++;
    }
}
void delay_us(float time_us)
{
    volatile float counter = 0;

    while ( counter < (DELAY_COUNT_us*time_us) )
    {
        counter++;
    }
}
