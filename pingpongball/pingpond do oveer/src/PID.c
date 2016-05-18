/*pid
 * codeLock.c
 *
 * Created: 2015-12-16 14:10:22
 * Author: Daniel Petersén and Marcus Sandberg
 *
 * Task for regulating controll signal via PID-regulation.
 *
 */ 
#include <asf.h>
#include "matlab.h"
#include "DAC.h"
#include "adcFunctions.h"
#include <inttypes.h>

//-------------------------------------------------------------
// Define volt/distance intervalls.
//-------------------------------------------------------------

#define distance10 2900
#define distance15 2000
#define distance20 1750
#define distance25 1360
#define distance30 1150
#define distance35 1100
#define distance40 1060
#define distance45 1000

//-------------------------------------------------------------
// Initialize variables
//-------------------------------------------------------------

static uint16_t sent_Target = 0;
static uint16_t Kp = 2;
static uint16_t Ti = 0;
static uint16_t Td = 0;
static uint16_t dT = 0;

static uint32_t distance, calculate_distance;
static uint32_t u, e;
static uint8_t real_Target = distance20;



void task_PID(void *pvParameters) 
{
	const portTickType xTimeIncrement = 100;
	real_Target = calculateDistance(sent_Target);
	e = real_Target - distance;
	
	u = Kp * (e);
	dacc_write_conversion_data(DACC, u);
	sendParameters(e, distance);
	vTaskDelay(50);					// 50 millisecond delay
}

int calculateDistance()
{
	calculate_distance = analogRead(1);
	/*
	Calculate distance from analog input.
	*/
	if(sent_Target >= 10 && sent_Target < 15)
	{
		return distance10;
	}
	else if(sent_Target >= 15 && sent_Target < 20)
	{
		return distance15;
	}
	else if(sent_Target >= 20 && sent_Target < 25)
	{
		return distance20;
	}
	else if(sent_Target >= 25 && sent_Target < 30)
	{
		return distance25;
	}
	else if(sent_Target >= 30 && sent_Target < 35)
	{
		return distance30;
	}
	else if(sent_Target >= 35 && sent_Target < 40)
	{
		return distance35;
	}
	else if(sent_Target >= 40 && sent_Target < 45)
	{
		return distance40;
	}
	else if(sent_Target > 45)
	{
		return distance45;
	}
}

void setParameters(uint16_t setTarget, uint16_t setKp, uint16_t setTi, uint16_t setTd, uint16_t setdT)
{
	sent_Target = setTarget;
	Kp = setKp;
	Ti = setTi;
	Td = setTd;
	dT = setdT;
}