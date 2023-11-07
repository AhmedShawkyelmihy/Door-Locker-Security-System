/*
 ============================================================================
 Name        : twi.h
 Author      : Ahmed Shawky
 Description : Header File for TWI(I2C) Driver
 Date        : 13/09/2023
 ============================================================================
 */

#ifndef TWI_H_
#define TWI_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <avr/io.h>
#include "std_types.h"
#include "common_macros.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 	/* Start condition has been transmitted */

#define TWI_REP_START     0x10 	/* A repeated start condition has been transmitted */

#define TWI_MT_SLA_W_ACK  0x18 	/* Master transmit ( slave address + Write request ) to
 	 	 	 	 	 	 	 	   slave + ACK received from slave. */

#define TWI_MT_SLA_R_ACK  0x40 	/* Master transmit ( slave address + Read request ) to
 	 	 	 	 	 	 	 	   slave + ACK received from slave. */

#define TWI_MT_DATA_ACK   0x28 	/* Master transmit data and ACK has been received from Slave. */

#define TWI_MR_DATA_ACK   0x50 	/* Master received data and send ACK to slave. */

#define TWI_MR_DATA_NACK  0x58 	/* Master received data but doesn't send ACK to slave. */

/****************************************************************************
 * 					          Types Declaration						        *
 ****************************************************************************/

typedef uint8 TWI_Address ;

typedef enum
{
	Normal_Mode,

	Fast_Mode,

	Fast_Mode_Plus,

	High_Speed_Mode

}TWI_BaudRate;

typedef struct
{
	TWI_Address address;

	TWI_BaudRate bit_rate;

}TWI_ConfigType;

/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/

/* Inputs:
 * 	1. Pointer to user defined data type : TWI_ConfigType.
 *
 * Return Value: void.
 *
 * Description:
 *	Initialize the TWI module.
 */
void TWI_init(const TWI_ConfigType *Config_Ptr);

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Master node sends a start condition.
 */
void TWI_start(void);

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 * 	Master node sends a stop condition.
 */
void TWI_stop(void);

/* Inputs:
 * 	1. The required data to be sent.
 *
 * Return Value: void.
 *
 * Description:
 *	Send the required data.
 */
void TWI_writeByte(uint8 data);

/* Inputs: void.
 *
 * Return Value: The required data to be received.
 *
 * Description:
 *	Receive the required data and send ACK.
 */
uint8 TWI_readByteWithACK(void);

/* Inputs: void.
 *
 * Return Value: The required data to be received.
 *
 * Description:
 *	Receive the required data and send NACK.
 */
uint8 TWI_readByteWithNACK(void);

/* Inputs: void.
 *
 * Return Value: The current status.
 *
 * Description:
 *	Getting the current status.
 */
uint8 TWI_getStatus(void);



#endif /* TWI_H_ */
