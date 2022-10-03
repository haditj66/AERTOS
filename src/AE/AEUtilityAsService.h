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

#endif