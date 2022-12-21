#pragma once 
#include "FreeRTOS.h"
#include "semphr.h"

#include <cstdint>
#include "AEAO.h"

#include "ActionRequestObjectArg.h"
#include "AECircularBuffer.h"




//typedef void(*funcPtr)(uint16_t);

//if there are no DDSMs, TDUs, or U being used as a service, than this should not be
//implemented.
static uint32_t blabdlasjbdl = 89;

#if ((configAE_USE_TDUs_AsService == 1)  || (configAE_USE_U_AsService == 1) || (configAE_USE_DDSM_AsService == 1))

template<TemplateFor_RAsAService>
class AEAOResourceAsService : public AEAO
{

	Friend_ToALL_ActionRequestObjects

public:

	virtual void CheckIfConfiguredProperly() const override {
		//assert all I need to assert here.
	}

	DeclareActionRequestTemplateArgs

		DeclareUtilityRequestFunctions

		//HardwarePeripheralUsed* HardwarePeripheralToUse;

	template<class TActionRequestToRun>
	Action1_RETURNTYPE_t WaitForRequestToFinish1(Token* tokenOfRequest) {
		if (false)
		{
			TActionRequestToRun* dummyVar = static_cast<ActionRequest1*>(&ActionReq1);
		}

		return ActionReq1.WaitForRequestToFinish(tokenOfRequest);
	};
	template<class TActionRequestToRun>
	Action2_RETURNTYPE_t WaitForRequestToFinish2(Token* tokenOfRequest) {
		if (false)
		{
			TActionRequestToRun* dummyVar = static_cast<ActionRequest2*>(&ActionReq2);
		}

		return ActionReq2.WaitForRequestToFinish(tokenOfRequest);
	};
	template<class TActionRequestToRun>
	Action3_RETURNTYPE_t WaitForRequestToFinish3(Token* tokenOfRequest) {
		if (false)
		{
			TActionRequestToRun* dummyVar = static_cast<ActionRequest3*>(&ActionReq3);
		}

		return ActionReq3.WaitForRequestToFinish(tokenOfRequest);
	};


protected:


	void* InitializeAnyClassToPassToActionRequestObjects() { return this; };

	ActionRequest1 ActionReq1;
	ActionRequest2 ActionReq2;
	ActionRequest3 ActionReq3;


	QueueClassForActionRequest TheRequestToServerNext;

	//std::queue<QueueClassForActionRequest> QueueForAOArgs[MAXNUMOFOBSERVORS];
	AECircularBuffer<QueueClassForActionRequest, POOLSIZE> QueueForAOArgs[NUMOFACTIVEOBJECTS];
	xSemaphoreHandle CountingSemaphoreForActionRequestExecutionTest;

	TaskHandle_t GaurdActionRequestExecutionTask = NULL;



	void InitResource() {

		//check that all action requests have the same classToPass type 
//check if same type or at least second one is AENullActionRequest
		static_assert (TypeChecker_isSame<Action1_CLASSTOPASS_t, Action2_CLASSTOPASS_t>::value
			|| TypeChecker_isSame<ActionRequest2, AENullActionRequest>::value
			, "ActionRequest1s and ActionRequest2s classToPass type are not the same for a utility holding these requests");
		static_assert (TypeChecker_isSame<Action1_CLASSTOPASS_t, Action3_CLASSTOPASS_t>::value
			|| TypeChecker_isSame<ActionRequest3, AENullActionRequest>::value
			, "ActionRequest1s and ActionRequest3s classToPass type are not the same for a utility holding these requests");


		//check if the HardwarePeripheralToUse is of null type. if not, get the instance.
		/*if (!TypeChecker::IsNULLPeripheral<HardwarePeripheralUsed>())
		{
			HardwarePeripheralToUse = (HardwarePeripheralUsed*)HardwarePeripheralUsed::getInstance();// initializePeripheral(); 

			//check that if the first (and then by extension the others) action request has the HardwarePeripheralToUse as the class to pass. if they do, pass that class
					  //also initialize this in all actionrequest
			if (TypeChecker_isSame<Action1_CLASSTOPASS_t, HardwarePeripheralUsed>::value)
			{
				ActionReq1.InitializeAnyClassTobeUsed((void*)HardwarePeripheralToUse);
				ActionReq2.InitializeAnyClassTobeUsed((void*)HardwarePeripheralToUse);
				ActionReq3.InitializeAnyClassTobeUsed((void*)HardwarePeripheralToUse);

				//  the InitializeAnyClassToPassToActionRequestObjects should not be implemented
				//as the actionrequests use the hardwareperipheral and that is passed already.
				configASSERT(this->InitializeAnyClassToPassToActionRequestObjects() == nullptr);
			}
			else if (this->InitializeAnyClassToPassToActionRequestObjects() != nullptr)
			{
				//if the InitializeAnyClassToPassToActionRequestObjects is not null, than the user must have implemented InitializeAnyClassToPassToActionRequestObjects
				ActionReq1.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				ActionReq2.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				ActionReq3.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
			}

		}
		else*/ if (this->InitializeAnyClassToPassToActionRequestObjects() != nullptr)
		{
			//if the class to pass is an AENull, dont pass anything. 
			if (!TypeChecker::IsAENull<Action1_CLASSTOPASS_t>())
			{
				ActionReq1.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
			}
			if (!TypeChecker::IsAENull<Action2_CLASSTOPASS_t>())
			{
				ActionReq2.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
			}
			if (!TypeChecker::IsAENull<Action3_CLASSTOPASS_t>())
			{
				ActionReq3.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
			}


		}
	};



