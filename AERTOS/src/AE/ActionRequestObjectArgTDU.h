//generated file: ActionArgGeneratedTDU.h


#pragma once

#include "FreeRTOS.h"
#include "AEUtils.h"

#include "ActionRequestObjectArg.h"
#include "AEEventBase.h"

#include "AEPublishSubscribeManager.h"

#include "AEAO.h"


typedef void(*CallBackForWaitForEvt_t)(void*, AEEventDiscriminator_t*);
typedef void(*CallBackForWaitTimeOut_t)(void*);
 
	
template<TemplateForActionArgTDU1>
class ActionRequestObjectArgTDU1 : public ActionRequestObjectArg1<TemplateForActionArgTDU_Args1>
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOResourceService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOUpdateable;
	
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AEAOUpdateableAAP;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AETDUAsPossession;
	template<TemplateFor_AEAOUpdateableAAS_NoDefaults_friend>
	friend class AEAOUpdateableAAS;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;
public:
	ActionRequestObjectArgTDU1() {
		IsWaitingForEvent = false;
	};
	
	
	//returns true if the event it was waiting on happened, otherwise returns false if it timedout
	template <uint16_t Tevt>
		bool WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec = 0xffffffff);

	//this will wait for an event with a timeout, if a timeout occurs, it will call the callbackTimeout and attempt to wait again
	//a number of times that you designate. if a event was found, it will return true, otherwise if it timedout all attempts to wait, it returns false.
	template <uint16_t Tevt>
		bool WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt);

	

	//this is the function that ets the parameters for the initiation of the actionrequest to start updating. 
//protected:	typedef void(*SetServiceReqFunc)(ForwardDeclaredTDU* p, ARG1 Argument1);
protected: typedef void(*CancelCleanUp_fptr)(ForwardDeclaredTDU* p);
protected:	CancelCleanUp_fptr _CancelCleanUp = nullptr;
public: void SetCancelCleanUpFunc(CancelCleanUp_fptr s) {this->_CancelCleanUp = s; }	
	typedef bool(*UpdateFunc)(ForwardDeclaredTDU* p, ARG1 Argument1);
//public: void SetServiceFunc(SetServiceReqFunc s) {_RequestImpl = s; }
public: void SetUpdateFunc(UpdateFunc s) {this->_Update = s; }		
protected:

	
	//virtual void RequestImpl(ARG1 Argument1) = 0;
	//this is the function that will continueally by called while updating.
	//virtual bool Update() = 0;


	
protected:
	 

	bool IsWaitingForEvent;

	AEEventDiscriminator_t* EvtWaitingFor;
	//QueueHandle_t* QueueExecuteForEvtOfTDU_ptr;
	xSemaphoreHandle* BinarySemaphoreForEventListening_ptr;

	void PostEvtToRequestingAO(AEEventBase * const evtToPost);
	void PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost);


	void CancelCleanUp() ;

	float* LinkedSPBData;
	float _frequencyIUpdateAt;

};

template<TemplateForActionArgTDU_NoDefaults1>
inline void ActionRequestObjectArgTDU1<TemplateForActionArgTDU_Args1>::CancelCleanUp() 
{
	//this CancelCleanUp needs to be implemented for the action request you tries to cancel
	configASSERT(_CancelCleanUp != nullptr);
	
	this->_CancelCleanUp(this->ClassForActionRequest);
}

template<TemplateForActionArgTDU_NoDefaults1>
inline void ActionRequestObjectArgTDU1<TemplateForActionArgTDU_Args1>::PostEvtToRequestingAO(AEEventBase * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}
template<TemplateForActionArgTDU_NoDefaults1>
inline void ActionRequestObjectArgTDU1<TemplateForActionArgTDU_Args1>::PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}



