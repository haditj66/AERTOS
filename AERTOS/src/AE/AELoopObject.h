#pragma once

#include "AELoop.h"
//#include "AEObjects.h"

#include "InlineISubscribeable.h"

//if currently updating, write to the backup variable
//else write to the main variable
#define AELoopObect_ReadWrite_Float(nameOfVariable)\
float  nameOfVariable;\
float  nameOfVariable##_Backup;\
void WriteTo##nameOfVariable(float ValueToUpdateItWith){\
if (isCurrentlyExecuting == true) \
{\
nameOfVariable##_Backup = ValueToUpdateItWith;\
}\
else{\
nameOfVariable = ValueToUpdateItWith;\
}\
}
constexpr int FloatCounts = 1;


#define SubToFunction(NameOfClass, FunctionName) \
[](AEEventDiscriminator_t* evt, void* p) -> void { \
static_cast<NameOfClass*>(p)->FunctionName(evt); \
}\
	
#define AELoopSubscribe(EventName, NameOfClass, FunctionName) \
Subscribe<EventName>(SubToFunction(NameOfClass, FunctionName));

typedef void(*EventLoopCallBack_t)(AEEventDiscriminator_t* evt, void* p);
typedef void(*InlineSubWorkAround_t)(int AOID);



class AELoopEventSubs
{
public:
	EventPoolSize_t ToEventID = ProjectEventSignals::_MAX_NumOfAllEvents;
	EventLoopCallBack_t CallbackToCall;
	
	bool IsInUse;
	
	AELoopEventSubs()
	{
		ToEventID = ProjectEventSignals::_MAX_NumOfAllEvents;
		IsInUse = false;
	}
	
};




//these objects have an AELoop that is set up to a clock

class AELoopObject  : public AEAO
{
public:



	friend class AELoop;
	
	xTimerHandle TimerForStart;

	AELoopObject() {
		initializedAEObject = false;
		LoopForThisObject = AELoop::GetFromPoolNoInitYet();
		LoopForThisObject->hasAEObject = true;
		
		
		//stuff for event subbing
		this->queueExecuteForEvt = xQueueCreate(20, sizeof(AEEventDiscriminator_t*));
		xTaskCreate([](void* p) {
			static_cast<AELoopObject*>(p)->GaurdTaskToExecuteForEvt(nullptr); 
			},
			"GaurdTaskToExecuteForEvt",
			configMINIMAL_STACK_SIZE,
			this,
			AOPRIORITYMEDIUM,
			&GaurdTaskToExecuteForEvtHandle);
		 
		MutexForSubbing = xSemaphoreCreateMutex();
		
		
		//create the timer that will notify this AELoop
//		uint32_t ticks = (configTICK_RATE_HZ / 1000);
//		auto TimerForStart = xTimerCreate("T",				/* The text name assigned to the software timer - for debug only as it is not used by the kernel. */
//			ticks,		                /* The period of the software timer in ticks. */
//			pdTRUE,			/* xAutoReload is set to true */
//			NULL,				/* The timer's ID is not used. */
//			[](void* p) {
//				static_cast<AELoopObject*>(p)->_StartAOLoopObject(nullptr); 
//			}); /* The function executed when the timer expires. */

		
		xTaskCreate([](void* p) {
			static_cast<AELoopObject*>(p)->_StartAOLoopObject(nullptr); 
			},
			"StartAOLoopObject",
			configMINIMAL_STACK_SIZE,
			this,
			AOPRIORITYMEDIUM,
			&StartAOLoopObjectHandle);
		 
		MutexForSubbing = xSemaphoreCreateMutex();
	}

	
	virtual void CheckIfConfiguredProperly() const override  
	{
		AEAO::CheckIfConfiguredProperly();
		if (initializedAEObject == false)
		{
			// you did not initialize one of your AEobjects
			configASSERT(false);
		}
		 

	}

	void InitObject(uint32_t frequencyOfClock, AEPriorities priority, uint32_t stackSizeOfLoop = 350) {
		LoopForThisObject = AELoop::InitPoolForAEObject(LoopForThisObject, this, frequencyOfClock, priority, stackSizeOfLoop);
		//AELoop::InitializeLoop(InitializeLoop);
		initializedAEObject = true;
		isCurrentlyExecuting = false;
	} 


	 

protected:

	bool initializedAEObject;
	AELoop* LoopForThisObject;


	virtual void Update() = 0;
	void PreUpdate() {
		AE_UpdateALLSPBSubscriptions

		AE_UpdateALLWritableVariables

//		this->isCurrentlyExecuting = true;
		AEEventDiscriminator_t* ptrToUpdate = &AEEventDiscriminator_t::UpdateEvtInstance;
		xQueueSendToBack(this->queueExecuteForEvt, &ptrToUpdate, 0);
//		Update();
//		this->isCurrentlyExecuting = false;
	}
	
	 
	AELoopEventSubs EventLoopCallBack[ProjectEventSignals::_MAX_NumOfAllEvents];
	//int SubsSoFar = 0;
	
	xSemaphoreHandle MutexForSubbing;
	
	
	
