#include "stm32f429xx.h"
#include "DIOHandler.h"


#define FALSE	0
#define TRUE	!FALSE
#define NULL	0


// Local store for current state of all digital inputs - see header for number of inputs.
uint8_t DI_States[5];



// A function pointer - will be assigned the address of a function to call.
//
// This is the same as declaring a variable pointer i.e. "uint8_t *pChar" except it's
// a pointer to a function instead of a variable.
//
// When declaring a function pointer you have to specify the return type as well as any
// parameters pass to it.
//
// An example declaration of a pointer to a function void MyVoidVoidFunc( void ) would look like...
// void (*PointerToAFuncTypeVoidVoid)(void);
// Of course the name of the pointer can be anything you want, much like a variable pointer.
//
// Declaration of a pointer to a function that returns a uint8_t and has two parameters of uint16_t
// would look like...
// uint8_t (*PointerToAFuncType_uint8_t_Return_2x_uint16_Params)(uint16_t sVal1, uint16_t sVal2);
//
// When using a function pointer you simply call the function, using the example above,
// to call the function pointed to by PointerToAFuncTypeVoidVoid you would use...
// PointerToAFuncTypeVoidVoid();
// Simply add the () to the function pointer name with the required parameters and use
// the return value as needed.
//
// Here's the function pointer we'll be using as an example. Here it's initialised to NULL as no
// function address is known at this time, it's assigned during runtime, however as it's file scope
// here it would be automatically initialised to 0, which is the same thing.
//
// Format...
// FunctionReturnType (*FunctionPointer_Name) (FunctionParameterTypes)
void (*FunctionPointer_AssignedWithTheAddressOfAFunctionToCall) (uint8_t) = NULL;




///////////////
// Main entry point - Read all digital inputs
// Note: This function would be reading and de-bouncing multiple digital inputs
void DIOHandler_Run(void)
{
	// Only really checking the User Button state.

	// A module like this would also de-bounce the inputs and take care of ALL digital inputs.
	// Here it's kept simple for the sake of this demo and are only checking the current state of the User Button (PA0).

	// Here we simply record the current state of the User Button input and check for a change.
	uint8_t DIStateLT = DI_States[DI_USER_BUTTON_ID];
	uint8_t DIStateNow = GPIOA->IDR & 0x01;
	// State changed?
	if (DIStateLT != DIStateNow)
	{
		// Save the new state - Here would be de-bouncing for instance.
		DI_States[DI_USER_BUTTON_ID] = DIStateNow;

		// Run the callback function if it exists / has been configured
		if (FunctionPointer_AssignedWithTheAddressOfAFunctionToCall != NULL)
		{
			// Function pointer has been assigned the address of a function to call, so call it!
			// Include the ID of the input that's changed.
			FunctionPointer_AssignedWithTheAddressOfAFunctionToCall(DI_USER_BUTTON_ID);
		}
	}
}

/////////////////////////
// Return last read state of a digital input.
uint8_t DIOHandler_Get_Digital_Input_State (uint8_t InputID)
{
	// Return the requested state.
	// Note: Would normally check for out of bounds here.
	return DI_States[InputID];
}

/////////////////////////
// Register a callback function to be called whenever an input state changes.
// I.e. save the address of the function supplied in the parameter to our function pointer.
void DIOHandler_Register_DI_Change_Callback(void (*Functon_Address)(uint8_t))
{
	// Save function address to our local function pointer 'variable'.
	FunctionPointer_AssignedWithTheAddressOfAFunctionToCall = Functon_Address;
}