template<TemplateForActionArgTDU_NoDefaults1>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU1<TemplateForActionArgTDU_Args1>::WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt)
{
	//you ned to attempt at least 1 time to wait for an event
	configASSERT(numOfAttempts > 0);

	//first attempt the first wait
	bool eventFound = false;
	eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
	if (eventFound == false)
	{

		//go through the amount of times designated 
		for (uint16_t i = 0; i < numOfAttempts - 1; i++)
		{
			//call the callback for a timeoutattempt
			callBackForTimeOutAttempt(this);
			//now wait for the event
			eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
			if (eventFound == true)
			{
				return eventFound;
			}
		}

	}
	return eventFound;

}

template<TemplateForActionArgTDU_NoDefaults1>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU1<TemplateForActionArgTDU_Args1>::WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec)
{
	//first I need to subscribe to the event 
	PublishSubscribeManager->_SubscribeToEvt(Tevt, this->AOID_OfResource);// EventSubscribers[Tevt][this->AOID_OfResource] = true;
	IsWaitingForEvent = true;
	//check for if user wants a timeout
	if (timeoutMillisec == 0xffffffff)
	{
		xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, portMAX_DELAY);
	}
	else
	{
		auto ticks = AE_Tick_To_Milli(timeoutMillisec);
		BaseType_t wasThereAnEvent = xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, ticks);

		//if it timeout, unsubscribe and return false
		if (wasThereAnEvent == pdFALSE)
		{
			IsWaitingForEvent = false;
			PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);
			return false;
		}

	}
	IsWaitingForEvent = false;

	if (callBackWhenEvtPublishes != nullptr)
	{
		callBackWhenEvtPublishes(this, EvtWaitingFor);
	}

	//after the callback is done with the reference, decrement the counter
	if (EvtWaitingFor->type == 1)
	{
		EvtWaitingFor->evt->DecrementRefCounter();
	}

	//after being, give semaphore back and unsubscribe
	PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);

}




template<TemplateForActionArgTDU2>
class ActionRequestObjectArgTDU2 : public ActionRequestObjectArg2<TemplateForActionArgTDU_Args2>
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOResourceService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOUpdateable;
	
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AEAOUpdateableAAP;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AETDUAsPossession;
	template<TemplateFor_AEAOUpdateableAAS_NoDefaults_friend>
	friend class AEAOUpdateableAAS;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;
public:
	ActionRequestObjectArgTDU2() {
		IsWaitingForEvent = false;
	};

	//this is the function that ets the parameters for the initiation of the actionrequest to start updating.
//	virtual void RequestImpl(ARG1 Argument1, ARG2 Argument2) = 0;
	//this is the function that will continueally by called while updating.
	//virtual bool Update() = 0;
protected: typedef void(*CancelCleanUp_fptr)(ForwardDeclaredTDU* p);
protected:	CancelCleanUp_fptr _CancelCleanUp = nullptr;
public: void SetCancelCleanUpFunc(CancelCleanUp_fptr s) {this->_CancelCleanUp = s; }	
protected: typedef bool(*UpdateFunc)(ForwardDeclaredTDU* p, ARG1 Argument1, ARG2 Argument2);
	//public: void SetServiceFunc(SetServiceReqFunc s) {_RequestImpl = s; }
public: void SetUpdateFunc(UpdateFunc s) {this->_Update = s; }		


	//returns true if the event it was waiting on happened, otherwise returns false if it timedout
	template <uint16_t Tevt>
		bool WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec = 0xffffffff);

	//this will wait for an event with a timeout, if a timeout occurs, it will call the callbackTimeout and attempt to wait again
	//a number of times that you designate. if a event was found, it will return true, otherwise if it timedout all attempts to wait, it returns false.
	template <uint16_t Tevt>
		bool WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt);

	
	
protected:
	 

	bool IsWaitingForEvent;

	AEEventDiscriminator_t* EvtWaitingFor;
	//QueueHandle_t* QueueExecuteForEvtOfTDU_ptr;
	xSemaphoreHandle* BinarySemaphoreForEventListening_ptr;

	void PostEvtToRequestingAO(AEEventBase * const evtToPost);
	void PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost);


	void CancelCleanUp()  ;

	float* LinkedSPBData;
	float _frequencyIUpdateAt;

};

