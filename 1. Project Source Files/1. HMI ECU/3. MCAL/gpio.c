/*
 ============================================================================
 Name        : gpio.c
 Author      : Ahmed Shawky
 Description : Source File for GPIO Driver
 Date        : 28/08/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <avr/io.h>
#include "gpio.h"
#include "common_macros.h"

/****************************************************************************
 * 							Functions Definitions						    *
 ****************************************************************************/

/* Inputs:
 * 	1. port_num  : ID for the port number.
 * 	2. pin_num   : ID for the pin number.
 * 	3. direction : The required direction for this pin its value should be PIN_INPUT or PIN_OUTPUT.
 *
 * Return Value: void.
 *
 * Description:
 * 	Setup the direction of the required pin input/output.
 * 	If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num,
		uint8 pin_num,
		GPIO_PinDirectionType direction)
{
	if((port_num >= PORTA_ID) && (port_num <= PORTD_ID))
	{
		if((pin_num >= PIN0_ID) && (pin_num <= PIN7_ID))
		{
			switch(port_num)
			{
			case PORTA_ID :
				if(PIN_INPUT == direction)
				{
					CLEAR_BIT(DDRA,pin_num);
				}
				else if(PIN_OUTPUT == direction)
				{
					SET_BIT(DDRA,pin_num);
				}
				break;
			case PORTB_ID :
				if(PIN_INPUT == direction)
				{
					CLEAR_BIT(DDRB,pin_num);
				}
				else if(PIN_OUTPUT == direction)
				{
					SET_BIT(DDRB,pin_num);
				}
				break;
			case PORTC_ID :
				if(PIN_INPUT == direction)
				{
					CLEAR_BIT(DDRC,pin_num);
				}
				else if(PIN_OUTPUT == direction)
				{
					SET_BIT(DDRC,pin_num);
				}
				break;
			case PORTD_ID :
				if(PIN_INPUT == direction)
				{
					CLEAR_BIT(DDRD,pin_num);
				}
				else if(PIN_OUTPUT == direction)
				{
					SET_BIT(DDRD,pin_num);
				}
				break;
			}
		}
		else
		{
			/* Do Nothing. */
		}
	}
	else
	{
		/* Do Nothing. */
	}
}

/* Inputs:
 * 	1. port_num  : ID for the port number.
 * 	2. pin_num   : ID for the pin number.
 * 	3. value     : value to be written on this pin it should be LOGIC_HIGH or LOGIC_LOW.
 *
 * Return Value: void.
 *
 * Description:
 * 	Write the value Logic High or Logic Low on the required pin.
 * 	If the input port number or pin number are not correct, The function will not handle the request.
 * 	If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num,
		uint8 pin_num,
		uint8 value)
{
	if((port_num >= PORTA_ID) && (port_num <= PORTD_ID))
	{
		if((pin_num >= PIN0_ID) && (pin_num <= PIN7_ID))
		{
			switch(port_num)
			{
			case PORTA_ID :
				if(LOGIC_LOW == value)
				{
					CLEAR_BIT(PORTA,pin_num);
				}
				else if(LOGIC_HIGH == value)
				{
					SET_BIT(PORTA,pin_num);
				}
				break;
			case PORTB_ID :
				if(LOGIC_LOW == value)
				{
					CLEAR_BIT(PORTB,pin_num);
				}
				else if(LOGIC_HIGH == value)
				{
					SET_BIT(PORTB,pin_num);
				}
				break;
			case PORTC_ID :
				if(LOGIC_LOW == value)
				{
					CLEAR_BIT(PORTC,pin_num);
				}
				else if(LOGIC_HIGH == value)
				{
					SET_BIT(PORTC,pin_num);
				}
				break;
			case PORTD_ID :
				if(LOGIC_LOW == value)
				{
					CLEAR_BIT(PORTD,pin_num);
				}
				else if(LOGIC_HIGH == value)
				{
					SET_BIT(PORTD,pin_num);
				}
				break;
			}
		}
		else
		{
			/* Do Nothing. */
		}
	}
	else
	{
		/* Do Nothing. */
	}
}

/* Inputs:
 * 	1. port_num  : ID for the port number.
 * 	2. pin_num   : ID for the pin number.
 *
 * Return Value: pin value it should be LOGIC_HIGH or LOGIC_LOW.
 *
 * Description:
 * 	Read and return the value for the required pin, it should be LOGIC_HIGH or LOGIC_LOW.
 * 	If the input port number or pin number are not correct, The function will return LOGIC_LOW.
 */