	AEAOResourceAsService()
		//(funcPtr actionReq1, funcPtr actionReq2, funcPtr actionReq3) : ActionReq1(actionReq1), ActionReq2(actionReq2), ActionReq3(actionReq3) 
	{


		//set AOID in the AOID_OfResource for the action requests.
		ActionReq1.AOID_OfResource = this->GetAO_ID();
		ActionReq2.AOID_OfResource = this->GetAO_ID();
		ActionReq3.AOID_OfResource = this->GetAO_ID();
 


		CountingSemaphoreForActionRequestExecutionTest = xSemaphoreCreateCounting(POOLSIZE * 2, 0);

		//ActionReq1 = actionReq1;
		ActionReq1.ActionRequestId = 1;
		//initialize the actionRequestObjects
		ActionReq1.Init(this); 
		if (TypeChecker::IsAENullActionRequest<ActionRequest2>() == false)//just a way to show that this is the AENullActionRequest
		{
			//ActionReq2 = actionReq2;
			ActionReq2.ActionRequestId = 2;
			ActionReq2.Init(this); 
		}
		if (TypeChecker::IsAENullActionRequest<ActionRequest3>() == false)
		{
			//ActionReq3 = actionReq3;
			ActionReq3.ActionRequestId = 3;
			ActionReq3.Init(this); 
		}
	};

	//template<class TRequestType>
	//TRequestType* GetActionRequest();



	ActionRequest1* GetActionRequest1() { return &ActionReq1; };
	ActionRequest2* GetActionRequest2() { return &ActionReq2; };
	ActionRequest3* GetActionRequest3() { return &ActionReq3; };
        
        


	QueueClassForActionRequest* GetNextActionRequestToService()
	{
		//get the id for the actionrequest arguments that is supposed to go next.
		//I need to check the AO with higher priorities first. If their queue 
		//has something in it, theres a request for it. 
		QueueClassForActionRequest* requestToReturn = nullptr;

		for (uint16_t i = 0; i < NUMOFACTIVEOBJECTS; i++)
		{
			//check the QueueForAOArgs in order of AOs Priority
			uint16_t AOOfHighestPriority = AEAO::AOIDsInOrderOfPriorities[i];
			if (QueueForAOArgs[AOOfHighestPriority].isEmpty() == false)
			{
				//QueueClassForActionRequest cssvd = QueueForAOArgs[AOOfHighestPriority].Peek();

				requestToReturn = ((this->QueueForAOArgs[AOOfHighestPriority].Peek()));//&cssvd;//((this->QueueForAOArgs[AOOfHighestPriority].Peek()));
				QueueForAOArgs[AOOfHighestPriority].Pop();
                                
                                if( (requestToReturn->ActionFunctionId > 3) || (requestToReturn->ActionFunctionId <= 0) )
                                {
                                    blabdlasjbdl = 989;
                                }

				//tell all action requests what the requesting AOID is 
				ActionReq1.AOID_OfCurrentRequestingAO = AOOfHighestPriority;
				ActionReq2.AOID_OfCurrentRequestingAO = AOOfHighestPriority;
				ActionReq3.AOID_OfCurrentRequestingAO = AOOfHighestPriority;

				break;
			}
		}
                
                 //a request was not found. something went wrong. this shoudl never happen.
                configASSERT(requestToReturn != nullptr);


		return requestToReturn;

	};

};



static int oaisncoiscn = 8;



template<TemplateFor_RAsAService_NoDefaults>
template<class TActionRequestToRun>
inline void AEAOResourceAsService<TemplateARGSFor_RAsAService>
::RunRequest1(uint16_t AOID, Action1_ARGTYPE1_t arg1, Action1_ARGTYPE2_t arg2, Action1_ARGTYPE3_t arg3, Action1_ARGTYPE4_t arg4, Action1_ARGTYPE5_t arg5)
{
	//TODO: becauserful as technically this class is always going to be 
	// a static class that can be called from any task. maybe I need
	//to mutext the part of the code. and then unmutex the stuff inside. 

	//the following is just a way to produce a compiler error in case the wrong actionRequest
	//is being requested.
#ifndef AEDontCheckForCorrectActionRequestTemplate  
	if (false)
	{
		TActionRequestToRun* dummyVar = static_cast<ActionRequest1*>(&ActionReq1);
	}
#endif
	//push the request in the proper queue. the ActionReq1() will get the request.
        
        QueueClassForActionRequest* reqtopush1 = ((ActionReq1)(arg1, arg2, arg3, arg4, arg5));
        QueueClassForActionRequest reqtopush = *reqtopush1 ;
        
        if( (reqtopush.ActionFunctionId > 3) || (reqtopush.ActionFunctionId <= 0) )  
        {
          oaisncoiscn++;
        }
         
	((QueueForAOArgs[AOID])).Push( reqtopush);

	//increase the countingsemaphore, indicating that another request has been set.
	xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

	return;
}