template<TemplateForActionArgTDU_NoDefaults2>
inline void ActionRequestObjectArgTDU2<TemplateForActionArgTDU_Args2>::CancelCleanUp()
{
	//this CancelCleanUp needs to be implemented for the action request you tries to cancel
	configASSERT(_CancelCleanUp != nullptr);
	
	this->_CancelCleanUp(this->ClassForActionRequest);
}

template<TemplateForActionArgTDU_NoDefaults2>
inline void ActionRequestObjectArgTDU2<TemplateForActionArgTDU_Args2>::PostEvtToRequestingAO(AEEventBase * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}
template<TemplateForActionArgTDU_NoDefaults2>
inline void ActionRequestObjectArgTDU2<TemplateForActionArgTDU_Args2>::PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}



template<TemplateForActionArgTDU_NoDefaults2>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU2<TemplateForActionArgTDU_Args2>::WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt)
{
	//you ned to attempt at least 1 time to wait for an event
	configASSERT(numOfAttempts > 0);

	//first attempt the first wait
	bool eventFound = false;
	eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
	if (eventFound == false)
	{

		//go through the amount of times designated 
		for (uint16_t i = 0; i < numOfAttempts - 1; i++)
		{
			//call the callback for a timeoutattempt
			callBackForTimeOutAttempt(this);
			//now wait for the event
			eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
			if (eventFound == true)
			{
				return eventFound;
			}
		}

	}
	return eventFound;

}

template<TemplateForActionArgTDU_NoDefaults2>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU2<TemplateForActionArgTDU_Args2>::WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec)
{
	//first I need to subscribe to the event 
	PublishSubscribeManager->_SubscribeToEvt(Tevt, this->AOID_OfResource);// EventSubscribers[Tevt][this->AOID_OfResource] = true;
	IsWaitingForEvent = true;
	//check for if user wants a timeout
	if (timeoutMillisec == 0xffffffff)
	{
		xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, portMAX_DELAY);
	}
	else
	{
		auto ticks = AE_Tick_To_Milli(timeoutMillisec);
		BaseType_t wasThereAnEvent = xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, ticks);

		//if it timeout, unsubscribe and return false
		if (wasThereAnEvent == pdFALSE)
		{
			IsWaitingForEvent = false;
			PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);
			return false;
		}

	}
	IsWaitingForEvent = false;

	if (callBackWhenEvtPublishes != nullptr)
	{
		callBackWhenEvtPublishes(this, EvtWaitingFor);
	}

	//after the callback is done with the reference, decrement the counter
	if (EvtWaitingFor->type == 1)
	{
		EvtWaitingFor->evt->DecrementRefCounter();
	}

	//after being, give semaphore back and unsubscribe
	PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);
        
        return true;

}




template<TemplateForActionArgTDU3>
class ActionRequestObjectArgTDU3 : public ActionRequestObjectArg3<TemplateForActionArgTDU_Args3>
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOResourceService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOUpdateable;
	
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AEAOUpdateableAAP;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AETDUAsPossession;
	template<TemplateFor_AEAOUpdateableAAS_NoDefaults_friend>
	friend class AEAOUpdateableAAS;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;
public:
	ActionRequestObjectArgTDU3() {
		IsWaitingForEvent = false;
	};

	//this is the function that ets the parameters for the initiation of the actionrequest to start updating.
//	virtual void RequestImpl(ARG1 Argument1, ARG2 Argument2, ARG3 Argument3) = 0;
	//this is the function that will continueally by called while updating.
	//virtual bool Update() = 0;
