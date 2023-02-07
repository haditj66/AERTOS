#include "AEAO.h"
#include "QueueArgStructures.h"
#include <memory> 

#include "AEPublishSubscribeManager.h"

#include "AEObservorBase.h"
#include "AESPBObservor.h"

#include "SPBDataSubscription.h"

AEAO const * AEAO::AllAO[NUMOFACTIVEOBJECTS] = {};
uint16_t AEAO::idIndex = 0;
bool AEAO::AERTOSStarted = false;
uint16_t AEAO::AOIDsInOrderOfPriorities[NUMOFACTIVEOBJECTS] = {};



AEAO::AEAO()  
{

	isCurrentlyExecuting = false;
	NeedsWritableVariableUpdated = false;

	NumOfSubscriptions = 0;
	 
	//give it the AO id and add it to the AllAO list
	_AO_ID = idIndex;
	//assert that the number of AO created so far does not exceed the 
	//NUMOFACTIVEOBJECTS set in the config
	configASSERT(_AO_ID < NUMOFACTIVEOBJECTS);
	AllAO[this->_AO_ID] = this;

	//stuff for different AO -------------------------------
	//queueExecuteForEvt = xQueueCreate(20, sizeof(AEEventBase*));
	//xTaskCreate([](void* p) {static_cast<AEAO*>(p)->GaurdTaskToExecuteForEvt(nullptr); }, "GaurdTaskToExecuteForEvt", configMINIMAL_STACK_SIZE+50, this, AOPRIORITYMEDIUM, &GaurdTaskToExecuteForEvtHandle);
	 
	//xSemaphoreForObjectExecution = xSemaphoreCreateMutex();
	idIndex++;


	
}

 
 
 
void AEAO::PublishEvt(AEEventBase * const evt)
{

	// I need to get the AEEventDiscriminator_t from evt
	ThreeIntAndAEEvtBasePtr* publishArgs = ThreeIntAndAEEvtBasePtr
		::GetFromPool(0, _AO_ID, 2, PoolManager->EventPoolsDisc[evt->EvtId][evt->poolId]);
	
	xQueueSendToBack(AEPublishSubscribeManager::getInstance()->queueForSubAndPub, &publishArgs,0);
}

void AEAO::PublishEvt(AEEventDiscriminator_t * const evt)
{

	ThreeIntAndAEEvtBasePtr* publishArgs = ThreeIntAndAEEvtBasePtr::GetFromPool(0, _AO_ID, 2, evt);
	xQueueSendToBack(AEPublishSubscribeManager::getInstance()->queueForSubAndPub, &publishArgs, 0);
}



void AEAO::PostEvtToAO(AEAO* AOToPostTo, AEEventBase* const evt)  const
{ 
	AEEventDiscriminator_t* evtBase = PoolManager->EventPoolsDisc[evt->EvtId][evt->poolId];
	_PostEvtToAO(AOToPostTo->GetAO_ID(), evtBase);
}

void AEAO::PostEvtToAO(uint16_t AOToPostToId, AEEventBase* const evt) const
{
	AEEventDiscriminator_t* evtBase = PoolManager->EventPoolsDisc[evt->EvtId][evt->poolId];
	_PostEvtToAO(AOToPostToId, evtBase);
}

void AEAO::PostEvtToAO(AEAO* AOToPostTo, AEEventDiscriminator_t * const evt) const
{ 
	_PostEvtToAO(AOToPostTo->GetAO_ID(), evt);
}

void AEAO::PostEvtToAO(uint16_t AOToPostToId, AEEventDiscriminator_t * const evt) const
{ 
	_PostEvtToAO(AOToPostToId, evt);
}


///These will post the event to the front of the queue so to run next in line
void AEAO::PostEvtToAOToTheFront(AEAO* AOToPostTo, AEEventBase* const evt)  const
{
	AEEventDiscriminator_t* evtBase = PoolManager->EventPoolsDisc[evt->EvtId][evt->poolId];
	_PostEvtToAO(AOToPostTo->GetAO_ID(), evtBase, true);
}

void AEAO::PostEvtToAOToTheFront(uint16_t AOToPostToId, AEEventBase* const evt) const
{
	AEEventDiscriminator_t* evtBase = PoolManager->EventPoolsDisc[evt->EvtId][evt->poolId];
	_PostEvtToAO(AOToPostToId, evtBase, true);
}

void AEAO::PostEvtToAOToTheFront(AEAO* AOToPostTo, AEEventDiscriminator_t * const evt) const
{
	_PostEvtToAO(AOToPostTo->GetAO_ID(), evt, true);
}

void AEAO::PostEvtToAOToTheFront(uint16_t AOToPostToId, AEEventDiscriminator_t * const evt) const
{
	_PostEvtToAO(AOToPostToId, evt, true);
}