uint8 GPIO_readPin(uint8 port_num,
		uint8 pin_num)
{
	uint8 value = LOGIC_LOW ;

	if((port_num >= PORTA_ID) && (port_num <= PORTD_ID))
	{
		if((pin_num >= PIN0_ID) && (pin_num <= PIN7_ID))
		{
			switch(port_num)
			{
			case PORTA_ID :
				if(BIT_IS_SET(PINA,pin_num))
				{
					value = LOGIC_HIGH ;
				}
				else if(BIT_IS_CLEAR(PINA,pin_num))
				{
					value = LOGIC_LOW ;
				}
				break;
			case PORTB_ID :
				if(BIT_IS_SET(PINB,pin_num))
				{
					value = LOGIC_HIGH ;
				}
				else if(BIT_IS_CLEAR(PINB,pin_num))
				{
					value = LOGIC_LOW ;
				}
				break;
			case PORTC_ID :
				if(BIT_IS_SET(PINC,pin_num))
				{
					value = LOGIC_HIGH ;
				}
				else if(BIT_IS_CLEAR(PINC,pin_num))
				{
					value = LOGIC_LOW ;
				}
				break;
			case PORTD_ID :
				if(BIT_IS_SET(PIND,pin_num))
				{
					value = LOGIC_HIGH ;
				}
				else if(BIT_IS_CLEAR(PIND,pin_num))
				{
					value = LOGIC_LOW ;
				}
				break;
			}
		}
		else
		{
			/* Do Nothing. */
		}
	}
	else
	{
		/* Do Nothing. */
	}

	return value ;
}

/* Inputs:
 * 	1. port_num  : ID for the port number.
 * 	2. direction : The required direction for all port its value should be PORT_INPUT or PORT_OUTPUT.
 *
 * Return Value: void.
 *
 * Description:
 * 	Setup the direction of the required port all pins input/output.
 * 	If the direction value is PORT_INPUT all pins in this port should be input pins.
 * 	If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * 	If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num,
		GPIO_PortDirectionType direction)
{
	if((port_num >= PORTA_ID) && (port_num <= PORTD_ID))
	{
		switch(port_num)
		{
		case PORTA_ID :
			if(PORT_INPUT == direction)
			{
				DDRA = PORT_INPUT ;
			}
			else if(PORT_OUTPUT == direction)
			{
				DDRA = PORT_OUTPUT ;
			}
			break;
		case PORTB_ID :
			if(PORT_INPUT == direction)
			{
				DDRB = PORT_INPUT ;
			}
			else if(PORT_OUTPUT == direction)
			{
				DDRB = PORT_OUTPUT ;
			}
			break;
		case PORTC_ID :
			if(PORT_INPUT == direction)
			{
				DDRC = PORT_INPUT ;
			}
			else if(PORT_OUTPUT == direction)
			{
				DDRC = PORT_OUTPUT ;
			}
			break;
		case PORTD_ID :
			if(PORT_INPUT == direction)
			{
				DDRD = PORT_INPUT ;
			}
			else if(PORT_OUTPUT == direction)
			{
				DDRD = PORT_OUTPUT ;
			}
			break;
		}
	}
	else
	{
		/* Do Nothing. */
	}
}

/* Inputs:
 * 	1. port_num  : ID for the port number.
 * 	2. value     : value to be written on all port pins.
 *
 * Return Value: void.
 *
 * Description:
 * 	Write the value on the required port.
 * 	If any pin in the port is output pin the value will be written.
 * 	If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * 	If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num,
		uint8 value)
{
	if((port_num >= PORTA_ID) && (port_num <= PORTD_ID))
	{
		switch(port_num)
		{
		case PORTA_ID :
			PORTA = value ;
			break;
		case PORTB_ID :
			PORTB = value ;
			break;
		case PORTC_ID :
			PORTC = value ;
			break;
		case PORTD_ID :
			PORTD = value ;
			break;
		}
	}
	else
	{
		/* Do Nothing. */
	}
}

/* Inputs:
 * 	1. port_num  : ID for the port number.
 *
 * Return Value: value for all the pins on this port.
 *
 * Description:
 * 	Read and return the value of the required port.
 * 	If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = 0 ;

	if((port_num >= PORTA_ID) && (port_num <= PORTD_ID))
	{
		switch(port_num)
		{
		case PORTA_ID :
			value = PINA ;
			break;
		case PORTB_ID :
			value = PINB ;
			break;
		case PORTC_ID :
			value = PINC ;
			break;
		case PORTD_ID :
			value = PIND ;
			break;
		}
	}
	else
	{
		/* Do Nothing. */
	}

	return value ;
}


