//generated file: AETimerSimple.h


#pragma once


//includes
//UserCode_Sectiona
#include <cstdint>
#include "AECore.h"
//UserCode_Sectiona_end

#if RTOS_USED != FREERTOS
typedef  TimerHandle_t uint8_t;
typedef void (*TimerSimpleCallback_t)( TimerHandle_t xTimer );
#else
typedef TimerCallbackFunction_t TimerSimpleCallback_t;
#endif



class AETimerSimple
{
public:
    AETimerSimple(uint32_t periodOfTimerTicksInMilli, bool autoReload,TimerSimpleCallback_t timerSimpleCallback);
	
	void StartTimer();
    void StopTimer();
    void PauseTimer();
    bool IsTimerActive();
    void ChangePeriod(uint32_t newPeriod);
    uint32_t GetPeriodOfTimer() const;

	//UserCode_Sectionc
//UserCode_Sectionc_end


private:
    TimerSimpleCallback_t TimerSimpleCallback;
	uint32_t PeriodOfTimerTicksInMilli;
	bool AutoReload;



    //UserCode_Sectiond
bool UpdateTimePaused;
	TimerHandle_t xTimerForThisSimpleTimer;
//UserCode_Sectiond_end
};

//UserCode_Sectione
//UserCode_Sectione_end
