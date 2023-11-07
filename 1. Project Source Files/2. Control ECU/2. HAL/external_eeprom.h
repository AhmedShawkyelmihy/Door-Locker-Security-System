/*
 ============================================================================
 Name        : external_eeprom.h
 Author      : Ahmed Shawky
 Description : Header File for External EEPROM Memory Driver
 Date        : 13/09/2023
 ============================================================================
 */

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "std_types.h"
#include "common_macros.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/
#define ERROR 		0
#define SUCCESS 	1

/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/

/* Inputs:
 * 	1.
 * 	2. The required data to be written into EEPROM memory.
 *
 * Return Value: The result of write operation.
 *
 * Description:
 *	Write data into EEPROM memory
 */
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);

/* Inputs:
 *
 * Return Value: The result of read operation.
 *
 * Description:
 *	Read data from EEPROM memory.
 */
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);



#endif /* EXTERNAL_EEPROM_H_ */
