/******************** (C) COPYRIGHT 2012 STMicroelectronics ********************
 * File Name          : lis3dsh_driver.h
 * Author             : MSH Application Team
 * Author             : Abhishek Anand, Fabio Tota
 * Author             : Emerson Moura
 * Version            : $Revision:$
 * Date               : $Date:$
 * Description        : Descriptor Header for lis3dsh_driver.c driver file
 *
 * HISTORY:
 * Date        | Modification                                		| Author
 * 24/06/2011  | Initial Revision                         		   	| Fabio Tota
 * 07/06/2012  | Support for multiple drivers in the same program 	| Abhishek Anand
 * 16/07/2016  | Change original drive from LIS3DH to LIS3DSH 		| Emerson Moura
 *
 ********************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * THIS SOFTWARE IS SPECIFICALLY DESIGNED FOR EXCLUSIVE USE WITH ST PARTS.
 *
 *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIS3DSH_DRIVER__H
#define __LIS3DSH_DRIVER__H

/* Includes ------------------------------------------------------------------*/
#include "../main.h"
#include "../io_macros.h"
#include "../spi.h"
/* Exported types ------------------------------------------------------------*/

//these could change accordingly with the architecture
#ifndef __ARCHDEP__TYPES
#define __ARCHDEP__TYPES

typedef unsigned char u8_t;
typedef unsigned short int u16_t;
typedef short int i16_t;
typedef signed char i8_t;

#endif /*__ARCHDEP__TYPES*/

typedef u8_t LIS3DSH_IntPinConf_t;
typedef u8_t LIS3DSH_Axis_t;
typedef u8_t LIS3DSH_Int1Conf_t;

//define structure
#ifndef __SHARED__TYPES
#define __SHARED__TYPES

typedef enum {
	MEMS_SUCCESS = 0x01, MEMS_ERROR = 0x00
} status_t;

typedef enum {
	MEMS_ENABLE = 0x01, MEMS_DISABLE = 0x00
} State_t;

typedef struct {
	i8_t AXIS_X;
	i8_t AXIS_Y;
	i8_t AXIS_Z;
} LIS3DSH_AxesOffset_t;

typedef struct {
	i16_t AXIS_X;
	i16_t AXIS_Y;
	i16_t AXIS_Z;
} LIS3DSH_AxesRaw_t;

#endif /*__SHARED__TYPES*/

typedef enum {
	LIS3DSH_ODR_POWER_DOWN = 0x00,
	LIS3DSH_ODR_3_126Hz = 0x01,
	LIS3DSH_ODR_6_25Hz = 0x02,
	LIS3DSH_ODR_12_5Hz = 0x03,
	LIS3DSH_ODR_25Hz = 0x04,
	LIS3DSH_ODR_50Hz = 0x05,
	LIS3DSH_ODR_100Hz = 0x06,
	LIS3DSH_ODR_400Hz = 0x07,
	LIS3DSH_ODR_800Hz = 0x08,
	LIS3DSH_ODR_1600Hz = 0x09
} LIS3DSH_ODRMode_t;

typedef enum {
	LIS3DSH_FIFO_BYPASS_MODE = 0x00,
	LIS3DSH_FIFO_MODE = 0x01,
	LIS3DSH_FIFO_STREAM_MODE = 0x02,
	LIS3DSH_FIFO_TRIGGER_MODE = 0x03,
	LIS3DSH_FIFO_DISABLE = 0x04,
} LIS3DSH_FifoMode_t;

typedef enum {
	LIS3DSH_HPM_NORMAL_MODE_RES = 0x00,
	LIS3DSH_HPM_REF_SIGNAL = 0x01,
	LIS3DSH_HPM_NORMAL_MODE = 0x02,
	LIS3DSH_HPM_AUTORESET_INT = 0x03
} LIS3DSH_HPFMode_t;

typedef enum {
	LIS3DSH_HPFCF_0 = 0x00,
	LIS3DSH_HPFCF_1 = 0x01,
	LIS3DSH_HPFCF_2 = 0x02,
	LIS3DSH_HPFCF_3 = 0x03
} LIS3DSH_HPFCutOffFreq_t;

typedef struct {
	u16_t AUX_1;
	u16_t AUX_2;
	u16_t AUX_3;
} LIS3DSH_Aux123Raw_t;

