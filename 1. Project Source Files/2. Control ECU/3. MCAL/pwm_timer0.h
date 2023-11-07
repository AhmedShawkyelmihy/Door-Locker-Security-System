/*
 ============================================================================
 Name        : pwm_timer0.h
 Author      : Ahmed Shawky
 Description : Header File for PWM Driver using Timer 0
 Date        : 02/09/2023
 ============================================================================
 */

#ifndef PWM_TIMER0_H_
#define PWM_TIMER0_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <avr/io.h>
#include "std_types.h"
#include "gpio.h"

/****************************************************************************
 * 							Functions Prototypes						    *
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
void PWM_Timer0_Start(float duty_cycle);


#endif /* PWM_TIMER0_H_ */
