/*
 ============================================================================
 Name        : lcd.c
 Author      : Ahmed Shawky
 Description : Source File for LCD
 Date        : 29/08/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h"
#include "gpio.h"
#include "common_macros.h"

/****************************************************************************
 * 							Functions Definitions						    *
 ****************************************************************************/

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 * 	Initialize the LCD:
 * 		1. Setup the LCD pins directions by use the GPIO driver.
 * 		2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void)
{
	/* Configure the direction for RS and E pins as output pins */
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

	/* LCD Power ON delay always > 15ms */
	_delay_ms(20);

	/* Configure the data port as output port */
#if(LCD_TWO_LINES_EIGHT_BITS_MODE == LCD_DATA_BITS_MODE)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
#elif(LCD_TWO_LINES_FOUR_BITS_MODE == LCD_DATA_BITS_MODE)
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN2_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN3_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN4_ID, PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
#endif

	/* Send LCD display mode command. */
	LCD_sendCommand(LCD_DATA_BITS_MODE);

	/* Send cursor off command. */
	LCD_sendCommand(LCD_CURSOR_OFF);

	/* Send clear LCD command at the beginning. */
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}

/* Inputs:
 * 	1. The required command to be sent to the screen.
 *
 * Return Value: void.
 *
 * Description:
 * 	Send the required command to the screen
 */
void LCD_sendCommand(uint8 command)
{
	/* Instruction Mode RS=0 */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	/* delay for processing Tas = 50ns */
	_delay_ms(1);

	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

#if(LCD_TWO_LINES_EIGHT_BITS_MODE == LCD_DATA_BITS_MODE)
	/* out the required command to the data bus D0 --> D7 */
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
#elif(LCD_TWO_LINES_FOUR_BITS_MODE == LCD_DATA_BITS_MODE)
	/* out the higher 4 bits of required command to the data bus */
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN1_ID, GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN2_ID, GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN3_ID, GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN4_ID, GET_BIT(command,7));

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);

	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

	/* out the lower 4 bits of required command to the data bus */
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN1_ID, GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN2_ID, GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN3_ID, GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN4_ID, GET_BIT(command,3));

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
#endif
}

/* Inputs:
 * 	1. The required character to be sent to the screen.
 *
 * Return Value: void.
 *
 * Description:
 * 	Display the required character on the screen.
 */
void LCD_displayCharacter(uint8 data)
{
	/* Data Mode RS=1 */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tas = 50ns */
	_delay_ms(1);

	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

#if(LCD_TWO_LINES_EIGHT_BITS_MODE == LCD_DATA_BITS_MODE)
	/* out the required data to the data bus D0 --> D7 */
	GPIO_writePort(LCD_DATA_PORT_ID, data);
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
#elif(LCD_TWO_LINES_FOUR_BITS_MODE == LCD_DATA_BITS_MODE)
	/* out the higher 4 bits of required data to the data bus */
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN1_ID, GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN2_ID, GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN3_ID, GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN4_ID, GET_BIT(data,7));

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);

	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

	/* out the lower 4 bits of required data to the data bus */
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN1_ID, GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN2_ID, GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN3_ID, GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN4_ID, GET_BIT(data,3));

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
#endif
}

/* Inputs:
 * 	1. Pointer to the required string (array of characters) to be sent to the screen.
 *
 * Return Value: void.
 *
 * Description:
 * 	Display the required string on the screen.
 */
void LCD_displayString(const char *Str)
{
	uint8 index = 0 ;
	while(Str[index] != '\0')
	{
		LCD_displayCharacter(Str[index]);
		index++ ;
	}
}

/* Inputs:
 * 	1. The required row.
 * 	2. The required column.
 *
 * Return Value: void.
 *
 * Description:
 * 	Move the cursor to a specified row and column index on the screen.
 */
void LCD_moveCursor(uint8 row, uint8 col)
{
	uint8 lcd_memory_address = 0 ;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
	case 0 :
		lcd_memory_address = col ;
		break;
	case 1 :
		lcd_memory_address = (col + 0x40) ;
		break;
	case 2 :
		lcd_memory_address = (col + 0x10) ;
		break;
	case 3 :
		lcd_memory_address = (col + 0x50) ;
		break;
	}

	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/* Inputs:
 * 	1. The required row.
 * 	2. The required column.
 * 	3. Pointer to the required string (array of characters) to be sent to the screen.
 *
 * Return Value: void.
 *
 * Description:
 * 	Display the required string in a specified row and column index on the screen.
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str)
{
	/* go to to the required LCD position */
	LCD_moveCursor(row,col);

	/* display the string */
	LCD_displayString(Str);
}

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 * 	Send the clear screen command.
 */
void LCD_clearScreen(void)
{
	/* Send clear display command */
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/* Inputs:
 * 	1. The required decimal value to convert it to character to display it on the screen.
 *
 * Return Value: void.
 *
 * Description:
 * 	Display the required decimal value on the screen
 */
void LCD_integerToString(int data)
{
	/* String to hold the ascii result */
	char buff[16];

	/* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	itoa(data,buff,10);

	/* Display the string */
	LCD_displayString(buff);
}