typedef enum {
	LIS3DSH_FULLSCALE_2 = 0x00,
	LIS3DSH_FULLSCALE_4 = 0x01,
	LIS3DSH_FULLSCALE_8 = 0x02,
	LIS3DSH_FULLSCALE_16 = 0x03
} LIS3DSH_Fullscale_t;

typedef enum {
	LIS3DSH_BLE_LSB = 0x00, LIS3DSH_BLE_MSB = 0x01
} LIS3DSH_Endianess_t;

typedef enum {
	LIS3DSH_SELF_TEST_DISABLE = 0x00,
	LIS3DSH_SELF_TEST_0 = 0x01,
	LIS3DSH_SELF_TEST_1 = 0x02
} LIS3DSH_SelfTest_t;

typedef enum {
	LIS3DSH_TRIG_INT1 = 0x00, LIS3DSH_TRIG_INT2 = 0x01
} LIS3DSH_TrigInt_t;

typedef enum {
	LIS3DSH_SPI_4_WIRE = 0x00, LIS3DSH_SPI_3_WIRE = 0x01
} LIS3DSH_SPIMode_t;

typedef enum {
	LIS3DSH_X_ENABLE = 0x01,
	LIS3DSH_X_DISABLE = 0x00,
	LIS3DSH_Y_ENABLE = 0x02,
	LIS3DSH_Y_DISABLE = 0x00,
	LIS3DSH_Z_ENABLE = 0x04,
	LIS3DSH_Z_DISABLE = 0x00
} LIS3DSH_AXISenable_t;

typedef enum {
	LIS3DSH_INT1_6D_4D_DISABLE = 0x00,
	LIS3DSH_INT1_6D_ENABLE = 0x01,
	LIS3DSH_INT1_4D_ENABLE = 0x02
} LIS3DSH_INT_6D_4D_t;

typedef enum {
	LIS3DSH_UP_SX = 0x44,
	LIS3DSH_UP_DX = 0x42,
	LIS3DSH_DW_SX = 0x41,
	LIS3DSH_DW_DX = 0x48,
	LIS3DSH_TOP = 0x60,
	LIS3DSH_BOTTOM = 0x50
} LIS3DSH_POSITION_6D_t;

typedef enum {
	LIS3DSH_INT_MODE_OR = 0x00,
	LIS3DSH_INT_MODE_6D_MOVEMENT = 0x01,
	LIS3DSH_INT_MODE_AND = 0x02,
	LIS3DSH_INT_MODE_6D_POSITION = 0x03
} LIS3DSH_Int1Mode_t;

//interrupt click response
//  b7 = don't care   b6 = IA  b5 = DClick  b4 = Sclick  b3 = Sign  
//  b2 = z      b1 = y     b0 = x
typedef enum {
	LIS3DSH_DCLICK_Z_P = 0x24,
	LIS3DSH_DCLICK_Z_N = 0x2C,
	LIS3DSH_SCLICK_Z_P = 0x14,
	LIS3DSH_SCLICK_Z_N = 0x1C,
	LIS3DSH_DCLICK_Y_P = 0x22,
	LIS3DSH_DCLICK_Y_N = 0x2A,
	LIS3DSH_SCLICK_Y_P = 0x12,
	LIS3DSH_SCLICK_Y_N = 0x1A,
	LIS3DSH_DCLICK_X_P = 0x21,
	LIS3DSH_DCLICK_X_N = 0x29,
	LIS3DSH_SCLICK_X_P = 0x11,
	LIS3DSH_SCLICK_X_N = 0x19,
	LIS3DSH_NO_CLICK = 0x00
} LIS3DSH_Click_Response;

//TODO: start from here and manage the shared macros etc before this

/* Exported constants --------------------------------------------------------*/

#ifndef __SHARED__CONSTANTS
#define __SHARED__CONSTANTS

#define MEMS_SET                       	0x01
#define MEMS_RESET                      0x00

#endif /*__SHARED__CONSTANTS*/

// INFORMATION REGISTER 1
#define LIS3DSH_INFO1_REG				0x0D

// INFORMATION REGISTER 2
#define LIS3DSH_INFO2_REG				0x0E

//Register Definition
#define LIS3DSH_WHO_AM_I_REG			0x0F  // device identification register

#define LIS3DSH_WHO_AM_I_VALUE			0x3F

//CONTROL REGISTER 3
#define LIS3DSH_CTRL_REG3				0x23
#define LIS3DSH_DR_EN					BIT(7)
#define LIS3DSH_IEA						BIT(6)
#define LIS3DSH_IEL						BIT(5)
#define LIS3DSH_INT2_EN					BIT(4)
#define LIS3DSH_INT1_EN					BIT(3)
#define LIS3DSH_VFILT					BIT(2)
#define LIS3DSH_STRT					BIT(0)

