#include "AEPerformanceTimer.h"

#include "stm32f4xx_hal.h"

static bool AEPerfInitAlready = false;
static float FrequencyInNano = 0;

#ifdef SWIL_HWIL_DRIVEN__HWIL
 const float AEPerformanceTimer::TimerCorrection = 4;
#endif

AEPerformanceTimer::AEPerformanceTimer()
{
	if (AEPerfInitAlready  == false) { 
		//enable the DWT->CYCCNT register to count cycles
		CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
		DWT->CYCCNT = 0;
		DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
		AEPerfInitAlready  = true;
	}

		
	ClckFreq  = HAL_RCC_GetSysClockFreq();
	FrequencyInNano = (float)ClckFreq / (float)(1000 * 1000 * 1000);
	StartingPoint = 0; 
	EndingPoint = 0; 
}

void AEPerformanceTimer::AEStart_Timer()
{ 
	StartingPoint = DWT->CYCCNT; 
}

void AEPerformanceTimer::AEStop_Timer()
{ 
	EndingPoint = DWT->CYCCNT;
	//check for if DWT->CYCCNT wrapped around
	if(EndingPoint < StartingPoint)
	{
		ElapsedCycles = (EndingPoint + (0xffffffff - StartingPoint))*TimerCorrection;
	}
	else
	{
		ElapsedCycles = (EndingPoint - StartingPoint)*TimerCorrection;
	} 
} 
	

uint32_t AEPerformanceTimer::GetElapsedTimeCPUCycles()
{
	return ElapsedCycles;  
}

PerfElapsed_t AEPerformanceTimer::GetElapsedTimeInNanoSeconds()
{
	return (PerfElapsed_t)((float)ElapsedCycles / (float)FrequencyInNano);
}