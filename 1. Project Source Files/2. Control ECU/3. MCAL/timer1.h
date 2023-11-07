/*
 ============================================================================
 Name        : timer1.h
 Author      : Ahmed Shawky
 Description : Header File for Timer1 Driver
 Date        : 16/09/2023
 ============================================================================
 */

#ifndef TIMER1_H_
#define TIMER1_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "std_types.h"

/****************************************************************************
 * 					          Types Declaration						        *
 ****************************************************************************/

typedef enum
{
	F_CPU_1 = 0x01,

	F_CPU_8,

	F_CPU_64,

	F_CPU_256,

	F_CPU_1024

}Timer1_Prescaler;

typedef enum
{
	Timer1_Normal_Mode,

	Timer1_Compare_Mode,

	Timer1_PWM_Mode

}Timer1_Mode;

typedef struct
{
	uint16 initial_value ;

	uint16 	compare_value ;

	Timer1_Prescaler prescaler ;

	Timer1_Mode mode ;

}Timer1_ConfigType;


/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void Timer1_init(const Timer1_ConfigType *Config_Ptr);

/* Inputs:
 *
 * Return Value: void.
 *
 * Description:
 *
 */
void Timer1_deInit(void);

/* Inputs:
 * 	1. Pointer to a Call Back function has a parameter void and return void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
