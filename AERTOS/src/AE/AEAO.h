#pragma once

#include <cstdint>


#include "FreeRTOS.h" 
#include "task.h"
#include "timers.h"
#include "semphr.h" 
#include "AEEventBase.h"
#include "SPBDataSubscription.h"

#include "AEObservorTypes.h"


//
//enum ObservorType : uint32_t
//{
//	Sensor = 1 << 2, 
//	// = 4, //1 << 2,
//	Interpretors = (1 << 3),
//	// = 8, //(1 << 3),
//	SPB = 1 << 4//= 16//1 << 4
//};


//if this AO is supscribing to any spbs, update that data
#define AE_UpdateALLSPBSubscriptions \
if (this->NumOfSubscriptions > 0) \
{\
	for (uint32_t i = 0; i < this->NumOfSubscriptions; i++)\
	{\
		this->SPBSubscriptions[i]->CopyDataOver();\
	}\
}

#define AE_UpdateALLWritableVariables \
if (this->NeedsWritableVariableUpdated  == true) \
	if (this->NeedsWritableVariableUpdated == true)\
	{\
		this->UpdateWriteableVariables();\
	}


class AEAO
{
public:
	  
	friend class SPBSubprivateImp;
	friend class AEPublishSubscribeManager;
	

	static uint16_t AOIDsInOrderOfPriorities[NUMOFACTIVEOBJECTS];

	uint8_t GetPriority() const { return _Priority; }; 
	PropertyGet(uint16_t, AO_ID) 
	static AEAO const * AllAO[NUMOFACTIVEOBJECTS];
	 
	QueueHandle_t queueExecuteForEvt;

	void PublishEvt(AEEventBase* const evt);
	void PublishEvt(AEEventDiscriminator_t * const evt);
	void PostEvtToAO(AEAO* AOToPostTo, AEEventBase * const evtToPost) const;
	void PostEvtToAO(uint16_t AOToPostToId, AEEventBase* const evt) const;
	void PostEvtToAO(AEAO* AOToPostTo, AEEventDiscriminator_t * const evt) const;
	void PostEvtToAO(uint16_t AOToPostToId, AEEventDiscriminator_t * const evt) const;

	///These will post the event to the front of the queue so to run next in line
	void PostEvtToAOToTheFront(AEAO* AOToPostTo, AEEventBase * const evtToPost) const;
	void PostEvtToAOToTheFront(uint16_t AOToPostToId, AEEventBase* const evt) const;
	void PostEvtToAOToTheFront(AEAO* AOToPostTo, AEEventDiscriminator_t * const evt) const;
	void PostEvtToAOToTheFront(uint16_t AOToPostToId, AEEventDiscriminator_t * const evt) const;

	static void ConfigureAndStart();

	

	//stufffor different AO -------------------------------
	/*template <class Tevt>
	void Subscribe();
	template <class Tevt>
	void UnSubscribe(); */
	 
protected:

	bool isCurrentlyExecuting;
	bool NeedsWritableVariableUpdated;
	virtual void UpdateWriteableVariables() {};

	uint8_t  _Priority;

	AEAO();

	

	virtual void CheckIfConfiguredProperly() const {
		//assert all i need to assert here,
	};

	static void ConfigurePriorities();
	//AECHANGED:
	void  _PostEvtToAO(uint16_t AOToPostToId, AEEventDiscriminator_t * const evt, bool toFront = false) const;
	//AECHANGEDDONE:

	//stuff dealing with data subscribing ---------------------------------------- 
	//if subscribeable, make it output size. if not, make it one 
	SPBDataSubscription* SPBSubscriptions[MAXNUM_OF_AE_SUBSCRIPTIONS_To_SPBs];

	void AddSubscribtionToSPB(SPBDataSubscription* subscription)
	{  
		SPBSubscriptions[this->NumOfSubscriptions] = subscription;
		this->NumOfSubscriptions++;

		configASSERT(this->NumOfSubscriptions <= MAXNUM_OF_AE_SUBSCRIPTIONS_To_SPBs);
	} 
	//---------------------------------------------------------------------------------





	//should not be here as all that derive will have tasks implemented
	//differently
	//TaskHandle_t GaurdTaskToObjectExecutionHandle;

	//stufffor different AO -------------------------------
	//TaskHandle_t GaurdTaskToExecuteForEvtHandle; 
	//QueueHandle_t queueExecuteForEvt; 
	//void GaurdTaskToExecuteForEvt(void* pvParameters);

	//SemaphoreHandle_t xSemaphoreForObjectExecution;

uint8_t NumOfSubscriptions;

private:

	

	static uint16_t idIndex;
	//uint16_t AO_ID;

};
 
/*
template<class Tevt>
inline void AEAO::Subscribe()
{
	//arg1 is evtId. arg2 is AOid
	ThreeIntAndAEEvtBasePtr subscriberArgs(Tevt::EvtIdStatic, this->AO_ID, 0, nullptr);

	xQueueSendToBack(AEPublishSubscribeManager::getInstance()->queueForSubAndPub, &subscriberArgs, 0);
}


template<class Tevt>
inline void AEAO::UnSubscribe()
{
	ThreeIntAndAEEvtBasePtr unsubscriberArgs(Tevt::EvtIdStatic, this->AO_ID, 1, nullptr);

	xQueueSendToBack(AEPublishSubscribeManager::getInstance()->queueForSubAndPub, &unsubscriberArgs, 0);
}*/