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

#include <stdint.h>
#include <stdio.h>


typedef struct
{
	uint8_t day;
	uint8_t month;
	uint8_t year;
}_sDATE;

typedef union
{
	_sDATE date;
	uint16_t date_num;
}_uDATE;

_uDATE Date1, Date2;

int main(void)
{
	Date1.date.day = 1; //1;
	Date1.date.month = 2; //11;
	Date1.date.year = 3; //23;

	Date2.date.day = 4; //20;
	Date2.date.month = 5; //11;
	Date2.date.year = 6; //22;

	Date2.date_num = 56789;

	if (Date1.date_num < Date2.date_num)
	{
		printf ("Date1 is before Date2\r\n");
	}
	else
	{
		printf ("Date1 is after Date2\r\n");
	}








    /* Loop forever */
	for(;;);
}
