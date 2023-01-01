#pragma once


#include "AEAOUpdateableAAS.h"
#include "FreeRTOS.h"
#include "SPBDataSubscription.h"


//only imlement all this if configAE_USE_TDUs_AsService

#if configAE_USE_TDUs_AsService == 0

template<TemplateFor_AEAOUpdateableAAS>
class AETDUAsService : public AEAOUpdateableAAS<TemplateARGSFor_AEAOUpdateableAAS>
{

	Friend_ToALL_ActionRequestObjects

	TEMPLATEFORNoDefaults_AEClock
		friend class AEClock;

public:


	uint8_t ActionRequestIdThatIsCurrentlyActive;
	 

	AETDUAsService() : AEAOUpdateableAAS<TemplateARGSFor_AEAOUpdateableAAS>() {
		isSetToClock = false;
		isInitialized = false;
	};

	virtual void CheckIfConfiguredProperly() const override {
		//call base class function
		AEAOUpdateableAAS<TemplateARGSFor_AEAOUpdateableAAS>::CheckIfConfiguredProperly();

		//assert that this tdu is set to some clock
		configASSERT(this->isSetToClock == true);

		//assert that this tdu was intialized with the init() function
		configASSERT(this->isInitialized == true);
	}


	void Init(AEPriorities priorityOfThisTDU)
		//: AEAOUpdateableAAS<TemplateARGSFor_AEAOUpdateableAAS>()
	{
		this->_Priority = (uint8_t)priorityOfThisTDU;

                this->InitResource();
                
                //the tdus are able to wait for certain events to happen. Because of this, the this->queueExecuteForEvt will need to be created
		//so that the action requests can wait for the events they need to wait for. 
		this->queueExecuteForEvt = xQueueCreate(3, sizeof(AEEventDiscriminator_t*));
		//give the pointer of this queue to every action request.
		this->ActionReq1.BinarySemaphoreForEventListening_ptr = &this->BinarySemaphoreForEventListening;
		if (TypeChecker::IsAENullActionRequest<ActionRequest2>() == false)
		{ 
			this->ActionReq2.BinarySemaphoreForEventListening_ptr = &this->BinarySemaphoreForEventListening;
		}
		if (TypeChecker::IsAENullActionRequest<ActionRequest3>() == false)
		{ 
			this->ActionReq3.BinarySemaphoreForEventListening_ptr = &this->BinarySemaphoreForEventListening;
		}
                
                
		ActionRequestIdThatIsCurrentlyActive = 0;

		//set the request to serve next to zero meaning no requests are there to serve.
		this->TheRequestToServerNext.ActionFunctionId = 0;

		//create semaphores
		BinarySemaphoreForActionRequestExecuting = xSemaphoreCreateBinary();
		//initiallly since this no action request is exectuing, this semaphore should be given
		xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);

		BinarySemaphoreForEventListening = xSemaphoreCreateBinary();

		//create tasks
		AETDUAsService* pToThisClass = this;
		xTaskCreate([](void* p) {static_cast<AETDUAsService*>(p)->GaurdActionRequestExecution(nullptr); }, "GaurdActionRequestExecution", 300, pToThisClass, this->_Priority, &this->GaurdActionRequestExecutionTask);

		xTaskCreate([](void* p) {static_cast<AETDUAsService*>(p)->GaurdUpdate(nullptr); }, "GaurdUpdateTask", 300, pToThisClass, this->_Priority, &this->GaurdUpdateTask);

		xTaskCreate([](void* p) {static_cast<AETDUAsService*>(p)->GaurdTaskForEventListening(nullptr); }, "TaskForEventListening", 80, pToThisClass, this->_Priority, &this->TaskForEventListening);

		isInitialized = true;
	};


	//void SetUpdateToAnSPBsRefresh(float percentageOfDeltaRefresh, AESPBObservor* spbObservorToUpdateWith);



