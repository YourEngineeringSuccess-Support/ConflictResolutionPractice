/*
 * GPIO_Sys.h
 *
 *  Created on: Dec 11, 2023
 *      Author: steph
 */

#ifndef GPIO_SYS_H_
#define GPIO_SYS_H_


typedef enum
{
	// Inputs
	eGPIO_UserButton = 0,
	eGPIO_Interlock1,
	eGPIO_Interlock2,
	// etc...

	// Outputs
	eGPIO_IndicatorLED,
	eGPIO_SirenOutput,
	eGPIO_WarningBeacon,
	// etc...

}eGPIO_PINS;



void GPIO_Sys_Init(void);
uint8_t GPIO_Sys_Get_Input (eGPIO_PINS ePin);
void GPIO_Sys_Set_Output (eGPIO_PINS ePin, uint8_t NewState);



#endif /* GPIO_SYS_H_ */
