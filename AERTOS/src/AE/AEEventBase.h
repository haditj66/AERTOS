#pragma once

#include "cstdint"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h" 

#include "AEUtils.h"
//#include "AEDefines.h"

#include <type_traits>

 
#if NUMOFEVENTS > (256-2) //the minus 2 is to account for the two enter and exit events
typedef uint16_t EventPoolSize_t;
#else  
typedef uint8_t EventPoolSize_t;
#endif

class AEEventBase
{
	template<class TEvent1, uint16_t sizeOfEvent1Pool, class TEvent2, uint16_t sizeOfEvent2Pool, class TEvent3, uint16_t sizeOfEvent3Pool, class TEvent4, uint16_t sizeOfEvent4Pool, class TEvent5, uint16_t sizeOfEvent5Pool>
	friend class AEPoolManager;
	friend class AEAO;
	friend class AEPublishSubscribeManager;
	friend class AEEventListener;
	template<TemplateFor_SimpleFSM_NoDefaults>
	friend class AESimpleFSM;
	friend class AEEventDiscriminator_t;

	Friend_ToALL_ActionRequestObjects_TDU

	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AETDUAsPossession;
	template<TemplateFor_AEAOUpdateableAAS_NoDefaults_friend>
	friend class AETDUAsService;

public:


	EventPoolSize_t GetEvtID() const { return EvtId; }

	EventPoolSize_t  poolId;

	static AEEventBase* GetNewEvt();


	AEEventBase() {
		isInUse = false;
		isInitialized = false;

	}


bool isInUse;

protected:
	static EventPoolSize_t EvtIdStatic;
	EventPoolSize_t EvtId;

private: 
	EventPoolSize_t RefCounter;
	 

	void init(EventPoolSize_t evtId);
	bool isInitialized;

	void DecrementRefCounter();
	void Reset();

};



class ENTEREvent : public AEEventBase
{

	//this class is a singleton class
public: 
	static ENTEREvent* getInstance();
	ENTEREvent(ENTEREvent const&) = delete;
	void operator=(ENTEREvent const&) = delete;
protected: 
	static ENTEREvent* instance;
	ENTEREvent() : AEEventBase() { EvtId = ENTEREVENT_Id; };
public:


	static EventPoolSize_t EvtIdStatic; 
};

class EXITEvent : public AEEventBase
{

	//this class is a singleton class
public:
	static EXITEvent* getInstance();
	EXITEvent(EXITEvent const&) = delete;
	void operator=(EXITEvent const&) = delete;
protected:
	static EXITEvent* instance;
	EXITEvent() : AEEventBase() { EvtId = EXITEVENT_Id; };
public:


	static EventPoolSize_t EvtIdStatic;
};



struct AEEventDiscriminator_t
{
public:

	EventPoolSize_t GetEvtID() const {

		EventPoolSize_t ret = type == 1 ? this->evt->EvtId : (EventPoolSize_t)this->signalEvt;
		return ret;
	};

	AEEventDiscriminator_t() { this->evt = nullptr; }

	AEEventDiscriminator_t(AEEventBase* evt) {
		SetAsAEEvent(evt);
	}
	AEEventDiscriminator_t(EventPoolSize_t evt) {
		SetAsEvtSignal(evt);
	}

	void SetAsAEEvent(AEEventBase* evt) {
		type = 1;
		this->evt = evt;
		evtId = evt->EvtId;
	}
	void SetAsEvtSignal(EventPoolSize_t evt) {
		type = 0;
		this->signalEvt = evt;
		evtId = evt;
	}

	bool type;


	static AEEventDiscriminator_t EnterEvtInstance;
	static AEEventDiscriminator_t ExitEvtInstance;
	static AEEventDiscriminator_t UpdateEvtInstance;
	static AEEventDiscriminator_t ActivateFSMEvtInstance;
	static AEEventDiscriminator_t DeActivateFSMEvtInstance;

	//use a union so that only one of the members is allocated memory
public:

	union 
	{
		AEEventBase* evt;
		EventPoolSize_t signalEvt;
		
	};
	protected:
		EventPoolSize_t evtId;



};


//create single instances of the signal events
#if Signal1 != 1000
static AEEventDiscriminator_t M_CONC(Signal1,_Instance)(Signal1);
#endif 
#if Signal2 != 1000
static AEEventDiscriminator_t M_CONC(Signal2, _Instance)(Signal2);
#endif 
#if Signal3 != 1000
static AEEventDiscriminator_t M_CONC(Signal3, _Instance)(Signal3);
#endif 
#if Signal4 != 1000
static AEEventDiscriminator_t M_CONC(Signal4, _Instance)(Signal4);
#endif 
#if Signal5 != 1000
static AEEventDiscriminator_t M_CONC(Signal5, _Instance)(Signal5);
#endif 
#if Signal6 != 1000
static AEEventDiscriminator_t M_CONC(Signal6, _Instance)(Signal6);
#endif 
#if Signal7 != 1000
static AEEventDiscriminator_t M_CONC(Signal7, _Instance)(Signal7);
#endif 

