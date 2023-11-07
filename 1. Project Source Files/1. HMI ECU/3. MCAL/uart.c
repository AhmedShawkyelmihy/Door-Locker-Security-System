/*
 ============================================================================
 Name        : uart.c
 Author      : Ahmed Shawky
 Description : Source File for UART Driver
 Date        : 10/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "uart.h"

/****************************************************************************
 * 							Functions Definitions						    *
 ****************************************************************************/

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void UART_init(const UART_ConfigType *Config_Ptr)
{
	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	uint16 ubrr_value = 0 ;

	UCSRB |= (1<<RXEN) | (1<<TXEN) ;

	UCSRC |= (1<<URSEL) ;

	switch(Config_Ptr->bit_data)
	{
	case Five_Bit_Data :
		CLEAR_BIT(UCSRB,UCSZ2);
		CLEAR_BIT(UCSRC,UCSZ0);
		CLEAR_BIT(UCSRC,UCSZ1);
		break;
	case Six_Bit_Data :
		CLEAR_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC,UCSZ0);
		CLEAR_BIT(UCSRC,UCSZ1);
		break;
	case Seven_Bit_Data :
		CLEAR_BIT(UCSRB,UCSZ2);
		CLEAR_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		break;
	case Eight_Bit_Data :
		CLEAR_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		break;
	case Nine_Bit_Data :
		SET_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		break;
	}

	switch(Config_Ptr->parity)
	{
	case Disable_Parity :
		UCSRC = ( UCSRC & 0xCF ) | ( Disable_Parity << 4 ) ;
		break;
	case Even_Parity :
		UCSRC = ( UCSRC & 0xCF ) | ( Even_Parity << 4 ) ;
		break;
	case Odd_Parity :
		UCSRC = ( UCSRC & 0xCF ) | ( Odd_Parity << 4 ) ;
		break;
	}

	switch(Config_Ptr->stop_bit)
	{
	case One_Bit_Stop :
		UCSRC = ( UCSRC & 0xF7 ) | ( One_Bit_Stop << 3 ) ;
		break;
	case Two_Bit_Stop :
		UCSRC = ( UCSRC & 0xF7 ) | ( Two_Bit_Stop << 3 ) ;
		break;
	}

	ubrr_value = (uint16)(((F_CPU / ((Config_Ptr->baud_rate) * 8UL))) - 1);

	UBRRH = ( ubrr_value >> 8 )  ;

	UBRRL = ubrr_value  ;
}

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void UART_sendByte(const uint8 data)
{
	while(!(UCSRA & (1<<UDRE)));

	UDR = data ;
}

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
uint8 UART_receiveByte(void)
{
	while(!(UCSRA & (1<<RXC)));

	return UDR ;
}

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void UART_sendString(const uint8 *Str)
{
	uint8 index = 0 ;
	while( Str[index] != '\0')
	{
		UART_sendByte(Str[index]);
		index++ ;
	}
}

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void UART_receiveString(uint8 *Str)
{
	uint8 index = 0 ;

	Str[index] = UART_receiveByte();

	while(Str[index] != '#')
	{
		index++ ;
		Str[index] = UART_receiveByte();
	}

	Str[index] = '\0' ;
}
