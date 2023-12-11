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

#include <stm32f429xx.h>
#include <stdint.h>
#include "SysTick.h"
#ifdef TEST
#include <assert.h>
#endif

#ifndef FALSE
#define FALSE	0
#endif
#ifndef TRUE
#define TRUE	!FALSE
#endif

// TASK type Function prototypes
void PrimaryFunc1 ( void );
void PrimaryFunc2 ( void );
void PrimaryFunc3 ( void );
void PrimaryFunc4 ( void );

void SecondaryFunc1 ( void );
void SecondaryFunc2 ( void );
void SecondaryFunc3 ( void );
void SecondaryFunc4 ( void );
void SecondaryFunc5 ( void );
void SecondaryFunc6 ( void );

void TertiaryFunc1 ( void );
void TertiaryFunc2 ( void );
void TertiaryFunc3 ( void );
void TertiaryFunc4 ( void );
void TertiaryFunc5 ( void );
void TertiaryFunc6 ( void );
void TertiaryFunc7 ( void );
void TertiaryFunc8 ( void );
void TertiaryFunc9 ( void );
void FlashLED ( void );

void MainLoopMonitor ( void );


#ifdef BANANA
#pragma message "BANANA BUILD | BANANA BUILD | BANANA BUILD | BANANA BUILD | BANANA BUILD"
#endif

//////////////////////////////////
// This is a typedef and a structure array used by the main loop to call and time the main loop modules
typedef struct
{
	void(*ModuleFunc)(void);	// Module function pointer type "void ModuleMainEntryPoint ( void )"
	uint32_t LastRunTime;		// The time the module took to run last time it was run - in uS.
	uint32_t MaxTime_uS;		// Maximum time the module has taken to run - in uS
	uint32_t MinTime_uS; 		// Minimum time the module has taken to run - in uS
	uint64_t LastCallStamp;		// Timestamp when last called.
	uint32_t CallInterval;		// Number of uS between calls to this task.
	uint8_t TaskEnabled;		// TRUE / FALSE for whether to run this task or not

}_MAIN_MODULES;


#define DEFAULT_MAXMINLAST_MODULE_TIMES							0, 0, 0xFFFFFFFF, 0, 0

