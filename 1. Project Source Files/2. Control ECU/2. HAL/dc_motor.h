/*
 ============================================================================
 Name        : dc_motor.h
 Author      : Ahmed Shawky
 Description : Header File for DC-Motor Driver
 Date        : 02/09/2023
 ============================================================================
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "gpio.h"
#include "pwm_timer0.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/
#define L293D_IN1_PORT		PORTB_ID
#define L293D_IN1_PIN 		PIN1_ID

#define L293D_IN2_PORT 		PORTB_ID
#define L293D_IN2_PIN 		PIN2_ID


/****************************************************************************
 * 					          Types Declaration						        *
 ****************************************************************************/
typedef enum
{
	MOTOR_OFF,
	MOTOR_CW,
	MOTOR_ACW
}DcMotor_State;

/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 *	Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void);

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
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */
