#pragma once

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h" 

#include "AEPoolManager.h" 



class AEPublishSubscribeManager
{
public:
        friend class AEEventListener;
        template<TemplateFor_SimpleFSM_NoDefaults>
        friend class AESimpleFSM; 
        template<uint16_t POOLSIZE, class ActionRequest1, class ActionRequest2 , class ActionRequest3>
        friend class AEAOSubscribeAble; 

		Friend_ToALL_ActionRequestObjects_TDU

		template <uint16_t Tevt>
		friend void _InlineSubscribeFROMISR(uint16_t AO_ID);
		template <uint16_t Tevt>
		friend void _InlineUnSubscribeFROMISR(uint16_t AO_ID);

	//make this a singleton
	MAKE_SINGLETON(AEPublishSubscribeManager)

	QueueHandle_t queueForSubAndPub;
	TaskHandle_t GaurdTaskForSubAndPubHandle;
	void GaurdTaskForSubAndPub(void* pvParameters);

	void PublishEvtFromISR(AEEventBase * evt);
	void PublishEvtFromISR(AEEventDiscriminator_t * evt);

	QueueHandle_t queuePublishEvt;
	TaskHandle_t GaurdTaskForPublishingEvtHandle; 
	 
	SemaphoreHandle_t MutexsForEvtSubsArray; 
	 
	 
	/*
	uint32_t Seats1[NUMOFEVENTS];//seats are binary placements of which eventsubscriber index in the EventSubscribers array is occupied by a subscriber.
	bool RowInUse1[NUMOFEVENTS];// this is a bool for if seats1 is in use
	uint32_t Seats2[NUMOFEVENTS];
	bool RowInUse2[NUMOFEVENTS];
	uint32_t Seats3[NUMOFEVENTS];
	bool RowInUse3[NUMOFEVENTS];
	uint32_t Seats4[NUMOFEVENTS];
	bool RowInUse4[NUMOFEVENTS];
	uint32_t Seats5[NUMOFEVENTS];
	bool RowInUse5[NUMOFEVENTS];
	uint32_t Seats6[NUMOFEVENTS];
	bool RowInUse6[NUMOFEVENTS];
	*/
	uint8_t CurrentIndexForAddingSubs[NUMOFEVENTS]; // this gives a current placement of where the last add was placed. next place will most likely not be occupied
	uint8_t theRowAddingexIsOn[NUMOFEVENTS];
	uint8_t CurrentIndexForRemovingSubs[NUMOFEVENTS];//the second number 6 is the row of seats it is currently on.
	uint8_t theRowRemovingexIsOn[NUMOFEVENTS];

	bool EventSubscribers[MAX_NumOfAllEvents][NUMOFACTIVEOBJECTS];
	//etl::set < string, 10, std::greater<string> >  EventSubscribers[NUMOFEVENTS][NUMOFACTIVEOBJECTS + 1];
	
	  
	void _UnSubscribeToEvt(uint16_t evtId, uint16_t AOID);

	template<uint16_t Tevt>
	bool IsAOSubscribedToEvent(uint16_t AOID) const; 
	bool IsAOSubscribedToEvent(uint16_t AOID, uint16_t evtID) const;
        
protected:
	
private:

	void _SubscribeToEvt(uint16_t evtId, uint16_t AOID);
	
	

	void PublishEvt(ThreeIntAndAEEvtBasePtr* AddingsubscriberArgs);


	
};

template<uint16_t Tevt>
inline bool AEPublishSubscribeManager::IsAOSubscribedToEvent(uint16_t AOID) const
{
	return IsAOSubscribedToEvent(AOID, Tevt);
}
