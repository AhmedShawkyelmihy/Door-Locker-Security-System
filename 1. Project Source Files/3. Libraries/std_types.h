/*
 ============================================================================
 Name        : std_types.h
 Author      : Ahmed Shawky
 Description : Header File for AVR Standard Types
 Date        : 28/08/2023
 ============================================================================
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Boolean Data Type */
typedef unsigned char boolean ;

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define LOGIC_HIGH        (1u)
#define LOGIC_LOW         (0u)

#define NULL_PTR    ((void*)0)

typedef unsigned char 		uint8 ;
typedef signed char 		sint8 ;
typedef unsigned short 		uint16 ;
typedef signed short 		sint16 ;
typedef unsigned long 		uint32 ;
typedef signed long 		sint32 ;
typedef unsigned long long 	uint64 ;
typedef signed long long 	sint64 ;
typedef float 				float32 ;
typedef double 				float64 ;

#endif /* STD_TYPES_H_ */
