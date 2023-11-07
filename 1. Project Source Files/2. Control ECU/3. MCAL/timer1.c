/*
 ============================================================================
 Name        : timer1.c
 Author      : Ahmed Shawky
 Description : Source File for Timer1 Driver
 Date        : 16/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer1.h"
#include "common_macros.h"

/****************************************************************************
 * 						   Static Global Variables							*
 ****************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR ;


/****************************************************************************
 * 						 Interrupt Service Routines							*
 ****************************************************************************/
ISR(TIMER1_OVF_vect)
{
	SET_BIT(TIFR,TOV1);

	if(g_callBackPtr != NULL_PTR)
	{
		g_callBackPtr();
	}
}

ISR(TIMER1_COMPA_vect)
{
	SET_BIT(TIFR,OCF1A);

	if(g_callBackPtr != NULL_PTR)
	{
		g_callBackPtr();
	}
}

/****************************************************************************
 * 							Functions Definitions						    *
 ****************************************************************************/

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void Timer1_init(const Timer1_ConfigType *Config_Ptr)
{
	switch(Config_Ptr->mode)
	{
	case Timer1_Normal_Mode :

		/* Normal port operation, OC1A/OC1B disconnected. */
		CLEAR_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);

		/* Specifies a non-PWM mode */
		SET_BIT(TCCR1A,FOC1A);

		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);

		SET_BIT(TIMSK,TOIE1);
		break;
	case Timer1_Compare_Mode :

		/* Toggle OC1A/OC1B on compare match */
		SET_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);

		/* Specifies a non-PWM mode */
		SET_BIT(TCCR1A,FOC1A);

		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);

		SET_BIT(TIMSK,OCIE1A);
		break;
	case Timer1_PWM_Mode :

		/* Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM, (non-inverting mode) */
		SET_BIT(TCCR1A,COM1A1);
		CLEAR_BIT(TCCR1A,COM1A0);

		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	}

	switch(Config_Ptr->prescaler)
	{
	case F_CPU_1 :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_1 ;
		break;
	case F_CPU_8 :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_8 ;
		break;
	case F_CPU_64 :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_64 ;
		break;
	case F_CPU_256 :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_256 ;
		break;
	case F_CPU_1024 :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_1024 ;
		break;
	}

	TCNT1 = (Config_Ptr->initial_value) ;

#if(TIMER1_SELECTED_MODE == TIMER1_COMPARE_MODE)
	OCR1A = (Config_Ptr->compare_value) ;
#endif
}

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void Timer1_deInit(void)
{
	TCCR1A = 0 ;
	TCCR1B = 0 ;
	TIMSK = 0 ;
	TCNT1 = 0 ;

#if(TIMER1_SELECTED_MODE == TIMER1_COMPARE_MODE)
	OCR1A = 0 ;
#endif
}

/* Inputs:
 * 	1. Pointer to a Call Back function has a parameter void and return void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr ;
}