protected: typedef void(*CancelCleanUp_fptr)(ForwardDeclaredTDU* p);
protected:	CancelCleanUp_fptr _CancelCleanUp = nullptr;
public: void SetCancelCleanUpFunc(CancelCleanUp_fptr s) {this->_CancelCleanUp = s; }	
protected: typedef bool(*UpdateFunc)(ForwardDeclaredTDU* p, ARG1 Argument1, ARG2 Argument22, ARG3 Argument3);
	//public: void SetServiceFunc(SetServiceReqFunc s) {_RequestImpl = s; }
public: void SetUpdateFunc(UpdateFunc s) {this->_Update = s; }		


	//returns true if the event it was waiting on happened, otherwise returns false if it timedout
	template <uint16_t Tevt>
		bool WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec = 0xffffffff);

	//this will wait for an event with a timeout, if a timeout occurs, it will call the callbackTimeout and attempt to wait again
	//a number of times that you designate. if a event was found, it will return true, otherwise if it timedout all attempts to wait, it returns false.
	template <uint16_t Tevt>
		bool WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt);

	
	
protected:
	 
	bool IsWaitingForEvent;

	AEEventDiscriminator_t* EvtWaitingFor;
	//QueueHandle_t* QueueExecuteForEvtOfTDU_ptr;
	xSemaphoreHandle* BinarySemaphoreForEventListening_ptr;

	void PostEvtToRequestingAO(AEEventBase * const evtToPost);
	void PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost);


	void CancelCleanUp()  ;

	float* LinkedSPBData;
	float _frequencyIUpdateAt;

};

template<TemplateForActionArgTDU_NoDefaults3>
inline void ActionRequestObjectArgTDU3<TemplateForActionArgTDU_Args3>::CancelCleanUp()
{
	//this CancelCleanUp needs to be implemented for the action request you tries to cancel
	configASSERT(_CancelCleanUp != nullptr);
	
	this->_CancelCleanUp(this->ClassForActionRequest);
}

template<TemplateForActionArgTDU_NoDefaults3>
inline void ActionRequestObjectArgTDU3<TemplateForActionArgTDU_Args3>::PostEvtToRequestingAO(AEEventBase * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}
template<TemplateForActionArgTDU_NoDefaults3>
inline void ActionRequestObjectArgTDU3<TemplateForActionArgTDU_Args3>::PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}



template<TemplateForActionArgTDU_NoDefaults3>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU3<TemplateForActionArgTDU_Args3>::WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt)
{
	//you ned to attempt at least 1 time to wait for an event
	configASSERT(numOfAttempts > 0);

	//first attempt the first wait
	bool eventFound = false;
	eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
	if (eventFound == false)
	{

		//go through the amount of times designated 
		for (uint16_t i = 0; i < numOfAttempts - 1; i++)
		{
			//call the callback for a timeoutattempt
			callBackForTimeOutAttempt(this);
			//now wait for the event
			eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
			if (eventFound == true)
			{
				return eventFound;
			}
		}

	}
	return eventFound;

}

template<TemplateForActionArgTDU_NoDefaults3>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU3<TemplateForActionArgTDU_Args3>::WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec)
{
	//first I need to subscribe to the event 
	PublishSubscribeManager->_SubscribeToEvt(Tevt, this->AOID_OfResource);// EventSubscribers[Tevt][this->AOID_OfResource] = true;
	IsWaitingForEvent = true;
	//check for if user wants a timeout
	if (timeoutMillisec == 0xffffffff)
	{
		xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, portMAX_DELAY);
	}
	else
	{
		auto ticks = AE_Tick_To_Milli(timeoutMillisec);
		BaseType_t wasThereAnEvent = xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, ticks);

		//if it timeout, unsubscribe and return false
		if (wasThereAnEvent == pdFALSE)
		{
			IsWaitingForEvent = false;
			PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);
			return false;
		}

	}
	IsWaitingForEvent = false;

	if (callBackWhenEvtPublishes != nullptr)
	{
		callBackWhenEvtPublishes(this, EvtWaitingFor);
	}

	//after the callback is done with the reference, decrement the counter
	if (EvtWaitingFor->type == 1)
	{
		EvtWaitingFor->evt->DecrementRefCounter();
	}

	//after being, give semaphore back and unsubscribe
	PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);

}