protected:

	bool isSetToClock;
	bool isInitialized;

	QueueClassForActionRequest* nextRequest;


	xSemaphoreHandle BinarySemaphoreForActionRequestExecuting;
	xSemaphoreHandle BinarySemaphoreForEventListening;
	TaskHandle_t TaskForEventListening;
	AEEventBase* LastEventListenedTo;


	void GaurdTaskForEventListening(void *pvParameters)
	{
		AEEventDiscriminator_t* evt;

		while (true)
		{
			// I wait for that specific event to happen that an actionrequest will specify. 
			//Remember that I can only subscribe to one event at a time so I only care about that one event.
			xQueueReceive((this->queueExecuteForEvt), &evt, portMAX_DELAY);

			if (this->ActionReq1.IsWaitingForEvent == true)
			{
				this->ActionReq1.EvtWaitingFor = evt;

				xSemaphoreGive(BinarySemaphoreForEventListening);
 
			} 
			else if (this->ActionReq2.IsWaitingForEvent == true)
			{
				this->ActionReq2.EvtWaitingFor = evt;

				xSemaphoreGive(BinarySemaphoreForEventListening); 
 
			}
			else if (this->ActionReq3.IsWaitingForEvent == true)
			{
				this->ActionReq3.EvtWaitingFor = evt;

				xSemaphoreGive(BinarySemaphoreForEventListening); 
 
			}
			else
			{
				//I need to clean up the event if no one used it.
				if (evt->type == 1)
				{
					evt->evt->DecrementRefCounter();
				}
			}
			  
		}

	}


	void GaurdActionRequestExecution(void *pvParameters)
	{

		while (true)
		{

			//in order to enter this, I need to be sure that the any current
			//running ActionRequest is finished.
			xSemaphoreTake(BinarySemaphoreForActionRequestExecuting, portMAX_DELAY);
			//take the counting semaphore to see if another request is in queue
			xSemaphoreTake(this->CountingSemaphoreForActionRequestExecutionTest, portMAX_DELAY);
			 
			//assert that this tdu is set to some clock
			configASSERT(this->isSetToClock == true);

			//get the request to serve next
			this->TheRequestToServerNext = *this->GetNextActionRequestToService();


			//run the ActionRequest
			switch (this->TheRequestToServerNext.ActionFunctionId)
			{
			case 1:
				//this will run the function that will set the parameters
				//that will prepare the actionRequest. 

				
				AE_UpdateALLSPBSubscriptions
				AE_UpdateALLWritableVariables
				this->isCurrentlyExecuting = true;
				this->ActionReq1.Request(this->TheRequestToServerNext.Argument_Id);
				this->isCurrentlyExecuting = false;
				//I need to now set the ActionRequestIdThatIsCurrentlyActive
				//to this request thus starting the request in the GaurdUpdate
				ActionRequestIdThatIsCurrentlyActive = 1;
				break;
			case 2:

				AE_UpdateALLSPBSubscriptions
				AE_UpdateALLWritableVariables

				this->isCurrentlyExecuting = true;
				this->ActionReq2.Request(this->TheRequestToServerNext.Argument_Id);
				this->isCurrentlyExecuting = false;
				ActionRequestIdThatIsCurrentlyActive = 2;
				break;
			case 3:

				AE_UpdateALLSPBSubscriptions
				AE_UpdateALLWritableVariables

				this->isCurrentlyExecuting = true;
				this->ActionReq3.Request(this->TheRequestToServerNext.Argument_Id);
				this->isCurrentlyExecuting = false;
				ActionRequestIdThatIsCurrentlyActive = 3;
				break;

			default:
                          //the TheRequestToServerNext had an ActionFunctionId that was not valid. something must have gone wrong when getting the next request
                          //up at this->TheRequestToServerNext = *this->GetNextActionRequestToService();
			configASSERT(false);
                        
				break;
			}



		}
	};




	void GaurdUpdate(void *pvParameters)
	{
		while (true)
		{
			//this will be triggered via a tasknotify
			ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
                        
                //clock for this tdu seems to have been too fast because it is trying to update before the last update finished.
		configASSERT(this->isCurrentlyExecuting == false);

			//update the proper ActionRequest object
			bool isCompleted;
			switch (ActionRequestIdThatIsCurrentlyActive)
			{
			case 1:
				AE_UpdateALLSPBSubscriptions
					AE_UpdateALLWritableVariables
					this->isCurrentlyExecuting = true;
				isCompleted = this->ActionReq1.Update();
				this->isCurrentlyExecuting = false;
				//if the action request is done, give the semaphore saying that it is done back
				if (isCompleted)
				{
					//since the request is done at this point, I can clean up
					this->ActionReq1.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
					xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
					//set the request to serve nextt id to zero to show no requests anymore
					ActionRequestIdThatIsCurrentlyActive = 0;
				} 
				

				break;
			case 2:
				AE_UpdateALLSPBSubscriptions
					AE_UpdateALLWritableVariables
					this->isCurrentlyExecuting = true;
				isCompleted = this->ActionReq2.Update();
				this->isCurrentlyExecuting = false;
				if (isCompleted)
				{
					this->ActionReq2.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
					xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
					ActionRequestIdThatIsCurrentlyActive = 0;
				}
				

				break;
			case 3:
				AE_UpdateALLSPBSubscriptions
					AE_UpdateALLWritableVariables
					this->isCurrentlyExecuting = true;
				isCompleted = this->ActionReq3.Update();
				this->isCurrentlyExecuting = false;
				if (isCompleted)
				{
					this->ActionReq3.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
					xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
					ActionRequestIdThatIsCurrentlyActive = 0;
				}
				

				break;

			default:
				break;
			}

		}
	}

};

#endif

/*
template<uint16_t POOLSIZE, class ActionRequest1, class ActionRequest2, class ActionRequest3>
inline void AETDUAsService<POOLSIZE, ActionRequest1, ActionRequest2, ActionRequest3>
::SetUpdateToAnSPBsRefresh(float percentageOfDeltaRefresh, AESPBObservor * spbObservorToUpdateWith)
{
	//over here
		//set tdus with some leeway to an SPBs refresh.. I need this leeway to make tdus
		//more deterministic in their refresh. 

	//first get the clock That I am set to
	//AEClock:: spbObservorToUpdateWith->GetClockIdImSourcedTo();


		//ultimately I will call SetTDUToClock() by getting the SPBs clock it is set to.

}
*/