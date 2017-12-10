/*******************************************************************************
 * (c) Copyright 2016-2017 Microsemi Corporation.  All rights reserved.
 *
 * Platform definitions
 * Version based on requirements of RISCV-HAL
 *
 * SVN $Revision: 9030 $
 * SVN $Date: 2017-04-23 15:17:47 +0530 (Sun, 23 Apr 2017) $
 */
 /*=========================================================================*//**
  @mainpage Sample file detailing how hw_platform.h should be constructed for 
    the CoreRISCV_AXI4

    @section intro_sec Introduction
    The  hw_platform.h is to be located in the project root directory.
    Currently this file must be hand crafted when using the CoreRISCV_AXI4.
    
    You can use this file as sample.
    Rename this file from sample_hw_platform.h to hw_platform.h and store it in
    the root folder of your project. Then customize it per your HW design.

    @section driver_configuration Project configuration Instructions
    1. Change SYS_CLK_FREQ define to frequency of CoreRISCV_AXI4 clock
    2  Add all other core BASE addresses
    3. Add peripheral Core Interrupt to CoreRISCV_AXI4 interrupt mappings
    4. Define MSCC_STDIO_UART_BASE_ADDR if you want a CoreUARTapb mapped to STDIO
*//*=========================================================================*/

#ifndef HW_PLATFORM_H
#define HW_PLATFORM_H

/***************************************************************************//**
 * Soft-processor clock definition
 * This is the only clock brought over from the CoreRISCV_AXI4 Libero design.
 */
#define SYS_CLK_FREQ                    66000000UL

/***************************************************************************//**
 * Non-memory Peripheral base addresses
 * Format of define is:
 * <corename>_<instance>_BASE_ADDR
 */
#define COREUARTAPB0_BASE_ADDR          0x70001000UL
#define COREGPIO_BASE_ADDR              0x70002000UL
#define COREPWM1_BASE_ADDR              0x70002000UL
#define CORETIMER0_BASE_ADDR            0x70003000UL
#define CORETIMER1_BASE_ADDR            0x70004000UL
#define COREGPIO_OUT_BASE_ADDR          0x70005000UL
#define FLASH_CORE_SPI_BASE             0x70006000UL
//#define CORE16550_BASE_ADDR             0x70007000UL
#define CORETIMER2_BASE_ADDR            0x70007000UL
#define COREPWM_BASE_ADDR               0x70008000UL
#define CORE_SPI1_BASE_ADDRESS          0x70009000UL
//#define COREGPIO_0_BASE_ADDR			0x7000A000UL
/***************************************************************************//**
 * Peripheral Interrupts are mapped to the corresponding CoreRISCV_AXI4 interrupt
 * from the Libero design.
 * There can be up to 31 external interrupts (IRQ[30:0] pins) on the CoreRISCV_AXI4
 * The CoreRISCV_AXI4 external interrupts are defined in the riscv_CoreplexE31.h
 * These are of the form
 * typedef enum
{
    NoInterrupt_IRQn = 0,
    External_1_IRQn  = 1,
    External_2_IRQn  = 2,
    .
    .
    .
    External_31_IRQn = 31
} IRQn_Type;
 
 The interrupt 0 on RISC-V processor is not used. The pin IRQ[0] should map to
 External_1_IRQn likewise IRQ[30] should map to External_31_IRQn
 * Format of define is:
 * <corename>_<instance>_<core interrupt name>
 */

#define TIMER0_IRQn                     External_30_IRQn
#define TIMER1_IRQn                     External_31_IRQn

/****************************************************************************
 * Baud value to achieve a 115200 baud rate with a 83MHz system clock.
 * This value is calculated using the following equation:
 *      BAUD_VALUE = (CLOCK / (16 * BAUD_RATE)) - 1
 *****************************************************************************/
#define BAUD_VALUE_115200   44

/***************************************************************************//**
 * User edit section- Edit sections below if required
 */
#ifdef MSCC_STDIO_THRU_CORE_UART_APB
/*
 * A base address mapping for the STDIO printf/scanf mapping to CortUARTapb
 * must be provided if it is being used
 *
 * e.g. #define MSCC_STDIO_UART_BASE_ADDR COREUARTAPB1_BASE_ADDR
 */
#define MSCC_STDIO_UART_BASE_ADDR COREUARTAPB0_BASE_ADDR

#ifndef MSCC_STDIO_UART_BASE_ADDR
#error MSCC_STDIO_UART_BASE_ADDR not defined- e.g. #define MSCC_STDIO_UART_BASE_ADDR COREUARTAPB1_BASE_ADDR
#endif

#ifndef MSCC_STDIO_BAUD_VALUE
/*
 * The MSCC_STDIO_BAUD_VALUE define should be set in your project's settings to
 * specify the baud value used by the standard output CoreUARTapb instance for
 * generating the UART's baud rate if you want a different baud rate from the
 * default of 115200 baud
 */
#define MSCC_STDIO_BAUD_VALUE           115200
#endif  /*MSCC_STDIO_BAUD_VALUE*/

#endif  /* end of MSCC_STDIO_THRU_CORE_UART_APB */
/*******************************************************************************
 * End of user edit section
 */
#endif /* HW_PLATFORM_H */