template<TemplateFor_RAsAService_NoDefaults>
template<class TActionRequestToRun>
inline void AEAOResourceAsService<TemplateARGSFor_RAsAService>
::RunRequest2(uint16_t AOID, Action2_ARGTYPE1_t arg1, Action2_ARGTYPE2_t arg2, Action2_ARGTYPE3_t arg3, Action2_ARGTYPE4_t arg4, Action2_ARGTYPE5_t arg5)
{
#ifndef AEDontCheckForCorrectActionRequestTemplate  
	if (false)
	{
		TActionRequestToRun* dummyVar = static_cast<ActionRequest2*>(&ActionReq2);
	}
#endif

	//push the request in the proper queue. the ActionReq1() will get the request.
	((QueueForAOArgs[AOID])).Push(
		*((ActionReq2)(arg1, arg2, arg3, arg4, arg5)));

	//increase the countingsemaphore, indicating that another request has been set.
	xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

	return;
}

template<TemplateFor_RAsAService_NoDefaults>
template<class TActionRequestToRun>
inline void AEAOResourceAsService<TemplateARGSFor_RAsAService>
::RunRequest3(uint16_t AOID, Action3_ARGTYPE1_t arg1, Action3_ARGTYPE2_t arg2, Action3_ARGTYPE3_t arg3, Action3_ARGTYPE4_t arg4, Action3_ARGTYPE5_t arg5)
{
#ifndef AEDontCheckForCorrectActionRequestTemplate
	if (false)
	{
		TActionRequestToRun* dummyVar = static_cast<ActionRequest3*>(&ActionReq3);
	}
#endif

	//push the request in the proper queue. the ActionReq1() will get the request.
	((QueueForAOArgs[AOID])).Push(
		*((ActionReq3)(arg1, arg2, arg3, arg4, arg5)));

	//increase the countingsemaphore, indicating that another request has been set.
	xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

	return;
}

template<TemplateFor_RAsAService_NoDefaults>
template<class TActionRequestToRun>
inline Token* AEAOResourceAsService<TemplateARGSFor_RAsAService>
::RunRequestWithWait1(uint16_t AOID, Action1_ARGTYPE1_t arg1, Action1_ARGTYPE2_t arg2, Action1_ARGTYPE3_t arg3, Action1_ARGTYPE4_t arg4, Action1_ARGTYPE5_t arg5)
{
#ifndef AEDontCheckForCorrectActionRequestTemplate
	if (false)
	{
		TActionRequestToRun* dummyVar = static_cast<ActionRequest1*>(&ActionReq1);
	}
#endif

	QueueClassForActionRequest request;
	Token* ret = (ActionReq1).Wait(request, arg1, arg2, arg3, arg4, arg5);
	QueueForAOArgs[AOID].Push(request);

	//increase the Utility Resource's countsemaphore telling it that one more request is in the queue
	xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

	return ret;
}



template<TemplateFor_RAsAService_NoDefaults>
template<class TActionRequestToRun>
inline void AEAOResourceAsService<TemplateARGSFor_RAsAService>
::DoneWithRequest1(Token * tokenOfRequest)
{
#ifndef AEDontCheckForCorrectActionRequestTemplate
	if (false)
	{
		TActionRequestToRun* dummyVar = static_cast<ActionRequest1*>(&ActionReq1);
	}
#endif

	return ActionReq1.DoneWithRequest(tokenOfRequest);
}

template<TemplateFor_RAsAService_NoDefaults>
template<class TActionRequestToRun>
inline Token* AEAOResourceAsService<TemplateARGSFor_RAsAService>
::RunRequestWithWait2(uint16_t AOID, Action2_ARGTYPE1_t arg1, Action2_ARGTYPE2_t arg2, Action2_ARGTYPE3_t arg3, Action2_ARGTYPE4_t arg4, Action2_ARGTYPE5_t arg5)
{
#ifndef AEDontCheckForCorrectActionRequestTemplate
	if (false)
	{
		TActionRequestToRun* dummyVar = static_cast<ActionRequest2*>(&ActionReq2);
	}
#endif

	QueueClassForActionRequest request;
	Token* ret = (ActionReq2).Wait(request, arg1, arg2, arg3, arg4, arg5);
	QueueForAOArgs[AOID].Push(request);

	//increase the Utility Resource's countsemaphore telling it that one more request is in the queue
	xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

	return ret;
}



