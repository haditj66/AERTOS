
#include "AEObservorInterpretorBase.h"
#include "AELinkDeterministic.h"




AEObservorInterpretorBase* AEObservorBase::InterpretorBasePool[MAXNUMOFINTERPRETORS];
uint16_t AEObservorBase::NumOfInterpretorsCreatedSoFar = 0;
uint16_t AEObservorBase::MappingIndex[MAXNUMOFOBSERVORS];


//todo: maybe get these working, but probably I wont need them
AEObservorInterpretorBase * AEObservorInterpretorBase::GetInterpretor(uint16_t observorID)
{
	return InterpretorBasePool[observorID - MappingIndex[observorID]];
}

void AEObservorInterpretorBase::Init()
{

	//map the Ids of this class to the ids of the base class
	for (int i = 0; i < MAXNUMOFOBSERVORS; i++)
	{ 
		//find the difference between the observor id and the count i 
		//MappingIndex[InterpretorBasePool[i]->ObservorId] =  InterpretorBasePool[i]->ObservorId - i;
	}
	
}



AEObservorInterpretorBase::AEObservorInterpretorBase()
{
	DoINeedARefresh = false;
	EOC_RefreshedWhileInSession = false; 
	
	InterpretorBasePool[NumOfInterpretorsCreatedSoFar] = this;
	InterpretorId = NumOfInterpretorsCreatedSoFar;
	NumOfInterpretorsCreatedSoFar++;

	//create the event group
	for (int i = 0; i < NUMBEROFMUTEXS; i++)
	{
		MutexHandles[i] = xSemaphoreCreateMutex();
		
		//take all mutexs to start
		//xSemaphoreTake(MutexHandles[i], portMAX_DELAY); 
	}
	
}

uint32_t AEObservorInterpretorBase::GetSizeOfChannel1()
{
	return SizeOfChannel1;
}


uint32_t AEObservorInterpretorBase::GetSizeOfChannel2()
{
	return SizeOfChannel2;
}

uint32_t AEObservorInterpretorBase::GetSizeOfChannel3()
{
	return SizeOfChannel3;
}



void AEObservorInterpretorBase::IncrementCurrentSession()
{
	//range is from 0 to 15
	CurrentSession = CurrentSession != (NUMBEROFMUTEXS-1) ? (CurrentSession + 1) : 0;
}

uint8_t AEObservorInterpretorBase::GetSessionThisManyBeforeCurrent(uint8_t thisManyBeforeCurrentSession) const
{
	if ((CurrentSession - thisManyBeforeCurrentSession) >= 0)
	{
		return (CurrentSession - thisManyBeforeCurrentSession);
	}
	else
	{
		return (NUMBEROFMUTEXS + ((CurrentSession - thisManyBeforeCurrentSession)));
	}
}



//should be called with other observors
void  AEObservorInterpretorBase::UpdateObservationIfNeeded(SemaphoreHandle_t*&  MutexHandleForObservorsToWaitFor)
{


	//local currentsession to make sure it is not changed while within this funcion
	uint8_t session = CurrentSession;

	if (AlreadyInSession)
	{

		MutexHandleForObservorsToWaitFor = &(this->MutexHandles[session]);
		return;
		//xEventGroupWaitBits(EventGroupHandle, (0x1 << currentSessionL), pdFALSE, pdTRUE, portMAX_DELAY); 
	}
	else if (DoINeedARefresh == false)
	{
		//if it doesnt even need a refresh, then just return nullptr
		MutexHandleForObservorsToWaitFor = nullptr;
		return;
	}

	//NO LONGER VALID
	//if This observor pointed to some deterministic interpretors, Then I would need to call Updates on those to make sure
	// they had not gone stale. however, if it has no interpretor that it depends on and if HasThereBeenARefreshOAnyDeterministicObservors
	//is false, then there would be nothing to check and I can be sure that HasThereBeenARefreshOAnyDeterministicObservors == false
	//is in fact false.
	//else if(HasThereBeenARefreshOAnyDeterministicObservors == false && numOfDeterministicLinksIPointThatAreInterpretors == 0)
	//{
		//EventGroupHandleForObservorsToWaitFor = nullptr;
		//return;
	//}
	else
	{// if it is not in a session then go ahead and start a new session and wait for an incremented currentsession 
		xTaskNotify(GaurdTaskToObjectExecutionHandle, session, eSetValueWithOverwrite);
		MutexHandleForObservorsToWaitFor = &(this->MutexHandles[session]);
		return;
		//xEventGroupWaitBits(EventGroupHandle, (0x1 << currentSessionL), pdFALSE, pdTRUE, portMAX_DELAY);


		 //Set the notification value of the task referenced by xTask4Handle to 0xfff,
		//but only if to do so would not overwrite the task's existing notification
		//value before the task had obtained it (by a call to xTaskNotifyWait()
		//or ulTaskNotifyTake()). 
		//if (xTaskNotify(RefreshObservationGaurdTask, currentSessionL, ); == pdPASS)

	}
}





