/*
 ============================================================================
 Name        : buzzer.h
 Author      : Ahmed Shawky
 Description : Header File for Buzzer Driver
 Date        : 16/09/2023
 ============================================================================
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/
#define BUZZER_PORT_ID 		PORTB_ID
#define BUZZER_PIN_ID 		PIN0_ID

/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Setup the direction for the buzzer pin as output pin through the GPIO driver.
 *	Turn off the buzzer through the GPIO.
 */
void Buzzer_init(void);

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void);

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
