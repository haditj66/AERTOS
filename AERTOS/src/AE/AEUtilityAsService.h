#pragma once

#include "AEAOResourceAsService.h"


#if configAE_USE_U_AsService == 1
//
//template<TemplateFor_RAsAService>
//class AEUtilityAsService : public  AEAOResourceAsService<TemplateARGSFor_RAsAService>
//{
//
//	Friend_ToALL_ActionRequestObjects
//
//public:
//	AEUtilityAsService()
//		:AEAOResourceAsService<TemplateARGSFor_RAsAService>()
//	{
//          
//                this->InitResource();
//          
//		//create tasks
//		AEUtilityAsService* pToThisClass = this;
//		xTaskCreate([](void* p) {static_cast<AEUtilityAsService*>(p)->GaurdActionRequestExecution(nullptr); }, "GaurdActionRequestExecution", 400, pToThisClass, AOPRIORITYMEDIUM, &this->GaurdActionRequestExecutionTask);
//
//	};
//
//
//protected:
//
//
//	
//
//	void GaurdActionRequestExecution(void *pvParameters)
//	{
//
//		while (true)
//		{
//			//take the counting semaphore
//			xSemaphoreTake(this->CountingSemaphoreForActionRequestExecutionTest, portMAX_DELAY);
//			
//			
//			//get the request to serve next
//			this->TheRequestToServerNext = *this->GetNextActionRequestToService();
//			 
//			//run the ActionRequest
//			switch (this->TheRequestToServerNext.ActionFunctionId)
//			{
//			case 1:
//				AE_UpdateALLSPBSubscriptions
//					AE_UpdateALLWritableVariables
//					this->isCurrentlyExecuting = true;
//				this->ActionReq1.Request(this->TheRequestToServerNext.Argument_Id);
//				this->isCurrentlyExecuting = false;
//				//since the request is done at this point, I can clean up
//				this->ActionReq1.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
//				break;
//			case 2:
//				AE_UpdateALLSPBSubscriptions
//					AE_UpdateALLWritableVariables
//					this->isCurrentlyExecuting = true;
//				this->ActionReq2.Request(this->TheRequestToServerNext.Argument_Id);
//				this->isCurrentlyExecuting = false;
//				this->ActionReq2.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
//				break;
//			case 3:
//				AE_UpdateALLSPBSubscriptions
//					AE_UpdateALLWritableVariables
//					this->isCurrentlyExecuting = true;
//				this->ActionReq3.Request(this->TheRequestToServerNext.Argument_Id);
//				this->isCurrentlyExecuting = false;
//				this->ActionReq3.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
//				break;
//
//			default:
//				break;
//			}
//
//
//		}
//	}; 
//
//};





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

		xTaskCreate([](void* p) {static_cast<AEService*>(p)->GaurdUpdate(nullptr); }, "GaurdUpdateTask", 800, pToThisClass, this->_Priority, &this->GaurdUpdateTask);

		xTaskCreate([](void* p) {static_cast<AEService*>(p)->GaurdTaskForEventListening(nullptr); }, "TaskForEventListening", 80, pToThisClass, this->_Priority, &this->TaskForEventListening);

		isInitialized = true;
	} 
		
	
	bool ServicesCurrentlyExecutingOrInQueue()
	{ 
		if (ServicesCurrentlyExecuting())
		{
			return true;
		} 
		if (ServicesInQueue() == true)
		{
			return true;
		} 
		
		return false;
	}
	
	bool ServicesCurrentlyExecuting()
	{ 
		if (ActionRequestIdThatIsCurrentlyActive > 0)
		{
			return true;
		}
		return false;
	}
	
	bool ServicesInQueue()
	{ 
		//check if queue is empty
		for (uint16_t i = 0; i < NUMOFACTIVEOBJECTS; i++)
		{
			if (this->QueueForAOArgs[i].isEmpty() == false)
			{
				return true;
			}
		}
		return false; 
	}
		
	virtual void CheckIfConfiguredProperly() const override {
		//call base class function
		AEAOUpdateable<TemplateARGSFor_Service>::CheckIfConfiguredProperly();

		//assert that this tdu is set to some clock
		//configASSERT(this->isSetToClock == true);

		//assert that this tdu was intialized with the init() function
		configASSERT(this->isInitialized == true);
	}


	void CancelCurrentRequest() { 
		//only cancel if there is a currently running request.
		if (ActionRequestIdThatIsCurrentlyActive != 0)
		{
			cancelCurrentRequest = true;
		}
	}
	;
	void CancelAllRequests() { 
		//empty the counting semaphore right away to not allow any more requests to get pushed
		//as a current request.
		//empty the request cicular buffer now that i am sure no other requests will be popped
		//while i am trying to pop them here (if i didnt empty the counting semaphore from 
		//before, this would not have veen thread safe.).
		xQueueReset(this->CountingSemaphoreForActionRequestExecutionTest);
		 
		for (size_t i = 0; i < NUMOFACTIVEOBJECTS; i++)
		{
			this->QueueForAOArgs[i].Clear();  
		}
			
		

		//now cancel any currently running request.
		CancelCurrentRequest();
	}
	;
		
		
