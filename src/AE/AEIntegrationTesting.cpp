

#include "AEIntegrationTesting.h"
#include "AETimerSimple.h"

void AEITEST_END_TestsAfterTimer_FUNC(uint32_t timeInMilliBeforeEnd)
{
	AETimerSimple timerEnd(timeInMilliBeforeEnd, true, [](TimerHandle_t xTimer)-> void{AEITEST_END_FUNC(); });
	timerEnd.StartTimer();
}
 