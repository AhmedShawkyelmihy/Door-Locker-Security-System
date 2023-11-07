/*
 ============================================================================
 Name        : external_eeprom.c
 Author      : Ahmed Shawky
 Description : Source File for External EEPROM Memory Driver
 Date        : 13/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "external_eeprom.h"
#include "twi.h"

/****************************************************************************
 * 							Functions Definitions						    *
 ****************************************************************************/

/* Inputs:
 * 	1. The required data to be written into EEPROM memory.
 *
 * Return Value: void.
 *
 * Description:
 *	Write data into EEPROM memory
 */
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start condition */
	TWI_start();
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR ;
	}

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700) >> 7)));
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR ;
	}

	/* Send the required memory location address */
	TWI_writeByte((uint8)(u16addr));
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR ;
	}

	/* write byte to EEPROM */
	TWI_writeByte(u8data);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR ;
	}

	/* Send the Stop condition */
	TWI_stop();

	return SUCCESS ;
}

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *	Read data from EEPROM memory.
 */
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start condition */
	TWI_start();
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR ;
	}

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700) >> 7)));
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR ;
	}

	/* Send the required memory location address */
	TWI_writeByte((uint8)(u16addr));
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR ;
	}

	/* Send the Start condition */
	TWI_start();
	if(TWI_getStatus() != TWI_REP_START)
	{
		return ERROR ;
	}

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=1 (read) */
	TWI_writeByte((uint8)((0xA0 | ((u16addr & 0x0700) >> 7)) | 1));
	if(TWI_getStatus() != TWI_MT_SLA_R_ACK)
	{
		return ERROR ;
	}

	/* Read byte from EEPROM */
	*u8data = TWI_readByteWithNACK();
	if(TWI_getStatus() != TWI_MR_DATA_NACK)
	{
		return ERROR ;
	}

	/* Send the Stop condition */
	TWI_stop();

	return SUCCESS ;
}