//CONTROL REGISTER 4
#define LIS3DSH_CTRL_REG4				0x20
#define LIS3DSH_ODR3					BIT(7)
#define LIS3DSH_ODR2					BIT(6)
#define LIS3DSH_ODR1					BIT(5)
#define LIS3DSH_ODR0					BIT(4)
#define LIS3DSH_BDU						BIT(3)
#define LIS3DSH_ZEN						BIT(2)
#define LIS3DSH_YEN						BIT(1)
#define LIS3DSH_XEN						BIT(0)

//CONTROL REGISTER 5
#define LIS3DSH_CTRL_REG5				0x24
#define LIS3DSH_BW2						BIT(7)
#define LIS3DSH_BW1						BIT(6)
#define LIS3DSH_FSCALE2					BIT(5)
#define LIS3DSH_FSCALE1					BIT(4)
#define LIS3DSH_FSCALE0					BIT(3)
#define LIS3DSH_ST2						BIT(2)
#define LIS3DSH_ST1						BIT(1)
#define LIS3DSH_SIM						BIT(0)

//CONTROL REGISTER 6
#define LIS3DSH_CTRL_REG6				0x25
#define LIS3DSH_BOOT					BIT(7)
#define LIS3DSH_FIFO_EN					BIT(6)
#define LIS3DSH_WTM_EN					BIT(5)
#define LIS3DSH_ADD_INC					BIT(4)
#define LIS3DSH_P1_EMPTY				BIT(3)
#define LIS3DSH_P1_WTM					BIT(2)
#define LIS3DSH_P1_OVERRUN				BIT(1)
#define LIS3DSH_P1_BOOT					BIT(0)

//STATUS_REG_AXIES
#define LIS3DSH_STATUS_REG				0x27
#define LIS3DSH_ZYXOR                   BIT(7)
#define LIS3DSH_ZOR                     BIT(6)
#define LIS3DSH_YOR                     BIT(5)
#define LIS3DSH_XOR                     BIT(4)
#define LIS3DSH_ZYXDA                   BIT(3)
#define LIS3DSH_ZDA                     BIT(2)
#define LIS3DSH_YDA                     BIT(1)
#define LIS3DSH_XDA                     BIT(0)

//OUT_C TEMPERATURE OUTPUT
#define LIS3DSH_OUT_T_REG				0x0C
#define LIS3DSH_TEMP7                   BIT(7)
#define LIS3DSH_TEMP6                   BIT(6)
#define LIS3DSH_TEMP5                   BIT(5)
#define LIS3DSH_TEMP4                   BIT(4)
#define LIS3DSH_TEMP3	                BIT(3)
#define LIS3DSH_TEMP2                   BIT(2)
#define LIS3DSH_TEMP1                   BIT(1)
#define LIS3DSH_TEMP0                   BIT(0)

//OFF_X Offset correction X-axis register, signed value.
#define LIS3DSH_OFF_X_REG				0x10

//OFF_Y Offset correction Y-axis register, signed value.
#define LIS3DSH_OFF_Y_REG				0x11

//OFF_Z Offset correction Z-axis register, signed value.
#define LIS3DSH_OFF_Z_REG				0x12

//CS_X Constant shift, signed value X-axis register - state machine only.
#define LIS3DSH_CS_X_REG				0x13

//CS_Y Constant shift, signed value Y-axis register - state machine only.
#define LIS3DSH_CS_Y_REG				0x14

//CS_Z Constant shift, signed value Z-axis register - state machine only.
#define LIS3DSH_CS_Z_REG				0x15

//LC 16-bit long-counter register for interrupt state machine
#define LIS3DSH_LC_L_REG				0x16
#define LIS3DSH_LC_H_REG				0x17

//Interrupt status - interrupt synchronization register.
#define LIS3DSH_STAT_REG				0x18
#define LIS3DSH_LONG                   	BIT(7)
#define LIS3DSH_SYNCW                   BIT(6)
#define LIS3DSH_SYNC1                   BIT(5)
#define LIS3DSH_SYNC2                   BIT(4)
#define LIS3DSH_INT_SM1	                BIT(3)
#define LIS3DSH_INT_SM2                 BIT(2)
#define LIS3DSH_DOR                   	BIT(1)
#define LIS3DSH_DRDY                   	BIT(0)

