#pragma once

#include "AEObservorBase.h"

#ifdef  Config_Check_Build_RTTI  
#include <typeinfo>
#endif


#define NUMBEROFMUTEXS  10
//#include "AELinkDeterministic.h"

//class AELinkDeterministic;

class AEObservorInterpretorBase : public AEObservorBase
{
public:
	TEMPLATEFORNoDefaults_AEClock
	friend class AEClock;

	 

	uint8_t numOfDeterministicLinksIPoint;
	uint8_t MyDeterministicLinksIPoint[50];

	

	uint8_t CurrentSession;
	uint8_t CLockSession;
	bool AlreadyInSession;

	bool DoINeedARefresh; //explained in onenote observer -> How/Why...
	bool EOC_RefreshedWhileInSession;//explained in onenote observer -> How/Why...

	bool UpdatedSinceClockTick;

	AEObservorInterpretorBase();

	uint32_t GetSizeOfChannel1();
	uint32_t GetSizeOfChannel2();
	uint32_t GetSizeOfChannel3();

	static AEObservorInterpretorBase* GetInterpretor(uint16_t observorID);
	void Init();

protected:


#ifdef  Config_Check_Build_RTTI  
	char const * typeIdForOutObservationType;
#endif

	uint32_t SizeOfChannel1;
	uint32_t SizeOfChannel2;
	uint32_t SizeOfChannel3;

	SemaphoreHandle_t* MutexForObservorsToWaitFor[40];
	uint8_t CurrentSessionsForObservorsToWaitFor[40];



	SemaphoreHandle_t MutexHandles[NUMBEROFMUTEXS];
	//StaticEventGroup_t xCreatedEventGroup;
	//TaskHandle_t RefreshObservationGaurdTask;
	void RefreshObservationGaurd(void *pvParameters);


	void AddDeterministicLink(AEObservorBase* toObservor);

	void IncrementCurrentSession();
	uint8_t GetSessionThisManyBeforeCurrent(uint8_t thisManyBeforeCurrentSession) const;

	virtual void Refresh() = 0; // todo: this needs to be CRTP inherited
	virtual void SwapObservationToReadWithTheOneToRefresh() = 0; // todo: this needs to be CRTP inherited
	virtual void CopyDeterminedValues() = 0;// todo: this needs to be CRTP inherited


	//this is to be used on observors for other observors
	void UpdateObservationIfNeeded(SemaphoreHandle_t*&  MutexHandleForObservorsToWaitFor);// todo: this needs to be CRTP inherited 
	//void UpdateObservationIfNeeded() override; // todo: this needs to be CRTP inherited 

	void UpdateObservationIfNeededForClock();

	
};

