/*
 ============================================================================
 Name        : lcd.h
 Author      : Ahmed Shawky
 Description : Header File for LCD
 Date        : 29/08/2023
 ============================================================================
 */

#ifndef LCD_H_
#define LCD_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "std_types.h"


/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   		 0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

#define LCD_DATA_BITS_MODE 			         (LCD_TWO_LINES_FOUR_BITS_MODE)

/* LCD HW Ports and Pins IDs */
#define LCD_RS_PORT_ID                 		 PORTA_ID
#define LCD_RS_PIN_ID                        PIN4_ID

#define LCD_E_PORT_ID                        PORTA_ID
#define LCD_E_PIN_ID                         PIN5_ID

#if(LCD_TWO_LINES_EIGHT_BITS_MODE == LCD_DATA_BITS_MODE)
#define LCD_DATA_PORT_ID                     PORTC_ID
#elif(LCD_TWO_LINES_FOUR_BITS_MODE == LCD_DATA_BITS_MODE)
#define LCD_DATA_PORT_ID			         PORTA_ID

#define LCD_DATA_PIN1_ID 			         PIN0_ID
#define LCD_DATA_PIN2_ID			         PIN1_ID
#define LCD_DATA_PIN3_ID 			         PIN2_ID
#define LCD_DATA_PIN4_ID			         PIN3_ID
#endif

/****************************************************************************
 * 							Functions Prototypes						    *
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
void LCD_init(void);

/* Inputs:
 * 	1. The required command to be sent to the screen.
 *
 * Return Value: void.
 *
 * Description:
 * 	Send the required command to the screen
 */
void LCD_sendCommand(uint8 command);

/* Inputs:
 * 	1. The required character to be sent to the screen.
 *
 * Return Value: void.
 *
 * Description:
 * 	Display the required character on the screen.
 */
void LCD_displayCharacter(uint8 data);

/* Inputs:
 * 	1. Pointer to the required string (array of characters) to be sent to the screen.
 *
 * Return Value: void.
 *
 * Description:
 * 	Display the required string on the screen.
 */
void LCD_displayString(const char *Str);

/* Inputs:
 * 	1. The required row.
 * 	2. The required column.
 *
 * Return Value: void.
 *
 * Description:
 * 	Move the cursor to a specified row and column index on the screen.
 */
void LCD_moveCursor(uint8 row, uint8 col);

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
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str);

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 * 	Send the clear screen command.
 */
void LCD_clearScreen(void);

/* Inputs:
 * 	1. The required decimal value to convert it to character to display it on the screen.
 *
 * Return Value: void.
 *
 * Description:
 * 	Display the required decimal value on the screen
 */
void LCD_integerToString(int data);


#endif /* LCD_H_ */
