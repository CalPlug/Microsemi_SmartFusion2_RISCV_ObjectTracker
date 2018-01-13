/*
 * delay.h
 *
 *  Created on: Nov 6, 2017
 *      Author: REN
 */

#ifndef SRC_DELAY_H_
#define SRC_DELAY_H_

#define DELAY_COUNT		   4720  //DO NOT CHANGE, THIS VALUE IS FOR DELAY_MS
#define DELAY_COUNT_us     0.159

void delay_ms(float time_ms);
/*
 * delay_us function is not precise, please do not use this function
 */
void delay_us(float time_us);



#endif /* SRC_DELAY_H_ */
