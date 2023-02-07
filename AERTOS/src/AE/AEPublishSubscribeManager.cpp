#include "AEPublishSubscribeManager.h"
#include "QueueArgStructures.h"
#include "AEEventBase.h"
#include "AEAO.h"
#include "FreeRTOS.h"

#include <memory>

#define CHECK_IF_BIT_SET(var,pos) ((var) & (1<<(pos)))


//make this a singleton
MAKE_SINGLETON_PUT_IN_CPP(AEPublishSubscribeManager)

AEPublishSubscribeManager::AEPublishSubscribeManager()
{

	AEPublishSubscribeManager *pToThisClass = this;

	queueForSubAndPub = xQueueCreate(20, sizeof(AEEventBase*));
	xTaskCreate([](void* p) {static_cast<AEPublishSubscribeManager*>(p)->GaurdTaskForSubAndPub(nullptr); }, "GaurdTaskForSubAndPub", 300, pToThisClass, configMAX_PRIORITIES, &GaurdTaskForSubAndPubHandle);

	/*
	queuePublishEvt = xQueueCreate(20, sizeof(AEEventBase*));
	xTaskCreate([](void* p) {static_cast<AEPublishSubscribeManager*>(p)->GaurdTaskForPublishingEvt(nullptr); }, "GaurdTaskForPublishingEvt", configMINIMAL_STACK_SIZE , pToThisClass, AOPRIORITYHIGHEST, &GaurdTaskForPublishingEvtHandle);
	*/

	MutexsForEvtSubsArray = xSemaphoreCreateMutex();


	for (int i = 0; i < NUMOFEVENTS; i++)
	{
		/*
		RowInUse1[i] = true;
		RowInUse2[i] = false;
		RowInUse3[i] = false;
		RowInUse4[i] = false;
		RowInUse5[i] = false;
		RowInUse6[i] = false;

		//set all seats to NOT occupies. so no subscribers.
		Seats1[i] = 0;
		Seats2[i] = 0;
		Seats3[i] = 0;
		Seats4[i] = 0;
		Seats5[i] = 0;
		Seats6[i] = 0;
		
		CurrentIndexForAddingSubs[i] = 0;
		CurrentIndexForRemovingSubs[i] = 0;

		theRowAddingexIsOn[i] = 0;
		theRowRemovingexIsOn[i] = 0;
		*/
	}

}



void AEPublishSubscribeManager::GaurdTaskForSubAndPub(void * pvParameters)
{
	//arg1: evtId. 
	//arg2: AOid 
	//arg3: the command.   0 is to subscribe	
	//arg4: AEEventBase*
	ThreeIntAndAEEvtBasePtr* AddingsubscriberArgs;

	for (;;)
	{
		xQueueReceive(this->queueForSubAndPub, &AddingsubscriberArgs, portMAX_DELAY);

		xSemaphoreTake(MutexsForEvtSubsArray, portMAX_DELAY);

		/*
		//look for seat that is not occupied
		//first check if the index is at the first row of seats.
		//AddingsubscriberArgs.Arg1 is the theEventId
		if (theRowAddingexIsOn[AddingsubscriberArgs.Arg1] == 0)
		{
			bool anySeatsFound = false;
			for (int i = 0; i < 32; i++)
			{
				//increment the index and check the seats all the way around.
				CurrentIndexForAddingSubs[AddingsubscriberArgs.Arg1] += i;
				if (CurrentIndexForAddingSubs[AddingsubscriberArgs.Arg1] > 31)
				{
					CurrentIndexForAddingSubs[AddingsubscriberArgs.Arg1] = 0;
				}
				if (Seats1[AddingsubscriberArgs.Arg1] & (1 << CurrentIndexForAddingSubs[AddingsubscriberArgs.Arg1]))//check if bit is occupied
				{
					anySeatsFound = true;
					break;
				}
			}

			if (!anySeatsFound)//if no seats were found, increment the theRowAddingexIsOn to move on to the next row of seats
			{

			}
		}
		*/

		//arg1: evtId. 
		//arg2: AOid 
		//arg3: 0 
		//arg4: null
		//0 is to subscribe			 ------------------------------------
		if (AddingsubscriberArgs->Arg3 == 0)
		{
			//no need for seats, just match the AO_ID to the seat number in the event array
			_SubscribeToEvt(AddingsubscriberArgs->Arg1, AddingsubscriberArgs->Arg2);
		}


		//arg1: evtId. 
		//arg2: AOid 
		//arg3: 1 
		//arg4: null
		//1 is to unsubscribe		-----------------------------------
		else if (AddingsubscriberArgs->Arg3 == 1)
		{
			_UnSubscribeToEvt(AddingsubscriberArgs->Arg1, AddingsubscriberArgs->Arg2);
		}


		//arg1: Signal Id, if its a signal
		//arg2: AOid 
		//arg3: 2 
		//arg4: AEEventBase*
		//2 is to publish an event	 ---------------------------------------
		else if (AddingsubscriberArgs->Arg3 == 2)
		{
			PublishEvt(AddingsubscriberArgs);
		}

		//EventSubscribers[][];
		//set bit to true signifiying that this spot has been taken.

		xSemaphoreGive(MutexsForEvtSubsArray);


	}
}



