// Demo project - function pointers.

/****************************************************/
/*Required Header Files */
#include "stm32f429xx.h"
#include "DIOHandler.h"

/****************************************************/
/*Local only definitions */
#define POLLING_METHOD			// Comment this line out to use a function pointer 'callback' method instead.

////////////////////////////////////
// Target function for either method -
// This function should get called whenever the user button (blue) is pressed or released.
void UserButtonStateChanged(void)
{
	// Add a line the debugger can break on
	// Insert break point on next line when debugging
	asm("nop");
}

/*********************************************
 * @brief main
 * Main entry point, carries out initialisation and calling all sub-systems within eternal loop.
 * @param None
 * @retval None
 */

#ifdef POLLING_METHOD

////////////////////
int main(void)
{
	static uint8_t UserButtonLT;
	uint8_t UserButtonNow;

	// Initialise GPIOA clock for our input
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /******************/
    /* Loop forever */
	while(1)
	{
		// Run the DIO Handler module.
		DIOHandler_Run();

		// Check for change in state of the user button...

		// Get the current state
		UserButtonNow = DIOHandler_Get_Digital_Input_State(DI_USER_BUTTON_ID);

		// Check current state against last known state.
		if (UserButtonLT != UserButtonNow)
		{
			// Record new state
			UserButtonLT = UserButtonNow;

			// Call our target function to indicate user button state has changed.
			UserButtonStateChanged();
		}
    }
}

#else // Function pointer callback method.

// Function header for our callback function
void DigitalInputStateChanged (uint8_t InputID);

//////////////////////////
int main(void)
{
	// Initialise GPIOA clock for our input
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// Pass the address of the function we want called when any input state changes to the DIOHandler
	DIOHandler_Register_DI_Change_Callback( & DigitalInputStateChanged);

    /******************/
    /* Loop forever */
	while(1)
	{
		DIOHandler_Run();
    }
}

//////////////////////////////
// Callback function for when state changes of any digital input.
void DigitalInputStateChanged (uint8_t InputID)
{
	// Was this a user button state change?
	if (InputID == DI_USER_BUTTON_ID)
	{
		// Call the target function for state change of user button
		UserButtonStateChanged();
	}
}

#endif

/*****************/
/* End of files */

