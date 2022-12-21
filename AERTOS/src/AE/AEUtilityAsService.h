#pragma once

#include "AEAOResourceAsService.h"


#if configAE_USE_U_AsService == 1

template<TemplateFor_RAsAService>
class AEUtilityAsService : public  AEAOResourceAsService<TemplateARGSFor_RAsAService>
{

	Friend_ToALL_ActionRequestObjects

public:
	AEUtilityAsService()
		:AEAOResourceAsService<TemplateARGSFor_RAsAService>()
	{
          
                this->InitResource();
          
		//create tasks
		AEUtilityAsService* pToThisClass = this;
		xTaskCreate([](void* p) {static_cast<AEUtilityAsService*>(p)->GaurdActionRequestExecution(nullptr); }, "GaurdActionRequestExecution", 400, pToThisClass, AOPRIORITYMEDIUM, &this->GaurdActionRequestExecutionTask);

	};


protected:


	

	void GaurdActionRequestExecution(void *pvParameters)
	{

		while (true)
		{
			//take the counting semaphore
			xSemaphoreTake(this->CountingSemaphoreForActionRequestExecutionTest, portMAX_DELAY);
			
			
			//get the request to serve next
			this->TheRequestToServerNext = *this->GetNextActionRequestToService();
			 
			//run the ActionRequest
			switch (this->TheRequestToServerNext.ActionFunctionId)
			{
			case 1:
				AE_UpdateALLSPBSubscriptions
					AE_UpdateALLWritableVariables
					this->isCurrentlyExecuting = true;
				this->ActionReq1.Request(this->TheRequestToServerNext.Argument_Id);
				this->isCurrentlyExecuting = false;
				//since the request is done at this point, I can clean up
				this->ActionReq1.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
				break;
			case 2:
				AE_UpdateALLSPBSubscriptions
					AE_UpdateALLWritableVariables
					this->isCurrentlyExecuting = true;
				this->ActionReq2.Request(this->TheRequestToServerNext.Argument_Id);
				this->isCurrentlyExecuting = false;
				this->ActionReq2.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
				break;
			case 3:
				AE_UpdateALLSPBSubscriptions
					AE_UpdateALLWritableVariables
					this->isCurrentlyExecuting = true;
				this->ActionReq3.Request(this->TheRequestToServerNext.Argument_Id);
				this->isCurrentlyExecuting = false;
				this->ActionReq3.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
				break;

			default:
				break;
			}


		}
	}; 

};





#include "AEAOUpdateableAAS.h"