void AEPublishSubscribeManager::PublishEvtFromISR(AEEventBase * evt)
{
	
	AEAssertRuntime(AEAO::GetAERTOSStarted() == true, "AERTOS has not been started but you tried to publish something via PublishEvtFromISR. This is not allowed");
	
	// I need to get the AEEventDiscriminator_t from evt
	ThreeIntAndAEEvtBasePtr* publishArgs =
		ThreeIntAndAEEvtBasePtr::GetFromPool(0, 0xffff, 2, PoolManager->EventPoolsDisc[evt->EvtId][evt->poolId]);
	/*BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
	xQueueSendToBackFromISR(queueForSubAndPub, &publishArgs, 0);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);*/

	//I dont really need to go through the task GaurdTaskForSubAndPub because I am
	//already in a highest level task(the interrupt.) I can just run the publish from
	//here
	PublishEvt(publishArgs);
}

void AEPublishSubscribeManager::PublishEvtFromISR(AEEventDiscriminator_t * evt)
{
	
	AEAssertRuntime(AEAO::GetAERTOSStarted() == true, "AERTOS has not been started but you tried to publish something via PublishEvtFromISR. This is not allowed");

	// I need to get the AEEventDiscriminator_t from evt
	ThreeIntAndAEEvtBasePtr* publishArgs = ThreeIntAndAEEvtBasePtr::GetFromPool(0, 0xffff, 2, evt);
	/*BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
	xQueueSendToBackFromISR(queueForSubAndPub, &publishArgs, 0);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);*/

	//I dont really need to go through the task GaurdTaskForSubAndPub because I am
	//already in a highest level task(the interrupt.) I can just run the publish from
	//here
	PublishEvt(publishArgs);
}






void AEPublishSubscribeManager::_SubscribeToEvt(uint16_t evtId, uint16_t AOID)
{
	
	EventSubscribers[evtId][AOID] = true;
}

void AEPublishSubscribeManager::_UnSubscribeToEvt(uint16_t evtId, uint16_t AOID)
{
	EventSubscribers[evtId][AOID] = false;
}

bool AEPublishSubscribeManager::IsAOSubscribedToEvent(uint16_t AOID, uint16_t evtID) const
{
	return EventSubscribers[evtID][AOID];
}


