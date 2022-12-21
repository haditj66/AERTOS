#pragma once

#include "FreeRTOS.h"
#include "AE.h"
#include "AEUtils.h"
#include "task.h"
#include "timers.h"
#include "AEAO.h"
//#include "AELoopObject.h"

//class AELoopObject;

typedef void(*LoopUpdateFunc_t)(void*);
  
class AELoopObject;

class AELoop //: public AEAO
{
	TEMPLATEFORNoDefaults_AEClock
	friend class AEClock;

	
	friend class AELoopObject; 
	friend class AELoop;

	friend void  TimerFunc1(TimerHandle_t xTimerHandle);
	friend void  TimerFunc2(TimerHandle_t xTimerHandle);
	friend void  TimerFunc3(TimerHandle_t xTimerHandle);
	friend void  TimerFunc4(TimerHandle_t xTimerHandle);
	friend void  TimerFunc5(TimerHandle_t xTimerHandle);

public: 


	float GetFrequency() const { return FrequencyOfClock; };

	static AELoop* GetFromPool(uint32_t frequencyOfClock, AEPriorities priorityOfThis, LoopUpdateFunc_t loopUpdateFunc, uint32_t stackSizeOfLoop = 300);

private:
	/*
	class PsuedoAEObjectType
	{
	public:
		PsuedoAEObjectType() {};
		virtual void Update() =0;
	private:

	};*/
	 
	static AELoop* GetFromPoolNoInitYet();
	static void InitializeLoop(AELoop* loop, uint32_t frequencyOfClock, AEPriorities priorityOfThis, LoopUpdateFunc_t loopUpdateFunc, uint32_t stackSizeOfLoop = 300);

	bool hasAEObject;
	
	template<class TPsuedoAEObjectType>
	static AELoop* InitPoolForAEObject(AELoop* theLoop, TPsuedoAEObjectType AEObjectthing, uint32_t frequencyOfClock, AEPriorities priorityOfThis, uint32_t stackSizeOfLoop = 300);


	AELoopObject* AEObjectIPossess;

	static uint16_t numOfAELoopsSoFar;
	AELoop() { 
	};
	static AELoop Pool[MaxNumOfAELoops];
	static TimerCallbackFunction_t PoolOfTimerFuncs[MaxNumOfAELoops];

	void GaurdUpdate(void* thisptr);

	LoopUpdateFunc_t LoopUpdateFunc;

	TaskHandle_t LoopUpdateTaskHandle;
	TimerHandle_t xTimerForClockTicks;

	AEPriorities _Priority;

	uint32_t FrequencyOfClock;
	 //void  LoopUpdate(void *pvParameters);
};




template<class TPsuedoAEObjectType>
inline AELoop * AELoop::InitPoolForAEObject(AELoop* theLoop, TPsuedoAEObjectType AEObjectthing, uint32_t frequencyOfClock, AEPriorities priorityOfThis, uint32_t stackSizeOfLoop)
{
	
	//auto theLoop = (AELoop::GetFromPool(frequencyOfClock, priorityOfThis, nullptr, stackSizeOfLoop));;
	AELoop::InitializeLoop(theLoop, frequencyOfClock, priorityOfThis, nullptr, stackSizeOfLoop);
	theLoop->AEObjectIPossess = (AELoopObject*)AEObjectthing;
	theLoop->hasAEObject = true;
	return theLoop;
}