template<TemplateFor_RAsAService_NoDefaults>
template<class TActionRequestToRun>
inline void AEAOResourceAsService<TemplateARGSFor_RAsAService>
::DoneWithRequest2(Token * tokenOfRequest)
{
#ifndef AEDontCheckForCorrectActionRequestTemplate
	if (false)
	{
		TActionRequestToRun* dummyVar = static_cast<ActionRequest2*>(&ActionReq2);
	}
#endif

	return ActionReq2.DoneWithRequest(tokenOfRequest);
}


template<TemplateFor_RAsAService_NoDefaults>
template<class TActionRequestToRun>
inline Token* AEAOResourceAsService<TemplateARGSFor_RAsAService>
::RunRequestWithWait3(uint16_t AOID, Action3_ARGTYPE1_t arg1, Action3_ARGTYPE2_t arg2, Action3_ARGTYPE3_t arg3, Action3_ARGTYPE4_t arg4, Action3_ARGTYPE5_t arg5)
{
#ifndef AEDontCheckForCorrectActionRequestTemplate
	if (false)
	{
		TActionRequestToRun* dummyVar = static_cast<ActionRequest3*>(&ActionReq3);
	}
#endif

	QueueClassForActionRequest request;
	Token* ret = (ActionReq3).Wait(request, arg1, arg2, arg3, arg4, arg5);
	QueueForAOArgs[AOID].Push(request);

	//increase the Utility Resource's countsemaphore telling it that one more request is in the queue
	xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

	return ret;
}



template<TemplateFor_RAsAService_NoDefaults>
template<class TActionRequestToRun>
inline void AEAOResourceAsService<TemplateARGSFor_RAsAService>
::DoneWithRequest3(Token * tokenOfRequest)
{
#ifndef AEDontCheckForCorrectActionRequestTemplate
	if (false)
	{
		TActionRequestToRun* dummyVar = static_cast<ActionRequest3*>(&ActionReq3);
	}
#endif

	return ActionReq3.DoneWithRequest(tokenOfRequest);
}

#endif














