template<TemplateForActionArgTDU4>
class ActionRequestObjectArgTDU4 : public ActionRequestObjectArg4<TemplateForActionArgTDU_Args4>
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOResourceService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOUpdateable;
	
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AEAOUpdateableAAP;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AETDUAsPossession;
	template<TemplateFor_AEAOUpdateableAAS_NoDefaults_friend>
	friend class AEAOUpdateableAAS;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;
public:
	ActionRequestObjectArgTDU4() {
		IsWaitingForEvent = false;
	};

	//this is the function that ets the parameters for the initiation of the actionrequest to start updating.
//	virtual void RequestImpl(ARG1 Argument1, ARG2 Argument2, ARG3 Argument3, ARG4 Argument4) = 0;
	//this is the function that will continueally by called while updating.
	//virtual bool Update() = 0;
protected: typedef void(*CancelCleanUp_fptr)(ForwardDeclaredTDU* p);
protected:	CancelCleanUp_fptr _CancelCleanUp = nullptr;
public: void SetCancelCleanUpFunc(CancelCleanUp_fptr s) {this->_CancelCleanUp = s; }	
protected: typedef bool(*UpdateFunc)(ForwardDeclaredTDU* p, ARG1 Argument1, ARG2 Argument22, ARG3 Argument3, ARG4 Argument4);
	//public: void SetServiceFunc(SetServiceReqFunc s) {_RequestImpl = s; }
public: void SetUpdateFunc(UpdateFunc s) {this->_Update = s; }	

	//returns true if the event it was waiting on happened, otherwise returns false if it timedout
	template <uint16_t Tevt>
		bool WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec = 0xffffffff);

	//this will wait for an event with a timeout, if a timeout occurs, it will call the callbackTimeout and attempt to wait again
	//a number of times that you designate. if a event was found, it will return true, otherwise if it timedout all attempts to wait, it returns false.
	template <uint16_t Tevt>
		bool WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt);


protected:
	 

	bool IsWaitingForEvent;

	AEEventDiscriminator_t* EvtWaitingFor;
	//QueueHandle_t* QueueExecuteForEvtOfTDU_ptr;
	xSemaphoreHandle* BinarySemaphoreForEventListening_ptr;

	void PostEvtToRequestingAO(AEEventBase * const evtToPost);
	void PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost);


	void CancelCleanUp()  ;

	float* LinkedSPBData;
	float _frequencyIUpdateAt;

};

template<TemplateForActionArgTDU_NoDefaults4>
inline void ActionRequestObjectArgTDU4<TemplateForActionArgTDU_Args4>::CancelCleanUp()
{
	//this CancelCleanUp needs to be implemented for the action request you tries to cancel
	configASSERT(_CancelCleanUp != nullptr);
	
	this->_CancelCleanUp(this->ClassForActionRequest);
}

template<TemplateForActionArgTDU_NoDefaults4>
inline void ActionRequestObjectArgTDU4<TemplateForActionArgTDU_Args4>::PostEvtToRequestingAO(AEEventBase * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}
template<TemplateForActionArgTDU_NoDefaults4>
inline void ActionRequestObjectArgTDU4<TemplateForActionArgTDU_Args4>::PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}



template<TemplateForActionArgTDU_NoDefaults4>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU4<TemplateForActionArgTDU_Args4>::WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt)
{
	//you ned to attempt at least 1 time to wait for an event
	configASSERT(numOfAttempts > 0);

	//first attempt the first wait
	bool eventFound = false;
	eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
	if (eventFound == false)
	{

		//go through the amount of times designated 
		for (uint16_t i = 0; i < numOfAttempts - 1; i++)
		{
			//call the callback for a timeoutattempt
			callBackForTimeOutAttempt(this);
			//now wait for the event
			eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
			if (eventFound == true)
			{
				return eventFound;
			}
		}

	}
	return eventFound;

}

