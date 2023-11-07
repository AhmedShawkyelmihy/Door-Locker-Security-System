/*
 ============================================================================
 Name        : HMI_ECU.c
 Author      : Ahmed Shawky
 Description : Source File (Application Code) for HMI ECU
 Date        : 19/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"
#include "timer1.h"
#include "uart.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/
#define PASSWORD_SIZE 	  					5
#define ENTER_VALUE 	  					13

#define CREATE_PASSWORD_CMD					0x10
#define OPEN_DOOR_CMD 						0x11
#define CHANGE_PASSWORD_CMD 				0x12

#define SUCCESSFUL_PASSWORD_CHECK   		0x20
#define UNSUCCESSFUL_PASSWORD_CHECK   		0x19

#define DISPLAY_CREATE_PASSWORD_SCREEN   	0x21
#define DISPLAY_MAIN_OPTIONS_SCREEN 		0x22
#define DISPLAY_CONTROL_SCREEN 				0x23

/****************************************************************************
 * 							   Global Variables								*
 ****************************************************************************/
uint8 password[PASSWORD_SIZE];
uint8 password_again[PASSWORD_SIZE];

uint8 g_flag = DISPLAY_CREATE_PASSWORD_SCREEN ;
uint8 g_counter ;
uint8 g_count_faults ;

/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/
void HMI_ECU_createPassword(uint8 *password_buffer_1,uint8 *password_buffer_2,uint8 size);
void HMI_ECU_enterPassword(uint8 *password_buffer, uint8 size);
void HMI_ECU_re_enterPassword(uint8 *password_buffer, uint8 size);
void HMI_ECU_sendPassword(uint8 *password_buffer, uint8 size);
void HMI_ECU_mainOptionsScreen(uint8 *password_buffer, uint8 size);
void HMI_ECU_displayControlScreenConfig(void);
void HMI_ECU_displayErrorMessageConfig(void);
void HMI_ECU_callBackFunction(void);

/****************************************************************************
 * 							   Main Function								*
 ****************************************************************************/
int main()
{
	sei();

	LCD_init();

	UART_ConfigType UART_ConfigStruct ;
	UART_ConfigStruct.baud_rate = 19200 ;
	UART_ConfigStruct.bit_data = Eight_Bit_Data ;
	UART_ConfigStruct.parity = Disable_Parity ;
	UART_ConfigStruct.stop_bit = One_Bit_Stop ;
	UART_init(&UART_ConfigStruct);

	while(1)
	{
		if(g_flag == DISPLAY_CREATE_PASSWORD_SCREEN)
		{
			HMI_ECU_createPassword(password, password_again, PASSWORD_SIZE);
			if(UART_receiveByte() == SUCCESSFUL_PASSWORD_CHECK)
			{
				g_flag = DISPLAY_MAIN_OPTIONS_SCREEN ;
			}
		}
		if(g_flag == DISPLAY_MAIN_OPTIONS_SCREEN)
		{
			HMI_ECU_mainOptionsScreen(password, PASSWORD_SIZE);
		}
		if(g_flag == DISPLAY_CONTROL_SCREEN)
		{
			HMI_ECU_displayControlScreenConfig();
		}
		if(g_count_faults == 3)
		{
			HMI_ECU_displayErrorMessageConfig();
		}
	}

	return 0 ;
}

/****************************************************************************
 * 							Functions Definitions						    *
 ****************************************************************************/
void HMI_ECU_createPassword(uint8 *password_buffer_1,uint8 *password_buffer_2,uint8 size)
{
	UART_sendByte(CREATE_PASSWORD_CMD);
	HMI_ECU_enterPassword(password_buffer_1,size);
	HMI_ECU_re_enterPassword(password_buffer_2,size);
}

void HMI_ECU_enterPassword(uint8 *password_buffer, uint8 size)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "plz enter pass: ");
	LCD_moveCursor(1, 0);
	uint8 index ;
	for(index = 0 ; index < size ; index++)
	{
		password_buffer[index] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(250);
	}
	while(!(KEYPAD_getPressedKey() == ENTER_VALUE));
	_delay_ms(250);
	HMI_ECU_sendPassword(password_buffer, size);
}