template<TemplateFor_Service>
	class AEAOResourceService : public AEAO
	{

		Friend_ToALL_ActionRequestObjects

		public :

			virtual void CheckIfConfiguredProperly() const override {
			//assert all I need to assert here.
		}

		DeclareActionRequestTemplateArgs2

			DeclareUtilityRequestFunctions2

			//HardwarePeripheralUsed* HardwarePeripheralToUse;

		//template<class TActionRequestToRun>
		Action1_RETURNTYPE_t WaitForRequestToFinish1(Token* tokenOfRequest) {
//			if (false)
//			{
//				TActionRequestToRun* dummyVar = static_cast<ActionRequest1*>(&ActionReq1);
//			}

			return ActionReq1.WaitForRequestToFinish(tokenOfRequest);
		}
		;
		//template<class TActionRequestToRun>
			Action2_RETURNTYPE_t WaitForRequestToFinish2(Token* tokenOfRequest) {
//				if (false)
//				{
//					TActionRequestToRun* dummyVar = static_cast<ActionRequest2*>(&ActionReq2);
//				}

				return ActionReq2.WaitForRequestToFinish(tokenOfRequest);
			}
		;
		//template<class TActionRequestToRun>
			Action3_RETURNTYPE_t WaitForRequestToFinish3(Token* tokenOfRequest) {
//				if (false)
//				{
//					TActionRequestToRun* dummyVar = static_cast<ActionRequest3*>(&ActionReq3);
//				}

				return ActionReq3.WaitForRequestToFinish(tokenOfRequest);
			} 
		
		//template<class TActionRequestToRun>
			Action4_RETURNTYPE_t WaitForRequestToFinish4(Token* tokenOfRequest) {
//				if (false)
//				{
//					TActionRequestToRun* dummyVar = static_cast<ActionRequest4*>(&ActionReq4);
//				}

				return ActionReq4.WaitForRequestToFinish(tokenOfRequest);
			} 
		
		//template<class TActionRequestToRun>
			Action5_RETURNTYPE_t WaitForRequestToFinish5(Token* tokenOfRequest) {
//				if (false)
//				{
//					TActionRequestToRun* dummyVar = static_cast<ActionRequest5*>(&ActionReq5);
//				}

				return ActionReq5.WaitForRequestToFinish(tokenOfRequest);
			} 
		
		//template<class TActionRequestToRun>
			Action6_RETURNTYPE_t WaitForRequestToFinish6(Token* tokenOfRequest) {
//				if (false)
//				{
//					TActionRequestToRun* dummyVar = static_cast<ActionRequest6*>(&ActionReq6);
//				}

				return ActionReq6.WaitForRequestToFinish(tokenOfRequest);
			} 


		
		ActionRequest1 ActionReq1;
		ActionRequest2 ActionReq2;
		ActionRequest3 ActionReq3;
		ActionRequest4 ActionReq4;
		ActionRequest5 ActionReq5;
		ActionRequest6 ActionReq6;
	protected:


		void* InitializeAnyClassToPassToActionRequestObjects() { return this; }
		;




		QueueClassForActionRequest TheRequestToServerNext;

		//std::queue<QueueClassForActionRequest> QueueForAOArgs[MAXNUMOFOBSERVORS];
		AECircularBuffer<QueueClassForActionRequest, POOLSIZE> QueueForAOArgs[NUMOFACTIVEOBJECTS];
		xSemaphoreHandle CountingSemaphoreForActionRequestExecutionTest;

		TaskHandle_t GaurdActionRequestExecutionTask = NULL;



		void InitResource() {

			//check that all action requests have the same classToPass type 
			//check if same type or at least second one is AENullActionRequest
			static_assert(TypeChecker_isSame<Action1_CLASSTOPASS_t,
				Action2_CLASSTOPASS_t>::value
				|| TypeChecker_isSame<ActionRequest2,
				AENullActionRequest>::value,
				"ActionRequest1s and ActionRequest2s classToPass type are not the same for a utility holding these requests");
			static_assert(TypeChecker_isSame<Action1_CLASSTOPASS_t,
				Action3_CLASSTOPASS_t>::value
				|| TypeChecker_isSame<ActionRequest3,
				AENullActionRequest>::value,
				"ActionRequest1s and ActionRequest3s classToPass type are not the same for a utility holding these requests");


			//check if the HardwarePeripheralToUse is of null type. if not, get the instance.
			/*if (!TypeChecker::IsNULLPeripheral<HardwarePeripheralUsed>())
			{
				HardwarePeripheralToUse = (HardwarePeripheralUsed*)HardwarePeripheralUsed::getInstance();// initializePeripheral(); 

				//check that if the first (and then by extension the others) action request has the HardwarePeripheralToUse as the class to pass. if they do, pass that class
						  //also initialize this in all actionrequest
					if (TypeChecker_isSame<Action1_CLASSTOPASS_t, HardwarePeripheralUsed>::value)
					{
						ActionReq1.InitializeAnyClassTobeUsed((void*)HardwarePeripheralToUse);
						ActionReq2.InitializeAnyClassTobeUsed((void*)HardwarePeripheralToUse);
						ActionReq3.InitializeAnyClassTobeUsed((void*)HardwarePeripheralToUse);

						//  the InitializeAnyClassToPassToActionRequestObjects should not be implemented
						//as the actionrequests use the hardwareperipheral and that is passed already.
						configASSERT(this->InitializeAnyClassToPassToActionRequestObjects() == nullptr);
			}
			else if (this->InitializeAnyClassToPassToActionRequestObjects() != nullptr)
			{
				//if the InitializeAnyClassToPassToActionRequestObjects is not null, than the user must have implemented InitializeAnyClassToPassToActionRequestObjects
				ActionReq1.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				ActionReq2.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				ActionReq3.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
			}

		}
		else*/ if (this->InitializeAnyClassToPassToActionRequestObjects() != nullptr)
			{
				//if the class to pass is an AENull, dont pass anything. 
				if (!TypeChecker::IsAENull<Action1_CLASSTOPASS_t>())
				{
					ActionReq1.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				}
				if (!TypeChecker::IsAENull<Action2_CLASSTOPASS_t>())
				{
					ActionReq2.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				}
				if (!TypeChecker::IsAENull<Action3_CLASSTOPASS_t>())
				{
					ActionReq3.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				}				
				if (!TypeChecker::IsAENull<Action4_CLASSTOPASS_t>())
				{
					ActionReq4.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				}
				if (!TypeChecker::IsAENull<Action5_CLASSTOPASS_t>())
				{
					ActionReq5.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				}
				if (!TypeChecker::IsAENull<Action6_CLASSTOPASS_t>())
				{
					ActionReq6.InitializeAnyClassTobeUsed(InitializeAnyClassToPassToActionRequestObjects());
				}

			}
		}
		;



		AEAOResourceService()
			//(funcPtr actionReq1, funcPtr actionReq2, funcPtr actionReq3) : ActionReq1(actionReq1), ActionReq2(actionReq2), ActionReq3(actionReq3) 
		{


			//set AOID in the AOID_OfResource for the action requests.
			ActionReq1.AOID_OfResource = this->GetAO_ID();
			ActionReq2.AOID_OfResource = this->GetAO_ID();
			ActionReq3.AOID_OfResource = this->GetAO_ID();
			ActionReq4.AOID_OfResource = this->GetAO_ID();
			ActionReq5.AOID_OfResource = this->GetAO_ID();
			ActionReq6.AOID_OfResource = this->GetAO_ID();
 


			CountingSemaphoreForActionRequestExecutionTest = xSemaphoreCreateCounting(POOLSIZE * 2, 0);

			//ActionReq1 = actionReq1;
//			ActionReq1.ActionRequestId = 1;
//			//initialize the actionRequestObjects
//			ActionReq1.Init(this); 
			if (TypeChecker::IsAENullActionRequest<ActionRequest1>() == false)//just a way to show that this is the AENullActionRequest
			{
				//ActionReq2 = actionReq2;
				ActionReq1.ActionRequestId = 1;
				ActionReq1.Init(this); 
			}
			if (TypeChecker::IsAENullActionRequest<ActionRequest2>() == false)//just a way to show that this is the AENullActionRequest
			{
				//ActionReq2 = actionReq2;
				ActionReq2.ActionRequestId = 2;
				ActionReq2.Init(this); 
			}
			if (TypeChecker::IsAENullActionRequest<ActionRequest3>() == false)
			{
				//ActionReq3 = actionReq3;
				ActionReq3.ActionRequestId = 3;
				ActionReq3.Init(this); 
			}
			if (TypeChecker::IsAENullActionRequest<ActionRequest4>() == false)
			{
				//ActionReq3 = actionReq3;
				ActionReq4.ActionRequestId = 4;
				ActionReq4.Init(this); 
			}
			if (TypeChecker::IsAENullActionRequest<ActionRequest5>() == false)
			{
				//ActionReq3 = actionReq3;
				ActionReq5.ActionRequestId = 5;
				ActionReq5.Init(this); 
			}
			if (TypeChecker::IsAENullActionRequest<ActionRequest6>() == false)
			{
				//ActionReq3 = actionReq3;
				ActionReq6.ActionRequestId = 6;
				ActionReq6.Init(this); 
			}
		}
		;

		//template<class TRequestType>
		//TRequestType* GetActionRequest();



		ActionRequest1* GetActionRequest1() { return &ActionReq1; }
		ActionRequest2* GetActionRequest2() { return &ActionReq2; }
		ActionRequest3* GetActionRequest3() { return &ActionReq3; }
		ActionRequest4* GetActionRequest4() { return &ActionReq4; }
		ActionRequest5* GetActionRequest5() { return &ActionReq5; }
		ActionRequest6* GetActionRequest6() { return &ActionReq6; }
		
        
        


		QueueClassForActionRequest* GetNextActionRequestToService()
		{
			//get the id for the actionrequest arguments that is supposed to go next.
			//I need to check the AO with higher priorities first. If their queue 
			//has something in it, theres a request for it. 
			QueueClassForActionRequest* requestToReturn = nullptr;

			for (uint16_t i = 0; i < NUMOFACTIVEOBJECTS; i++)
			{
				//check the QueueForAOArgs in order of AOs Priority
				uint16_t AOOfHighestPriority = AEAO::AOIDsInOrderOfPriorities[i];
				if (QueueForAOArgs[AOOfHighestPriority].isEmpty() == false)
				{
					//QueueClassForActionRequest cssvd = QueueForAOArgs[AOOfHighestPriority].Peek();

					requestToReturn = ((this->QueueForAOArgs[AOOfHighestPriority].Peek())); //&cssvd;//((this->QueueForAOArgs[AOOfHighestPriority].Peek()));
					QueueForAOArgs[AOOfHighestPriority].Pop();
                                
//					if ((requestToReturn->ActionFunctionId > 3) || (requestToReturn->ActionFunctionId <= 0))
//					{
//						blabdlasjbdl = 989;
//					}

					//tell all action requests what the requesting AOID is 
					ActionReq1.AOID_OfCurrentRequestingAO = AOOfHighestPriority;
					ActionReq2.AOID_OfCurrentRequestingAO = AOOfHighestPriority;
					ActionReq3.AOID_OfCurrentRequestingAO = AOOfHighestPriority;
					ActionReq4.AOID_OfCurrentRequestingAO = AOOfHighestPriority;
					ActionReq5.AOID_OfCurrentRequestingAO = AOOfHighestPriority;
					ActionReq6.AOID_OfCurrentRequestingAO = AOOfHighestPriority;

					break;
				}
			}
                
			//a request was not found. something went wrong. this shoudl never happen.
			configASSERT(requestToReturn != nullptr);


			return requestToReturn;

		}
		;

	};

 



