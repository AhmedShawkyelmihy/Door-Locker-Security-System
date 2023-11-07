/*
 ============================================================================
 Name        : dc_motor.c
 Author      : Ahmed Shawky
 Description : Source File for DC-Motor Driver
 Date        : 02/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "dc_motor.h"

/****************************************************************************
 * 							Functions Definitions						    *
 ****************************************************************************/

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 *	Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(L293D_IN1_PORT, L293D_IN1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(L293D_IN2_PORT, L293D_IN2_PIN, PIN_OUTPUT);

	PWM_Timer0_Start(0);
}

/* Inputs:
 * 	1. state: The required DC Motor state, it should be CW or A-CW or stop.
 * 	2. speed: decimal value for the required motor speed, it should be from 0 → 100.
 *
 * Return Value: void.
 *
 * Description:
 *	The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor
 *	based on the state input state value.
 *	Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	float duty_cycle ;
	switch(state)
	{
	case MOTOR_OFF :
		GPIO_writePin(L293D_IN1_PORT, L293D_IN1_PIN, LOGIC_LOW);
		GPIO_writePin(L293D_IN2_PORT, L293D_IN2_PIN, LOGIC_LOW);
		PWM_Timer0_Start(0);
		break;
	case MOTOR_CW :
		duty_cycle = ((float)speed/100) ;
		GPIO_writePin(L293D_IN1_PORT, L293D_IN1_PIN, LOGIC_HIGH);
		GPIO_writePin(L293D_IN2_PORT, L293D_IN2_PIN, LOGIC_LOW);
		PWM_Timer0_Start(duty_cycle);
		break;
	case MOTOR_ACW :
		duty_cycle = ((float)speed/100) ;
		GPIO_writePin(L293D_IN1_PORT, L293D_IN1_PIN, LOGIC_LOW);
		GPIO_writePin(L293D_IN2_PORT, L293D_IN2_PIN, LOGIC_HIGH);
		PWM_Timer0_Start(duty_cycle);
		break;
	}
}


