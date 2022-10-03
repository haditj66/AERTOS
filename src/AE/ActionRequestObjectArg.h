//generated file: ActionArgGenerated.h


#pragma once

//UserCode_Section0
#include "FreeRTOS.h" 
#include "semphr.h" 
#include <cstdint>

#include "AECircularBuffer.h"

#include "AEUtils.h"

//#include "MCUTypeDefs.h"


class AENullActionRequest {
public:
	bool TypeIdOfthisClass;
	bool _frequencyIUpdateAt;
	bool Input;
	bool ClassForActionRequest;

	bool AOID_OfCurrentRequestingAO;
	bool AOID_OfResource;

	bool IsWaitingForEvent;
	bool EvtWaitingFor;
	bool BinarySemaphoreForEventListening_ptr;
	//bool QueueExecuteForEvtOfTDU_ptr;

	typedef AENull ARGTYPE1;
	typedef AENull RETURNTYPE;
	typedef AENull ARGTYPE2;
	typedef AENull ARGTYPE3;
	typedef AENull ARGTYPE4;
	typedef AENull ARGTYPE5;
	typedef bool CLASSTOPASS;

	bool ActionRequestId;
	void Request(uint16_t) {};
	bool Update() { return true; };
	void ActionRequestComplete(uint16_t) {};
	void InitializeAnyClassTobeUsed(void*) {};
	template<class TutilityResource>
	void Init(TutilityResource*  utilityResource) {};
	AENullActionRequest() { ActionRequestId = false; };
	void CancelCleanUp() {};
};



class QueueClassForActionRequest
{
public:
	uint16_t Argument_Id;
	uint16_t ActionFunctionId;
};


//this is temporary as you need to make your own queue
//#include "queue.h"
#include <queue>

class Token
{
public:
	int Id;
	xSemaphoreHandle BinarySemaphore;

	Token() {
		BinarySemaphore = xSemaphoreCreateBinary();
	}

	bool CheckIfTokenReadyToReturn() {
		if (xQueuePeek((xQueueHandle)BinarySemaphore, (void *)NULL, (portTickType)NULL) != pdTRUE)
		{
			return false;
		}
		else {
			return true;
		}
	};

};

static uint16_t indexForTypeIdOfthisClass = 0;
//UserCode_Section0_end


template<TemplateForActionArg1>
class ActionRequestObjectArg1
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;

	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;

protected:


	class ActionArguments
	{
	public:
		//UserCode_Section0_Loop1_Iteration1
//leave the arguments as it. dont try to cast things to a pointer or anything. if I wanted
	// a pointer, the user would have set that explicitly in the template arguments!
		ARG1 arg1;
		RETURNARG returnArg;
		//UserCode_Section0_Loop1_Iteration1_end 


		uint16_t Id;
		bool IsAvailable;
		bool IntendToWait;
		ActionArguments() {
			IsAvailable = true;

		};
	};

public:

	uint16_t TypeIdOfthisClass;

	//UserCode_Section1_Loop1_Iteration1
	typedef ARG1 ARGTYPE1;
	typedef RETURNARG RETURNTYPE;
	typedef AENull ARGTYPE2;
	typedef AENull ARGTYPE3;
	typedef AENull ARGTYPE4;
	typedef AENull ARGTYPE5;
	//UserCode_Section1_Loop1_Iteration1_end 

	typedef ForwardDeclaredUtility CLASSTOPASS;

	ActionRequestObjectArg1() {
		this->TypeIdOfthisClass = 0;
	};

	uint16_t GetAOID_OfResource()
	{
		return AOID_OfResource;
	}


	RETURNARG WaitForRequestToFinish(Token* tokenOfRequest)
	{
		xSemaphoreTake(tokenOfRequest->BinarySemaphore, portMAX_DELAY);
		return argPool[tokenOfRequest->Id].returnArg;
	}

	//this is the function to call if you want to request an action but dont intend to wait
	QueueClassForActionRequest* operator()(ARG1 arg1_l, bool arg2 = false, bool arg3 = false, bool arg4 = false, bool arg5 = false);

	//this is the function to call if you want to request an action and DO intend to wait.
	Token* Wait(QueueClassForActionRequest& requestToReturn, ARG1 arg1_l, bool arg2 = false, bool arg3 = false, bool arg4 = false, bool arg5 = false) {
		//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
		ActionArguments* actionArg = GetActionArgument();
		//UserCode_Section2_Loop1_Iteration1
/*
		if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
		{
			//memcpy(&actionArg->arg1, static_cast<void*>(arg1_l), sizeof(ARG1));
		}
		else
		{
			memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
		}
		*/
		ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
		//UserCode_Section2_Loop1_Iteration1_end 
		actionArg->IntendToWait = true;

		//place that actionargument in the pool for the respective AOId 
		requestToReturn.Argument_Id = actionArg->Id; requestToReturn.ActionFunctionId = ActionRequestId;

		return &Tokens[requestToReturn.Argument_Id];

	};


	void DoneWithRequest(Token* tokenOfRequest)
	{

		//there shouldnt be a chance of a race condition here as only the AO has access to the argpool with the id given
		//mark arguments as available here
		//the reason why i need to do this is because I need a way for the AO to release
		// the returnArg to its pool in order to elminiate the chance of it getting used and written over.
		argPool[tokenOfRequest->Id].IsAvailable = true;

	};


