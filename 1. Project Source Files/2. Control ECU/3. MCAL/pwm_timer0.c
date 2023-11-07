/*
 ============================================================================
 Name        : pwm_timer0.c
 Author      : Ahmed Shawky
 Description : Source File for PWM Driver using Timer 0
 Date        : 02/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "pwm_timer0.h"

/****************************************************************************
 * 							Functions Definitions						    *
 ****************************************************************************/

/* Inputs:
 * 	1. duty_cycle: The required duty cycle percentage of the generated PWM signal.
 *
 * Return Value: void.
 *
 * Description:
 * 	The function responsible for trigger the Timer0 with the PWM Mode.
 * 	Setup the PWM mode with Non-Inverting.
 * 	Setup the prescaler with F_CPU/8.
 * 	Setup the compare value based on the required input duty cycle.
 *	Setup the direction for OC0 as output pin through the GPIO driver.
 *	The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 */
void PWM_Timer0_Start(float duty_cycle)
{
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01) ;

	TCNT0 = 0 ;

	OCR0 = ( duty_cycle * 255 ) ;
}
