/*
 ============================================================================
 Name        : twi.c
 Author      : Ahmed Shawky
 Description : Source File for TWI(I2C) Driver
 Date        : 13/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "twi.h"

/****************************************************************************
 * 							Functions Definitions						    *
 ****************************************************************************/

/* Inputs:
 * 	1. Pointer to user defined data type : TWI_ConfigType.
 *
 * Return Value: void.
 *
 * Description:
 *	Initialize the TWI module.
 */
void TWI_init(const TWI_ConfigType *Config_Ptr)
{
	switch(Config_Ptr->bit_rate)
	{
	case Normal_Mode :
		/* Bit Rate: 100.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
		TWBR = 0x20 ;
		TWSR = 0x00 ;
		break;
	case Fast_Mode :
		/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
		TWBR = 0x02 ;
		TWSR = 0x00 ;
		break;
	case Fast_Mode_Plus :
		break;
	case High_Speed_Mode :
		break;
	}

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
	   General Call Recognition: Off */
	TWAR = Config_Ptr->address ;

	/* Enable TWI module. */
	TWCR = (1<<TWEN) ;
}

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Master node sends a start condition.
 */
void TWI_start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ;

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 * 	Master node sends a stop condition.
 */
void TWI_stop(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN) ;
}

/* Inputs:
 * 	1. The required data to be sent.
 *
 * Return Value: void.
 *
 * Description:
 *	Send the required data.
 */
void TWI_writeByte(uint8 data)
{
	/* Put data On TWI data Register */
	TWDR = data ;

	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) ;

	/* Wait for TWINT flag set in TWCR Register (data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/* Inputs: void.
 *
 * Return Value: The required data to be received.
 *
 * Description:
 *	Receive the required data and send ACK.
 */
uint8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA) ;

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Read Data */
	return TWDR ;
}

/* Inputs: void.
 *
 * Return Value: The required data to be received.
 *
 * Description:
 *	Receive the required data and send NACK.
 */
uint8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) ;

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Read Data */
	return TWDR ;
}

/* Inputs: void.
 *
 * Return Value: The current status.
 *
 * Description:
 *	Getting the current status.
 */
uint8 TWI_getStatus(void)
{
	uint8 status ;

	/* Masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8 ;

	return status ;
}