protected:

	uint16_t AOID_OfResource;
	uint16_t AOID_OfCurrentRequestingAO;

	xSemaphoreHandle MutexForGetActionArg;
	ActionArguments argPool[__POOLSIZE];
	QueueClassForActionRequest requestPool[__POOLSIZE];
	Token Tokens[__POOLSIZE];

	uint16_t ActionRequestId;

	ForwardDeclaredUtility* ClassForActionRequest;

	template<class TutilityResource>
	void Init(TutilityResource*  utilityResource);

	//use this class to initialize any classes that need to be used in the action request.
	virtual void InitializeAnyClassTobeUsed(void* classToUse) {
		ClassForActionRequest = reinterpret_cast<ForwardDeclaredUtility*>(classToUse);
	};


	ActionArguments* GetActionArgument()
	{

		//the only way to rid of the mutex here is to partition the argpool to each AO.
		xSemaphoreTake(MutexForGetActionArg, portMAX_DELAY);

		for (int i = 0; i < __POOLSIZE; i++)
		{
			if (argPool[i].IsAvailable == true)
			{
				argPool[i].IsAvailable = false;
				xSemaphoreGive(MutexForGetActionArg);
				return &argPool[i];
			}
		}

		xSemaphoreGive(MutexForGetActionArg);

		//the argument pool for the action request was all used up. you may
		//need to inscrease the pool size for the action request.
		configASSERT(false);
		return nullptr;
	}


	uint16_t CurrentActionArgId;

	//this is the function that will be called by the execution task. it is one layer of misdirection to 
	//get the arguments before it executes the function.
	void Request(uint16_t idOfArgument) {

		CurrentActionArgId = idOfArgument;

		//retrieve the actionargument object from the pool and run the override implementation function.
		//UserCode_Section3_Loop1_Iteration1
		RequestImpl(argPool[idOfArgument].arg1);
		//UserCode_Section3_Loop1_Iteration1_end 

				//note that I can not set the argPool[idOfArgument].isavailable to true yet because if i did,
				//there is the possibility that that argPool[idOfArgument] might get taken up again and changed. 

	};



	///this is set as a way to set the return arg without having to do it through the 
	/// return of the "virtual RETURNARG RequestImpl(ARG1 Argument1) = 0;"  function.
	///it needs to be the same for tdus and U so that they dont have to share the same interface of RequestImpl having a RequestImpl return type.
	void SetReturnArg(RETURNTYPE returnValueToSet);

	//this is the function that will be oveeriden and implemented.  
	//UserCode_Section4_Loop1_Iteration1
	virtual void RequestImpl(ARG1 Argument1) = 0;
	//UserCode_Section4_Loop1_Iteration1_end 


		///this function it to clean up anything needed to be cleaned up when an
		///action request is completed.
	void ActionRequestComplete(uint16_t idOfArgument)
	{
		//if there was NOT an intend to wait, than I can finish with the argument and set it back to available
		if (argPool[idOfArgument].IntendToWait == false)
		{
			argPool[idOfArgument].IsAvailable = true;
		}

		else
		{
			//give correspondng token the semaphore back so to the AO that is waiting, can stop waiting
			xSemaphoreGive(Tokens[idOfArgument].BinarySemaphore);
		}


	}

};



template<TemplateForActionArg_NoDefaults1>
inline void ActionRequestObjectArg1<TemplateForActionArg_Args1>
::SetReturnArg(RETURNTYPE returnValueToSet)
{
	//if there was no intent to wait, then there is no need to set the return arg
	if (this->argPool[this->CurrentActionArgId].IntendToWait == false)
	{
		return;
	}

	else
	{
		this->argPool[this->CurrentActionArgId].returnArg = returnValueToSet;
	}
}


template<TemplateForActionArg_NoDefaults1 >
template<class TutilityResource>
inline void ActionRequestObjectArg1<TemplateForActionArg_Args1>
::Init(TutilityResource * utilityResource)
{

	MutexForGetActionArg = xSemaphoreCreateMutex();
	for (int i = 0; i < __POOLSIZE; i++)
	{
		argPool[i].Id = i;
		Tokens[i].Id = i;
		Tokens[i].BinarySemaphore = xSemaphoreCreateBinary();

	}
}


template<TemplateForActionArg_NoDefaults1>
inline QueueClassForActionRequest* ActionRequestObjectArg1<TemplateForActionArg_Args1>
::operator()
//UserCode_Section5_Loop1_Iteration1
(ARG1 arg1_l, bool arg2, bool arg3, bool arg4, bool arg5)
//UserCode_Section5_Loop1_Iteration1_end 
{
	//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
	ActionArguments* actionArg = GetActionArgument();
	//UserCode_Section6_Loop1_Iteration1
	//TODO:!!!!! This GetActionArgument() needs to be accesible at the user level. The user should be the one 
	//to grab the argument, fill it, and then just pass in the ActionArguments* to a function.
/*
	if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
	{

	}
	else
	{
		memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
	}
	*/

	ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
	//UserCode_Section6_Loop1_Iteration1_end 
	actionArg->IntendToWait = false;

	//place that actionargument in the pool for the respective AOId 
	QueueClassForActionRequest* request = &requestPool[actionArg->Id];
	request->Argument_Id = actionArg->Id; request->ActionFunctionId = ActionRequestId;

	return request;

}
















































//-----------------------------------------------------------------------------------------------------------------------------

template<TemplateForActionArg2>
class ActionRequestObjectArg2
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;

	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;

protected:


	class ActionArguments
	{
	public:
		//UserCode_Section0_Loop1_Iteration2
		ARG1 arg1;
		ARG2 arg2;
		RETURNARG returnArg;
		//UserCode_Section0_Loop1_Iteration2_end 


		uint16_t Id;
		bool IsAvailable;
		bool IntendToWait;
		ActionArguments() {
			IsAvailable = true;

		};
	};

public:

	uint16_t TypeIdOfthisClass;

	//UserCode_Section1_Loop1_Iteration2
	typedef ARG1 ARGTYPE1;
	typedef RETURNARG RETURNTYPE;
	typedef ARG2 ARGTYPE2;
	typedef AENull ARGTYPE3;
	typedef AENull ARGTYPE4;
	typedef AENull ARGTYPE5;
	//UserCode_Section1_Loop1_Iteration2_end 

	typedef ForwardDeclaredUtility CLASSTOPASS;

	ActionRequestObjectArg2() {
		this->TypeIdOfthisClass = 0;
	};

	uint16_t GetAOID_OfResource()
	{
		return AOID_OfResource;
	}


	RETURNARG WaitForRequestToFinish(Token* tokenOfRequest)
	{
		xSemaphoreTake(tokenOfRequest->BinarySemaphore, portMAX_DELAY);
		return argPool[tokenOfRequest->Id].returnArg;
	}

	//this is the function to call if you want to request an action but dont intend to wait
	QueueClassForActionRequest* operator()(ARG1 arg1_l, ARG2 arg2 = false, bool arg3 = false, bool arg4 = false, bool arg5 = false);

	//this is the function to call if you want to request an action and DO intend to wait.
	Token* Wait(QueueClassForActionRequest& requestToReturn, ARG1 arg1_l, ARG2 arg2 = false, bool arg3 = false, bool arg4 = false, bool arg5 = false) {
		//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
		ActionArguments* actionArg = GetActionArgument();
		//UserCode_Section2_Loop1_Iteration2
/*
		if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
		{
			memcpy(&actionArg->arg1, (void*)arg1_l, sizeof(ARG1));
		}
		else
		{
			memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
		}
		if (IsArrayChecker<ARG2>::IsArgumentArray(arg2))
		{
			memcpy(&actionArg->arg2, (void*)arg2, sizeof(ARG2));
		}
		else
		{
			memcpy(&actionArg->arg2, (void*)&arg2, sizeof(ARG2));
		}
		*/

		ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
		ArrayCheckToMemCopy<ARG2>::AEMemcpy(&actionArg->arg2, arg2, sizeof(ARG2));
		//UserCode_Section2_Loop1_Iteration2_end 
		actionArg->IntendToWait = true;

		//place that actionargument in the pool for the respective AOId 
		requestToReturn.Argument_Id = actionArg->Id; requestToReturn.ActionFunctionId = ActionRequestId;

		return &Tokens[requestToReturn.Argument_Id];

	};


	void DoneWithRequest(Token* tokenOfRequest)
	{

		//there shouldnt be a chance of a race condition here as only the AO has access to the argpool with the id given
		//mark arguments as available here
		//the reason why i need to do this is because I need a way for the AO to release
		// the returnArg to its pool in order to elminiate the chance of it getting used and written over.
		argPool[tokenOfRequest->Id].IsAvailable = true;

	};


