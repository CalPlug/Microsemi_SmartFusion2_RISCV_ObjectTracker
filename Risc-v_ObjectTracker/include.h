/*
 * include.h
 *
 *  Created on: Nov 6, 2017
 *      Author: REN
 */

#ifndef INCLUDE_H_
#define INCLUDE_H_

#include "hw_platform.h"
#include "drivers/CoreGPIO/core_gpio.h"
#include "drivers/CoreUARTapb/core_uart_apb.h"
#include "drivers/CoreSPI/core_spi.h"
#include "drivers/CoreTimer/core_timer.h"
#include "drivers/CorePWM/core_pwm.h"
#include "riscv_hal.h"
#include "MicrosemiTFTDriver/Microsemi_Adafruit_ILI9341.h"
#include "MicrosemiTSDriver/Microsemi_Adafruit_STMPE610.h"
#include "src/delay.h"
#include "src/pixy.h"

#define PWM_PRESCALE       800
#define PWM_PERIOD         100
#define Load_value         7000

#define duty_cycle_13_steer 100//real duty_cycle = this value/PWM_PERIOD *100%
#define duty_cycle_24_steer 100
#define duty_cycle_13_search 100
#define duty_cycle_24_search 100
#define duty_cycle_move 70

#define body_x 159.5; // image size is 319*319
#define body_y 132;
#define standard_size 19000
#define MoveThreshold_postive 5000
#define MoveThreshold_negative -4000


#endif /* INCLUDE_H_ */