//Vector coefficient register 1 for diff filter.
#define LIS3DSH_VFC_1_REG				0x1B

//Vector coefficient register 2 for diff filter.
#define LIS3DSH_VFC_2_REG				0x1C

//Vector coefficient register 3 for diff filter.
#define LIS3DSH_VFC_3_REG				0x1D

//Vector coefficient register 4 for diff filter.
#define LIS3DSH_VFC_4_REG				0x1E

//Threshold value register.
#define LIS3DSH_THRS3_REG				0x1F

//X-axis output register
#define LIS3DSH_OUT_X_L_REG				0x28
#define LIS3DSH_OUT_X_H_REG				0x29

//Y-axis output register
#define LIS3DSH_OUT_Y_L_REG				0x2A
#define LIS3DSH_OUT_Y_H_REG				0x2B

//Z-axis output register
#define LIS3DSH_OUT_Z_L_REG				0x2C
#define LIS3DSH_OUT_Z_H_REG				0x2D

//FIFO control register.
#define LIS3DSH_FIFO_CTRL				0x2E
#define LIS3DSH_FMODE2                  BIT(7)
#define LIS3DSH_FMODE1                 	BIT(6)
#define LIS3DSH_FMODE0                	BIT(5)
#define LIS3DSH_WTMP4                	BIT(4)
#define LIS3DSH_WTMP3                   BIT(3)
#define LIS3DSH_WTMP2                 	BIT(2)
#define LIS3DSH_WTMP1                	BIT(1)
#define LIS3DSH_WTMP0                	BIT(0)

//FIFO SRC control register.
#define LIS3DSH_FIFO_SRC_REG			0x2F
#define LIS3DSH_WTM		                BIT(7)
#define LIS3DSH_OVRN_FIFO              	BIT(6)
#define LIS3DSH_EMPTY                	BIT(5)
#define LIS3DSH_FSS4                	BIT(4)
#define LIS3DSH_FSS3	                BIT(3)
#define LIS3DSH_FSS2                 	BIT(2)
#define LIS3DSH_FSS1                	BIT(1)
#define LIS3DSH_FSS0                	BIT(0)

//SM1 control register.
#define LIS3DSH_CTRL_REG1				0x21
#define LIS3DSH_HYST2_1	                BIT(7)
#define LIS3DSH_HYST1_1              	BIT(6)
#define LIS3DSH_HYST0_1                	BIT(5)
#define LIS3DSH_SM1_PIN	                BIT(3)
#define LIS3DSH_SM1_EN                	BIT(0)

//State machine 1 code register STx_1 (x = 1-16).
//State machine 1 system register is made up of 16, 8-bit registers to implement 16-step opcode.
#define LIS3DSH_ST1_1_REG				0x40
#define LIS3DSH_ST1_2_REG				0x41
#define LIS3DSH_ST1_3_REG				0x42
#define LIS3DSH_ST1_4_REG				0x43
#define LIS3DSH_ST1_5_REG				0x44
#define LIS3DSH_ST1_6_REG				0x45
#define LIS3DSH_ST1_7_REG				0x46
#define LIS3DSH_ST1_8_REG				0x47
#define LIS3DSH_ST1_9_REG				0x48
#define LIS3DSH_ST1_10_REG				0x49
#define LIS3DSH_ST1_11_REG				0x4A
#define LIS3DSH_ST1_12_REG				0x4B
#define LIS3DSH_ST1_13_REG				0x4C
#define LIS3DSH_ST1_14_REG				0x4D
#define LIS3DSH_ST1_15_REG				0x4E
#define LIS3DSH_ST1_16_REG				0x4F

//8-bit general timer (unsigned value) for SM1 operation timing.
#define LIS3DSH_TIM4_1_REG				0x50

//8-bit general timer (unsigned value) for SM1 operation timing.
#define LIS3DSH_TIM3_1_REG				0x51

//16-bit general timer (unsigned value) for SM1 operation timing.
#define LIS3DSH_TIM2_1_L_REG			0x52
#define LIS3DSH_TIM2_1_H_REG			0x53

//16-bit general timer (unsigned value) for SM1 operation timing.
#define LIS3DSH_TIM1_1_L_REG			0x54
#define LIS3DSH_TIM1_1_H_REG			0x55

//8-bit general timer (unsigned value) for SM1 operation timing.
#define LIS3DSH_THRS2_1_REG				0x56