protected:

	uint16_t AOID_OfResource;
	uint16_t AOID_OfCurrentRequestingAO;

	xSemaphoreHandle MutexForGetActionArg;
	ActionArguments argPool[__POOLSIZE];
	QueueClassForActionRequest requestPool[__POOLSIZE];
	Token Tokens[__POOLSIZE];

	uint16_t ActionRequestId;

	ForwardDeclaredUtility* ClassForActionRequest;

	template<class TutilityResource>
	void Init(TutilityResource*  utilityResource);

	//use this class to initialize any classes that need to be used in the action request.
	virtual void InitializeAnyClassTobeUsed(void* classToUse) {
		ClassForActionRequest = reinterpret_cast<ForwardDeclaredUtility*>(classToUse);
	};


	ActionArguments* GetActionArgument()
	{

		//the only way to rid of the mutex here is to partition the argpool to each AO.
		xSemaphoreTake(MutexForGetActionArg, portMAX_DELAY);

		for (int i = 0; i < __POOLSIZE; i++)
		{
			if (argPool[i].IsAvailable == true)
			{
				argPool[i].IsAvailable = false;
				xSemaphoreGive(MutexForGetActionArg);
				return &argPool[i];
			}
		}

		xSemaphoreGive(MutexForGetActionArg);

		//the argument pool for the action request was all used up. you may
		//need to inscrease the pool size for the action request.
		configASSERT(false);
		return nullptr;
	}


	uint16_t CurrentActionArgId;

	//this is the function that will be called by the execution task. it is one layer of misdirection to 
	//get the arguments before it executes the function.
	void Request(uint16_t idOfArgument) {

		CurrentActionArgId = idOfArgument;

		//retrieve the actionargument object from the pool and run the override implementation function.
		//UserCode_Section3_Loop1_Iteration2
		RequestImpl(argPool[idOfArgument].arg1, argPool[idOfArgument].arg2);
		//UserCode_Section3_Loop1_Iteration2_end 

				//note that I can not set the argPool[idOfArgument].isavailable to true yet because if i did,
				//there is the possibility that that argPool[idOfArgument] might get taken up again and changed. 

	};



	///this is set as a way to set the return arg without having to do it through the 
	/// return of the "virtual RETURNARG RequestImpl(ARG1 Argument1) = 0;"  function.
	///it needs to be the same for tdus and U so that they dont have to share the same interface of RequestImpl having a RequestImpl return type.
	void SetReturnArg(RETURNTYPE returnValueToSet);

	//this is the function that will be oveeriden and implemented.  
	//UserCode_Section4_Loop1_Iteration2
	virtual void RequestImpl(ARG1 Argument1, ARG2 Argument2) = 0;
	//UserCode_Section4_Loop1_Iteration2_end 


		///this function it to clean up anything needed to be cleaned up when an
		///action request is completed.
	void ActionRequestComplete(uint16_t idOfArgument)
	{
		//if there was NOT an intend to wait, than I can finish with the argument and set it back to available
		if (argPool[idOfArgument].IntendToWait == false)
		{
			argPool[idOfArgument].IsAvailable = true;
		}

		else
		{
			//give correspondng token the semaphore back so to the AO that is waiting, can stop waiting
			xSemaphoreGive(Tokens[idOfArgument].BinarySemaphore);
		}


	}

};



template<TemplateForActionArg_NoDefaults2>
inline void ActionRequestObjectArg2<TemplateForActionArg_Args2>
::SetReturnArg(RETURNTYPE returnValueToSet)
{
	//if there was no intent to wait, then there is no need to set the return arg
	if (this->argPool[this->CurrentActionArgId].IntendToWait == false)
	{
		return;
	}

	else
	{
		this->argPool[this->CurrentActionArgId].returnArg = returnValueToSet;
	}
}


template<TemplateForActionArg_NoDefaults2 >
template<class TutilityResource>
inline void ActionRequestObjectArg2<TemplateForActionArg_Args2>
::Init(TutilityResource * utilityResource)
{

	MutexForGetActionArg = xSemaphoreCreateMutex();
	for (int i = 0; i < __POOLSIZE; i++)
	{
		argPool[i].Id = i;
		Tokens[i].Id = i;
		Tokens[i].BinarySemaphore = xSemaphoreCreateBinary();

	}
}


template<TemplateForActionArg_NoDefaults2>
inline QueueClassForActionRequest* ActionRequestObjectArg2<TemplateForActionArg_Args2>
::operator()
//UserCode_Section5_Loop1_Iteration2
(ARG1 arg1_l, ARG2 arg2, bool arg3, bool arg4, bool arg5)
//UserCode_Section5_Loop1_Iteration2_end 
{
	//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
	ActionArguments* actionArg = GetActionArgument();
	//UserCode_Section6_Loop1_Iteration2
/*if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
	{
		memcpy(&actionArg->arg1, (void*)arg1_l, sizeof(ARG1));
	}
	else
	{
		memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
	}
	if (IsArrayChecker<ARG2>::IsArgumentArray(arg2))
	{
		memcpy(&actionArg->arg2, (void*)arg2, sizeof(ARG2));
	}
	else
	{
		memcpy(&actionArg->arg2, (void*)&arg2, sizeof(ARG2));
	} */
	ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
	ArrayCheckToMemCopy<ARG2>::AEMemcpy(&actionArg->arg2, arg2, sizeof(ARG2));
	//UserCode_Section6_Loop1_Iteration2_end 
	actionArg->IntendToWait = false;

	//place that actionargument in the pool for the respective AOId 
	QueueClassForActionRequest* request = &requestPool[actionArg->Id];
	request->Argument_Id = actionArg->Id; request->ActionFunctionId = ActionRequestId;

	return request;

}
















































//-----------------------------------------------------------------------------------------------------------------------------

template<TemplateForActionArg3>
class ActionRequestObjectArg3
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;

	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;

