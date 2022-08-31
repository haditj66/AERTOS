#pragma once

/* Standard includes. */
#include <stdio.h> 
#include <type_traits>
#include <assert.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h" 

#include "AEEventBase.h" 

#include "AEUtils.h" 

#include "assert.h"
#include "QueueArgStructures.h"

#include "EventsForProject.h"




#define InitializeEvents(eventNum)\
(EventPools[eventNum-1])[i]->poolId = i;\
((TEvent##eventNum *)((EventPools[eventNum-1])[i]))->EvtIdStatic = eventNum-1;\
((EventPools[eventNum-1])[i])->EvtId = eventNum-1;\
((TEvent##eventNum*)((EventPools[eventNum-1])[i]))->init(eventNum-1);
//
//assert(((TEvent##eventNum *)((EventPools[eventNum-1])[i]))->EvtId != 60000, "one of the events wqas not declared with a static uint16_t EvtIdStatic;");

template<
	class TEvent1 = AENULLEvent, uint16_t sizeOfEvent1Pool = 0,
	class TEvent2 = AENULLEvent, uint16_t sizeOfEvent2Pool = 0,
	class TEvent3 = AENULLEvent, uint16_t sizeOfEvent3Pool = 0,
	class TEvent4 = AENULLEvent, uint16_t sizeOfEvent4Pool = 0,
	class TEvent5 = AENULLEvent, uint16_t sizeOfEvent5Pool = 0>
	class AEPoolManager
{
public:
	/*
	//make singleton
	static AEPoolManager* getInstance();
	// ========
	// Don't forget to declare these two. You want to make sure they
	// are unacceptable otherwise you may accidentally get copies of
	// your singleton appearing.
	AEPoolManager(AEPoolManager const&) = delete;
	void operator=(AEPoolManager const&) = delete;
	*/

	//MAKE_SINGLETON(AEPoolManager);

	friend class AEPublishSubscribeManager;

public:
	static AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>* getInstance();
	AEPoolManager(AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS> const&) = delete;
	void operator=(AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS> const&) = delete;
private:
	static AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>* instance;

	AEPoolManager();
public:

	QueueHandle_t queueToEnableEventInstances;
	TaskHandle_t TaskToEnableEventInstancesHandle;

	SemaphoreHandle_t MutexsForEvtPools[NUMOFEVENTS];
	SemaphoreHandle_t MutexForGettingEvtId;


	QueueHandle_t queueToDecrement;
	TaskHandle_t GaurdTaskDecrementRefCntHandle;

	//this should be of lowest priority as there is no need to rush decrememnting
	// an AEEvent object and sending it back to the pool.
	void GaurdTaskDecrementRefCnt(void* pvParameters);

	TEvent1 EvtPool1[(sizeOfEvent1Pool == 0) + sizeOfEvent1Pool];
	AEEventDiscriminator_t EvtDiscrimPool1[(sizeOfEvent1Pool == 0) + sizeOfEvent1Pool];
	AEEventDiscriminator_t* EvtDiscrimPoolptr1[(sizeOfEvent1Pool == 0) + sizeOfEvent1Pool];
	AEEventBase*   EvtPoolBase1[(sizeOfEvent1Pool == 0) + sizeOfEvent1Pool];
	TEvent2 EvtPool2[(sizeOfEvent2Pool == 0) + sizeOfEvent2Pool];
	AEEventDiscriminator_t EvtDiscrimPool2[(sizeOfEvent2Pool == 0) + sizeOfEvent2Pool];
	AEEventDiscriminator_t* EvtDiscrimPoolptr2[(sizeOfEvent2Pool == 0) + sizeOfEvent2Pool];
	AEEventBase*   EvtPoolBase2[(sizeOfEvent2Pool == 0) + sizeOfEvent2Pool];
	TEvent3 EvtPool3[(sizeOfEvent3Pool == 0) + sizeOfEvent3Pool];
	AEEventDiscriminator_t EvtDiscrimPool3[(sizeOfEvent3Pool == 0) + sizeOfEvent3Pool];
	AEEventDiscriminator_t* EvtDiscrimPoolptr3[(sizeOfEvent3Pool == 0) + sizeOfEvent3Pool];
	AEEventBase*   EvtPoolBase3[(sizeOfEvent3Pool == 0) + sizeOfEvent3Pool];
	TEvent4 EvtPool4[(sizeOfEvent4Pool == 0) + sizeOfEvent4Pool];
	AEEventDiscriminator_t EvtDiscrimPool4[(sizeOfEvent4Pool == 0) + sizeOfEvent4Pool];
	AEEventDiscriminator_t* EvtDiscrimPoolptr4[(sizeOfEvent4Pool == 0) + sizeOfEvent4Pool];
	AEEventBase*   EvtPoolBase4[(sizeOfEvent4Pool == 0) + sizeOfEvent4Pool];
	TEvent5 EvtPool5[(sizeOfEvent5Pool == 0) + sizeOfEvent5Pool];
	AEEventDiscriminator_t EvtDiscrimPool5[(sizeOfEvent5Pool == 0) + sizeOfEvent5Pool];
	AEEventDiscriminator_t* EvtDiscrimPoolptr5[(sizeOfEvent5Pool == 0) + sizeOfEvent5Pool];
	AEEventBase*   EvtPoolBase5[(sizeOfEvent5Pool == 0) + sizeOfEvent5Pool];

	uint16_t EventPoolSizes[NUMOFEVENTS];
	//AEEventBase** EventPools[NUMOFEVENTS]; //array EventPools[NUMOFEVENTS] to a pointer of an array of AEEventBase. or { &AEEventBase[],&AEEventBase[], &AEEventBase[] , ...}  
	//AEEventBase** EventPools[NUMOFEVENTS];
	AEEventBase** EventPools[NUMOFEVENTS];
	AEEventDiscriminator_t** EventPoolsDisc[NUMOFEVENTS];

	//arrEvt: this function takes an array of derived instances of type AEEventBase 
	//template<class TAEEvent>
	//(TAEEvent* arrEvt, int arrayEvtSize);

	//template <class Tevt>
	//Tevt* GetEvtFromPool(char* nameOfEvent);
	template<class Tevt>
	Tevt* GetEvtFromPool();
	template<class Tevt>
	Tevt* GetEvtFromPoolFromISR();

	void TaskToEnableEventInstances(void *pvParameters);
	void SetEventNotInUse(uint16_t eventId, uint16_t poolId);

private:

	//make singleton
   //static AEPoolManager* instance;
   //AEPoolManager();
	void Init();

	void _GetEventFromPool(uint16_t& eventId, uint16_t EvtId);

	//uint16_t GetCorrectEvtIdFromName(char * nameOfEvent);

};



AEPOOLMANAGERTEMPLATE
inline void AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>::Init()//(TAEEvent * arrEvt, int arrayEvtSize)
{
	//static_assert(std::is_base_of<AEEventBase, TAEEvent>::value, "type parameter Tevt of this class must derive from AEEventBase");

	//arrEvt = (AEEventBase*)arrEvt;

	//add event array to pool and set event id for the event
	//EventPools[numOfPoolsAddedSoFar] = arrEvt;

	//initialize ALL Event pools 
	//first check that the type of the pool is not set as an AENULLPool
	if (!TypeChecker::IsAEEventNullClass<TEvent1>())
	{
		//make sure the config for this event has a size larger than 0 
		configASSERT(sizeOfEvent1Pool > 0);
		//and make sure numOfEvents s correct
		configASSERT(NUMOFEVENTS > 0);

		//set all pointer of the derived event into the EvtPoolBase1 array
		for (uint16_t i = 0; i < sizeOfEvent1Pool; i++)
		{
			(EvtDiscrimPool1[i]).SetAsAEEvent((AEEventBase*)(&EvtPool1[i]));
			//EvtPoolBase1[i] = &(EvtDiscrimPool1[i]);
			EvtPoolBase1[i] = (AEEventBase*)(&EvtPool1[i]);
			EvtDiscrimPoolptr1[i] = &EvtDiscrimPool1[i];
		}


		EventPoolsDisc[0] = EvtDiscrimPoolptr1;
		EventPools[0] = EvtPoolBase1;
		EventPoolSizes[0] = sizeOfEvent1Pool;
	}
	if (!TypeChecker::IsAEEventNullClass<TEvent2>())
	{
		//make sure the config for this event has a size larger than 0
		configASSERT(sizeOfEvent2Pool > 0);
		//and make sure numOfEvents s correct
		configASSERT(NUMOFEVENTS > 1);

		//set all pointer of the derived event into the EvtPoolBase1 array
		for (uint16_t i = 0; i < sizeOfEvent2Pool; i++)
		{
			(EvtDiscrimPool2[i]).SetAsAEEvent((AEEventBase*)(&EvtPool2[i]));
			//EvtPoolBase2[i] = &(EvtDiscrimPool2[i]);
			EvtPoolBase2[i] = (AEEventBase*)(&EvtPool2[i]);
			EvtDiscrimPoolptr2[i] = &EvtDiscrimPool2[i];
		}

		EventPoolsDisc[1] = EvtDiscrimPoolptr2;
		EventPools[1] = EvtPoolBase2;
		EventPoolSizes[1] = sizeOfEvent2Pool;
	}
	if (!TypeChecker::IsAEEventNullClass<TEvent3>())
	{
		//make sure the config for this event has a size larger than 0
		configASSERT(sizeOfEvent3Pool > 0);
		//and make sure numOfEvents s correct
		configASSERT(NUMOFEVENTS > 2);

		//set all pointer of the derived event into the EvtPoolBase1 array
		for (uint16_t i = 0; i < sizeOfEvent3Pool; i++)
		{
			(EvtDiscrimPool3[i]).SetAsAEEvent((AEEventBase*)(&EvtPool3[i]));
			//EvtPoolBase3[i] = &(EvtDiscrimPool3[i]);
			EvtPoolBase3[i] = (AEEventBase*)(&EvtPool3[i]);
			EvtDiscrimPoolptr3[i] = &EvtDiscrimPool3[i];
		}

		EventPoolsDisc[2] = EvtDiscrimPoolptr3;
		EventPools[2] = EvtPoolBase3;
		EventPoolSizes[2] = sizeOfEvent3Pool;
	}
	if (!TypeChecker::IsAEEventNullClass<TEvent4>())
	{
		//make sure the config for this event has a size larger than 0
		configASSERT(sizeOfEvent4Pool > 0);
		//and make sure numOfEvents s correct
		configASSERT(NUMOFEVENTS > 3);

		//set all pointer of the derived event into the EvtPoolBase1 array
		for (uint16_t i = 0; i < sizeOfEvent4Pool; i++)
		{
			(EvtDiscrimPool4[i]).SetAsAEEvent((AEEventBase*)(&EvtPool4[i]));
			//EvtPoolBase4[i] = &(EvtDiscrimPool4[i]);
			EvtPoolBase4[i] = (AEEventBase*)(&EvtPool4[i]);
			EvtDiscrimPoolptr4[i] = &EvtDiscrimPool4[i];
		}

		EventPoolsDisc[3] = EvtDiscrimPoolptr4;
		EventPools[3] = EvtPoolBase4;
		EventPoolSizes[3] = sizeOfEvent4Pool;
	}
	if (!TypeChecker::IsAEEventNullClass<TEvent5>())
	{

		//make sure the config for this event has a size larger than 0
		configASSERT(sizeOfEvent5Pool > 0);
		//and make sure numOfEvents s correct
		configASSERT(NUMOFEVENTS > 4);

		//set all pointer of the derived event into the EvtPoolBase1 array
		for (uint16_t i = 0; i < sizeOfEvent5Pool; i++)
		{
			(EvtDiscrimPool5[i]).SetAsAEEvent((AEEventBase*)(&EvtPool5[i]));
			//EvtPoolBase5[i] = &(EvtDiscrimPool5[i]);
			EvtPoolBase5[i] = (AEEventBase*)(&EvtPool5[i]);
			EvtDiscrimPoolptr5[i] = &EvtDiscrimPool5[i];
		}

		EventPoolsDisc[4] = EvtDiscrimPoolptr5;
		EventPools[4] = EvtPoolBase5;
		EventPoolSizes[4] = sizeOfEvent5Pool;
	}




	

	//initialize all events in all pools
	if (!TypeChecker::IsAEEventNullClass<TEvent1>())
	{ 
		for (uint16_t i = 0; i < sizeOfEvent1Pool; i++)
		{ 
			(EventPools[0])[i]->poolId = i;
			//assert(((TEvent1 *)((EventPools[0])[i]))->EvtId != 60000, "one of the events wqas not declared with a static uint16_t EvtIdStatic;");
			((TEvent1 *)((EventPools[0])[i]))->EvtIdStatic = Event1_Evt;
			((EventPools[0])[i])->EvtId = Event1_Evt;
			((TEvent1*)((EventPools[0])[i]))->init(0);
			//InitializeEvents(1)
		}
	}
	if (!TypeChecker::IsAEEventNullClass<TEvent2>())
	{
		//set all pointer of the derived event into the EvtPoolBase1 array
		for (uint16_t i = 0; i < sizeOfEvent2Pool; i++)
		{ 
			InitializeEvents(2)
		}
	}
	if (!TypeChecker::IsAEEventNullClass<TEvent3>())
	{
		//set all pointer of the derived event into the EvtPoolBase1 array
		for (uint16_t i = 0; i < sizeOfEvent3Pool; i++)
		{ 
			InitializeEvents(3)
		}
	}
	if (!TypeChecker::IsAEEventNullClass<TEvent4>())
	{
		//set all pointer of the derived event into the EvtPoolBase1 array
		for (uint16_t i = 0; i < sizeOfEvent4Pool; i++)
		{ 
			InitializeEvents(4)
		}
	}
	if (!TypeChecker::IsAEEventNullClass<TEvent5>())
	{
		//set all pointer of the derived event into the EvtPoolBase1 array
		for (uint16_t i = 0; i < sizeOfEvent5Pool; i++)
		{ 
			InitializeEvents(5)
		}
	}


	//set pool ids and initialize all EventBase objects for all pools
	/*
	for (uint16_t j = 0; j < NUMOFEVENTS; j++)
	{
		for (int i = 0; i < EventPoolSizes[j]; i++)
		{

			(EventPools[j])[i]->poolId = i;
			assert(((TEvent1*)((EventPools[j])[i]))->EvtId != 60000, "one of the events wqas not declared with a static uint16_t EvtIdStatic;");
			((TEvent1*)((EventPools[j])[i]))->EvtIdStatic = j;
			((EventPools[j])[i])->EvtId = j;
			//initialize all events
			((TAEEvent*)((EventPools[j])[i]))->init(j);

		}
	}*/

	/*
	EventPoolSizes[numOfPoolsAddedSoFar] = arrayEvtSize;

	//get an array of AEEventBase pointers that point to the addresses of arrEvt
	AEEventBase* EvtPool[HIGHEST_NUM_OF_EVT_INSTANCES];

	for (int i = 0; i < arrayEvtSize; i++)
	{
		void* ptr = &arrEvt[i];
		//EvtPool[i] = (AEEventBase*)ptr;
		//EventPools[numOfPoolsAddedSoFar][i] = (AEEventBase*)ptr;
		EventPools[numOfPoolsAddedSoFar][i] = (AEEventBase)arrEvt[i];
	}

	//set that array of AEEventBase* to the correct event pool in EventPools
	//EventPools[numOfPoolsAddedSoFar] = EvtPool;
	//EventPools[numOfPoolsAddedSoFar] = reinterpret_cast<AEEventBase*> (arrEvt);

	//arrEvt[0].EvtId = numOfPoolsAddedSoFar;


	numOfPoolsAddedSoFar++;
	*/
}


/*
AEPOOLMANAGERTEMPLATE
template<class Tevt>
inline Tevt* AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>::GetEvtFromPool(char* nameOfEvent)
{
	static_assert(std::is_base_of<AEEventBase, Tevt>::value, "type parameter Tevt of this class must derive from AEEventBase");
	//auto nameOfEvent = static_cast<AEEventBase>(Tevt)::; 

	//get correct pool
	int EvtId = GetCorrectEvtIdFromName(nameOfEvent);

	return GetEvtFromPool<Tevt>();
}
*/


AEPOOLMANAGERTEMPLATE
template<class Tevt>
inline Tevt* AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>::GetEvtFromPool( )
{
	//static_assert(std::is_base_of<AEEventBase, Tevt>::value, "type parameter Tevt of this class must derive from AEEventBase");
	//auto nameOfEvent = static_cast<AEEventBase>(Tevt)::; 


	uint16_t EvtId = Tevt::EvtIdStatic;//evtID;

	//get the event that is not in use within the pool
	xSemaphoreTake(this->MutexsForEvtPools[EvtId], portMAX_DELAY);
	uint16_t EventNotInUseFromPool = 0xffff;
	_GetEventFromPool(EventNotInUseFromPool, EvtId);
	xSemaphoreGive(this->MutexsForEvtPools[EvtId]);

	//reset this event, cast it and return it
	//todo
	//EventPools[EvtId][EventNotInUseFromPool].reset();

	
	return (Tevt*)((EventPools[EvtId][EventNotInUseFromPool]));
}

AEPOOLMANAGERTEMPLATE
template<class Tevt>
inline Tevt* AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>::GetEvtFromPoolFromISR()
{
	//because this is from an ISR, there is no risk of this getting preempted (unless it is from another ISR)
	//so I do not need a semaphore to take it.
	//TODO because it is possible for another ISR to preempt this one, I can solve that problem by having
	// it grab an event object from the pool that is not next in line but maybe every third in line.
	//static_assert(std::is_base_of<AEEventBase, Tevt>::value, "type parameter Tevt of this class must derive from AEEventBase");
	  
	uint16_t EvtId = Tevt::EvtIdStatic;//evtID; 
	uint16_t EventNotInUseFromPool = 0xffff;
	_GetEventFromPool(EventNotInUseFromPool, EvtId); 
	  
	return (Tevt*)((EventPools[EvtId][EventNotInUseFromPool]));//nullptr;//(Tevt*)(EventPools[EvtId][EventNotInUseFromPool]);
}


AEPOOLMANAGERTEMPLATE
inline void AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>::_GetEventFromPool(uint16_t& EventNotInUseFromPool, uint16_t EvtId)
{
	for (uint32_t i = 0; i < EventPoolSizes[EvtId]; ++i)
	{
		if (!EventPools[EvtId][i]->isInUse)
		{
			EventNotInUseFromPool = EventPools[EvtId][i]->poolId;
			break;
		}
	}
	//i need to now set this event to in use. This means that the AO taking this event NEEDS to publish it otherwise it will stay in use.
        
        //make sure that  EventNotInUseFromPool = 0xffff  never happens as it means the pool was exceeded.
        configASSERT(EventNotInUseFromPool != 0xffff);
        
	(EventPools[EvtId][EventNotInUseFromPool])->isInUse = true;

}






//MAKE_SINGLETON_PUT_IN_CPP(AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>)
template<class TEvent1, uint16_t sizeOfEvent1Pool , class TEvent2 , uint16_t sizeOfEvent2Pool , class TEvent3 , uint16_t sizeOfEvent3Pool , class TEvent4 , uint16_t sizeOfEvent4Pool , class TEvent5 , uint16_t sizeOfEvent5Pool > AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>* AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>
	::instance = 0;
template<
	class TEvent1 , uint16_t sizeOfEvent1Pool ,
	class TEvent2 , uint16_t sizeOfEvent2Pool ,
	class TEvent3 , uint16_t sizeOfEvent3Pool ,
	class TEvent4 , uint16_t sizeOfEvent4Pool ,
	class TEvent5 , uint16_t sizeOfEvent5Pool >
	inline AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>* AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>
	::getInstance()
{
	if (instance == 0)
	{
		static AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS> soleInstance;
		instance = &soleInstance;
	}
	return instance;
}

AEPOOLMANAGERTEMPLATE
inline AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>::AEPoolManager()
{

	//create tasks and queues 
	queueToDecrement = xQueueCreate(40, sizeof(TwoIntArgStructure));
	//this priorirty of this task should be LOW. There is no rush to throw an object back into a pool
	xTaskCreate([](void* p) {static_cast<AEPoolManager*>(p)->GaurdTaskDecrementRefCnt(nullptr); }, "GaurdTaskDecrementRefCnt", configMINIMAL_STACK_SIZE, this, AOPRIORITYMEDIUM, &GaurdTaskDecrementRefCntHandle);

	//create mutexs
	for (int i = 0; i < NUMOFEVENTS; ++i)
	{
		MutexsForEvtPools[i] = xSemaphoreCreateMutex();
	}
	MutexForGettingEvtId = xSemaphoreCreateMutex();

	//create queues
	queueToEnableEventInstances = xQueueCreate(20, sizeof(TwoIntArgStructure));

	//create tasks
	//this priorirty of this task should be medium. There is no rush to throw an object back into a pool
	AEPoolManager *pToThisClass = this;
	xTaskCreate([](void* p) {static_cast<AEPoolManager*>(p)->TaskToEnableEventInstances(nullptr); }, "TaskToEnableEventInstances", configMINIMAL_STACK_SIZE, pToThisClass, AOPRIORITYMEDIUM, &TaskToEnableEventInstancesHandle);


	//initialize this poolmanager
	Init();

}

AEPOOLMANAGERTEMPLATE
inline void AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>
::TaskToEnableEventInstances(void * pvParameters)
{
	static TwoIntArgStructure QueueArgs;
	//int n;
	for (;;)
	{
		xQueueReceive(this->queueToEnableEventInstances, &QueueArgs, portMAX_DELAY);
		EventPools[QueueArgs.Arg1][QueueArgs.Arg2]->isInUse = false;
	}
}

AEPOOLMANAGERTEMPLATE
void AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>
::SetEventNotInUse(uint16_t eventId, uint16_t poolId)
{
	TwoIntArgStructure args(eventId, poolId);
	//int n = 3;
	xQueueSendToBack(queueToEnableEventInstances, &args, 0);
}

/*
AEPOOLMANAGERTEMPLATE
inline uint16_t AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>
::GetCorrectEvtIdFromName(char * nameOfEvent)
{

	xSemaphoreTake(this->MutexForGettingEvtId, portMAX_DELAY);
	uint32_t EvtId = 0xffff;
	for (uint16_t i = 0; i < NUMOFEVENTS; i++)
	{
		uint16_t cmpValue = strcmp(AEEventBase::Name[i], nameOfEvent);//EventPools[i][0]->GetName()
		if (cmpValue == 0)
		{
			EvtId = i;// EventPools[i][0]->EvtId;
			break;
		}
	}



	assert(EvtId != 0xffffffff);
	xSemaphoreGive(this->MutexForGettingEvtId);
	return EvtId;
}*/


AEPOOLMANAGERTEMPLATE
inline void AEPoolManager<AEPOOLMANAGERTEMPLATE_ARGS>
::GaurdTaskDecrementRefCnt(void * pvParameters)
{

	TwoIntArgStructure args;

	for (;;)
	{
		xQueueReceive(queueToDecrement, &args, portMAX_DELAY);

		--EventPools[args.Arg1][args.Arg2]->RefCounter;
                  UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		//check if it went to zero, if so then reset this event and put it back into not being used. 
		if (EventPools[args.Arg1][args.Arg2]->RefCounter <= 0)
		{
			EventPools[args.Arg1][args.Arg2]->Reset();
		}
		
	}

}