//8-bit general timer (unsigned value) for SM1 operation timing.
#define LIS3DSH_THRS1_1_REG				0x57

//Axis and sign mask (swap) for SM1 motion-detection operation.
#define LIS3DSH_MASK1_B_REG				0x59
#define LIS3DSH_P_X						BIT(7)
#define LIS3DSH_N_X						BIT(6)
#define LIS3DSH_P_Y						BIT(5)
#define LIS3DSH_N_Y						BIT(4)
#define LIS3DSH_P_Z						BIT(3)
#define LIS3DSH_N_Z						BIT(2)
#define LIS3DSH_P_V						BIT(1)
#define LIS3DSH_N_V						BIT(0)

//Axis and sign mask (default) for SM1 motion-detection operation.
#define LIS3DSH_MASK1_A_REG				0x5A
#define LIS3DSH_P_X						BIT(7)
#define LIS3DSH_N_X						BIT(6)
#define LIS3DSH_P_Y						BIT(5)
#define LIS3DSH_N_Y						BIT(4)
#define LIS3DSH_P_Z						BIT(3)
#define LIS3DSH_N_Z						BIT(2)
#define LIS3DSH_P_V						BIT(1)
#define LIS3DSH_N_V						BIT(0)

//Setting of threshold, peak detection and flags for SM1 motion-detection operation.
#define LIS3DSH_SETT1_REG				0x5B
#define LIS3DSH_P_DET					BIT(7)
#define LIS3DSH_THR3_SA					BIT(6)
#define LIS3DSH_ABS						BIT(5)
#define LIS3DSH_THR3_MA					BIT(2)
#define LIS3DSH_R_TAM					BIT(1)
#define LIS3DSH_SITR					BIT(0)

//Program and reset pointer for SM1 motion-detection operation.
#define LIS3DSH_PR1_REG					0x5C
#define LIS3DSH_PP3						BIT(7)
#define LIS3DSH_PP2						BIT(6)
#define LIS3DSH_PP1						BIT(5)
#define LIS3DSH_PP0						BIT(4)
#define LIS3DSH_RP3						BIT(3)
#define LIS3DSH_RP2						BIT(2)
#define LIS3DSH_RP1						BIT(1)
#define LIS3DSH_RP0						BIT(0)

//16-bit general timer (unsigned output value) for SM1 operation timing.
#define LIS3DSH_TC1_L_REG				0x5D
#define LIS3DSH_TC1_H_REG				0x5E

//Output flags on axis for interrupt SM1 management.
#define LIS3DSH_OUTS1_REG				0x5F
#define LIS3DSH_P_X						BIT(7)
#define LIS3DSH_N_X						BIT(6)
#define LIS3DSH_P_Y						BIT(5)
#define LIS3DSH_N_Y						BIT(4)
#define LIS3DSH_P_Z						BIT(3)
#define LIS3DSH_N_Z						BIT(2)
#define LIS3DSH_P_V						BIT(1)
#define LIS3DSH_N_V						BIT(0)

//Peak detection value register for SM1 operation.
#define LIS3DSH_PEAK1_REG				0x19

//State program 2 interrupt MNG - SM2 control register.
#define LIS3DSH_CTRL_REG2				0x22
#define LIS3DSH_HYST2_2					BIT(7)
#define LIS3DSH_HYST1_2					BIT(6)
#define LIS3DSH_HYST0_2					BIT(5)
#define LIS3DSH_SM2_PIN					BIT(3)
#define LIS3DSH_SM2_EN					BIT(0)

//State machine 2 code register STx_1 (x = 1-16).
//State machine 2 system register is made up of 16 8-bit registers, to implement 16-step opcode.
#define LIS3DSH_ST2_0_REG				0X60
#define LIS3DSH_ST2_1_REG				0X61
#define LIS3DSH_ST2_2_REG				0X62
#define LIS3DSH_ST2_3_REG				0X63
#define LIS3DSH_ST2_4_REG				0X64
#define LIS3DSH_ST2_5_REG				0X65
#define LIS3DSH_ST2_6_REG				0X66
#define LIS3DSH_ST2_7_REG				0X67
#define LIS3DSH_ST2_8_REG				0X68
#define LIS3DSH_ST2_9_REG				0X69
#define LIS3DSH_ST2_10_REG				0X6A
#define LIS3DSH_ST2_11_REG				0X6B
#define LIS3DSH_ST2_12_REG				0X6C
#define LIS3DSH_ST2_13_REG				0X6D
#define LIS3DSH_ST2_1_REG4				0X6E
#define LIS3DSH_ST2_15_REG				0X6F