template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::RunRequest1(uint16_t AOID, Action1_ARGTYPE1_t arg1, Action1_ARGTYPE2_t arg2, Action1_ARGTYPE3_t arg3, Action1_ARGTYPE4_t arg4, Action1_ARGTYPE5_t arg5)
		{
			//TODO: becauserful as technically this class is always going to be 
			// a static class that can be called from any task. maybe I need
			//to mutext the part of the code. and then unmutex the stuff inside. 

			//the following is just a way to produce a compiler error in case the wrong actionRequest
			//is being requested.
#ifndef AEDontCheckForCorrectActionRequestTemplate  
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest1*>(&ActionReq1);
			}
#endif
			//push the request in the proper queue. the ActionReq1() will get the request.
        
			QueueClassForActionRequest* reqtopush1 = ((ActionReq1)(arg1, arg2, arg3, arg4, arg5));
			QueueClassForActionRequest reqtopush = *reqtopush1;
        
			if ((reqtopush.ActionFunctionId > 3) || (reqtopush.ActionFunctionId <= 0))  
			{
				oaisncoiscn++;
			}
         
			((QueueForAOArgs[AOID])).Push(reqtopush);

			//increase the countingsemaphore, indicating that another request has been set.
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return;
		}

template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::RunRequest2(uint16_t AOID, Action2_ARGTYPE1_t arg1, Action2_ARGTYPE2_t arg2, Action2_ARGTYPE3_t arg3, Action2_ARGTYPE4_t arg4, Action2_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate  
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest2*>(&ActionReq2);
			}