void HMI_ECU_re_enterPassword(uint8 *password_buffer, uint8 size)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "plz re-enter the");
	LCD_displayStringRowColumn(1, 0, "same pass: ");
	uint8 index ;
	for(index = 0 ; index < size ; index++)
	{
		password_buffer[index] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(250);
	}
	while(!(KEYPAD_getPressedKey() == ENTER_VALUE));
	_delay_ms(250);
	HMI_ECU_sendPassword(password_buffer, size);
}

void HMI_ECU_sendPassword(uint8 *password_buffer,uint8 size)
{
	uint8 index ;
	for(index = 0 ; index < size ; index++)
	{
		UART_sendByte(password_buffer[index]);
	}
}

void HMI_ECU_mainOptionsScreen(uint8 *password_buffer, uint8 size)
{
	uint8 key_value;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "+ : Open Door");
	LCD_displayStringRowColumn(1, 0, "- : Change Pass");
	key_value = KEYPAD_getPressedKey();
	_delay_ms(250);
	while(!((key_value == '+') || (key_value == '-')))
	{
		key_value = KEYPAD_getPressedKey();
		_delay_ms(250);
	}
	switch(key_value)
	{
	case '+' :
		UART_sendByte(OPEN_DOOR_CMD);
		HMI_ECU_enterPassword(password_buffer, size);
		if(UART_receiveByte() == SUCCESSFUL_PASSWORD_CHECK)
		{
			g_count_faults = 0 ;
			g_flag = DISPLAY_CONTROL_SCREEN ;
		}
		else
		{
			g_count_faults += 1 ;
		}
		break;
	case '-' :
		UART_sendByte(CHANGE_PASSWORD_CMD);
		HMI_ECU_enterPassword(password_buffer, size);
		if(UART_receiveByte() == SUCCESSFUL_PASSWORD_CHECK)
		{
			g_count_faults = 0 ;
			g_flag = DISPLAY_CREATE_PASSWORD_SCREEN ;
		}
		else
		{
			g_count_faults += 1 ;
		}
		break;
	}
}

void HMI_ECU_displayControlScreenConfig(void)
{
	g_counter = 0 ;
	Timer1_setCallBack(HMI_ECU_callBackFunction);
	Timer1_ConfigType Timer1_ConfigStruct;
	Timer1_ConfigStruct.mode = Timer1_Compare_Mode ;
	Timer1_ConfigStruct.prescaler = F_CPU_1024 ;
	Timer1_ConfigStruct.initial_value = 0 ;
	Timer1_ConfigStruct.compare_value = 7812 ;
	Timer1_init(&Timer1_ConfigStruct);
	LCD_clearScreen();
	while(!(g_counter == 33))
	{
		if(g_counter < 15)
		{
			LCD_displayStringRowColumn(0, 0, "Door's Unlocking");
		}
		if(g_counter == 15)
		{
			LCD_displayStringRowColumn(0, 0, "Door is Unlocked");
		}
		if(g_counter == 18)
		{
			LCD_displayStringRowColumn(0, 0, "Door is Locking ");
		}
	}
	Timer1_deInit();
	g_counter = 0 ;
	g_flag = DISPLAY_MAIN_OPTIONS_SCREEN ;
}

void HMI_ECU_displayErrorMessageConfig(void)
{
	Timer1_setCallBack(HMI_ECU_callBackFunction);
	Timer1_ConfigType Timer1_ConfigStruct;
	Timer1_ConfigStruct.mode = Timer1_Compare_Mode ;
	Timer1_ConfigStruct.prescaler = F_CPU_1024 ;
	Timer1_ConfigStruct.initial_value = 0 ;
	Timer1_ConfigStruct.compare_value = 7812 ;
	Timer1_init(&Timer1_ConfigStruct);
	LCD_clearScreen();
	while(!(g_counter == 60))
	{
		LCD_displayStringRowColumn(0, 0, "error !!");
	}
	Timer1_deInit();
	g_count_faults = 0 ;
	g_counter = 0 ;
	g_flag = DISPLAY_MAIN_OPTIONS_SCREEN ;
}

void HMI_ECU_callBackFunction(void)
{
	g_counter += 1 ;
	TCNT1 = 0 ;
}