//8-bit general timer (unsigned value) for SM2 operation timing.
#define LIS3DSH_TIM4_2_REG				0x70

//8-bit general timer (unsigned value) for SM2 operation timing.
#define LIS3DSH_TIM3_2_REG				0x71

//16-bit general timer (unsigned value) for SM2 operation timing.
#define LIS3DSH_TIM2_2_L_REG			0x72
#define LIS3DSH_TIM2_2_H_REG			0x73

//16-bit general timer (unsigned value) for SM2 operation timing.
#define LIS3DSH_TIM1_2_L_REG			0x73
#define LIS3DSH_TIM1_2_H_REG			0x74

//Threshold signed value for SM2 operation.
#define LIS3DSH_THRS2_2_REG				0x76

//Threshold signed value for SM2 operation.
#define LIS3DSH_THRS1_2_REG				0x77

//Axis and sign mask (default) for SM2 motion-detection operation.
#define LIS3DSH_MASK2_B_REG				0x79
#define LIS3DSH_P_X						BIT(7)
#define LIS3DSH_N_X						BIT(6)
#define LIS3DSH_P_Y						BIT(5)
#define LIS3DSH_N_Y						BIT(4)
#define LIS3DSH_P_Z						BIT(3)
#define LIS3DSH_N_Z						BIT(2)
#define LIS3DSH_P_V						BIT(1)
#define LIS3DSH_N_V						BIT(0)

//Axis and sign mask (default) for SM1 motion-detection operation.
#define LIS3DSH_MASK2_A_REG				0x7A
#define LIS3DSH_P_X						BIT(7)
#define LIS3DSH_N_X						BIT(6)
#define LIS3DSH_P_Y						BIT(5)
#define LIS3DSH_N_Y						BIT(4)
#define LIS3DSH_P_Z						BIT(3)
#define LIS3DSH_N_Z						BIT(2)
#define LIS3DSH_P_V						BIT(1)
#define LIS3DSH_N_V						BIT(0)

//Setting of threshold, peak detection and flags for SM1 motion-detection operation.
#define LIS3DSH_SETT2_REG				0x7B
#define LIS3DSH_P_DET					BIT(7)
#define LIS3DSH_THR3_SA					BIT(6)
#define LIS3DSH_ABS						BIT(5)
#define LIS3DSH_THR3_MA					BIT(2)
#define LIS3DSH_R_TAM					BIT(1)
#define LIS3DSH_SITR					BIT(0)

//Program and reset pointer for SM1 motion-detection operation.
#define LIS3DSH_PR2_REG					0x7C
#define LIS3DSH_PP3						BIT(7)
#define LIS3DSH_PP2						BIT(6)
#define LIS3DSH_PP1						BIT(5)
#define LIS3DSH_PP0						BIT(4)
#define LIS3DSH_RP3						BIT(3)
#define LIS3DSH_RP2						BIT(2)
#define LIS3DSH_RP1						BIT(1)
#define LIS3DSH_RP0						BIT(0)

//16-bit general timer (unsigned output value) for SM1 operation timing.
#define LIS3DSH_TC2_L_REG				0x7D
#define LIS3DSH_TC2_H_REG				0x7E

//Output flags on axis for interrupt SM1 management.
#define LIS3DSH_OUTS2_REG				0x7F
#define LIS3DSH_P_X						BIT(7)
#define LIS3DSH_N_X						BIT(6)
#define LIS3DSH_P_Y						BIT(5)
#define LIS3DSH_N_Y						BIT(4)
#define LIS3DSH_P_Z						BIT(3)
#define LIS3DSH_N_Z						BIT(2)
#define LIS3DSH_P_V						BIT(1)
#define LIS3DSH_N_V						BIT(0)

//Peak detection value register for SM1 operation.
#define LIS3DSH_PEAK2_REG				0x1A

//Decimation counter value register for SM2 operation.
#define LIS3DSH_DES2_REG				0x78