void AEObservorInterpretorBase::AddDeterministicLink(AEObservorBase * toObservor)
{

	uint8_t linkId = AELinkDeterministic::InitializeLinkFromPool(this, toObservor);

	this->MyDeterministicLinksIPoint[this->numOfDeterministicLinksIPoint] = linkId;
	this->numOfDeterministicLinksIPoint++;

	toObservor->MyDeterministicLinksPointingToMe[toObservor->numOfDeterministicLinksPointToMe] = linkId;
	toObservor->numOfDeterministicLinksPointToMe += 1;


	//start moving away from links and just embed the information i need directly.
	//
	//toObservor->IDsOfDeterministicObservorsPointingToMe[toObservor->numOfDeterministicObservorsPointToMe] 	= this->ObservorId;
	toObservor->DeterministicObservorsPointingToMe[toObservor->numOfDeterministicObservorsPointToMe] = this;
	toObservor->numOfDeterministicObservorsPointToMe++;

	
}



void AEObservorInterpretorBase::UpdateObservationIfNeededForClock()
{

	//only do something if this observor is on. this is only for a clock update though
	if (this->isObservorOn)
	{

		//local currentsession to make sure it is not changed while within this funcion
		uint8_t currentSessionL = CurrentSession;


		//
		if (AlreadyInSession)
		{
			CLockSession = currentSessionL;
			UpdatedSinceClockTick = false;


			//xEventGroupWaitBits(EventGroupHandle, (0x1 << currentSessionL), pdFALSE, pdTRUE, portMAX_DELAY);


		}
		else
		{// if it is not in a session then go ahead and start a new session and wait for an incremented currentsession
			CLockSession = currentSessionL;
			UpdatedSinceClockTick = false;

			xTaskNotify(GaurdTaskToObjectExecutionHandle, currentSessionL, eSetValueWithOverwrite);
		}
	}
} 

#include <iostream>
#include <ctime> 
#include <chrono>