template<TemplateForActionArgTDU_NoDefaults4>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU4<TemplateForActionArgTDU_Args4>::WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec)
{
	//first I need to subscribe to the event 
	PublishSubscribeManager->_SubscribeToEvt(Tevt, this->AOID_OfResource);// EventSubscribers[Tevt][this->AOID_OfResource] = true;
	IsWaitingForEvent = true;
	//check for if user wants a timeout
	if (timeoutMillisec == 0xffffffff)
	{
		xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, portMAX_DELAY);
	}
	else
	{
		auto ticks = AE_Tick_To_Milli(timeoutMillisec);
		BaseType_t wasThereAnEvent = xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, ticks);

		//if it timeout, unsubscribe and return false
		if (wasThereAnEvent == pdFALSE)
		{
			IsWaitingForEvent = false;
			PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);
			return false;
		}

	}
	IsWaitingForEvent = false;

	if (callBackWhenEvtPublishes != nullptr)
	{
		callBackWhenEvtPublishes(this, EvtWaitingFor);
	}

	//after the callback is done with the reference, decrement the counter
	if (EvtWaitingFor->type == 1)
	{
		EvtWaitingFor->evt->DecrementRefCounter();
	}

	//after being, give semaphore back and unsubscribe
	PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);
	return true;
}




template<TemplateForActionArgTDU5>
class ActionRequestObjectArgTDU5 : public ActionRequestObjectArg5<TemplateForActionArgTDU_Args5>
{
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEAOResourceAsService;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AEUtilityAsService;
	
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOResourceService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOUpdateable;
	
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEAOResourceAsAPossession;
	template<TemplateFor_RAsAPossession_NoDefaults_friend>
	friend class AEUtilityAsPossession;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AEAOUpdateableAAP;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AETDUAsPossession;
	template<TemplateFor_AEAOUpdateableAAS_NoDefaults_friend>
	friend class AEAOUpdateableAAS;
	template<TemplateFor_RAsAService_NoDefaults_friend>
	friend class AETDUAsService;
public:
	ActionRequestObjectArgTDU5() {
		IsWaitingForEvent = false;
	};

	//this is the function that ets the parameters for the initiation of the actionrequest to start updating.
//	virtual void RequestImpl(ARG1 Argument1, ARG2 Argument2, ARG3 Argument3, ARG4 Argument4, ARG5 Argument5) = 0;
	//this is the function that will continueally by called while updating.
	//virtual bool Update() = 0;
	
protected: typedef bool(*CancelCleanUp_fptr)(ForwardDeclaredTDU* p);
protected:	CancelCleanUp_fptr _CancelCleanUp = nullptr;
public: void SetCancelCleanUpFunc(CancelCleanUp_fptr s) {this->_CancelCleanUp = s; }	
protected: typedef bool(*UpdateFunc)(ForwardDeclaredTDU* p, ARG1 Argument1, ARG2 Argument22, ARG3 Argument3, ARG4 Argument4, ARG5 Argument5);
	//public: void SetServiceFunc(SetServiceReqFunc s) {_RequestImpl = s; }
public: void SetUpdateFunc(UpdateFunc s) {this->_Update = s; }	


	//returns true if the event it was waiting on happened, otherwise returns false if it timedout
	template <uint16_t Tevt>
		bool WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec = 0xffffffff);

	//this will wait for an event with a timeout, if a timeout occurs, it will call the callbackTimeout and attempt to wait again
	//a number of times that you designate. if a event was found, it will return true, otherwise if it timedout all attempts to wait, it returns false.
	template <uint16_t Tevt>
		bool WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt);

	