	template<uint16_t Tevt>
		void Subscribe(EventLoopCallBack_t callback)
		{
			InlineSubWorkAround_t aa = [](int AOID)->void
			{
				_InlineSubscribe<Tevt>(AOID);
			};
			_Subscribe(Tevt, callback, aa);
		}
	template<class Tevt>
		void Subscribe(EventLoopCallBack_t callback)
		{
			InlineSubWorkAround_t aa = [](int AOID)->void
			{
				_InlineSubscribe<Tevt>(AOID);
			};
			_Subscribe(Tevt::EvtIdStatic, callback, aa);
		}
	
	template<class Tevt>
		void UnSubscribe()
		{
			InlineSubWorkAround_t aa = [](int AOID)->void
			{
				_InlineUnSubscribe<Tevt>(AOID);
			};
			_UnSubscribe(Tevt::EvtIdStatic, aa);
		}
	
	template<uint16_t Tevt>
		void UnSubscribe()
		{
			InlineSubWorkAround_t aa = [](int AOID)->void
			{
				_InlineUnSubscribe<Tevt>(AOID);
			};
			_UnSubscribe(Tevt, aa);
		}
	
	
	void _UnSubscribe(int evtId, InlineSubWorkAround_t inlineSubWorkAround)
	{
		xSemaphoreTake(MutexForSubbing, portMAX_DELAY);
		for (size_t i = 0; i < ProjectEventSignals::_MAX_NumOfAllEvents; i++)
		{
			if (EventLoopCallBack[i].IsInUse == true)
			{
				if (EventLoopCallBack[i].ToEventID == evtId)
				{
					EventLoopCallBack[i].IsInUse = false;
					EventLoopCallBack[i].ToEventID = ProjectEventSignals::_MAX_NumOfAllEvents;
					inlineSubWorkAround(this->GetAO_ID());
					break;
				}
			}
		} 
		xSemaphoreGive(MutexForSubbing); 
		
	}
	
	
	
	void _Subscribe(int evtId, EventLoopCallBack_t callback, InlineSubWorkAround_t inlineSubWorkAround)
	{
		//subscribe to event 
		xSemaphoreTake(MutexForSubbing, portMAX_DELAY);
		//check if event already subscribed to. if so, just replace the callback
		
		for (size_t i = 0; i < ProjectEventSignals::_MAX_NumOfAllEvents; i++)
		{
			if (EventLoopCallBack[i].IsInUse == true)
			{ 
				if (evtId == EventLoopCallBack[i].ToEventID)		
				{ 
					xSemaphoreGive(MutexForSubbing);
					EventLoopCallBack[i].CallbackToCall = callback;
					return;
				}
			}  	
		}
		//iterate through and get a EventLoopCallBack that is not in use
		uint32_t eventLoopIndNotInUse = 0xffffffff;
		for (size_t i = 0; i < ProjectEventSignals::_MAX_NumOfAllEvents; i++)
		{
			if (EventLoopCallBack[i].IsInUse == false)
			{ 
			 eventLoopIndNotInUse = i;
				break;
			}
		}
		AEAssertRuntime(eventLoopIndNotInUse != 0xffffffff, "AELoop's subscription of EventLoopCallBack has overflowed. That should never happen")
		
		
		inlineSubWorkAround(this->GetAO_ID()); //_InlineSubscribe<Tevt>(this->GetAO_ID());
		EventLoopCallBack[eventLoopIndNotInUse].ToEventID =  evtId;
		EventLoopCallBack[eventLoopIndNotInUse].CallbackToCall = callback; // 
		
		//			[](AEEventDiscriminator_t* evt, void* p) -> void { 
		//			static_cast<AELoopObject1Test*>(p)->Button1_Callback(evt);
		//		};
		//SubsSoFar++;
		xSemaphoreGive(MutexForSubbing);
	}
	
	
	void _StartAOLoopObject(void * pvParameters)
	{ 
		StartAOLoopObject();
		vTaskDelete(NULL);
	}	
	
	virtual void StartAOLoopObject() = 0;
	
	
	TaskHandle_t GaurdTaskToExecuteForEvtHandle;
	TaskHandle_t StartAOLoopObjectHandle;
	
	void GaurdTaskToExecuteForEvt(void * pvParameters)
	{
		AEEventDiscriminator_t* evt;
		for (;;)
		{
			xQueueReceive(this->queueExecuteForEvt, &evt, portMAX_DELAY);
				
			AEAssertRuntime(uxQueueSpacesAvailable(queueExecuteForEvt) > 1, "queue for your AEObject has filled. This should never happen. Your implementaions in update or event callbacks are too long. or your udpate frequency is too fast.");
			
			auto evtID = evt->GetEvtID();
			
			if (evtID == AEEventDiscriminator_t::UpdateEvtInstance.GetEvtID())
			{
				this->isCurrentlyExecuting = true;
				Update();
				this->isCurrentlyExecuting = false;
				 
			}
			else
			{
				//go through all EventLoopCallBack and check
				EventLoopCallBack_t callbackForEvt;
				xSemaphoreTake(MutexForSubbing, portMAX_DELAY);
				for (size_t i = 0; i < ProjectEventSignals::_MAX_NumOfAllEvents; i++)
				{
					if (evtID == EventLoopCallBack[i].ToEventID)		
					{
						callbackForEvt = EventLoopCallBack[i].CallbackToCall;
						break;
					} 
				}
				xSemaphoreGive(MutexForSubbing);
				
				//call the callback
				callbackForEvt(evt, this);	
				
				
				if (evt->type == 1)
				{
					evt->evt->DecrementRefCounter();
				}
			}
			
				

				
		}

	}
	
	 

private:





};
