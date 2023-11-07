/*
 ============================================================================
 Name        : uart.h
 Author      : Ahmed Shawky
 Description : Header File for UART Driver
 Date        : 10/09/2023
 ============================================================================
 */

#ifndef UART_H_
#define UART_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_types.h"
#include "common_macros.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/


/****************************************************************************
 * 					          Types Declaration						        *
 ****************************************************************************/

typedef uint32 UART_BaudRate ;

typedef enum
{
	Five_Bit_Data,

	Six_Bit_Data,

	Seven_Bit_Data,

	Eight_Bit_Data,

	Nine_Bit_Data

}UART_BitData;

typedef enum
{
	Disable_Parity,

	Even_Parity = 0x02,

	Odd_Parity

}UART_Parity;

typedef enum
{
	One_Bit_Stop,

	Two_Bit_Stop

}UART_StopBit;

typedef struct
{
	UART_BitData 	bit_data;

	UART_Parity 	parity;

	UART_StopBit 	stop_bit;

	UART_BaudRate   baud_rate;

}UART_ConfigType;

/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void UART_sendByte(const uint8 data);

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
uint8 UART_receiveByte(void);

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void UART_sendString(const uint8 *Str);

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void UART_receiveString(uint8 *Str);


#endif /* UART_H_ */
