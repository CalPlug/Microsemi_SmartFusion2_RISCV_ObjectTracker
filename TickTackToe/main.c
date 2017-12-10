/*******************************************************************************
 * (c) Copyright 2016 Microsemi SoC Products Group. All rights reserved.
 *
 *	Tick Tack Toe program
 *	This project is targeted at the RISC-V design running on the M2S025
 *	development board and Adafruit Arduino TFT screen linked in  the read me.
 *
 * SVN $Revision: $
 * SVN $Date: $
 */
//#include <unistd.h>

#include "include.h"

/*
 * CoreGPIO instance data.
 */
gpio_instance_t g_gpio;

/*-----------------------------------------------------------------------------
 * UART instance data.
 */
UART_instance_t g_uart;

/******************************************************************************
 * PLIC instance data.
 *****************************************************************************/
//plic_instance_t g_plic;

/******************************************************************************
 * GPIO instance data.
 *****************************************************************************/
gpio_instance_t g_gpio;
gpio_instance_t g_gpio_in;

/******************************************************************************
 * Timer 0 instance data.
 *****************************************************************************/
timer_instance_t g_timer0;
//timer_instance_t g_timer1;

/******************************************************************************
 * CoreSPI 0 instance data.
 *****************************************************************************/
spi_instance_t g_core_spi0;
spi_instance_t g_core_spi1;

/******************************************************************************
 * CorePWM 0 instance data.
 *****************************************************************************/
pwm_instance_t g_pwm_0;
pwm_instance_t g_pwm_1;

uint32_t duty_cycle_13;//real duty_cycle = this value/PWM_PERIOD *100%
uint32_t duty_cycle_24;

/******************************************************************************
 *
 *****************************************************************************/
void init(void);
void search (void);
void stop(void);
void steer(int dir);
void move(int dir);
void servo( uint16_t pan,uint16_t tilt);
/*-------------------------------------------------------------------------*//**
 *
 * main() function.
 */

int main()
{

    init();
    //Block *block;
    int dir = 0; // dir =1 => right, dir =0 => left
    int dx = 0;
    int size = 0;
    int d_size = 0;
    uint16_t block[6];
    uint16_t pan = 750;
    uint16_t tilt = 750;
    int dx_body =0;

	while(1)
	{
		/**
		 * ultrasonic sensor, incomplete
		//while (!(GPIO_get_inputs( &g_gpio_in) == 1));
		//TMR_start( &g_timer0);
		//while (!(GPIO_get_inputs( &g_gpio_in) == 0));
		//TMR_stop( &g_timer0);
		//distance = (Load_value - TMR_current_value( &g_timer0))*85/64453;
		*/

		/**
		 * LCD display
		//LCD_ShowNum( 90, 50, distance, 10,16, &g_core_spi0, &g_gpio);
		//LCD_ShowChar( 90, 10, '1', 24, 0, &g_core_spi0, &g_gpio);//typical font size is 24
		*/

i:		getBlocks( &g_core_spi1,2,block); // 0 sig, 1 x, 2 y, 3 width, 4 height, 5 angle
		if (block[0] == 0x0001 && block[1] <319)
		{
			dx = block[1] - body_x;
			size = block[3]*block[4];
			d_size = size - standard_size;
			pan = pan -0.03*dx*50/9;
			if (pan <250) pan =250;
			else if (pan >1250) pan =1250;
			if (dx >40 || dx< (-40))
			{
				servo(pan,tilt);
				goto i;
			}

			dx_body = pan -750;
			if (dx_body > 0) // left
			{
				dir = 0;
			}
			else if (dx_body < 0) //right
			{
				dir = 1;
			}
			if ( dx_body >50 || dx_body < -50) //30
			{
				steer( dir);
				delay_ms(20); //15
				if (d_size > MoveThreshold_postive)
				{
					move(0);
					delay_ms(15);//1 forward 5000
				}
				else if (d_size < MoveThreshold_negative)
				{
					move(1);
					delay_ms(15);//4000
				}
				else stop();
			}
			else
			{
				if (d_size > MoveThreshold_postive)
				{
					move(0);
					delay_ms(15);//1 forward
				}
				else if (d_size < MoveThreshold_negative)
				{
					move(1);
					delay_ms(15);//4000
				}
				else stop();
			}

		}
		else
		{
			stop();
		}
	}
	return 0;

}

/*------------------------------------------------------------------------------
 * Count the number of elapsed milliseconds (SysTick_Handler is called every
 * 10mS so the resolution will be 10ms). Rolls over every 49 days or so...
 *
 * Should be safe to read g_10ms_count from elsewhere.
 */