// Primary tasks / submodules.
_MAIN_MODULES PrimaryModules[] = {
	// ModuleMainFunc				Last, Max, Min defaults.		Enabled
#ifndef CALIBRATING
	{ PrimaryFunc1,					DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ PrimaryFunc2,					DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ PrimaryFunc3,					DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
	{ PrimaryFunc4,					DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
#endif
#ifdef DEBUG
	{ MainLoopMonitor,				DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
#endif
};
#define NUM_PRI_TASKS				sizeof(PrimaryModules) / sizeof(_MAIN_MODULES)

// Secondary tasks / submodules.
_MAIN_MODULES SecondaryModules[] = {
	// ModuleMainFunc				Last, Max, Min defaults.		Enabled
#ifndef CALIBRATING
	{ SecondaryFunc1,				DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ SecondaryFunc2,				DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ SecondaryFunc3,				DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ SecondaryFunc4,				DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
	{ SecondaryFunc5,				DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
	{ SecondaryFunc6,				DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
#endif
};
#define NUM_SEC_TASKS				sizeof(SecondaryModules) / sizeof(_MAIN_MODULES)

// Tertiary tasks / submodules.
_MAIN_MODULES TertiaryModules[] = {
	// ModuleMainFunc				Last, Max, Min defaults.		Enabled
#ifndef CALIBRATING
	{ TertiaryFunc1,				DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ TertiaryFunc2,				DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ TertiaryFunc3,				DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ TertiaryFunc4,				DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ FlashLED,						DEFAULT_MAXMINLAST_MODULE_TIMES, TRUE },
	{ TertiaryFunc5,				DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
	{ TertiaryFunc6,				DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
	{ TertiaryFunc7,				DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
	{ TertiaryFunc8,				DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
	{ TertiaryFunc9,				DEFAULT_MAXMINLAST_MODULE_TIMES, FALSE },
#endif
};
#define NUM_TER_TASKS				sizeof(TertiaryModules) / sizeof(_MAIN_MODULES)

// Maximum time a submodule / task is allowed to take.
#define MODULE_CALL_DURATION_LIMIT_uS	250

// Floating point enabling
#define FPU_CP10_FULL	(0x00200000 + 0x00100000)
#define FPU_CP11_FULL	(0x00800000 + 0x00400000)

// Normal function prototypes
void FunctionSimulator ( void );

// Run tasks directly or include additional diagnostics?
#ifdef DEBUG

// Function header for diagnostics function.
void TimeAndRunTask(_MAIN_MODULES *pTask);

// Call tasks with additional timing diagnostics
#define RUN_THIS_TASK(a)		TimeAndRunTask(&a)

#else // i.e. RELEASE

// Call tasks directly (without diagnostics)
#define RUN_THIS_TASK(a)		a.ModuleFunc()

#endif // DEBUG


// Test condition - only include this function header if TEST build configuration.
#ifdef TEST
void RunTests(void);
#endif



// Main entry point.
int main(void)
{
	static uint8_t uc_Sec_Index; // Secondary task index
	static uint8_t uc_Ter_Index; // Tertiary task index.

	// Run self tests if configured to do so.
#ifdef TEST
	RunTests();
#endif


	//Initialise SysTick Interrupt.
	SysTick_Init();

	// Enable the FPU (floating point co-processor, access = full access)
	SCB->CPACR |= FPU_CP10_FULL | FPU_CP11_FULL;

	//Enable clock access to GPIOG - for LED Output
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	//Set PG13 as output - Green LED.
	GPIOG->MODER |= (1 << 26);
	GPIOG->MODER &= ~(1 << 27);


    /* Loop forever */
	while(1)
	{
		// Call ALL primary tasks
		for (int i = 0; i < NUM_PRI_TASKS; i++)
		{
			// Skip disabled tasks
			if (PrimaryModules[i].TaskEnabled == FALSE)
				continue;

			//**********************
			// RUN NEXT PRIMARY TASK
			RUN_THIS_TASK(PrimaryModules[i]); // How the function is called depends on build configuration.
		}

		// Call 1 secondary task
		if (uc_Sec_Index < NUM_SEC_TASKS)
		{
			// Run next secondary task
			// Only continue if selected task is enabled - else skip.
			if (SecondaryModules[uc_Sec_Index].TaskEnabled)
			{
				//************************
				// RUN NEXT SECONDARY TASK
				RUN_THIS_TASK(SecondaryModules[uc_Sec_Index]); // How the function is called depends on build configuration.
			}
		}
		uc_Sec_Index++;

		// When all secondary tasks completed, call 1 tertiary task
		if (uc_Sec_Index == (NUM_SEC_TASKS + 1))
		{
			// Start the secondary task list again next time.
			uc_Sec_Index = 0;

			// Run next tertiary task
			if (uc_Ter_Index < NUM_TER_TASKS)
			{
				// Only run enabled tasks or skip
				if (TertiaryModules[uc_Ter_Index].TaskEnabled)
				{
					//***********************
					// RUN NEXT TERTIARY TASK
					RUN_THIS_TASK(TertiaryModules[uc_Ter_Index]); // How the function is called depends on build configuration.
				}
			}
			// Next tertiary task with wrap
			uc_Ter_Index++;
			if (uc_Ter_Index >= NUM_TER_TASKS)
			{
				uc_Ter_Index = 0;
			}
		}
	}
}







// Function bodies

// This function is only included if the DEBUG is included in the pre-eprocessor defines.
#ifdef DEBUG // Main loop monitoring

#define IDLE_MAIN_LOOPS_PER_SECOND		12000
#define MIN_MAIN_LOOPS_PER_SECOND		1000
float PctIdle;
void MainLoopMonitor ( void )
{
	static uint8_t DurationInitRequired = TRUE;
	static uint32_t MainLoopDurationLast_uS = 0;
	static uint32_t MainLoopDurationMax_uS = 0;
	static uint32_t MainLoopDurationMin_uS = 0xFFFFFFFF;
	static uint32_t MainLoopsPerSecond = 0;
	static uint32_t MainLoopsPerSecondMAX = 0;
	static uint32_t MainLoopsPerSecondMIN = 0xFFFFFFF;
	static uint32_t MainLoopCounter = 0;
	static uint64_t MainLoopDurationTimer;
	static uint64_t MainLoopCountTimer;

	// How long since last here?
	// Includes first pass handling
	if (!DurationInitRequired)
	{
		// Record duration and update max / min if needed
		MainLoopDurationLast_uS = SysTick_Elapsed_MicroSeconds(MainLoopDurationTimer);
		if (MainLoopDurationLast_uS < MainLoopDurationMin_uS)
			MainLoopDurationMin_uS = MainLoopDurationLast_uS;
		if (MainLoopDurationLast_uS > MainLoopDurationMax_uS)
			MainLoopDurationMax_uS = MainLoopDurationLast_uS;
	}
	else
		DurationInitRequired = FALSE;
	// Reset timer for next pass of main loop
	MainLoopDurationTimer = SysTick_Get_Timestamp();

	////////////////////////////////
	// Only run this once per second - the number of main loops per second counter...
	if (SysTick_Elapsed_MicroSeconds(MainLoopCountTimer) >= 1000000)
	{
		// Record number of main loops in the last second
		MainLoopsPerSecond = MainLoopCounter;

		// Record Max / Min
		if (MainLoopsPerSecond < MainLoopsPerSecondMIN)
			MainLoopsPerSecondMIN = MainLoopsPerSecond;
		if (MainLoopsPerSecond > MainLoopsPerSecondMAX)
			MainLoopsPerSecondMAX = MainLoopsPerSecond;

		// Reset for another go
		MainLoopCountTimer = SysTick_Get_Timestamp();
		MainLoopCounter = 0;

		// Update % Busy
		PctIdle = 100.0 * ((float)(MainLoopsPerSecond - MIN_MAIN_LOOPS_PER_SECOND) / (float)(IDLE_MAIN_LOOPS_PER_SECOND - MIN_MAIN_LOOPS_PER_SECOND));
	}
	else
		// Still waiting for 1 second marker, count main loops...
		MainLoopCounter++;

}
#endif

// Minimum time the function simulator should take.
uint16_t us_Func_Min_Time_uS = 10;

// Simulate a function taking some time to process stuff.
void FunctionSimulator ( void )
{
	uint64_t timestamp = SysTick_Get_Timestamp();
	uint16_t delay = us_Func_Min_Time_uS + (timestamp & 0x0F);  // Add in the lowest bits from the timestamp to give some variation.

	// Delay the required period.
	while (SysTick_Elapsed_MicroSeconds(timestamp) < delay);
}

void PrimaryFunc1 ( void )
{
	FunctionSimulator();
}
void PrimaryFunc2 ( void )
{
	FunctionSimulator();
}

void PrimaryFunc3 ( void )
{
	FunctionSimulator();
}

void PrimaryFunc4 ( void )
{
	FunctionSimulator();
}


void SecondaryFunc1 ( void )
{
	FunctionSimulator();
}

void SecondaryFunc2 ( void )
{
	FunctionSimulator();
}

void SecondaryFunc3 ( void )
{
	FunctionSimulator();
}

void SecondaryFunc4 ( void )
{
	FunctionSimulator();
}

void SecondaryFunc5 ( void )
{
	FunctionSimulator();
}

void SecondaryFunc6 ( void )
{
	FunctionSimulator();
}


void TertiaryFunc1 ( void )
{
	FunctionSimulator();
}

void TertiaryFunc2 ( void )
{
	FunctionSimulator();
}

void TertiaryFunc3 ( void )
{
	FunctionSimulator();
}

void TertiaryFunc4 ( void )
{
	FunctionSimulator();
}

void TertiaryFunc5 ( void )
{
	FunctionSimulator();
}

void TertiaryFunc6 ( void )
{
	FunctionSimulator();
}

void TertiaryFunc7 ( void )
{
	FunctionSimulator();
}

void TertiaryFunc8 ( void )
{
	FunctionSimulator();
}

void TertiaryFunc9 ( void )
{
	FunctionSimulator();
}

// Example function that includes a runtime time test.
uint16_t MultipleBy3(uint16_t val)
{
	return val * 4;
}

#ifdef TEST

void RunFuncTest1(void)
{
	uint16_t testval = 3;
	uint32_t returnVal = MultipleBy3(testval);
	assert (returnVal == testval * 3);
}

void RunTests(void)
{
	RunFuncTest1();
	// Add other functions to test here
}
#endif

// Flash the Green LED
void FlashLED ( void )
{
	GPIOG->ODR ^= (1 << 13);
}

#ifdef DEBUG // Additional task running diagnostics

// Called if a task takes too long.
void HandleTaskOverrun()
{
	asm("nop");
}

// Max / Min definitions to simplify recording max / min.
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

// Run and time how long a task takes.
void TimeAndRunTask(_MAIN_MODULES *pTask)
{
	// Note starting time
	uint64_t ull_StartTime = SysTick_Get_Timestamp();

	// Run task
	pTask->ModuleFunc();

	// Record time taken this time
	pTask->LastRunTime = SysTick_Elapsed_MicroSeconds(ull_StartTime);

	// Note time since last call - call interval
	pTask->CallInterval = SysTick_Elapsed_MicroSeconds(pTask->LastCallStamp);
	pTask->LastCallStamp = ull_StartTime;

	// Log max / min
	pTask->MaxTime_uS = MAX(pTask->LastRunTime, pTask->MaxTime_uS);
	pTask->MinTime_uS = MIN(pTask->LastRunTime, pTask->MinTime_uS);

	// Trap a module taking too long
	if (pTask->LastRunTime > MODULE_CALL_DURATION_LIMIT_uS)
	{
		HandleTaskOverrun();
	}
}

#endif // DEBUG - additional task diagnostics

// EOF