protected:


	class ActionArguments
	{
	public:
		//UserCode_Section0_Loop1_Iteration3
		ARG1 arg1;
		ARG2 arg2;
		ARG3 arg3;
		RETURNARG returnArg;
		//UserCode_Section0_Loop1_Iteration3_end 


		uint16_t Id;
		bool IsAvailable;
		bool IntendToWait;
		ActionArguments() {
			IsAvailable = true;

		};
	};

public:

	uint16_t TypeIdOfthisClass;

	//UserCode_Section1_Loop1_Iteration3
	typedef ARG1 ARGTYPE1;
	typedef RETURNARG RETURNTYPE;
	typedef ARG2 ARGTYPE2;
	typedef ARG3 ARGTYPE3;
	typedef AENull ARGTYPE4;
	typedef AENull ARGTYPE5;
	//UserCode_Section1_Loop1_Iteration3_end 

	typedef ForwardDeclaredUtility CLASSTOPASS;

	ActionRequestObjectArg3() {
		this->TypeIdOfthisClass = 0;
	};

	uint16_t GetAOID_OfResource()
	{
		return AOID_OfResource;
	}


	RETURNARG WaitForRequestToFinish(Token* tokenOfRequest)
	{
		xSemaphoreTake(tokenOfRequest->BinarySemaphore, portMAX_DELAY);
		return argPool[tokenOfRequest->Id].returnArg;
	}

	//this is the function to call if you want to request an action but dont intend to wait
	QueueClassForActionRequest* operator()(ARG1 arg1_l, ARG2 arg2 = false, ARG3 arg3 = false, bool arg4 = false, bool arg5 = false);

	//this is the function to call if you want to request an action and DO intend to wait.
	Token* Wait(QueueClassForActionRequest& requestToReturn, ARG1 arg1_l, ARG2 arg2 = false, ARG3 arg3 = false, bool arg4 = false, bool arg5 = false) {
		//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
		ActionArguments* actionArg = GetActionArgument();
		//UserCode_Section2_Loop1_Iteration3
/*if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
		{
			memcpy(&actionArg->arg1, (void*)arg1_l, sizeof(ARG1));
		}
		else
		{
			memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
		}

		if (IsArrayChecker<ARG2>::IsArgumentArray(arg2))
		{
			memcpy(&actionArg->arg2, (void*)arg2, sizeof(ARG2));
		}
		else
		{
			memcpy(&actionArg->arg2, (void*)&arg2, sizeof(ARG2));
		}

		if (IsArrayChecker<ARG3>::IsArgumentArray(arg3))
		{
			memcpy(&actionArg->arg3, (void*)arg3, sizeof(ARG3));
		}
		else
		{
			memcpy(&actionArg->arg3, (void*)&arg3, sizeof(ARG3));
		}*/
		ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
		ArrayCheckToMemCopy<ARG2>::AEMemcpy(&actionArg->arg2, arg2, sizeof(ARG2));
		ArrayCheckToMemCopy<ARG3>::AEMemcpy(&actionArg->arg3, arg3, sizeof(ARG3));
		//UserCode_Section2_Loop1_Iteration3_end 
		actionArg->IntendToWait = true;

		//place that actionargument in the pool for the respective AOId 
		requestToReturn.Argument_Id = actionArg->Id; requestToReturn.ActionFunctionId = ActionRequestId;

		return &Tokens[requestToReturn.Argument_Id];

	};


	void DoneWithRequest(Token* tokenOfRequest)
	{

		//there shouldnt be a chance of a race condition here as only the AO has access to the argpool with the id given
		//mark arguments as available here
		//the reason why i need to do this is because I need a way for the AO to release
		// the returnArg to its pool in order to elminiate the chance of it getting used and written over.
		argPool[tokenOfRequest->Id].IsAvailable = true;

	};


protected:

	uint16_t AOID_OfResource;
	uint16_t AOID_OfCurrentRequestingAO;

	xSemaphoreHandle MutexForGetActionArg;
	ActionArguments argPool[__POOLSIZE];
	QueueClassForActionRequest requestPool[__POOLSIZE];
	Token Tokens[__POOLSIZE];

	uint16_t ActionRequestId;

	ForwardDeclaredUtility* ClassForActionRequest;

	template<class TutilityResource>
	void Init(TutilityResource*  utilityResource);

	//use this class to initialize any classes that need to be used in the action request.
	virtual void InitializeAnyClassTobeUsed(void* classToUse) {
		ClassForActionRequest = reinterpret_cast<ForwardDeclaredUtility*>(classToUse);
	};


	ActionArguments* GetActionArgument()
	{

		//the only way to rid of the mutex here is to partition the argpool to each AO.
		xSemaphoreTake(MutexForGetActionArg, portMAX_DELAY);

		for (int i = 0; i < __POOLSIZE; i++)
		{
			if (argPool[i].IsAvailable == true)
			{
				argPool[i].IsAvailable = false;
				xSemaphoreGive(MutexForGetActionArg);
				return &argPool[i];
			}
		}

		xSemaphoreGive(MutexForGetActionArg);

		//the argument pool for the action request was all used up. you may
		//need to inscrease the pool size for the action request.
		configASSERT(false);
		return nullptr;
	}


	uint16_t CurrentActionArgId;

	//this is the function that will be called by the execution task. it is one layer of misdirection to 
	//get the arguments before it executes the function.
	void Request(uint16_t idOfArgument) {

		CurrentActionArgId = idOfArgument;

		//retrieve the actionargument object from the pool and run the override implementation function.
		//UserCode_Section3_Loop1_Iteration3
		RequestImpl(argPool[idOfArgument].arg1, argPool[idOfArgument].arg2, argPool[idOfArgument].arg3);
		//UserCode_Section3_Loop1_Iteration3_end 

				//note that I can not set the argPool[idOfArgument].isavailable to true yet because if i did,
				//there is the possibility that that argPool[idOfArgument] might get taken up again and changed. 

	};



	///this is set as a way to set the return arg without having to do it through the 
	/// return of the "virtual RETURNARG RequestImpl(ARG1 Argument1) = 0;"  function.
	///it needs to be the same for tdus and U so that they dont have to share the same interface of RequestImpl having a RequestImpl return type.
	void SetReturnArg(RETURNTYPE returnValueToSet);

	//this is the function that will be oveeriden and implemented.  
	//UserCode_Section4_Loop1_Iteration3
	virtual void RequestImpl(ARG1 Argument1, ARG2 Argument2, ARG3 Argument3) = 0;
	//UserCode_Section4_Loop1_Iteration3_end 


		///this function it to clean up anything needed to be cleaned up when an
		///action request is completed.
	void ActionRequestComplete(uint16_t idOfArgument)
	{
		//if there was NOT an intend to wait, than I can finish with the argument and set it back to available
		if (argPool[idOfArgument].IntendToWait == false)
		{
			argPool[idOfArgument].IsAvailable = true;
		}

		else
		{
			//give correspondng token the semaphore back so to the AO that is waiting, can stop waiting
			xSemaphoreGive(Tokens[idOfArgument].BinarySemaphore);
		}


	}

};