//CONTROL REG3 bit mask
#define LIS3DSH_CLICK_ON_PIN_INT1_ENABLE                0x80
#define LIS3DSH_CLICK_ON_PIN_INT1_DISABLE               0x00
#define LIS3DSH_I1_INT1_ON_PIN_INT1_ENABLE              0x40
#define LIS3DSH_I1_INT1_ON_PIN_INT1_DISABLE             0x00
#define LIS3DSH_I1_INT2_ON_PIN_INT1_ENABLE              0x20
#define LIS3DSH_I1_INT2_ON_PIN_INT1_DISABLE             0x00
#define LIS3DSH_I1_DRDY1_ON_INT1_ENABLE                 0x10
#define LIS3DSH_I1_DRDY1_ON_INT1_DISABLE                0x00
#define LIS3DSH_I1_DRDY2_ON_INT1_ENABLE                 0x08
#define LIS3DSH_I1_DRDY2_ON_INT1_DISABLE                0x00
#define LIS3DSH_WTM_ON_INT1_ENABLE                      0x04
#define LIS3DSH_WTM_ON_INT1_DISABLE                     0x00
#define LIS3DSH_INT1_OVERRUN_ENABLE                     0x02
#define LIS3DSH_INT1_OVERRUN_DISABLE                    0x00

//CONTROL REG6 bit mask
#define LIS3DSH_CLICK_ON_PIN_INT2_ENABLE                0x80
#define LIS3DSH_CLICK_ON_PIN_INT2_DISABLE               0x00
#define LIS3DSH_I2_INT1_ON_PIN_INT2_ENABLE              0x40
#define LIS3DSH_I2_INT1_ON_PIN_INT2_DISABLE             0x00
#define LIS3DSH_I2_INT2_ON_PIN_INT2_ENABLE              0x20
#define LIS3DSH_I2_INT2_ON_PIN_INT2_DISABLE             0x00
#define LIS3DSH_I2_BOOT_ON_INT2_ENABLE                  0x10
#define LIS3DSH_I2_BOOT_ON_INT2_DISABLE                 0x00
#define LIS3DSH_INT_ACTIVE_HIGH                         0x00
#define LIS3DSH_INT_ACTIVE_LOW                          0x02

//INT1_CFG bit mask
#define LIS3DSH_INT1_AND                                0x80
#define LIS3DSH_INT1_OR                                 0x00
#define LIS3DSH_INT1_ZHIE_ENABLE                        0x20
#define LIS3DSH_INT1_ZHIE_DISABLE                       0x00
#define LIS3DSH_INT1_ZLIE_ENABLE                        0x10
#define LIS3DSH_INT1_ZLIE_DISABLE                       0x00
#define LIS3DSH_INT1_YHIE_ENABLE                        0x08
#define LIS3DSH_INT1_YHIE_DISABLE                       0x00
#define LIS3DSH_INT1_YLIE_ENABLE                        0x04
#define LIS3DSH_INT1_YLIE_DISABLE                       0x00
#define LIS3DSH_INT1_XHIE_ENABLE                        0x02
#define LIS3DSH_INT1_XHIE_DISABLE                       0x00
#define LIS3DSH_INT1_XLIE_ENABLE                        0x01
#define LIS3DSH_INT1_XLIE_DISABLE                       0x00

//INT1_SRC bit mask
#define LIS3DSH_INT1_SRC_IA                             0x40
#define LIS3DSH_INT1_SRC_ZH                             0x20
#define LIS3DSH_INT1_SRC_ZL                             0x10
#define LIS3DSH_INT1_SRC_YH                             0x08
#define LIS3DSH_INT1_SRC_YL                             0x04
#define LIS3DSH_INT1_SRC_XH                             0x02
#define LIS3DSH_INT1_SRC_XL                             0x01

//INT1 REGISTERS
#define LIS3DSH_INT1_THS                                0x32
#define LIS3DSH_INT1_DURATION                           0x33

//INTERRUPT 1 SOURCE REGISTER
#define LIS3DSH_INT1_SRC								0x31

//FIFO Source Register bit Mask
#define LIS3DSH_FIFO_SRC_WTM                            0x80
#define LIS3DSH_FIFO_SRC_OVRUN                          0x40
#define LIS3DSH_FIFO_SRC_EMPTY                          0x20

//INTERRUPT CLICK REGISTER
#define LIS3DSH_CLICK_CFG								0x38
//INTERRUPT CLICK CONFIGURATION bit mask
#define LIS3DSH_ZD_ENABLE                               0x20
#define LIS3DSH_ZD_DISABLE                              0x00
#define LIS3DSH_ZS_ENABLE                               0x10
#define LIS3DSH_ZS_DISABLE                              0x00
#define LIS3DSH_YD_ENABLE                               0x08
#define LIS3DSH_YD_DISABLE                              0x00
#define LIS3DSH_YS_ENABLE                               0x04
#define LIS3DSH_YS_DISABLE                              0x00
#define LIS3DSH_XD_ENABLE                               0x02
#define LIS3DSH_XD_DISABLE                              0x00
#define LIS3DSH_XS_ENABLE                               0x01
#define LIS3DSH_XS_DISABLE                              0x00