template<TemplateFor_Service>//template<TemplateFor_RAsAService>
class AEService : public AEAOUpdateable<TemplateARGSFor_Service> //: public  AEAOResourceAsService<TemplateARGSFor_RAsAService>
	{

		Friend_ToALL_ActionRequestObjects
			
		TEMPLATEFORNoDefaults_AEClock
		friend class AEClock;

		public:
		
		
		 
		uint8_t ActionRequestIdThatIsCurrentlyActive;
		
			AEService()
				: AEAOUpdateable<TemplateARGSFor_Service>()
		{
          
			this->InitResource();
          
			//create tasks
			AEService* pToThisClass = this;
			xTaskCreate([](void* p) {static_cast<AEService*>(p)->GaurdActionRequestExecution(nullptr); }, "GaurdActionRequestExecution", 400, pToThisClass, AOPRIORITYMEDIUM, &this->GaurdActionRequestExecutionTask);

			
			//tdu stuff
			isSetToClock = false;
			isInitialized = false;
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
			
			if (TypeChecker::IsAENullActionRequest<ActionRequest4>() == false)
			{ 
				this->ActionReq4.BinarySemaphoreForEventListening_ptr = &this->BinarySemaphoreForEventListening;
			}
			
			if (TypeChecker::IsAENullActionRequest<ActionRequest5>() == false)
			{ 
				this->ActionReq5.BinarySemaphoreForEventListening_ptr = &this->BinarySemaphoreForEventListening;
			}
			if (TypeChecker::IsAENullActionRequest<ActionRequest6>() == false)
			{ 
				this->ActionReq6.BinarySemaphoreForEventListening_ptr = &this->BinarySemaphoreForEventListening;
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
			AEService* pToThisClass = this;
			xTaskCreate([](void* p) {static_cast<AEService*>(p)->GaurdActionRequestExecution(nullptr); }, "GaurdActionRequestExecution", 300, pToThisClass, this->_Priority, &this->GaurdActionRequestExecutionTask);

			xTaskCreate([](void* p) {static_cast<AEService*>(p)->GaurdUpdate(nullptr); }, "GaurdUpdateTask", 300, pToThisClass, this->_Priority, &this->GaurdUpdateTask);

			xTaskCreate([](void* p) {static_cast<AEService*>(p)->GaurdTaskForEventListening(nullptr); }, "TaskForEventListening", 80, pToThisClass, this->_Priority, &this->TaskForEventListening);

			isInitialized = true;
		} 
		
		
		virtual void CheckIfConfiguredProperly() const override {
			//call base class function
			AEAOUpdateable<TemplateARGSFor_Service>::CheckIfConfiguredProperly();

			//assert that this tdu is set to some clock
			//configASSERT(this->isSetToClock == true);

			//assert that this tdu was intialized with the init() function
			configASSERT(this->isInitialized == true);
		}


	protected:


	
		//tdu stuff --------------------------
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

				if (this->ActionReq4.IsWaitingForEvent == true)
				{
					this->ActionReq4.EvtWaitingFor = evt;

					xSemaphoreGive(BinarySemaphoreForEventListening);
 
				} 
				else if (this->ActionReq5.IsWaitingForEvent == true)
				{
					this->ActionReq5.EvtWaitingFor = evt;

					xSemaphoreGive(BinarySemaphoreForEventListening); 
 
				}
				else if (this->ActionReq6.IsWaitingForEvent == true)
				{
					this->ActionReq6.EvtWaitingFor = evt;

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
				case 4:
					AE_UpdateALLSPBSubscriptions
						AE_UpdateALLWritableVariables
						this->isCurrentlyExecuting = true;
					isCompleted = this->ActionReq4.Update(this->TheRequestToServerNext.Argument_Id);
					this->isCurrentlyExecuting = false;
					//if the action request is done, give the semaphore saying that it is done back
					if (isCompleted)
					{
						//since the request is done at this point, I can clean up
						this->ActionReq4.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
						xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
						//set the request to serve nextt id to zero to show no requests anymore
						ActionRequestIdThatIsCurrentlyActive = 0;
					} 
				

					break;
				case 5:
					AE_UpdateALLSPBSubscriptions
						AE_UpdateALLWritableVariables
						this->isCurrentlyExecuting = true;
					isCompleted = this->ActionReq5.Update(this->TheRequestToServerNext.Argument_Id);
					this->isCurrentlyExecuting = false;
					if (isCompleted)
					{
						this->ActionReq5.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
						xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
						ActionRequestIdThatIsCurrentlyActive = 0;
					}
				

					break;
				case 6:
					AE_UpdateALLSPBSubscriptions
						AE_UpdateALLWritableVariables
						this->isCurrentlyExecuting = true;
					isCompleted = this->ActionReq6.Update(this->TheRequestToServerNext.Argument_Id);
					this->isCurrentlyExecuting = false;
					if (isCompleted)
					{
						this->ActionReq6.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
						xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
						ActionRequestIdThatIsCurrentlyActive = 0;
					}
				

					break;

				default:
					break;
				}

			}
		}
		
		//----------------------------------------------------

		void GaurdActionRequestExecution(void *pvParameters)
		{

			while (true)
			{
				
				//in order to enter this, I need to be sure that the any current
				//running ActionRequest is finished.
				xSemaphoreTake(BinarySemaphoreForActionRequestExecuting, portMAX_DELAY);
				
				//take the counting semaphore
				xSemaphoreTake(this->CountingSemaphoreForActionRequestExecutionTest, portMAX_DELAY);
			
			
				//get the request to serve next
				this->TheRequestToServerNext = *this->GetNextActionRequestToService();
			 
				//run the ActionRequest
				switch (this->TheRequestToServerNext.ActionFunctionId)
				{
				case 1:
					AE_UpdateALLSPBSubscriptions
						AE_UpdateALLWritableVariables
						this->isCurrentlyExecuting = true;
					this->ActionReq1.Request(this->TheRequestToServerNext.Argument_Id);
					this->isCurrentlyExecuting = false;
					//since the request is done at this point, I can clean up
					this->ActionReq1.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
					//this is a simple service request that will be done in one call. So I can return the BinarySemaphoreForActionRequestExecuting right away
					xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
					
					break;
				case 2:
					AE_UpdateALLSPBSubscriptions
						AE_UpdateALLWritableVariables
						this->isCurrentlyExecuting = true;
					this->ActionReq2.Request(this->TheRequestToServerNext.Argument_Id);
					this->isCurrentlyExecuting = false;
					this->ActionReq2.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
					//this is a simple service request that will be done in one call. So I can return the BinarySemaphoreForActionRequestExecuting right away
					xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
					
					break;
				case 3:
					AE_UpdateALLSPBSubscriptions
						AE_UpdateALLWritableVariables
						this->isCurrentlyExecuting = true;
					this->ActionReq3.Request(this->TheRequestToServerNext.Argument_Id);
					this->isCurrentlyExecuting = false;
					this->ActionReq3.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
					//this is a simple service request that will be done in one call. So I can return the BinarySemaphoreForActionRequestExecuting right away
					xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
					
					break;
					
					
					//TDU stuff ---------------------------------------------------------
				case 4:
					//this will run the function that will set the parameters
					//that will prepare the actionRequest. 

				
					AE_UpdateALLSPBSubscriptions
					AE_UpdateALLWritableVariables
					this->isCurrentlyExecuting = true;
					this->ActionReq4.Request(this->TheRequestToServerNext.Argument_Id);
					this->isCurrentlyExecuting = false;
					//I need to now set the ActionRequestIdThatIsCurrentlyActive
					//to this request thus starting the request in the GaurdUpdate
					ActionRequestIdThatIsCurrentlyActive = 4;
					break;
				case 5:

					AE_UpdateALLSPBSubscriptions
					AE_UpdateALLWritableVariables

					this->isCurrentlyExecuting = true;
					this->ActionReq5.Request(this->TheRequestToServerNext.Argument_Id);
					this->isCurrentlyExecuting = false;
					ActionRequestIdThatIsCurrentlyActive = 5;
					break;
				case 6:

					AE_UpdateALLSPBSubscriptions
					AE_UpdateALLWritableVariables

					this->isCurrentlyExecuting = true;
					this->ActionReq6.Request(this->TheRequestToServerNext.Argument_Id);
					this->isCurrentlyExecuting = false;
					ActionRequestIdThatIsCurrentlyActive = 6;
					break;
					

				default:
					break;
				}


			}
		}
		; 

	};


#endif