/**
 * \file
 *
 * \brief Empty user application template
 *
 * Author: Daniel Petersén and Marcus Sandberg
 */

#include "adcFunctions.h"
#include <asf.h>
#include "matlab.h"
#include "PID.h"
#include "delayFunctions.h"
#include "DAC.h"
#include "io_uart.h"

int tempDistance = 0;

int main(void)
{
	/* Initialise the Due board */
	sysclk_init();
	board_init();
	delayInit();
	daccInit();
	analogInit(1);
	

	if (xTaskCreate(task_PID, (const signed char * const) "Task_PID", TASK_STACK_PID_SIZE, NULL, TASK_PID_STACK_PRIORITY, NULL) != pdPASS) 
	{
		printf("Failed to create PID task\r\n");
	}
	/*
	if (xTaskCreate(task_Matlab, (const signed char * const) "Task_Matlab", TASK_STACK_MATLAB_SIZE, NULL, TASK_MATLAB_STACK_PRIORITY, NULL) != pdPASS) 
	{
		printf("Failed to create Matlab task\r\n");
	}*/
	vTaskStartScheduler();
}