template<TemplateForActionArg_NoDefaults3>
inline void ActionRequestObjectArg3<TemplateForActionArg_Args3>
::SetReturnArg(RETURNTYPE returnValueToSet)
{
	//if there was no intent to wait, then there is no need to set the return arg
	if (this->argPool[this->CurrentActionArgId].IntendToWait == false)
	{
		return;
	}

	else
	{
		this->argPool[this->CurrentActionArgId].returnArg = returnValueToSet;
	}
}


template<TemplateForActionArg_NoDefaults3 >
template<class TutilityResource>
inline void ActionRequestObjectArg3<TemplateForActionArg_Args3>
::Init(TutilityResource * utilityResource)
{

	MutexForGetActionArg = xSemaphoreCreateMutex();
	for (int i = 0; i < __POOLSIZE; i++)
	{
		argPool[i].Id = i;
		Tokens[i].Id = i;
		Tokens[i].BinarySemaphore = xSemaphoreCreateBinary();

	}
}


template<TemplateForActionArg_NoDefaults3>
inline QueueClassForActionRequest* ActionRequestObjectArg3<TemplateForActionArg_Args3>
::operator()
//UserCode_Section5_Loop1_Iteration3
(ARG1 arg1_l, ARG2 arg2, ARG3 arg3, bool arg4, bool arg5)
//UserCode_Section5_Loop1_Iteration3_end 
{
	//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
	ActionArguments* actionArg = GetActionArgument();
	//UserCode_Section6_Loop1_Iteration3
/*
	if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
	{
		memcpy(&actionArg->arg1, (void*)arg1_l, sizeof(ARG1));
	}
	else
	{
		memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
	}

	if (IsArrayChecker<ARG2>::IsArgumentArray(arg2))
	{
		memcpy(&actionArg->arg2, (void*)arg2, sizeof(ARG2));
	}
	else
	{
		memcpy(&actionArg->arg2, (void*)&arg2, sizeof(ARG2));
	}

	if (IsArrayChecker<ARG3>::IsArgumentArray(arg3))
	{
		memcpy(&actionArg->arg3, (void*)arg3, sizeof(ARG3));
	}
	else
	{
		memcpy(&actionArg->arg3, (void*)&arg3, sizeof(ARG3));
	}*/

	ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
	ArrayCheckToMemCopy<ARG2>::AEMemcpy(&actionArg->arg2, arg2, sizeof(ARG2));
	ArrayCheckToMemCopy<ARG3>::AEMemcpy(&actionArg->arg3, arg3, sizeof(ARG3));


	//actionArg->arg1 =  arg1_l;
	//actionArg->arg2 = arg2;
	//actionArg->arg3 = arg3;
//UserCode_Section6_Loop1_Iteration3_end 
	actionArg->IntendToWait = false;

	//place that actionargument in the pool for the respective AOId 
	QueueClassForActionRequest* request = &requestPool[actionArg->Id];
	request->Argument_Id = actionArg->Id; request->ActionFunctionId = ActionRequestId;

	return request;

}
















































//-----------------------------------------------------------------------------------------------------------------------------

template<TemplateForActionArg4>
class ActionRequestObjectArg4
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;

	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;

protected:


	class ActionArguments
	{
	public:
		//UserCode_Section0_Loop1_Iteration4
		ARG1 arg1;
		ARG2 arg2;
		ARG3 arg3;
		ARG4 arg4;
		RETURNARG returnArg;
		//UserCode_Section0_Loop1_Iteration4_end 


		uint16_t Id;
		bool IsAvailable;
		bool IntendToWait;
		ActionArguments() {
			IsAvailable = true;

		};
	};

public:

	uint16_t TypeIdOfthisClass;

	//UserCode_Section1_Loop1_Iteration4
	typedef ARG1 ARGTYPE1;
	typedef RETURNARG RETURNTYPE;
	typedef ARG2 ARGTYPE2;
	typedef ARG3 ARGTYPE3;
	typedef ARG4 ARGTYPE4;
	typedef AENull ARGTYPE5;
	//UserCode_Section1_Loop1_Iteration4_end 

	typedef ForwardDeclaredUtility CLASSTOPASS;

	ActionRequestObjectArg4() {
		this->TypeIdOfthisClass = 0;
	};

	uint16_t GetAOID_OfResource()
	{
		return AOID_OfResource;
	}


	RETURNARG WaitForRequestToFinish(Token* tokenOfRequest)
	{
		xSemaphoreTake(tokenOfRequest->BinarySemaphore, portMAX_DELAY);
		return argPool[tokenOfRequest->Id].returnArg;
	}

	//this is the function to call if you want to request an action but dont intend to wait
	QueueClassForActionRequest* operator()(ARG1 arg1_l, ARG2 arg2 = false, ARG3 arg3 = false, ARG4 arg4 = false, bool arg5 = false);

	//this is the function to call if you want to request an action and DO intend to wait.
	Token* Wait(QueueClassForActionRequest& requestToReturn, ARG1 arg1_l, ARG2 arg2 = false, ARG3 arg3 = false, ARG4 arg4 = false, bool arg5 = false) {
		//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
		ActionArguments* actionArg = GetActionArgument();
		//UserCode_Section2_Loop1_Iteration4
/*
		if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
		{
			memcpy(&actionArg->arg1, (void*)arg1_l, sizeof(ARG1));
		}
		else
		{
			memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
		}

		if (IsArrayChecker<ARG2>::IsArgumentArray(arg2))
		{
			memcpy(&actionArg->arg2, (void*)arg2, sizeof(ARG2));
		}
		else
		{
			memcpy(&actionArg->arg2, (void*)&arg2, sizeof(ARG2));
		}

		if (IsArrayChecker<ARG3>::IsArgumentArray(arg3))
		{
			memcpy(&actionArg->arg3, (void*)arg3, sizeof(ARG3));
		}
		else
		{
			memcpy(&actionArg->arg3, (void*)&arg3, sizeof(ARG3));
		}

		if (IsArrayChecker<ARG4>::IsArgumentArray(arg4))
		{
			memcpy(&actionArg->arg4, (void*)arg4, sizeof(ARG4));
		}
		else
		{
			memcpy(&actionArg->arg4, (void*)&arg4, sizeof(ARG4));
		}
		 */

		ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
		ArrayCheckToMemCopy<ARG2>::AEMemcpy(&actionArg->arg2, arg2, sizeof(ARG2));
		ArrayCheckToMemCopy<ARG3>::AEMemcpy(&actionArg->arg3, arg3, sizeof(ARG3));
		ArrayCheckToMemCopy<ARG4>::AEMemcpy(&actionArg->arg4, arg4, sizeof(ARG4));
		//UserCode_Section2_Loop1_Iteration4_end 
		actionArg->IntendToWait = true;

		//place that actionargument in the pool for the respective AOId 
		requestToReturn.Argument_Id = actionArg->Id; requestToReturn.ActionFunctionId = ActionRequestId;

		return &Tokens[requestToReturn.Argument_Id];

	};


	void DoneWithRequest(Token* tokenOfRequest)
	{

		//there shouldnt be a chance of a race condition here as only the AO has access to the argpool with the id given
		//mark arguments as available here
		//the reason why i need to do this is because I need a way for the AO to release
		// the returnArg to its pool in order to elminiate the chance of it getting used and written over.
		argPool[tokenOfRequest->Id].IsAvailable = true;

	};