void  AEAO::_PostEvtToAO(uint16_t AOToPostToId, AEEventDiscriminator_t * const evt, bool toFront) const
{
	//since this is posting to just one AO max, there is no need to go through the publishsubscribe manager.
	 
	ThreeIntAndAEEvtBasePtr* publishArgs = ThreeIntAndAEEvtBasePtr
		::GetFromPool(0, _AO_ID, 2, evt);


	//check if the ONLY AO I care about is subscribed
	//I only need to check if the event ID is less then the _MAX_NumOfAllEvents as
	// any event after that is considered to be always subscribed to 
	//Enter_Sig,
	//Exit_Sig,
	//Update_Sig,
	//ActivateFSM_Sig,
	//DeActivateFSM_Sig
	if (PublishSubscribeManager->EventSubscribers[evt->GetEvtID()][AOToPostToId] == true
		|| evt->GetEvtID() > MAX_NumOfAllEvents)
	{
		//if this is an aeevent, I need to incrmeent the refcounter
		if (evt->type == 1)
		{
			evt->evt->RefCounter++;
		}

		//send the event to the AO evtQueue  
		if (toFront == true)
		{
			xQueueSendToFront(AEAO::AllAO[AOToPostToId]->queueExecuteForEvt, &evt, 0);
		}
		else
		{
			xQueueSendToBack(AEAO::AllAO[AOToPostToId]->queueExecuteForEvt, &evt, 0);
		}

	}

	else {
		//if that one AO that I am posting is not even subscribed, reset the event
		if (evt->type == 1)
		{
			evt->evt->Reset();
		} 
	}
}

void AEAO::ConfigureAndStart()
{
	//get instances of all singletons at least once righ now so their constructor will be called for tasks 
	PoolManager; //7000
	AEPublishSubscribeManager::getInstance();//1000

 
	//initialize endchain observors
	AEObservorBase::InitializeEndChainObservors();
	AESPBObservor::ConfigureSPBs(); 


	//first configure all priorities
	AEAO::ConfigurePriorities();

	SPBDataSubscription::CheckIfAllSubscriptionsAreValid();

	//go through each AO and check if they were configure properly.
	for (uint16_t i = 0; i < idIndex; i++)
	{
		AEAO::AllAO[i]->CheckIfConfiguredProperly();
	}
	
	

	for (int i = 0; i < 30; i++)
	{
		AEPrint("ssvsc %d", 1);
	}
	AERTOSStarted = true;
	
	vTaskStartScheduler();//12000
}

void AEAO::ConfigurePriorities()
{
	//I need to go through all AO of types and configure their priorities and then
	//set the priorities in order of higher priority to lower priority.





	AEAO const * tempOfAllAOInOrder[NUMOFACTIVEOBJECTS]; 
	for (size_t i = 0; i < NUMOFACTIVEOBJECTS; i++){ tempOfAllAOInOrder[i] = AllAO[i];}

	//now that all priorities have been established and locked in. order them correctly
	uint16_t orderIndex = 0; 
	while (orderIndex < idIndex)//idIndex is the numOfAOCreastedSoFar
	{ 
		//go through and find the largest Priority
		uint16_t indexOfLargestPriorityFoundSoFar = idIndex-1;
		for (uint16_t i = orderIndex; i < idIndex; i++)
		{ 
			if (tempOfAllAOInOrder[i]->GetPriority() >= tempOfAllAOInOrder[indexOfLargestPriorityFoundSoFar]->GetPriority())
			{
				indexOfLargestPriorityFoundSoFar = i;
			}  
		}
		 
		//set indexOfLargestPriorityFoundSoFar in the list AOIDsInOrderOfPriorities 
		AOIDsInOrderOfPriorities[orderIndex] = tempOfAllAOInOrder[indexOfLargestPriorityFoundSoFar]->GetAO_ID();

		//swap the AO in the temp array
		AEAO const*  tpSwap = tempOfAllAOInOrder[orderIndex];
		tempOfAllAOInOrder[orderIndex] = tempOfAllAOInOrder[indexOfLargestPriorityFoundSoFar];
		tempOfAllAOInOrder[indexOfLargestPriorityFoundSoFar] = tpSwap;

		orderIndex++;
	}


}


//stufffor different AO -------------------------------
/*
 void AEAO::GaurdTaskToExecuteForEvt(void * pvParameters)
{
	 AEEventBase* evt;

	 for (;;)
	 {
		 xQueueReceive(queueExecuteForEvt, &evt, portMAX_DELAY);
		 xSemaphoreTake(xSemaphoreForObjectExecution, portMAX_DELAY);
		 
		 //should pass in the AEEventBase pointer to the SM and when done, let the reference counter structure know that you are done

		 //EventTest1* s = static_cast<EventTest1*>(evt);
		//EventTest1* s = (EventTest1*)evt;
		 //do some thing with the SM object. where every state will have its own implementation
		 int bla;
		 //bla = (*evtSharedPointer.get()).GetEvtID();
		 //auto count = evtSharedPointer->use_count();
		 printf("AO%d executing event \n", AO_ID);
		 for (int i = 0; i < 3000000000; i++)
		 {
			 
		 }
		 printf("AO%d Done executing event \n", AO_ID);

		 //after the sm is done with the reference, decrement the counter
		 evt->DecrementRefCounter();

		 xSemaphoreGive(xSemaphoreForObjectExecution);

	 }
}
 */