//generated file: AETimerSimple.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.



//includes
#include "AETimerSimple.h"

//UserCode_Sectionf
//UserCode_Sectionf_end


AETimerSimple::AETimerSimple(uint32_t periodOfTimerTicksInMilli, bool autoReload,TimerSimpleCallback_t timerSimpleCallback)
{
TimerSimpleCallback = timerSimpleCallback;
PeriodOfTimerTicksInMilli = periodOfTimerTicksInMilli;
AutoReload = autoReload;

//UserCode_Sectiona
#if RTOS_USED == FREERTOS
uint16_t periodInTicks = pdMS_TO_TICKS(PeriodOfTimerTicksInMilli);
	
	//create the timer for freertos
		UpdateTimePaused = false;
	
	xTimerForThisSimpleTimer = xTimerCreate
	( /* Just a text name, not used by the RTOS
	  kernel. */
		"Timer",
		/* The timer period in ticks, must be
		greater than 0. */
		periodInTicks,
		/* The timers will auto-reload themselves
		when they expire. */
		autoReload,
		/* The ID is used to store the AO id*/
		(void *)1,
		/* Each timer calls the same callback when
		it expires. */
		timerSimpleCallback);
	
#endif
//UserCode_Sectiona_end

    //always stop the timer
    StopTimer();

}



void AETimerSimple::StartTimer(){
    //UserCode_Sectionb
#if RTOS_USED == FREERTOS
xTimerStart(xTimerForThisSimpleTimer, 0);
#endif
//UserCode_Sectionb_end
}


void AETimerSimple::StopTimer(){
    //UserCode_Sectionc
#if RTOS_USED == FREERTOS
xTimerStop(xTimerForThisSimpleTimer, 0);
#endif
//UserCode_Sectionc_end
}

void AETimerSimple::PauseTimer(){
    //UserCode_Sectiond
#if RTOS_USED == FREERTOS
//this will pause the timer only if it is active
		if(xTimerIsTimerActive(xTimerForThisSimpleTimer) != pdFALSE)
	{
		//TODO: first maybe I need to grab the ticks remaining for when there is an unpause?
		//auto xRemainingTime = xTimerGetExpiryTime(xTimerForUpdatingStates) - xTaskGetTickCount();
		xTimerStop(xTimerForThisSimpleTimer, 0);

		UpdateTimePaused = true;
	}
	else
	{
		UpdateTimePaused = false;
	}
	
#endif
//UserCode_Sectiond_end
}

bool AETimerSimple::IsTimerActive(){
    //UserCode_Sectione
#if RTOS_USED == FREERTOS
return xTimerIsTimerActive(xTimerForThisSimpleTimer);
#else
	return true;
#endif
//UserCode_Sectione_end
}


void AETimerSimple::ChangePeriod(uint32_t newPeriod){
    //UserCode_Sectiong
#if RTOS_USED == FREERTOS
uint16_t periodInTicks = pdMS_TO_TICKS(newPeriod);
	AEAssertRuntime(periodInTicks >= 1, "");

	
	xTimerChangePeriod(xTimerForThisSimpleTimer, periodInTicks, 0);
#endif
//UserCode_Sectiong_end
}

uint32_t AETimerSimple::GetPeriodOfTimer()  const {
    //UserCode_Sectionh
#if RTOS_USED == FREERTOS
return xTimerGetPeriod(xTimerForThisSimpleTimer);
#else
	return 1;
#endif
//UserCode_Sectionh_end
}