protected:

	uint16_t AOID_OfResource;
	uint16_t AOID_OfCurrentRequestingAO;

	xSemaphoreHandle MutexForGetActionArg;
	ActionArguments argPool[__POOLSIZE];
	QueueClassForActionRequest requestPool[__POOLSIZE];
	Token Tokens[__POOLSIZE];

	uint16_t ActionRequestId;

	ForwardDeclaredUtility* ClassForActionRequest;

	template<class TutilityResource>
	void Init(TutilityResource*  utilityResource);

	//use this class to initialize any classes that need to be used in the action request.
	virtual void InitializeAnyClassTobeUsed(void* classToUse) {
		ClassForActionRequest = reinterpret_cast<ForwardDeclaredUtility*>(classToUse);
	};


	ActionArguments* GetActionArgument()
	{

		//the only way to rid of the mutex here is to partition the argpool to each AO.
		xSemaphoreTake(MutexForGetActionArg, portMAX_DELAY);

		for (int i = 0; i < __POOLSIZE; i++)
		{
			if (argPool[i].IsAvailable == true)
			{
				argPool[i].IsAvailable = false;
				xSemaphoreGive(MutexForGetActionArg);
				return &argPool[i];
			}
		}

		xSemaphoreGive(MutexForGetActionArg);

		//the argument pool for the action request was all used up. you may
		//need to inscrease the pool size for the action request.
		configASSERT(false);
		return nullptr;
	}


	uint16_t CurrentActionArgId;

	//this is the function that will be called by the execution task. it is one layer of misdirection to 
	//get the arguments before it executes the function.
	void Request(uint16_t idOfArgument) {

		CurrentActionArgId = idOfArgument;

		//retrieve the actionargument object from the pool and run the override implementation function.
		//UserCode_Section3_Loop1_Iteration4
		RequestImpl(argPool[idOfArgument].arg1, argPool[idOfArgument].arg2, argPool[idOfArgument].arg3, argPool[idOfArgument].arg4);
		//UserCode_Section3_Loop1_Iteration4_end 

				//note that I can not set the argPool[idOfArgument].isavailable to true yet because if i did,
				//there is the possibility that that argPool[idOfArgument] might get taken up again and changed. 

	};



	///this is set as a way to set the return arg without having to do it through the 
	/// return of the "virtual RETURNARG RequestImpl(ARG1 Argument1) = 0;"  function.
	///it needs to be the same for tdus and U so that they dont have to share the same interface of RequestImpl having a RequestImpl return type.
	void SetReturnArg(RETURNTYPE returnValueToSet);

	//this is the function that will be oveeriden and implemented.  
	//UserCode_Section4_Loop1_Iteration4
	virtual void RequestImpl(ARG1 Argument1, ARG2 Argument2, ARG3 Argument3, ARG4 Argument4) = 0;
	//UserCode_Section4_Loop1_Iteration4_end 


		///this function it to clean up anything needed to be cleaned up when an
		///action request is completed.
	void ActionRequestComplete(uint16_t idOfArgument)
	{
		//if there was NOT an intend to wait, than I can finish with the argument and set it back to available
		if (argPool[idOfArgument].IntendToWait == false)
		{
			argPool[idOfArgument].IsAvailable = true;
		}

		else
		{
			//give correspondng token the semaphore back so to the AO that is waiting, can stop waiting
			xSemaphoreGive(Tokens[idOfArgument].BinarySemaphore);
		}


	}

};



template<TemplateForActionArg_NoDefaults4>
inline void ActionRequestObjectArg4<TemplateForActionArg_Args4>
::SetReturnArg(RETURNTYPE returnValueToSet)
{
	//if there was no intent to wait, then there is no need to set the return arg
	if (this->argPool[this->CurrentActionArgId].IntendToWait == false)
	{
		return;
	}

	else
	{
		this->argPool[this->CurrentActionArgId].returnArg = returnValueToSet;
	}
}


template<TemplateForActionArg_NoDefaults4 >
template<class TutilityResource>
inline void ActionRequestObjectArg4<TemplateForActionArg_Args4>
::Init(TutilityResource * utilityResource)
{

	MutexForGetActionArg = xSemaphoreCreateMutex();
	for (int i = 0; i < __POOLSIZE; i++)
	{
		argPool[i].Id = i;
		Tokens[i].Id = i;
		Tokens[i].BinarySemaphore = xSemaphoreCreateBinary();

	}
}


template<TemplateForActionArg_NoDefaults4>
inline QueueClassForActionRequest* ActionRequestObjectArg4<TemplateForActionArg_Args4>
::operator()
//UserCode_Section5_Loop1_Iteration4
(ARG1 arg1_l, ARG2 arg2, ARG3 arg3, ARG4 arg4, bool arg5)
//UserCode_Section5_Loop1_Iteration4_end 
{
	//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
	ActionArguments* actionArg = GetActionArgument();
	//UserCode_Section6_Loop1_Iteration4
/*
	if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
	{
		memcpy(&actionArg->arg1, (void*)arg1_l, sizeof(ARG1));
	}
	else
	{
		memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
	}

	if (IsArrayChecker<ARG2>::IsArgumentArray(arg2))
	{
		memcpy(&actionArg->arg2, (void*)arg2, sizeof(ARG2));
	}
	else
	{
		memcpy(&actionArg->arg2, (void*)&arg2, sizeof(ARG2));
	}

	if (IsArrayChecker<ARG3>::IsArgumentArray(arg3))
	{
		memcpy(&actionArg->arg3, (void*)arg3, sizeof(ARG3));
	}
	else
	{
		memcpy(&actionArg->arg3, (void*)&arg3, sizeof(ARG3));
	}

	if (IsArrayChecker<ARG4>::IsArgumentArray(arg4))
	{
		memcpy(&actionArg->arg4, (void*)arg4, sizeof(ARG4));
	}
	else
	{
		memcpy(&actionArg->arg4, (void*)&arg4, sizeof(ARG4));
	}
	 */
	ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
	ArrayCheckToMemCopy<ARG2>::AEMemcpy(&actionArg->arg2, arg2, sizeof(ARG2));
	ArrayCheckToMemCopy<ARG3>::AEMemcpy(&actionArg->arg3, arg3, sizeof(ARG3));
	ArrayCheckToMemCopy<ARG4>::AEMemcpy(&actionArg->arg4, arg4, sizeof(ARG4));
	//UserCode_Section6_Loop1_Iteration4_end 
	actionArg->IntendToWait = false;

	//place that actionargument in the pool for the respective AOId 
	QueueClassForActionRequest* request = &requestPool[actionArg->Id];
	request->Argument_Id = actionArg->Id; request->ActionFunctionId = ActionRequestId;

	return request;

}
















































