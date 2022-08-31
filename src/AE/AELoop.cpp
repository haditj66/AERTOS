#include "AELoop.h"

#include "AELoopObject.h"

AELoop AELoop::Pool[MaxNumOfAELoops];
uint16_t AELoop::numOfAELoopsSoFar = 0;


#if MaxNumOfAELoops > 0
//AECHANGED: no static keyworkds
void  TimerFunc1(TimerHandle_t xTimerHandle) { 
	xTaskNotifyGive(AELoop::Pool[0].LoopUpdateTaskHandle);
}
#endif
#if MaxNumOfAELoops > 1
void  TimerFunc2(TimerHandle_t xTimerHandle) {
	xTaskNotifyGive(AELoop::Pool[1].LoopUpdateTaskHandle);
}
#endif

#if MaxNumOfAELoops > 2
void  TimerFunc3(TimerHandle_t xTimerHandle) {
	xTaskNotifyGive(AELoop::Pool[2].LoopUpdateTaskHandle);
}
#endif
#if MaxNumOfAELoops > 3
void  TimerFunc4(TimerHandle_t xTimerHandle) {
	xTaskNotifyGive(AELoop::Pool[3].LoopUpdateTaskHandle);
}
#endif
#if MaxNumOfAELoops > 4
void  TimerFunc5(TimerHandle_t xTimerHandle) {
	xTaskNotifyGive(AELoop::Pool[4].LoopUpdateTaskHandle);
}
#endif
//AECHANGEDDONE:

TimerCallbackFunction_t AELoop::PoolOfTimerFuncs[MaxNumOfAELoops] =
{
#if MaxNumOfAELoops > 0
	TimerFunc1
#endif
	#if MaxNumOfAELoops > 1
	 ,TimerFunc2
#endif
		#if MaxNumOfAELoops > 2
	 ,TimerFunc3
#endif
		#if MaxNumOfAELoops > 3
	 ,TimerFunc4
#endif
		#if MaxNumOfAELoops > 4
	 ,TimerFunc5
#endif 
};



AELoop * AELoop::GetFromPool(uint32_t frequencyOfClock, AEPriorities priorityOfThis, LoopUpdateFunc_t loopUpdateFunc, uint32_t stackSizeOfLoop)
{ 

	AELoop* loop = GetFromPoolNoInitYet();//&Pool[numOfAELoopsSoFar];

	InitializeLoop(loop, frequencyOfClock, priorityOfThis, loopUpdateFunc, stackSizeOfLoop);

	//make sure the number of AEloops createddoes not exceed the MaxNumOfAELoops
	//configASSERT(numOfAELoopsSoFar <= MaxNumOfAELoops);
	//numOfAELoopsSoFar++;

	return loop;
}


AELoop * AELoop::GetFromPoolNoInitYet()
{
	AELoop* loop = &Pool[numOfAELoopsSoFar];

	//make sure the number of AEloops createddoes not exceed the MaxNumOfAELoops
	configASSERT(numOfAELoopsSoFar <= MaxNumOfAELoops);
	numOfAELoopsSoFar++;
	return loop;
}

void AELoop::InitializeLoop(AELoop* loop, uint32_t frequencyOfClock, AEPriorities priorityOfThis, LoopUpdateFunc_t loopUpdateFunc, uint32_t stackSizeOfLoop)
{
	loop->FrequencyOfClock = frequencyOfClock;

	loop->LoopUpdateFunc = loopUpdateFunc;
	loop->_Priority = priorityOfThis;
	auto* pToThisClass = loop;
	xTaskCreate([](void* p) {static_cast<AELoop*>(p)->GaurdUpdate(nullptr); }, "LoopUpdateTask", stackSizeOfLoop, pToThisClass, loop->_Priority, &loop->LoopUpdateTaskHandle);

	//create the timer that will notify this AELoop
	uint32_t ticks = (configTICK_RATE_HZ / frequencyOfClock) <= 1 ? 1 : (configTICK_RATE_HZ / frequencyOfClock);
	loop->xTimerForClockTicks = xTimerCreate("T",				/* The text name assigned to the software timer - for debug only as it is not used by the kernel. */
		ticks,		                /* The period of the software timer in ticks. */
		pdTRUE,			/* xAutoReload is set to true */
		NULL,				/* The timer's ID is not used. */
		PoolOfTimerFuncs[numOfAELoopsSoFar-1]);/* The function executed when the timer expires. */
	xTimerReset(loop->xTimerForClockTicks, portMAX_DELAY);

}


inline void AELoop::GaurdUpdate(void * thisptr)
{
	while (true)
	{
		//triggered via a tasknotify
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		 
			if (hasAEObject == false)
			{
				LoopUpdateFunc(thisptr);
			}
			else
			{
				AEObjectIPossess->PreUpdate();
			}
	}
}


/*
AELoop * AELoop::GetFromPoolForAEObject(uint32_t frequencyOfClock, AEPriorities priorityOfThis, uint32_t stackSizeOfLoop)
{ 
	auto theLoop = (AELoop::GetFromPool(frequencyOfClock, priorityOfThis, nullptr, stackSizeOfLoop));;
	theLoop->hasAEObject = true;
	return theLoop;
}*/
