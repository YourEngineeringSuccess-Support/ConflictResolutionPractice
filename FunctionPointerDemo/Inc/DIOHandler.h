/*
 * DIOHandler.h
 *
 *  Created on: Nov 15, 2023
 *      Author: steph
 */

#ifndef DIOHANDLER_H_
#define DIOHANDLER_H_

// Example of types of input IDs
#define DI_USER_BUTTON_ID			0
#define DI_ANOTHER_INPUT_ID			1
#define DI_AANOTHER_INPUT_ID		2
#define DI_AAANOTHER_INPUT_ID		3
#define DI_AAAANOTHER_INPUT_ID		4


void DIOHandler_Run(void);
void DIOHandler_Register_DI_Change_Callback(void (*Functon_Address)(uint8_t));
uint8_t DIOHandler_Get_Digital_Input_State (uint8_t InputID);


#endif /* DIOHANDLER_H_ */
