/*
 * GPIO_Sys.c
 *
 *  Created on: Dec 11, 2023
 *      Author: steph
 */

#include <stm32f429xx.h>
#include <stdint.h>
#include "GPIO_Sys.h"

// Enumeration for PIN mode type
typedef enum
{
	GPIO_Mode_Input,
	GPIO_Mode_Output,
	GPIO_Mode_Alt,
	GPIO_Mode_Analogue,
}ePIN_MODE;


// Structure used to declare pin usage
typedef struct
{
	GPIO_TypeDef *pPort;					// Defined the port to use (GPIOA, GPIOB etc)
	uint8_t uc_Pin;							// Defines the Port Pin number (0-15)
	uint32_t ul_ClockSourceEnableBit;		// Clock source 'bit' to enable the port clock in AHPB1ENR
	ePIN_MODE eMode;						// Defines the Pin type, Input, Output, Alternate or Analogue

	// This would also include...
	// Output Type
	// Output Speed
	// Pull Up/Down
	// Alternate Function,
	// Debounce (ms)

}_GPIO_PIN_STRUCT;



//#define BANANA		0

#ifdef BANANA

Include this

#endif



// VARIANT 1 PCB - Actual product for instance.
#ifdef PCBVariant1

// Pin configuration...
_GPIO_PIN_STRUCT GPIO_Pins[] =
{
	// Inputs			  	PORT		Pin		Clock Source Bit		Mode
	[eGPIO_UserButton] = 	{GPIOA, 	1,		RCC_AHB1ENR_GPIOAEN,	GPIO_Mode_Input},
	[eGPIO_Interlock1] = 	{GPIOG,		12,		RCC_AHB1ENR_GPIOGEN,	GPIO_Mode_Input},
	[eGPIO_Interlock2] = 	{GPIOC,		11,		RCC_AHB1ENR_GPIOCEN,	GPIO_Mode_Input},
	[eGPIO_Interlock3] = 	{GPIOC,		11,		RCC_AHB1ENR_GPIOCEN,	GPIO_Mode_Input},


	// Outputs
	[eGPIO_IndicatorLED] = 	{GPIOG,		13,		RCC_AHB1ENR_GPIOGEN,	GPIO_Mode_Output},
	[eGPIO_SirenOutput] = 	{GPIOD,		12,		RCC_AHB1ENR_GPIODEN,	GPIO_Mode_Output},
	[eGPIO_WarningBeacon] = {GPIOE,		10,		RCC_AHB1ENR_GPIOEEN,	GPIO_Mode_Output},
};

// Simplify loops
#define NUM_GPIO_PINS		(sizeof (GPIO_Pins) / sizeof (_GPIO_PIN_STRUCT))

#endif // PCB Varaint 1


// VARIANT 2 PCB - Development kit for instance
#ifdef PCBVariant2

// Pin configuration...
_GPIO_PIN_STRUCT GPIO_Pins[] =
{
	// Inputs			  	PORT		Pin		Clock Source Bit		Mode
	[eGPIO_UserButton] = 	{GPIOA, 	10,		RCC_AHB1ENR_GPIOAEN,	GPIO_Mode_Input},
	[eGPIO_Interlock1] = 	{GPIOE,		1,		RCC_AHB1ENR_GPIOEEN,	GPIO_Mode_Input},
	[eGPIO_Interlock2] = 	{GPIOD,		13,		RCC_AHB1ENR_GPIODEN,	GPIO_Mode_Input},
//	[eGPIO_DebugInput] =	{GPIOF,		10,		RCC_AHB1ENR_GPIOCEN,	GPIO_Mode_Input},


	// Outputs
	[eGPIO_IndicatorLED] = 	{GPIOG,		14,		RCC_AHB1ENR_GPIOGEN,	GPIO_Mode_Output},
	[eGPIO_SirenOutput] = 	{GPIOB,		10,		RCC_AHB1ENR_GPIOBEN,	GPIO_Mode_Output},
	[eGPIO_WarningBeacon] = {GPIOA,		1,		RCC_AHB1ENR_GPIOAEN,	GPIO_Mode_Output},
//	[eGPIO_DebugOutput] = {GPIOA,		3,		RCC_AHB1ENR_GPIOEEN,	GPIO_Mode_Output},
};

// Simplify loops
#define NUM_GPIO_PINS		(sizeof (GPIO_Pins) / sizeof (_GPIO_PIN_STRUCT))

#endif // PCB Varaint 2





// Trap no GPIO Pins configured and throw a compile time error.
#ifndef NUM_GPIO_PINS
#pragma GCC error "No GPIO pins configured!"
#endif







//////////////////////////
// Initialisation function
void GPIO_Sys_Init(void)
{
	_GPIO_PIN_STRUCT *pPin;
	for (int i = 0; i < NUM_GPIO_PINS; i++)
	{
		// Get pointer to next pin
		pPin = &GPIO_Pins[i];

		// Enable the clock for the port
		RCC->AHB1ENR |= pPin->ul_ClockSourceEnableBit;

		// Set the mode
		// Note: 2 bits per pin 00=input, 01=output, 10=AltFunc and 11=Analogue
		switch (pPin->eMode)
		{
		case GPIO_Mode_Input:
			// Clear both bits
			pPin->pPort->MODER &= ~(0x03 << (pPin->uc_Pin * 2));
			break;

		case GPIO_Mode_Output:
			// Set 01
			pPin->pPort->MODER |= (0x01 << (pPin->uc_Pin * 2));
			pPin->pPort->MODER &= ~(0x02 << (pPin->uc_Pin * 2));
			break;

		case GPIO_Mode_Alt:
			// Set 10
			pPin->pPort->MODER &= ~(0x01 << (pPin->uc_Pin * 2));
			pPin->pPort->MODER |= (0x02 << (pPin->uc_Pin * 2));
			break;

		case GPIO_Mode_Analogue:
			// Set 11
			pPin->pPort->MODER |= (0x03 << (pPin->uc_Pin * 2));
			break;
		}

		// Other GPIO initialisation would go here - Alternate functions, PushPull, Pull up / down etc.
	}
}

/////////////////////////////////
// Example GetInput type function
// Returns 0/1 for input state.
uint8_t GPIO_Sys_Get_Input (eGPIO_PINS ePin)
{
	// Return the data for relevant GPIO pin
	// i.e. (note: Compressed if - if relevant bit set, return 1 instead of the bit in the relevant position).
	return ((GPIO_Pins[ePin].pPort->IDR & (1 << GPIO_Pins[ePin].uc_Pin)) == 0) ? 0: 1;
}


///////////////////////////////////
// Example SetOutput type function.
void GPIO_Sys_Set_Output (eGPIO_PINS ePin, uint8_t NewState)
{
	// Set the output state for the given pin
	// i.e.
	if (NewState)
	{
		GPIO_Pins[ePin].pPort->ODR |= 1 << GPIO_Pins[ePin].uc_Pin;
	}
	else
	{
		GPIO_Pins[ePin].pPort->ODR &= ~(1 << GPIO_Pins[ePin].uc_Pin);
	}
}
