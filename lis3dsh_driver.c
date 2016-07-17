/******************** (C) COPYRIGHT 2012 STMicroelectronics ********************
 * File Name          : LIS3DSH_driver.c
 * Author             : MSH Application Team
 * Author             : Fabio Tota
 * Author             : Emerson Moura
 * Version            : $Revision:$
 * Date               : $Date:$
 * Description        : LIS3DSH driver file
 *
 * HISTORY:
 * Date             | Modification                    					| Author
 * 24/06/2011       | Initial Revision                					| Fabio Tota
 * 11/06/2012       | Support for multiple drivers in the same program 	| Abhishek Anand
 * 16/07/2016  		| Change original drive from LIS3DH to LIS3DSH 		| Emerson Moura

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

/* Includes ------------------------------------------------------------------*/
#include "lis3dsh_driver.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
 * Function Name		: LIS3DSH_ReadReg
 * Description		: Generic Reading function. It must be fullfilled with either
 *			: I2C or SPI reading functions
 * Input			: Register Address
 * Output		: Data REad
 * Return		: None
 *******************************************************************************/
status_t LIS3DSH_ReadReg(u8_t Reg, u8_t* Data) {

	//To be completed with either I2c or SPI reading function
	//i.e. *Data = SPI_Mems_Read_Reg( Reg );

	out_off(SPI_ACC_EVAL);

	spi_send(Reg | BIT7);
	*Data = spi_send(0xFF);

	out_on(SPI_ACC_EVAL);

	return MEMS_SUCCESS;
}

/*******************************************************************************
 * Function Name		: LIS3DSH_WriteReg
 * Description		: Generic Writing function. It must be fullfilled with either
 *			: I2C or SPI writing function
 * Input			: Register Address, Data to be written
 * Output		: None
 * Return		: None
 *******************************************************************************/
status_t LIS3DSH_WriteReg(u8_t WriteAddr, u8_t Data) {

	//To be completed with either I2c or SPI writing function
	//i.e. SPI_Mems_Write_Reg(WriteAddr, Data);

	out_off(SPI_ACC_EVAL);

	spi_send(WriteAddr);
	spi_send(Data);

	out_on(SPI_ACC_EVAL);

	return MEMS_SUCCESS;
}

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : LIS3DSH_GetWHO_AM_I
 * Description    : Read identification code by WHO_AM_I register
 * Input          : Char to empty by Device identification Value
 * Output         : None
 * Return         : Status [value of FSS]
 *******************************************************************************/
status_t LIS3DSH_GetWHO_AM_I(u8_t* val) {
	uint8_t value;

	if (!LIS3DSH_ReadReg(LIS3DSH_WHO_AM_I_REG, &value))
		return MEMS_ERROR;

	if (value != LIS3DSH_WHO_AM_I_VALUE)
		return MEMS_ERROR;

	*val = value;

	return MEMS_SUCCESS;
}

void step() {
	asm("nop");
}

/*******************************************************************************
 * Function Name  : LIS3DSH_SetODR
 * Description    : Sets LIS3DSH Power Mode and ODR Selection
 * Input          : Modality (ODR_MDOE)
 * Output         : None
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
status_t LIS3DSH_SetODR(LIS3DSH_ODRMode_t md) {
	u8_t value;
	u8_t odr;

	odr = (md << 4);

	if (!LIS3DSH_ReadReg(LIS3DSH_CTRL_REG4, &value))
		return MEMS_ERROR;

	value = (value & 0x0f) | odr;

	if (!LIS3DSH_WriteReg(LIS3DSH_CTRL_REG4, value))
		return MEMS_ERROR;

	return MEMS_SUCCESS;
}

/*******************************************************************************
 * Function Name : LIS3DSH_SetAxis
 * Description : Enable/Disable LIS3DSH Axis
 * Input : LIS3DSH_X_ENABLE/DISABLE | LIS3DSH_Y_ENABLE/DISABLE | LIS3DSH_Z_ENABLE/DISABLE
 * Output : None
 * Note : You MUST use all input variable in the argument, as example
 * Return : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
status_t LIS3DSH_SetAxis(LIS3DSH_Axis_t axis) {
	u8_t value;

	if (!LIS3DSH_ReadReg(LIS3DSH_CTRL_REG4, &value))
		return MEMS_ERROR;

	value &= 0b11111000;

	value |= (0b111 & axis);

	if (!LIS3DSH_WriteReg(LIS3DSH_CTRL_REG4, value))
		return MEMS_ERROR;

	return MEMS_SUCCESS;
}

/*******************************************************************************
 * Function Name  : LIS3DSH_GetAccAxesOffset
 * Description    : Read the Acceleration Offset Values Output Registers
 * Input          : buffer to empity by AxesRaw_t Typedef
 * Output         : None
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
status_t LIS3DSH_GetAccAxesOffset(LIS3DSH_AxesOffset_t* buff) {
	i16_t value;
	u8_t *valueL = (u8_t *) (&value);

	if (!LIS3DSH_ReadReg(LIS3DSH_OFF_X_REG, valueL))
		return MEMS_ERROR;

	buff->AXIS_X = value;

	if (!LIS3DSH_ReadReg(LIS3DSH_OFF_Y_REG, valueL))
		return MEMS_ERROR;

	buff->AXIS_Y = value;

	if (!LIS3DSH_ReadReg(LIS3DSH_OFF_Z_REG, valueL))
		return MEMS_ERROR;

	buff->AXIS_Z = value;

	return MEMS_SUCCESS;
}

/*******************************************************************************
 * Function Name  : LIS3DSH_GetAccAxesRaw
 * Description    : Read the Acceleration Values Output Registers
 * Input          : buffer to empity by AxesRaw_t Typedef
 * Output         : None
 * Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
 *******************************************************************************/
status_t LIS3DSH_GetAccAxesRaw(LIS3DSH_AxesRaw_t* buff) {
	i16_t value;
	u8_t *valueL = (u8_t *) (&value);
	u8_t *valueH = ((u8_t *) (&value) + 1);

	if (!LIS3DSH_ReadReg(LIS3DSH_OUT_X_L_REG, valueL))
		return MEMS_ERROR;

	if (!LIS3DSH_ReadReg(LIS3DSH_OUT_X_H_REG, valueH))
		return MEMS_ERROR;

	buff->AXIS_X = value;

	if (!LIS3DSH_ReadReg(LIS3DSH_OUT_Y_L_REG, valueL))
		return MEMS_ERROR;

	if (!LIS3DSH_ReadReg(LIS3DSH_OUT_Y_H_REG, valueH))
		return MEMS_ERROR;

	buff->AXIS_Y = value;

	if (!LIS3DSH_ReadReg(LIS3DSH_OUT_Z_L_REG, valueL))
		return MEMS_ERROR;

	if (!LIS3DSH_ReadReg(LIS3DSH_OUT_Z_H_REG, valueH))
		return MEMS_ERROR;

	buff->AXIS_Z = value;

	return MEMS_SUCCESS;
}

/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
