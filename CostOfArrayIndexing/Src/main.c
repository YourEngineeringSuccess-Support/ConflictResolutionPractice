/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "stm32f429xx.h"
#include <stdint.h>


//Pin definitions
#define PIN13                      (1<<13)
//GPIO Pins in use
#define LED_PIN                     PIN13


typedef struct
{
	int i_Example1;
	int i_Example2;
	int i_Example3;
	int i_Example4;
	int i_Example5;
	int i_Example6;
	int i_Example7;
	int i_Example8;
	int i_Example9;
	int i_Example10;

}_EXAMPLE_STRUCT;



#define ARRAY_SIZE					100

_EXAMPLE_STRUCT Ex1[ARRAY_SIZE];
_EXAMPLE_STRUCT Ex2[ARRAY_SIZE];
_EXAMPLE_STRUCT Ex3[ARRAY_SIZE];



// Main entry point
int main(void)
{
	//Enable clock access to GPIOG and GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

	//Set PG13 as output
	GPIOG->MODER |= (1 << 26);
	GPIOG->MODER &= ~(1 << 27);

	// Initialise Ex1...
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		Ex1[i].i_Example1 = i + 1;
		Ex1[i].i_Example2 = i + 2;
		Ex1[i].i_Example3 = i + 3;
		Ex1[i].i_Example4 = i + 4;
		Ex1[i].i_Example5 = i + 5;
		Ex1[i].i_Example6 = i + 6;
		Ex1[i].i_Example7 = i + 7;
		Ex1[i].i_Example8 = i + 8;
		Ex1[i].i_Example9 = i + 9;
		Ex1[i].i_Example10 = i + 10;
	}

	// Turn the LED on.
	GPIOG->ODR ^= LED_PIN;

	// Do the work
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		Ex2[i].i_Example1 = Ex1[i].i_Example1;
		Ex2[i].i_Example2 = Ex1[i].i_Example2;
		Ex2[i].i_Example3 = Ex1[i].i_Example3;
		Ex2[i].i_Example4 = Ex1[i].i_Example4;
		Ex2[i].i_Example5 = Ex1[i].i_Example5;
		Ex2[i].i_Example6 = Ex1[i].i_Example6;
		Ex2[i].i_Example7 = Ex1[i].i_Example7;
		Ex2[i].i_Example8 = Ex1[i].i_Example8;
		Ex2[i].i_Example9 = Ex1[i].i_Example9;
		Ex2[i].i_Example10 = Ex1[i].i_Example10;
	}

	// Turn the LED off.
	GPIOG->ODR ^= LED_PIN;

	// Do the work more efficiently
	_EXAMPLE_STRUCT *pEx1 = Ex1;
	_EXAMPLE_STRUCT *pEx3 = Ex3;

	// Turn the LED on.
	GPIOG->ODR ^= LED_PIN;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		pEx3->i_Example1 = pEx1->i_Example1;
		pEx3->i_Example2 = pEx1->i_Example2;
		pEx3->i_Example3 = pEx1->i_Example3;
		pEx3->i_Example4 = pEx1->i_Example4;
		pEx3->i_Example5 = pEx1->i_Example5;
		pEx3->i_Example6 = pEx1->i_Example6;
		pEx3->i_Example7 = pEx1->i_Example7;
		pEx3->i_Example8 = pEx1->i_Example8;
		pEx3->i_Example9 = pEx1->i_Example9;
		pEx3->i_Example10 = pEx1->i_Example10;

		// Increment structure pointers
		pEx1++;
		pEx3++;
	}

	// Turn the LED off.
	GPIOG->ODR ^= LED_PIN;


    /* Loop forever */
	for(;;);
}