void AEObservorInterpretorBase::RefreshObservationGaurd(void * pvParameters)
{
	//initialize all mutexes to taken by this task (has to be this task as this is the task to give those mustexs back)
	for (int i = 0; i < NUMBEROFMUTEXS; i++)
	{ 
		//take all mutexs to start
		xSemaphoreTake(MutexHandles[i], portMAX_DELAY);
	}


	uint32_t ulNotifiedValueCurrentSession;
	while (true)
	{
		xTaskNotifyWait(pdFALSE, pdTRUE, &ulNotifiedValueCurrentSession, portMAX_DELAY);


		//timer section 1 the whole thing is 1000000
		//std::chrono::high_resolution_clock::time_point bbt1;
		//std::chrono::high_resolution_clock::time_point bbt2;
                


		//bbt1 = std::chrono::high_resolution_clock::now();
        //StartTimer(1)


		//I can only continue if the ulNotifiedValueCurrentSession is the same as the currentsession that I should be on.
		//if it is not the same than it must be from a task that came in after I changed Alreadysession to false but before I incremented
		//current session. not to worry though as there is a local current session in ggetobservation that should stop any AO current session 
		//from exceeding the actual currentsession.
		if (ulNotifiedValueCurrentSession == CurrentSession)
		{
			AlreadyInSession = true;


			//timer section 2 ------------ 9000
			
			//call UpdateObservationIfNeeded() on all Interpretor observations I link TO that I am deterministic on 
			//iF an interpretor it is linked to does not need a refresh, it will simply return a null_ptr for the eventhandle to wait for.
			uint16_t numOfObservorsUpdateWasCalledOn = 0;
			for (int i = 0; i < numOfDeterministicLinksIPoint; i++)
			{
				if (AELinkDeterministic::Links[MyDeterministicLinksIPoint[i]].LinkPointsToObservorOfType & ObservorType::Interpretors)
				{
					//it shouldnt matter if this thing was on a clock as it still may need an update!
					//think about if the observor I am determined by had a long clock of 5 sec, meanwhile,
					//one of That observors determined by observors had updated since then!

					//if (AELinkDeterministic::Links[MyDeterministicLinksIPoint[i]].GetTheInterpretorObservorIPointTo()->SetToClock == false)
					//{ 

					
					 

					AELinkDeterministic::Links[MyDeterministicLinksIPoint[i]]
						.GetTheInterpretorObservorIPointTo()
						->UpdateObservationIfNeeded(MutexForObservorsToWaitFor[numOfObservorsUpdateWasCalledOn]);
					numOfObservorsUpdateWasCalledOn++;


					//}
				}
			}
			
			//timer section 2 END ------------

			//timer section 2 900000 ------------
 			//now that every observation has had an update called on, wait for each one to finish. this is my way of waiting on all
			//of them concurrently.
			

			for (uint16_t i = 0; i < numOfObservorsUpdateWasCalledOn; i++)
			{
				if (MutexForObservorsToWaitFor[i] != nullptr)
				{
					//peek at the mutex
					xSemaphoreTake(*MutexForObservorsToWaitFor[i], portMAX_DELAY); 
					xSemaphoreGive(*MutexForObservorsToWaitFor[i]);
				
					//xQueuePeek(*MutexForObservorsToWaitFor[i], NULL, portMAX_DELAY);
				}
			}
		

			//timer section 3 END ------------ 
			
			//get and create a copy of all determined values
			CopyDeterminedValues();

			//now calculate a refresh
			Refresh();
			//update the observation-To-Read with the observationToRefresh.
			SwapObservationToReadWithTheOneToRefresh();
			//change this observors HasThereBeenARefreshOAnyDeterministicObservors to false as it has just refreshed and now all 
			//observors it depends on should be considered not refreshed yet.
			//HasThereBeenARefreshOAnyDeterministicObservors = false;

			if (EOC_RefreshedWhileInSession == false)
			{
				DoINeedARefresh = false;
			}
			else
			{
				EOC_RefreshedWhileInSession = false;
			}


			//not needed anymore
			//tell all observors That point to me that I have refreshed. because I have refreshed, I am 
			//assuming the value must now be different than the last. (99% of the time this will be true)
			//for (int i = 0; i < numOfDeterministicLinksPointToMe; i++)
			//{
				//AELinkDeterministic::Links[MyDeterministicLinksPointingToMe[i]].GetTheObservorIPointFrom()->HasThereBeenARefreshOAnyDeterministicObservors = true;
				//MyDeterministicLinksPointingToMe[i]->GetTheObservorIPointFrom()->HasThereBeenARefreshOAnyDeterministicObservors = true;
			//}


			//auto bits = xEventGroupGetBits(EventGroupHandle);
			//set sessions that were THREE before this session to off
			xSemaphoreTake(MutexHandles[GetSessionThisManyBeforeCurrent(3)], 0);
			//auto bits1 = xEventGroupGetBits(EventGroupHandle);
			 
			xSemaphoreGive(MutexHandles[CurrentSession]);

			//auto bits2 = xEventGroupGetBits(EventGroupHandle);

			AlreadyInSession = false;
			UpdatedSinceClockTick = true;
			IncrementCurrentSession();
			//timer section 1 the whole thing is 1000000 END ----------------
			//bbt2 = std::chrono::high_resolution_clock::now();

            //StopTimer(1)
             //PrintTimerDuration(1)

			//uint32_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(bbt2 - bbt1).count();
			//AEPrint("\nduration of the session::::::: %d\n", duration);
		//not needed anymore	
		/*
		}
		else
		{

			//set sessions that were THREE before this session to off
			xEventGroupClearBits(EventGroupHandle, 0x1 << GetSessionThisManyBeforeCurrent(3));

			xEventGroupSetBits(EventGroupHandle, 0x1 << (CurrentSession));

			AlreadyInSession = false;
			UpdatedSinceClockTick = true;
			IncrementCurrentSession();

		}
		*/

		}
	}


}