protected:


	
	//tdu stuff --------------------------
	bool isSetToClock;
	bool isInitialized;
	bool cancelCurrentRequest;

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
			AEAssertRuntime(this->isCurrentlyExecuting == false, "clock for this tdu seems to have been too fast because it is trying to update before the last update finished.");

			//I need to do the following if this TDU is set to a SPB
			if (this->IsSetToAnSPBRefresh)
			{
				//update the proper ActionRequest object
				bool isCompleted;
				
				//this is done because frequency of the spb is not set until after configuration. This function is called only once
				if (this->OnFirstupdate == true)
				{
					this->SetFrequencyIUpdateAt(this->spbIFlowTo->GetFrequencyIRefreshAt());
					
					this->OnFirstupdate = false;
				}
				
				

				//RETIRE THIS
				//					this->IndexUpdateClockCount++;
				//					if (this->IndexUpdateClockCount >= this->UpdateClockCount)
				//					{
				//						//if this was the first time that this tdu is
				//						//updating, than go ahead and subtract the extraticks from the
				//						//UpdateClockCount so to match the spb frequency this tdu is set to. 
				//						if (this->OnFirstupdate)
				//						{
				//							this->UpdateClockCount -= this->ExtraTicks;
				//							this->OnFirstupdate = false;
				//						}

				switch (ActionRequestIdThatIsCurrentlyActive)
				{
				case 4:
					//if a cancelation has been given, then cancel this and break
					if (_CancelRer(this->ActionReq4) == true) 
					{ 
						break;
					} 

					this->SPBIamSetToHasbeenRefreshed = false;
					this->IndexUpdateClockCount = 0;

					//copy the input of the spb into this local input 
					memcpy(this->LinkedSPBData, this->ReferenceOfLinkedSPBOutput, this->LinkedSPBOutPutSize * sizeof(float));
							
							
					_RunTDU(this->ActionReq4);
							
 
					break;
				case 5:
					//if a cancelation has been given, then cancel this and break
					if (_CancelRer(this->ActionReq5) == true) 
					{ 
						break;
					} 

					//copy the input of the spb into this local input 
					memcpy(this->LinkedSPBData, this->ReferenceOfLinkedSPBOutput, this->LinkedSPBOutPutSize * sizeof(float));

					_RunTDU(this->ActionReq5);
							  
					break;
				case 6:
					//if a cancelation has been given, then cancel this and break
					if (_CancelRer(this->ActionReq6) == true) 
					{ 
						break;
					} 

					//copy the input of the spb into this local input 
					memcpy(this->LinkedSPBData, this->ReferenceOfLinkedSPBOutput, this->LinkedSPBOutPutSize * sizeof(float));

							
					_RunTDU(this->ActionReq6);
							 
					break;

				default:
					break;

				}
				//}
			}
			//update the proper ActionRequest object
			else
			{
				bool isCompleted;
				switch (ActionRequestIdThatIsCurrentlyActive)
				{
				case 4:
					//if a cancelation has been given, then cancel this and break
					if (_CancelRer(this->ActionReq4) == true) 
					{ 
						break;
					} 
					
					_RunTDU(this->ActionReq4);
					 

					break;
				case 5:
					
					//if a cancelation has been given, then cancel this and break 
					if (_CancelRer(this->ActionReq5) == true) 
					{ 
						break;
					} 
					
					_RunTDU(this->ActionReq5);
  
					break;
				case 6:
					
					//if a cancelation has been given, then cancel this and break 
					if (_CancelRer(this->ActionReq6) == true) 
					{ 
						break;
					} 
						
					_RunTDU(this->ActionReq6);
					  
					break;

				default:
					break;
				}

			}
		}
			
	}
		
		
	template<class TActionReq>
		bool _CancelRer(TActionReq actionreq)
		{
			if (cancelCurrentRequest == true)
			{
				cancelCurrentRequest = false;
				//call the requests cancelation function and clean up
				actionreq.CancelCleanUp();
				actionreq.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
				xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
				ActionRequestIdThatIsCurrentlyActive = 0;
				//break;
				return true;
			}
			return false;
		}		
		
		
	template<class TActionReq>
		void _RunTDU(TActionReq actionreq)
		{
			AE_UpdateALLSPBSubscriptions
			AE_UpdateALLWritableVariables
			this->isCurrentlyExecuting = true;
			bool isCompleted =  actionreq.Update(this->TheRequestToServerNext.Argument_Id);
			this->isCurrentlyExecuting = false;
			//if the action request is done, give the semaphore saying that it is done back
			if (isCompleted)
			{
				//since the request is done at this point, I can clean up
				actionreq.ActionRequestComplete(this->TheRequestToServerNext.Argument_Id);
				xSemaphoreGive(BinarySemaphoreForActionRequestExecuting);
				//set the request to serve nextt id to zero to show no requests anymore
				ActionRequestIdThatIsCurrentlyActive = 0;
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
			if (this->IsExclusivelyPossessed == true)
			{
				//TODO: this is going to be changed later where it will iterate though the QueueForAOArgs[i]. read the note where 
				//QueueForAOArgs is declared
				this->TheRequestToServerNext = *this->QueueForAOArgs[this->PossessingAO->GetAO_ID()].Peek();
				this->QueueForAOArgs[this->PossessingAO->GetAO_ID()].Pop();
			}
			else
			{
				this->TheRequestToServerNext = *this->GetNextActionRequestToService();	
			}
				
				
			 
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