void SysTick_Handler( void )
{

}

void init( void )
{
	/**************************************************************************
	 * PWM_init
	 * Real_PERIOD = SYS_CLOCK_PERIOD * ( PWM_prescale + 1 ) * ( PWM_period + 1 )
	 * system_clock = 66MHz
	 *************************************************************************/
	PWM_init(&g_pwm_0, COREPWM_BASE_ADDR, PWM_PRESCALE, PWM_PERIOD);

	PWM_enable(&g_pwm_0, PWM_1);
	PWM_enable(&g_pwm_0, PWM_2);
	PWM_enable(&g_pwm_0, PWM_3);
	PWM_enable(&g_pwm_0, PWM_4);

	PWM_set_duty_cycle( &g_pwm_0, PWM_1, 0 );
	PWM_set_duty_cycle( &g_pwm_0, PWM_2, 0 );
	PWM_set_duty_cycle( &g_pwm_0, PWM_3, 0 );
	PWM_set_duty_cycle( &g_pwm_0, PWM_4, 0 );

	// servo init
	// 50Hz center:7.5% =750; range: 250-1250 = 0-180 degree
	PWM_init(&g_pwm_1, COREPWM1_BASE_ADDR, 132, 10000);
	PWM_enable(&g_pwm_1, PWM_1);
	PWM_enable(&g_pwm_1, PWM_2);
	PWM_set_duty_cycle( &g_pwm_1, PWM_1, 750 );
	PWM_set_duty_cycle( &g_pwm_1, PWM_2, 750 );

	/**************************************************************************
	 * Enable and Dir init
	 *************************************************************************/
	GPIO_init( &g_gpio, COREGPIO_OUT_BASE_ADDR, GPIO_APB_32_BITS_BUS );
	GPIO_set_outputs(&g_gpio, 0);
	GPIO_config( &g_gpio, GPIO_5, GPIO_OUTPUT_MODE); //DIR 13
	GPIO_config( &g_gpio, GPIO_6, GPIO_OUTPUT_MODE); //DIR 24
	GPIO_config( &g_gpio, GPIO_7, GPIO_OUTPUT_MODE); //PWM_EN

	/**************************************************************************
	 * ultrasonic init
	 * GPIO_4 Trig; GPIO_3 Echo
	 * CHANGE GPIO PORT
	 *************************************************************************/
/*	GPIO_config( &g_gpio, GPIO_3, GPIO_OUTPUT_MODE);
	GPIO_set_output( &g_gpio, GPIO_3, 0 );
	GPIO_config( &g_gpio, GPIO_4, GPIO_INPUT_MODE);
	GPIO_set_output( &g_gpio, GPIO_4, 0 );*/
	//GPIO_init( &g_gpio_in, COREGPIO_IN_BASE_ADDR, GPIO_APB_32_BITS_BUS );
	//GPIO_config( &g_gpio_in, GPIO_0, GPIO_INPUT_MODE);
	/**************************************************************************
	 * CoreTimer init
	 * prescaler_512
	 * 128.9kHz
	 *************************************************************************/
	TMR_init( &g_timer0, CORETIMER0_BASE_ADDR, TMR_CONTINUOUS_MODE, 8, Load_value);

	/**************************************************************************
	 * TFT init
	 * DO NOT CHANGE TFT GPIO
	 *************************************************************************/

    GPIO_config( &g_gpio, GPIO_0, GPIO_OUTPUT_MODE); // Data Command Signal
	GPIO_set_output( &g_gpio, GPIO_0, 1 ); // Data Command Signal
	GPIO_config( &g_gpio, GPIO_2, GPIO_OUTPUT_MODE); // reset Signal
	GPIO_set_output( &g_gpio, GPIO_2, 1 ); // reset Signal
	GPIO_config( &g_gpio, GPIO_1, GPIO_OUTPUT_MODE); // Chip Select Signal TS
	GPIO_set_output( &g_gpio, GPIO_1, 1 ); // Chip Select Signal TS
    /**************************************************************************
      * Initialize CoreSPI0  in master mode.
      *************************************************************************/
	SPI_init(&g_core_spi0, CORE_SPI0_BASE_ADDRESS,8);//for LCD
	SPI_configure_master_mode(&g_core_spi0);

	SPI_init( &g_core_spi1, CORE_SPI1_BASE_ADDRESS, 8 ); //for camera
	SPI_configure_master_mode( &g_core_spi1 );

	/**************************************************************************
      * Initialize TFT Screen.
      *************************************************************************/
	TFT_begin( &g_core_spi0, &g_gpio); // initialize the TFT Screen
	for(volatile uint16_t delay0 = 0; delay0 < 0xFF; delay0++); // Delay

	/**************************************************************************
      * Initialize Touch Screen (TS).
      *************************************************************************/
	//TS_begin(&g_core_spi0, &g_gpio); // initialize the touch screen
	//for(volatile uint16_t delay1 = 0; delay1 < 0xFF; delay1++); // Delay
	//uint16_t baud_value;
	//baud_value = (66000000 /(19200 * 16)) - 1;
	//UART_init( &g_uart,COREUARTAPB0_BASE_ADDR,baud_value,(DATA_8_BITS | NO_PARITY));
}