//-----------------------------------------------------------------------------------------------------------------------------

template<TemplateForActionArg5>
class ActionRequestObjectArg5
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;

	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;

protected:


	class ActionArguments
	{
	public:
		//UserCode_Section0_Loop1_Iteration5
		ARG1 arg1;
		ARG2 arg2;
		ARG3 arg3;
		ARG4 arg4;
		ARG5 arg5;
		RETURNARG returnArg;
		//UserCode_Section0_Loop1_Iteration5_end 


		uint16_t Id;
		bool IsAvailable;
		bool IntendToWait;
		ActionArguments() {
			IsAvailable = true;

		};
	};

public:

	uint16_t TypeIdOfthisClass;

	//UserCode_Section1_Loop1_Iteration5
	typedef ARG1 ARGTYPE1;
	typedef RETURNARG RETURNTYPE;
	typedef ARG2 ARGTYPE2;
	typedef ARG3 ARGTYPE3;
	typedef ARG4 ARGTYPE4;
	typedef ARG5 ARGTYPE5;
	//UserCode_Section1_Loop1_Iteration5_end 

	typedef ForwardDeclaredUtility CLASSTOPASS;

	ActionRequestObjectArg5() {
		this->TypeIdOfthisClass = 0;
	};

	uint16_t GetAOID_OfResource()
	{
		return AOID_OfResource;
	}


	RETURNARG WaitForRequestToFinish(Token* tokenOfRequest)
	{
		xSemaphoreTake(tokenOfRequest->BinarySemaphore, portMAX_DELAY);
		return argPool[tokenOfRequest->Id].returnArg;
	}

	//this is the function to call if you want to request an action but dont intend to wait
	QueueClassForActionRequest* operator()(ARG1 arg1_l, ARG2 arg2 = false, ARG3 arg3 = false, ARG4 arg4 = false, ARG5 arg5 = false);

	//this is the function to call if you want to request an action and DO intend to wait.
	Token* Wait(QueueClassForActionRequest& requestToReturn, ARG1 arg1_l, ARG2 arg2 = false, ARG3 arg3 = false, ARG4 arg4 = false, ARG5 arg5 = false) {
		//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
		ActionArguments* actionArg = GetActionArgument();
		//UserCode_Section2_Loop1_Iteration5
/*
		if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
		{
			memcpy(&actionArg->arg1, (void*)arg1_l, sizeof(ARG1));
		}
		else
		{
			memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
		}

		if (IsArrayChecker<ARG2>::IsArgumentArray(arg2))
		{
			memcpy(&actionArg->arg2, (void*)arg2, sizeof(ARG2));
		}
		else
		{
			memcpy(&actionArg->arg2, (void*)&arg2, sizeof(ARG2));
		}

		if (IsArrayChecker<ARG3>::IsArgumentArray(arg3))
		{
			memcpy(&actionArg->arg3, (void*)arg3, sizeof(ARG3));
		}
		else
		{
			memcpy(&actionArg->arg3, (void*)&arg3, sizeof(ARG3));
		}

		if (IsArrayChecker<ARG4>::IsArgumentArray(arg4))
		{
			memcpy(&actionArg->arg4, (void*)arg4, sizeof(ARG4));
		}
		else
		{
			memcpy(&actionArg->arg4, (void*)&arg4, sizeof(ARG4));
		}

		if (IsArrayChecker<ARG5>::IsArgumentArray(arg5))
		{
			memcpy(&actionArg->arg5, (void*)arg5, sizeof(ARG5));
		}
		else
		{
			memcpy(&actionArg->arg5, (void*)&arg5, sizeof(ARG5));
		}*/
		ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
		ArrayCheckToMemCopy<ARG2>::AEMemcpy(&actionArg->arg2, arg2, sizeof(ARG2));
		ArrayCheckToMemCopy<ARG3>::AEMemcpy(&actionArg->arg3, arg3, sizeof(ARG3));
		ArrayCheckToMemCopy<ARG4>::AEMemcpy(&actionArg->arg4, arg4, sizeof(ARG4));
		ArrayCheckToMemCopy<ARG5>::AEMemcpy(&actionArg->arg5, arg5, sizeof(ARG5));
		//UserCode_Section2_Loop1_Iteration5_end 
		actionArg->IntendToWait = true;

		//place that actionargument in the pool for the respective AOId 
		requestToReturn.Argument_Id = actionArg->Id; requestToReturn.ActionFunctionId = ActionRequestId;

		return &Tokens[requestToReturn.Argument_Id];

	};


	void DoneWithRequest(Token* tokenOfRequest)
	{

		//there shouldnt be a chance of a race condition here as only the AO has access to the argpool with the id given
		//mark arguments as available here
		//the reason why i need to do this is because I need a way for the AO to release
		// the returnArg to its pool in order to elminiate the chance of it getting used and written over.
		argPool[tokenOfRequest->Id].IsAvailable = true;

	};