//INTERRUPT CLICK SOURCE REGISTER
#define LIS3DSH_CLICK_SRC                               0x39
//INTERRUPT CLICK SOURCE REGISTER bit mask
#define LIS3DSH_IA                                      0x40
#define LIS3DSH_DCLICK                                  0x20
#define LIS3DSH_SCLICK                                  0x10
#define LIS3DSH_CLICK_SIGN                              0x08
#define LIS3DSH_CLICK_Z                                 0x04
#define LIS3DSH_CLICK_Y                                 0x02
#define LIS3DSH_CLICK_X                                 0x01

//Click-click Register
#define LIS3DSH_CLICK_THS                               0x3A
#define LIS3DSH_TIME_LIMIT                              0x3B
#define LIS3DSH_TIME_LATENCY                            0x3C
#define LIS3DSH_TIME_WINDOW                             0x3D

//AUX REGISTER
#define LIS3DSH_OUT_1_L					0x08
#define LIS3DSH_OUT_1_H					0x09
#define LIS3DSH_OUT_2_L					0x0A
#define LIS3DSH_OUT_2_H					0x0B
#define LIS3DSH_OUT_3_L					0x0C
#define LIS3DSH_OUT_3_H					0x0D

//STATUS REGISTER bit mask
#define LIS3DSH_STATUS_REG_ZYXOR                        0x80    // 1	:	new data set has over written the previous one
// 0	:	no overrun has occurred (default)
#define LIS3DSH_STATUS_REG_ZOR                          0x40    // 0	:	no overrun has occurred (default)
// 1	:	new Z-axis data has over written the previous one
#define LIS3DSH_STATUS_REG_YOR                          0x20    // 0	:	no overrun has occurred (default)
// 1	:	new Y-axis data has over written the previous one
#define LIS3DSH_STATUS_REG_XOR                          0x10    // 0	:	no overrun has occurred (default)
// 1	:	new X-axis data has over written the previous one
#define LIS3DSH_STATUS_REG_ZYXDA                        0x08    // 0	:	a new set of data is not yet avvious one
// 1	:	a new set of data is available
#define LIS3DSH_STATUS_REG_ZDA                          0x04    // 0	:	a new data for the Z-Axis is not availvious one
// 1	:	a new data for the Z-Axis is available
#define LIS3DSH_STATUS_REG_YDA                          0x02    // 0	:	a new data for the Y-Axis is not available
// 1	:	a new data for the Y-Axis is available
#define LIS3DSH_STATUS_REG_XDA                          0x01    // 0	:	a new data for the X-Axis is not available

#define LIS3DSH_DATAREADY_BIT                           LIS3DSH_STATUS_REG_ZYXDA

#define LIS3DSH_MEMS_I2C_ADDRESS			    0x33

/* Exported macro ------------------------------------------------------------*/

#ifndef __SHARED__MACROS

#define __SHARED__MACROS
#define ValBit(VAR,Place)         (VAR & (1<<Place))
#define BIT(x) ( (x) )

#endif /*__SHARED__MACROS*/

/* Exported functions --------------------------------------------------------*/
//Sensor Configuration Functions
status_t LIS3DSH_SetODR(LIS3DSH_ODRMode_t mode);
status_t LIS3DSH_SetAxis(LIS3DSH_Axis_t axis);
status_t LIS3DSH_SetSelfTest(LIS3DSH_SelfTest_t st);

//Filtering Functions

//Interrupt Functions

//FIFO Functions

//Other Reading Functions
status_t LIS3DSH_GetWHO_AM_I(u8_t* val);
status_t LIS3DSH_GetAccAxesRaw(LIS3DSH_AxesRaw_t* buff);
status_t LIS3DSH_GetAccAxesOffset(LIS3DSH_AxesOffset_t* buff);

//Generic
status_t LIS3DSH_ReadReg(u8_t Reg, u8_t* Data);
status_t LIS3DSH_WriteReg(u8_t Reg, u8_t Data);

#endif /* __LIS3DSH_H */

/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/