#endif

			//push the request in the proper queue. the ActionReq1() will get the request.
			((QueueForAOArgs[AOID])).Push(
				*((ActionReq2)(arg1, arg2, arg3, arg4, arg5)));

			//increase the countingsemaphore, indicating that another request has been set.
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return;
		}

template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::RunRequest3(uint16_t AOID, Action3_ARGTYPE1_t arg1, Action3_ARGTYPE2_t arg2, Action3_ARGTYPE3_t arg3, Action3_ARGTYPE4_t arg4, Action3_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest3*>(&ActionReq3);
			}
#endif

			//push the request in the proper queue. the ActionReq1() will get the request.
			((QueueForAOArgs[AOID])).Push(
				*((ActionReq3)(arg1, arg2, arg3, arg4, arg5)));

			//increase the countingsemaphore, indicating that another request has been set.
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return;
		}

template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline Token* AEAOResourceService<TemplateARGSFor_Service>
		::RunRequestWithWait1(uint16_t AOID, Action1_ARGTYPE1_t arg1, Action1_ARGTYPE2_t arg2, Action1_ARGTYPE3_t arg3, Action1_ARGTYPE4_t arg4, Action1_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest1*>(&ActionReq1);
			}
#endif

			QueueClassForActionRequest request;
			Token* ret = (ActionReq1).Wait(request, arg1, arg2, arg3, arg4, arg5);
			QueueForAOArgs[AOID].Push(request);

			//increase the Utility Resource's countsemaphore telling it that one more request is in the queue
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return ret;
		}



template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::DoneWithRequest1(Token * tokenOfRequest)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest1*>(&ActionReq1);
			}
#endif

			return ActionReq1.DoneWithRequest(tokenOfRequest);
		}

template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline Token* AEAOResourceService<TemplateARGSFor_Service>
		::RunRequestWithWait2(uint16_t AOID, Action2_ARGTYPE1_t arg1, Action2_ARGTYPE2_t arg2, Action2_ARGTYPE3_t arg3, Action2_ARGTYPE4_t arg4, Action2_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest2*>(&ActionReq2);
			}
#endif

			QueueClassForActionRequest request;
			Token* ret = (ActionReq2).Wait(request, arg1, arg2, arg3, arg4, arg5);
			QueueForAOArgs[AOID].Push(request);

			//increase the Utility Resource's countsemaphore telling it that one more request is in the queue
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return ret;
		}



template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::DoneWithRequest2(Token * tokenOfRequest)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest2*>(&ActionReq2);
			}
#endif

			return ActionReq2.DoneWithRequest(tokenOfRequest);
		}


template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline Token* AEAOResourceService<TemplateARGSFor_Service>
		::RunRequestWithWait3(uint16_t AOID, Action3_ARGTYPE1_t arg1, Action3_ARGTYPE2_t arg2, Action3_ARGTYPE3_t arg3, Action3_ARGTYPE4_t arg4, Action3_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest3*>(&ActionReq3);
			}
#endif

			QueueClassForActionRequest request;
			Token* ret = (ActionReq3).Wait(request, arg1, arg2, arg3, arg4, arg5);
			QueueForAOArgs[AOID].Push(request);

			//increase the Utility Resource's countsemaphore telling it that one more request is in the queue
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return ret;
		}



template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::DoneWithRequest3(Token * tokenOfRequest)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest3*>(&ActionReq3);
			}
#endif

			return ActionReq3.DoneWithRequest(tokenOfRequest);
		}









//tdus ===========================================================



template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::RunRequest4(uint16_t AOID, Action4_ARGTYPE1_t arg1, Action4_ARGTYPE2_t arg2, Action4_ARGTYPE3_t arg3, Action4_ARGTYPE4_t arg4, Action4_ARGTYPE5_t arg5)
		{
			//TODO: becauserful as technically this class is always going to be 
			// a static class that can be called from any task. maybe I need
			//to mutext the part of the code. and then unmutex the stuff inside. 

			//the following is just a way to produce a compiler error in case the wrong actionRequest
			//is being requested.
#ifndef AEDontCheckForCorrectActionRequestTemplate  
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest4*>(&ActionReq4);
			}