protected:

	uint16_t AOID_OfResource;
	uint16_t AOID_OfCurrentRequestingAO;

	xSemaphoreHandle MutexForGetActionArg;
	ActionArguments argPool[__POOLSIZE];
	QueueClassForActionRequest requestPool[__POOLSIZE];
	Token Tokens[__POOLSIZE];

	uint16_t ActionRequestId;

	ForwardDeclaredUtility* ClassForActionRequest;

	template<class TutilityResource>
	void Init(TutilityResource*  utilityResource);

	//use this class to initialize any classes that need to be used in the action request.
	virtual void InitializeAnyClassTobeUsed(void* classToUse) {
		ClassForActionRequest = reinterpret_cast<ForwardDeclaredUtility*>(classToUse);
	};


	ActionArguments* GetActionArgument()
	{

		//the only way to rid of the mutex here is to partition the argpool to each AO.
		xSemaphoreTake(MutexForGetActionArg, portMAX_DELAY);

		for (int i = 0; i < __POOLSIZE; i++)
		{
			if (argPool[i].IsAvailable == true)
			{
				argPool[i].IsAvailable = false;
				xSemaphoreGive(MutexForGetActionArg);
				return &argPool[i];
			}
		}

		xSemaphoreGive(MutexForGetActionArg);

		//the argument pool for the action request was all used up. you may
		//need to inscrease the pool size for the action request.
		configASSERT(false);
		return nullptr;
	}


	uint16_t CurrentActionArgId;

	//this is the function that will be called by the execution task. it is one layer of misdirection to 
	//get the arguments before it executes the function.
	void Request(uint16_t idOfArgument) {

		CurrentActionArgId = idOfArgument;

		//retrieve the actionargument object from the pool and run the override implementation function.
		//UserCode_Section3_Loop1_Iteration5
		RequestImpl(argPool[idOfArgument].arg1, argPool[idOfArgument].arg2, argPool[idOfArgument].arg3, argPool[idOfArgument].arg4, argPool[idOfArgument].arg5);
		//UserCode_Section3_Loop1_Iteration5_end 

				//note that I can not set the argPool[idOfArgument].isavailable to true yet because if i did,
				//there is the possibility that that argPool[idOfArgument] might get taken up again and changed. 

	};



	///this is set as a way to set the return arg without having to do it through the 
	/// return of the "virtual RETURNARG RequestImpl(ARG1 Argument1) = 0;"  function.
	///it needs to be the same for tdus and U so that they dont have to share the same interface of RequestImpl having a RequestImpl return type.
	void SetReturnArg(RETURNTYPE returnValueToSet);

	//this is the function that will be oveeriden and implemented.  
	//UserCode_Section4_Loop1_Iteration5
	virtual void RequestImpl(ARG1 Argument1, ARG2 Argument2, ARG3 Argument3, ARG4 Argument4, ARG5 Argument5) = 0;
	//UserCode_Section4_Loop1_Iteration5_end 


		///this function it to clean up anything needed to be cleaned up when an
		///action request is completed.
	void ActionRequestComplete(uint16_t idOfArgument)
	{
		//if there was NOT an intend to wait, than I can finish with the argument and set it back to available
		if (argPool[idOfArgument].IntendToWait == false)
		{
			argPool[idOfArgument].IsAvailable = true;
		}

		else
		{
			//give correspondng token the semaphore back so to the AO that is waiting, can stop waiting
			xSemaphoreGive(Tokens[idOfArgument].BinarySemaphore);
		}


	}

};



template<TemplateForActionArg_NoDefaults5>
inline void ActionRequestObjectArg5<TemplateForActionArg_Args5>
::SetReturnArg(RETURNTYPE returnValueToSet)
{
	//if there was no intent to wait, then there is no need to set the return arg
	if (this->argPool[this->CurrentActionArgId].IntendToWait == false)
	{
		return;
	}

	else
	{
		this->argPool[this->CurrentActionArgId].returnArg = returnValueToSet;
	}
}


template<TemplateForActionArg_NoDefaults5 >
template<class TutilityResource>
inline void ActionRequestObjectArg5<TemplateForActionArg_Args5>
::Init(TutilityResource * utilityResource)
{

	MutexForGetActionArg = xSemaphoreCreateMutex();
	for (int i = 0; i < __POOLSIZE; i++)
	{
		argPool[i].Id = i;
		Tokens[i].Id = i;
		Tokens[i].BinarySemaphore = xSemaphoreCreateBinary();

	}
}


template<TemplateForActionArg_NoDefaults5>
inline QueueClassForActionRequest* ActionRequestObjectArg5<TemplateForActionArg_Args5>
::operator()
//UserCode_Section5_Loop1_Iteration5
(ARG1 arg1_l, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
//UserCode_Section5_Loop1_Iteration5_end 
{
	//I need to create an actionrequest object to throw into a queue that 
	//will be used to get back the arguments stored when the implementation is 
	//actually executed.

	//get a actionargument object from the pool and fill it
	ActionArguments* actionArg = GetActionArgument();
	//UserCode_Section6_Loop1_Iteration5
/*
	if (IsArrayChecker<ARG1>::IsArgumentArray(arg1_l))
	{
		memcpy(&actionArg->arg1, (void*)arg1_l, sizeof(ARG1));
	}
	else
	{
		memcpy(&actionArg->arg1, (void*)&arg1_l, sizeof(ARG1));
	}

	if (IsArrayChecker<ARG2>::IsArgumentArray(arg2))
	{
		memcpy(&actionArg->arg2, (void*)arg2, sizeof(ARG2));
	}
	else
	{
		memcpy(&actionArg->arg2, (void*)&arg2, sizeof(ARG2));
	}

	if (IsArrayChecker<ARG3>::IsArgumentArray(arg3))
	{
		memcpy(&actionArg->arg3, (void*)arg3, sizeof(ARG3));
	}
	else
	{
		memcpy(&actionArg->arg3, (void*)&arg3, sizeof(ARG3));
	}

	if (IsArrayChecker<ARG4>::IsArgumentArray(arg4))
	{
		memcpy(&actionArg->arg4, (void*)arg4, sizeof(ARG4));
	}
	else
	{
		memcpy(&actionArg->arg4, (void*)&arg4, sizeof(ARG4));
	}

	if (IsArrayChecker<ARG5>::IsArgumentArray(arg5))
	{
		memcpy(&actionArg->arg5, (void*)arg5, sizeof(ARG5));
	}
	else
	{
		memcpy(&actionArg->arg5, (void*)&arg5, sizeof(ARG5));
	}*/

	ArrayCheckToMemCopy<ARG1>::AEMemcpy(&actionArg->arg1, arg1_l, sizeof(ARG1));
	ArrayCheckToMemCopy<ARG2>::AEMemcpy(&actionArg->arg2, arg2, sizeof(ARG2));
	ArrayCheckToMemCopy<ARG3>::AEMemcpy(&actionArg->arg3, arg3, sizeof(ARG3));
	ArrayCheckToMemCopy<ARG4>::AEMemcpy(&actionArg->arg4, arg4, sizeof(ARG4));
	ArrayCheckToMemCopy<ARG5>::AEMemcpy(&actionArg->arg5, arg5, sizeof(ARG5));
	//UserCode_Section6_Loop1_Iteration5_end 
	actionArg->IntendToWait = false;

	//place that actionargument in the pool for the respective AOId 
	QueueClassForActionRequest* request = &requestPool[actionArg->Id];
	request->Argument_Id = actionArg->Id; request->ActionFunctionId = ActionRequestId;

	return request;

}
















































//-----------------------------------------------------------------------------------------------------------------------------