void AEPublishSubscribeManager::PublishEvt(ThreeIntAndAEEvtBasePtr* AddingsubscriberArgs)
{

	AEAssertRuntime(AEAO::GetAERTOSStarted() == true, "AERTOS has not been started but you tried to publish something via PublishEvtFromISR. This is not allowed");
	
	//from that event, tell all subscribed AO to execute that the event by passing it the shared pointer event std::shared_ptr<AEEventBase>
	uint16_t numOfReferences = 0;
	uint16_t evtId = AddingsubscriberArgs->Arg4->GetEvtID();
	AEEventDiscriminator_t* evtBase = AddingsubscriberArgs->Arg4;

	/*create an event discriminator
	AEEventDiscriminator_t* discEvent = nullptr;
	if (evtBase == nullptr)
	{
		discEvent = PoolManager->EventPoolsDisc[evtId][evtBase->poolId];
	}
	else
	{
		AEEventDiscriminator_t discEventl(evtBase);
		discEvent = &discEventl;
	}
	*/
	//TODO: there is no need to go through EVERY AO because
	//only decision type AOs can subscribe to events. make it
	//so that decision AO are ID first or give them a seperate
	//decisionAO id that they will go off of. of course NUMOFACTIVEOBJECTS
	//will be NUMOF_DECISION_ACTIVEOBJECTS instead.
	//OR WHATA MIGHT Be BETTER
	// have an array that holds all subscribers IDs to a particular event.
	//and an int that holds how many subscribers are to a particular array.
	//uint16_t AOsSubscribed{2,5,6,4,1,0xffff,0xffff} int numOfSubscribed = 5
	//however this way would be difficult to actually remove a particular subscriber from the array.


	//if the AOID is 0xffff then this must be published from an ISR
	//so I will need to use the ISR version of this.
	if (AddingsubscriberArgs->Arg2 == 0xffff)
	{
		BaseType_t  xHigherPriorityTaskWoken = pdFALSE;

		for (int i = 0; i < NUMOFACTIVEOBJECTS; i++)
		{
			//if this subvscriber to this event is true 
			if (EventSubscribers[evtId][i] == true)
			{

				//if this is an aeevent, I need to incrmeent the refcounter
				if (evtBase->type == 1)
				{
					evtBase->evt->RefCounter++;
					numOfReferences++;
				} 

				//send the event to the AO evtQueue    
				xQueueSendToBackFromISR(AEAO::AllAO[i]->queueExecuteForEvt, &evtBase, &xHigherPriorityTaskWoken);
				//portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
		}



		//check that any subscribers were even there. if not then make the event reset
		if (numOfReferences == 0 && evtBase->type == 1)
		{
			evtBase->evt->Reset();
		}


		/* Actual macro used here is port specific. */
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);


	}
	else
	{
		for (int i = 0; i < NUMOFACTIVEOBJECTS; i++)
		{
			//if this subvscriber to this event is true 
			if (EventSubscribers[evtId][i] == true)
			{
				//if this is an aeevent, I need to incrmeent the refcounter
				if (evtBase->type == 1)
				{
					evtBase->evt->RefCounter++;
					numOfReferences++;
				}

				//send the event to the AO evtQueue  
				xQueueSendToBack(AEAO::AllAO[i]->queueExecuteForEvt, &evtBase, 0);

			}
		}

		//check that any subscribers were even there. if not then make the event reset
		if (numOfReferences == 0 && evtBase->type == 1)
		{
			evtBase->evt->Reset();
		}
	}


}

/*
void AEPublishSubscribeManager::GaurdTaskForPublishingEvt(void * pvParameters)
{

	AEEventBase* theEvent;

	AEPoolManager* poolmanager = AEPoolManager::getInstance();
	auto LambdaEvtSharedPointerReferencesZero = [poolmanager](AEEventBase*  x) {
		//when shared pointer reference goes to zero, tell the poolmanager to take that event off the "being used"

		poolmanager->SetEventNotInUse(x->GetEvtID(), x->poolId);
	};

	for (;;)
	{
		xQueueReceive(this->queuePublishEvt, &theEvent, portMAX_DELAY);


		//create a shared pointer to the event
		//std::shared_ptr<AEEventBase> shrdPointerToEvent(theEvent, LambdaEvtSharedPointerReferencesZero);
		//int t = shrdPointerToEvent.use_count();
		//std::shared_ptr<AEEventBase>* shrdPointerToEventPtr = &shrdPointerToEvent;
		//int yt = shrdPointerToEventPtr->use_count();



		xSemaphoreTake(MutexsForEvtSubsArray, portMAX_DELAY);

		//from that event, tell all subscribed AO to execute that the event by passing it the shared pointer event std::shared_ptr<AEEventBase>
		uint16_t numOfReferences = 0;
		for (int i = 0; i < NUMOFACTIVEOBJECTS; i++)
		{
			//if this subvscriber to this event is true
			if (EventSubscribers[theEvent->GetEvtID()][i] == true)
			{
				theEvent->RefCounter++;
				numOfReferences++;

				//send the event to the AO evtQueue
				xQueueSendToBack(AEAO::AllAO[i]->queueExecuteForEvt, &theEvent, 0);

			}
		}

		//check that any subscribers were even there. if not then make the event reset
		if (numOfReferences == 0)
		{
			theEvent->Reset();
		}


		xSemaphoreGive(MutexsForEvtSubsArray);
	}


}

*/