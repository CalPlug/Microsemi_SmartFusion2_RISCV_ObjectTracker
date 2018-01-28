#ifndef PROC_SUBSYSTEM_HW_PLATFORM_H_
#define PROC_SUBSYSTEM_HW_PLATFORM_H_
/*****************************************************************************
*
*Created by Microsemi SmartDesign  Tue Jan 23 17:25:14 2018
*
*Memory map specification for peripherals in PROC_SUBSYSTEM
*/

/*-----------------------------------------------------------------------------
* CM3 subsystem memory map
* Master(s) for this subsystem: CM3 FABRICTOMSSFIC0_AHB_BRIDGE FABRIC2MSSFIC2 
*---------------------------------------------------------------------------*/
#define MSS_SUBSYSTEM_SB_MSS_0          0x40020800U


/*-----------------------------------------------------------------------------
* CORERISCV_AXI4_0 subsystem memory map
* Master(s) for this subsystem: CORERISCV_AXI4_0 CORERISCV_AXI4_0 
*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
* COREAXITOAHBL_0 subsystem memory map
* Master(s) for this subsystem: COREAXITOAHBL_0 
*---------------------------------------------------------------------------*/
#define MSS_SUBSYSTEM_SB_0              0x60000000U
#define COREUARTAPB_0                   0x70001000U
#define COREPWM_1                       0x70002000U
#define CORETIMER_0                     0x70003000U
#define CORETIMER_1                     0x70004000U
#define COREGPIO_1                      0x70005000U
#define CORESPI_0                       0x70006000U
#define CORETIMER_2                     0x70007000U
#define COREPWM_0                       0x70008000U
#define CORESPI_1                       0x70009000U
#define COREI2C_0                       0x7000A000U


/*-----------------------------------------------------------------------------
* COREAXITOAHBL_1 subsystem memory map
* Master(s) for this subsystem: COREAXITOAHBL_1 
*---------------------------------------------------------------------------*/
#define MSS_SUBSYSTEM_SB_0_MDDR_DDR_AMBA_SLAVE 0x80000000U


#endif /* PROC_SUBSYSTEM_HW_PLATFORM_H_*/