#endif
			//push the request in the proper queue. the ActionReq1() will get the request.
        
			QueueClassForActionRequest* reqtopush1 = ((ActionReq4)(arg1, arg2, arg3, arg4, arg5));
			QueueClassForActionRequest reqtopush = *reqtopush1;
         
			((QueueForAOArgs[AOID])).Push(reqtopush);

			//increase the countingsemaphore, indicating that another request has been set.
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return;
		}

template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::RunRequest5(uint16_t AOID, Action5_ARGTYPE1_t arg1, Action5_ARGTYPE2_t arg2, Action5_ARGTYPE3_t arg3, Action5_ARGTYPE4_t arg4, Action5_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate  
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest5*>(&ActionReq5);
			}
#endif

			//push the request in the proper queue. the ActionReq1() will get the request.
			((QueueForAOArgs[AOID])).Push(
				*((ActionReq5)(arg1, arg2, arg3, arg4, arg5)));

			//increase the countingsemaphore, indicating that another request has been set.
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return;
		}

template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::RunRequest6(uint16_t AOID, Action6_ARGTYPE1_t arg1, Action6_ARGTYPE2_t arg2, Action6_ARGTYPE3_t arg3, Action6_ARGTYPE4_t arg4, Action6_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest6*>(&ActionReq6);
			}
#endif

			//push the request in the proper queue. the ActionReq1() will get the request.
			((QueueForAOArgs[AOID])).Push(
				*((ActionReq6)(arg1, arg2, arg3, arg4, arg5)));

			//increase the countingsemaphore, indicating that another request has been set.
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return;
		}

template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline Token* AEAOResourceService<TemplateARGSFor_Service>
		::RunRequestWithWait4(uint16_t AOID, Action4_ARGTYPE1_t arg1, Action4_ARGTYPE2_t arg2, Action4_ARGTYPE3_t arg3, Action4_ARGTYPE4_t arg4, Action4_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest4*>(&ActionReq1);
			}
#endif

			QueueClassForActionRequest request;
			Token* ret = (ActionReq4).Wait(request, arg1, arg2, arg3, arg4, arg5);
			QueueForAOArgs[AOID].Push(request);

			//increase the Utility Resource's countsemaphore telling it that one more request is in the queue
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return ret;
		}



template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::DoneWithRequest4(Token * tokenOfRequest)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest4*>(&ActionReq4);
			}
#endif

			return ActionReq4.DoneWithRequest(tokenOfRequest);
		}

template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline Token* AEAOResourceService<TemplateARGSFor_Service>
		::RunRequestWithWait5(uint16_t AOID, Action5_ARGTYPE1_t arg1, Action5_ARGTYPE2_t arg2, Action5_ARGTYPE3_t arg3, Action5_ARGTYPE4_t arg4, Action5_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest5*>(&ActionReq5);
			}
#endif

			QueueClassForActionRequest request;
			Token* ret = (ActionReq5).Wait(request, arg1, arg2, arg3, arg4, arg5);
			QueueForAOArgs[AOID].Push(request);

			//increase the Utility Resource's countsemaphore telling it that one more request is in the queue
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return ret;
		}



template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::DoneWithRequest5(Token * tokenOfRequest)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest5*>(&ActionReq5);
			}
#endif

			return ActionReq5.DoneWithRequest(tokenOfRequest);
		}


template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline Token* AEAOResourceService<TemplateARGSFor_Service>
		::RunRequestWithWait6(uint16_t AOID, Action6_ARGTYPE1_t arg1, Action6_ARGTYPE2_t arg2, Action6_ARGTYPE3_t arg3, Action6_ARGTYPE4_t arg4, Action6_ARGTYPE5_t arg5)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest6*>(&ActionReq6);
			}
#endif

			QueueClassForActionRequest request;
			Token* ret = (ActionReq6).Wait(request, arg1, arg2, arg3, arg4, arg5);
			QueueForAOArgs[AOID].Push(request);

			//increase the Utility Resource's countsemaphore telling it that one more request is in the queue
			xSemaphoreGive(CountingSemaphoreForActionRequestExecutionTest);

			return ret;
		}



template<TemplateFor_Service_NoDefaults>
	template<class TActionRequestToRun>
		inline void AEAOResourceService<TemplateARGSFor_Service>
		::DoneWithRequest6(Token * tokenOfRequest)
		{
#ifndef AEDontCheckForCorrectActionRequestTemplate
			if (false)
			{
				TActionRequestToRun* dummyVar = static_cast<ActionRequest6*>(&ActionReq6);
			}
#endif

			return ActionReq6.DoneWithRequest(tokenOfRequest);
		}
