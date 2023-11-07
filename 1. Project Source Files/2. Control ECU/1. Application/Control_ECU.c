/*
 ============================================================================
 Name        : Control_ECU.c
 Author      : Ahmed Shawky
 Description : Source File (Application Code) for Control ECU
 Date        : 19/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <util/delay.h>
#include "buzzer.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include "uart.h"
#include "timer1.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/
#define PASSWORD_SIZE 	  					5

#define CREATE_PASSWORD_CMD					0x10
#define OPEN_DOOR_CMD 						0x11
#define CHANGE_PASSWORD_CMD 				0x12

#define SUCCESSFUL_PASSWORD_CHECK   		0x20
#define UNSUCCESSFUL_PASSWORD_CHECK   		0x19

/****************************************************************************
 * 							   Global Variables								*
 ****************************************************************************/
uint8 password[PASSWORD_SIZE];
uint8 password_check[PASSWORD_SIZE];

uint8 g_counter;
uint8 g_command;
uint8 g_check_status;
uint8 g_count_faults;

/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/
void Control_ECU_fetchCommand(void);
void Control_ECU_receivePassword(uint8 *password_buffer,uint8 size);
void Control_ECU_checkPassword(uint8 *password_buffer_1,uint8 *password_buffer_2,uint8 size);
void Control_ECU_writePassword(uint8 *password_buffer,uint8 size);
void Control_ECU_checkSavedPassword(uint8 *password_buffer_1,uint8 *password_buffer_2,uint8 size);
void Control_ECU_controllingDcMotorConfig(void);
void Control_ECU_activateBuzzerConfig(void);
void Control_ECU_callBackFunction(void);


/****************************************************************************
 * 							   Main Function								*
 ****************************************************************************/
int main()
{
	sei();

	DcMotor_Init();

	Buzzer_init();

	UART_ConfigType UART_ConfigStruct ;
	UART_ConfigStruct.baud_rate = 19200 ;
	UART_ConfigStruct.bit_data = Eight_Bit_Data ;
	UART_ConfigStruct.parity = Disable_Parity ;
	UART_ConfigStruct.stop_bit = One_Bit_Stop ;
	UART_init(&UART_ConfigStruct);

	while(1)
	{
		Control_ECU_fetchCommand();
	}

	return 0 ;
}

void Control_ECU_fetchCommand(void)
{
	g_command = UART_receiveByte();
	switch(g_command)
	{
	case CREATE_PASSWORD_CMD :
		Control_ECU_receivePassword(password,PASSWORD_SIZE);
		Control_ECU_receivePassword(password_check,PASSWORD_SIZE);
		Control_ECU_checkPassword(password, password_check, PASSWORD_SIZE);
		if(g_check_status == SUCCESSFUL_PASSWORD_CHECK)
		{
			Control_ECU_writePassword(password, PASSWORD_SIZE);
		}
		break;
	case OPEN_DOOR_CMD :
		Control_ECU_receivePassword(password,PASSWORD_SIZE);
		Control_ECU_checkSavedPassword(password, password_check, PASSWORD_SIZE);
		if(g_check_status == SUCCESSFUL_PASSWORD_CHECK)
		{
			g_count_faults = 0 ;
			Control_ECU_controllingDcMotorConfig();
		}
		else
		{
			g_count_faults += 1 ;
		}
		if(g_count_faults == 3)
		{
			Control_ECU_activateBuzzerConfig();
			g_count_faults = 0 ;
		}
		break;
	case CHANGE_PASSWORD_CMD :
		Control_ECU_receivePassword(password,PASSWORD_SIZE);
		Control_ECU_checkSavedPassword(password, password_check, PASSWORD_SIZE);
		if(g_check_status == SUCCESSFUL_PASSWORD_CHECK)
		{
			g_count_faults = 0 ;
			Control_ECU_writePassword(password, PASSWORD_SIZE);
		}
		else
		{
			g_count_faults += 1 ;
		}
		if(g_count_faults == 3)
		{
			Control_ECU_activateBuzzerConfig();
			g_count_faults = 0 ;
		}
		break;
	}
}

void Control_ECU_receivePassword(uint8 *password_buffer,uint8 size)
{
	uint8 index ;
	for(index = 0 ; index < size ; index++)
	{
		password_buffer[index] = UART_receiveByte();
	}
}

void Control_ECU_checkPassword(uint8 *password_buffer_1,uint8 *password_buffer_2,uint8 size)
{
	g_check_status = SUCCESSFUL_PASSWORD_CHECK ;
	uint8 index ;
	for(index = 0 ; index < size ; index++)
	{
		if(password_buffer_1[index] != password_buffer_2[index])
		{
			g_check_status = UNSUCCESSFUL_PASSWORD_CHECK ;
		}
	}

	UART_sendByte(g_check_status);
}

void Control_ECU_writePassword(uint8 *password_buffer,uint8 size)
{
	uint8 index ;
	for(index = 0 ; index < size ; index++)
	{
		EEPROM_writeByte((0x0311+index), password_buffer[index]);
	}
}

void Control_ECU_checkSavedPassword(uint8 *password_buffer_1,uint8 *password_buffer_2,uint8 size)
{
	g_check_status = SUCCESSFUL_PASSWORD_CHECK ;
	uint8 index ;
	for(index = 0 ; index < size ; index++)
	{
		EEPROM_readByte((0x0311+index), &password_buffer_2[index]);
	}
	for(index = 0 ; index < size ; index++)
	{
		if(password_buffer_1[index] != password_buffer_2[index])
		{
			g_check_status = UNSUCCESSFUL_PASSWORD_CHECK ;
		}
	}

	UART_sendByte(g_check_status);
}

void Control_ECU_controllingDcMotorConfig(void)
{
	g_counter = 0 ;
	Timer1_setCallBack(Control_ECU_callBackFunction);
	Timer1_ConfigType Timer1_ConfigStruct;
	Timer1_ConfigStruct.mode = Timer1_Compare_Mode ;
	Timer1_ConfigStruct.prescaler = F_CPU_1024 ;
	Timer1_ConfigStruct.initial_value = 0 ;
	Timer1_ConfigStruct.compare_value = 7812 ;
	Timer1_init(&Timer1_ConfigStruct);
	while(!(g_counter == 33))
	{
		if(g_counter < 15)
		{
			DcMotor_Rotate(MOTOR_CW, 100);
		}
		if(g_counter == 15)
		{
			DcMotor_Rotate(MOTOR_OFF, 0);
		}
		if(g_counter == 18)
		{
			DcMotor_Rotate(MOTOR_ACW, 100);
		}
	}
	Timer1_deInit();
	DcMotor_Rotate(MOTOR_OFF, 0);
	g_counter = 0 ;
}

void Control_ECU_activateBuzzerConfig(void)
{
	g_counter = 0 ;
	Timer1_setCallBack(Control_ECU_callBackFunction);
	Timer1_ConfigType Timer1_ConfigStruct;
	Timer1_ConfigStruct.mode = Timer1_Compare_Mode ;
	Timer1_ConfigStruct.prescaler = F_CPU_1024 ;
	Timer1_ConfigStruct.initial_value = 0 ;
	Timer1_ConfigStruct.compare_value = 7812 ;
	Timer1_init(&Timer1_ConfigStruct);
	while(!(g_counter == 60))
	{
		Buzzer_on();
	}
	Timer1_deInit();
	Buzzer_off();
	g_counter = 0 ;
}

void Control_ECU_callBackFunction(void)
{
	g_counter += 1 ;
	TCNT1 = 0 ;
}