protected:
	 

	bool IsWaitingForEvent;

	AEEventDiscriminator_t* EvtWaitingFor;
	//QueueHandle_t* QueueExecuteForEvtOfTDU_ptr;
	xSemaphoreHandle* BinarySemaphoreForEventListening_ptr;

	void PostEvtToRequestingAO(AEEventBase * const evtToPost);
	void PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost);


	void CancelCleanUp() override;

	float* LinkedSPBData;
	float _frequencyIUpdateAt;

};

template<TemplateForActionArgTDU_NoDefaults5>
inline void ActionRequestObjectArgTDU5<TemplateForActionArgTDU_Args5>::CancelCleanUp()  
{
	//this CancelCleanUp needs to be implemented for the action request you tries to cancel
	configASSERT(_CancelCleanUp != nullptr);
	
	this->_CancelCleanUp(this->ClassForActionRequest);
}

template<TemplateForActionArgTDU_NoDefaults5>
inline void ActionRequestObjectArgTDU5<TemplateForActionArgTDU_Args5>::PostEvtToRequestingAO(AEEventBase * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}
template<TemplateForActionArgTDU_NoDefaults5>
inline void ActionRequestObjectArgTDU5<TemplateForActionArgTDU_Args5>::PostEvtToRequestingAO(AEEventDiscriminator_t * const evtToPost)
{
	AEAO::AllAO[this->AOID_OfResource]->PostEvtToAO(this->AOID_OfCurrentRequestingAO, evtToPost);
}



template<TemplateForActionArgTDU_NoDefaults5>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU5<TemplateForActionArgTDU_Args5>::WaitForEventWithTimeOutAttempts(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec, uint32_t numOfAttempts, CallBackForWaitTimeOut_t callBackForTimeOutAttempt)
{
	//you ned to attempt at least 1 time to wait for an event
	configASSERT(numOfAttempts > 0);

	//first attempt the first wait
	bool eventFound = false;
	eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
	if (eventFound == false)
	{

		//go through the amount of times designated 
		for (uint16_t i = 0; i < numOfAttempts - 1; i++)
		{
			//call the callback for a timeoutattempt
			callBackForTimeOutAttempt(this);
			//now wait for the event
			eventFound = this->WaitForEvent<Tevt>(callBackWhenEvtPublishes, timeoutMillisec);
			if (eventFound == true)
			{
				return eventFound;
			}
		}

	}
	return eventFound;

}

template<TemplateForActionArgTDU_NoDefaults5>
template <uint16_t Tevt>
inline bool ActionRequestObjectArgTDU5<TemplateForActionArgTDU_Args5>::WaitForEvent(CallBackForWaitForEvt_t callBackWhenEvtPublishes, uint32_t timeoutMillisec)
{
	//first I need to subscribe to the event 
	PublishSubscribeManager->_SubscribeToEvt(Tevt, this->AOID_OfResource);// EventSubscribers[Tevt][this->AOID_OfResource] = true;
	IsWaitingForEvent = true;
	//check for if user wants a timeout
	if (timeoutMillisec == 0xffffffff)
	{
		xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, portMAX_DELAY);
	}
	else
	{
		auto ticks = AE_Tick_To_Milli(timeoutMillisec);
		BaseType_t wasThereAnEvent = xSemaphoreTake(*BinarySemaphoreForEventListening_ptr, ticks);

		//if it timeout, unsubscribe and return false
		if (wasThereAnEvent == pdFALSE)
		{
			IsWaitingForEvent = false;
			PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);
			return false;
		}

	}
	IsWaitingForEvent = false;

	if (callBackWhenEvtPublishes != nullptr)
	{
		callBackWhenEvtPublishes(this, EvtWaitingFor);
	}

	//after the callback is done with the reference, decrement the counter
	if (EvtWaitingFor->type == 1)
	{
		EvtWaitingFor->evt->DecrementRefCounter();
	}

	//after being, give semaphore back and unsubscribe
	PublishSubscribeManager->_UnSubscribeToEvt(Tevt, this->AOID_OfResource);

}



