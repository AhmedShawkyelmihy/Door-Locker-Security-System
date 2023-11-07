/*
 ============================================================================
 Name        : gpio.h
 Author      : Ahmed Shawky
 Description : Header File for GPIO Driver
 Date        : 28/08/2023
 ============================================================================
 */

#ifndef GPIO_H_
#define GPIO_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "std_types.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/
#define NUM_OF_PORTS 			4
#define NUM_OF_PINS_PER_PORT 	8

#define PORTA_ID 				0
#define PORTB_ID 				1
#define PORTC_ID 				2
#define PORTD_ID 				3

#define PIN0_ID 				0
#define PIN1_ID 				1
#define PIN2_ID 				2
#define PIN3_ID 				3
#define PIN4_ID 				4
#define PIN5_ID 				5
#define PIN6_ID 				6
#define PIN7_ID 				7

/****************************************************************************
 * 					          Types Declaration						        *
 ****************************************************************************/

/* 1. GPIO_PinDirectionTypedata type, it is used for the pin direction value. */
typedef enum
{
	PIN_INPUT,
	PIN_OUTPUT
}GPIO_PinDirectionType;

/* 2. GPIO_PortDirectionTypedata type, it is used for port direction value. */
typedef enum
{
	PORT_INPUT,
	PORT_OUTPUT = 0xFF
}GPIO_PortDirectionType;

/****************************************************************************
 * 							Functions Prototypes						    *
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
							GPIO_PinDirectionType direction);

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
				   uint8 value);

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
				   uint8 pin_num);

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
						     GPIO_PortDirectionType direction);

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
					uint8 value);

/* Inputs:
 * 	1. port_num  : ID for the port number.
 *
 * Return Value: value for all the pins on this port.
 *
 * Description:
 * 	Read and return the value of the required port.
 * 	If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