// This function is to search for the object once the object exceeds the image.
void search (void)
{
	GPIO_set_output( &g_gpio, GPIO_5, 1 );//dir = 0, backward; dir =1, forward
	GPIO_set_output( &g_gpio, GPIO_6, 0 );
	PWM_set_duty_cycle( &g_pwm_0, PWM_1, duty_cycle_13_search );
	PWM_set_duty_cycle( &g_pwm_0, PWM_2, duty_cycle_24_search );
	PWM_set_duty_cycle( &g_pwm_0, PWM_3, duty_cycle_13_search );
	PWM_set_duty_cycle( &g_pwm_0, PWM_4, duty_cycle_24_search );
}

// car body
void steer ( int dir)
{
	if (dir == 1) // right
	{
		GPIO_set_output( &g_gpio, GPIO_5, 1 );
		GPIO_set_output( &g_gpio, GPIO_6, 0 );
		PWM_set_duty_cycle( &g_pwm_0, PWM_1, duty_cycle_13_steer );
		PWM_set_duty_cycle( &g_pwm_0, PWM_2, duty_cycle_24_steer );
		PWM_set_duty_cycle( &g_pwm_0, PWM_3, duty_cycle_13_steer );
		PWM_set_duty_cycle( &g_pwm_0, PWM_4, duty_cycle_24_steer );
	}
	else if (dir == 0) //left
	{
		GPIO_set_output( &g_gpio, GPIO_5, 0 );
		GPIO_set_output( &g_gpio, GPIO_6, 1 );
		PWM_set_duty_cycle( &g_pwm_0, PWM_1, duty_cycle_13_steer );
		PWM_set_duty_cycle( &g_pwm_0, PWM_2, duty_cycle_24_steer );
		PWM_set_duty_cycle( &g_pwm_0, PWM_3, duty_cycle_13_steer );
		PWM_set_duty_cycle( &g_pwm_0, PWM_4, duty_cycle_24_steer );
	}
}

void stop(void)
{
	PWM_set_duty_cycle( &g_pwm_0, PWM_1, 0 );
	PWM_set_duty_cycle( &g_pwm_0, PWM_2, 0 );
	PWM_set_duty_cycle( &g_pwm_0, PWM_3, 0 );
	PWM_set_duty_cycle( &g_pwm_0, PWM_4, 0 );

}

// motor control: moving forward or backward
void move(int dir)
{
	if (dir == 1) // forward
	{
		GPIO_set_output( &g_gpio, GPIO_5, 1 );
		GPIO_set_output( &g_gpio, GPIO_6, 1 );
		PWM_set_duty_cycle( &g_pwm_0, PWM_1, duty_cycle_move );
		PWM_set_duty_cycle( &g_pwm_0, PWM_2, duty_cycle_move );
		PWM_set_duty_cycle( &g_pwm_0, PWM_3, duty_cycle_move );
		PWM_set_duty_cycle( &g_pwm_0, PWM_4, duty_cycle_move );
	}
	else if (dir == 0) //backward
	{
		GPIO_set_output( &g_gpio, GPIO_5, 0 );
		GPIO_set_output( &g_gpio, GPIO_6, 0 );
		PWM_set_duty_cycle( &g_pwm_0, PWM_1, duty_cycle_move );
		PWM_set_duty_cycle( &g_pwm_0, PWM_2, duty_cycle_move );
		PWM_set_duty_cycle( &g_pwm_0, PWM_3, duty_cycle_move );
		PWM_set_duty_cycle( &g_pwm_0, PWM_4, duty_cycle_move );
	}
}

// servo control function
void servo( uint16_t pan,uint16_t tilt)
{
	PWM_set_duty_cycle( &g_pwm_1, PWM_1, pan ); //horizontal
	PWM_set_duty_cycle( &g_pwm_1, PWM_2, tilt );//vertical
}
