#pragma once
//#include "AELinkDeterministic.h"
//#include "FreeRTOS.h"

//#include "AELinkSignalFlow.h"

#include <cstdint>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "event_groups.h"

#include "AEObservorTypes.h"
#include "AEUtils.h"

#include "AEAO.h"



//class AELinkDeterministic;
//class AELinkSignalFlow;
class AESPBObservor;
class AEObservorInterpretorBase;

class AEObservorBase : public AEAO
{
public:
	friend class AESPBObservor;

	TEMPLATEFOR_AESPBOUTPUT
	friend class AESPBObservorOutputType;

	TEMPLATEFORNoDefaults_AEClock
	friend class AEClock;
	friend class AEObservorBase;
	//friend void AESPBObservor::RefreshUpdateGaurd(void * pvParameters);

	uint16_t ObservorId;
	static AEObservorBase* ObservorPool[MAXNUMOFOBSERVORS];
	static uint16_t CurrentId;

	bool SetToClock;

	bool IsEndChain;


	uint8_t numOfDeterministicLinksPointToMe;
	uint8_t MyDeterministicLinksPointingToMe[50];

	uint8_t numOfDeterministicObservorsPointToMe;
	AEObservorInterpretorBase* DeterministicObservorsPointingToMe[50];
	//uint16_t IDsOfDeterministicObservorsPointingToMe[50];

	/*
	uint8_t numOfSPBLinksPointToMe;
	uint8_t MySPBLinksPointingToMe[50];

	uint8_t numOfSPBLinksIPoint;
	uint8_t MySPBLinksIPointing[50];
	*/ 
	uint8_t OutputFilterThatSignalGoesFrom[MAXNUMBEROFOUTPUTSIGNALS_TO_A_SPB];
	AESPBObservor* SPBObservorsIPointTo[MAXNUMBEROFOUTPUTSIGNALS_TO_A_SPB];
	uint16_t ChannelIdsIConnectTo[MAXNUMBEROFOUTPUTSIGNALS_TO_A_SPB];
	uint16_t NumOfSPBObservorsIPointTo;

	uint16_t numOfSignalLinksPointToMe;
	//AELinkSignalFlow* MySignalLinksPointingToMe[50];

	uint8_t numOfDeterministicLinksIPointThatAreInterpretors;

	bool HasThereBeenARefreshOAnyDeterministicObservors;

	//conversion constructor to convert to derived type AEObservorInterpretorBase
	uint16_t InterpretorId;
	bool FrequencyHasBeenConfigured;

	static void InitializeEndChainObservors();

	//virtual void UpdateObservationIfNeeded() = 0;
	uint16_t GetnumOfObservorsOfInfluence();
	bool** GetObservorsOfInfluenceNeedARefeshValues();

	float GetFrequencyIRefreshAt();
	 
	void TurnObservorOff() { isObservorOn = false; };
	void TurnObservorOn() { isObservorOn = true; };

	/*operator AEObservorInterpretorBase*() const {
		return InterpretorBasePool[InterpretorId];
	}*/
	 
	uint16_t GetClockIdImSourcedTo();
	
	uint8_t GetMyObservorType();

	virtual ~AEObservorBase() {}; //DONT REMOVE THIS!!

protected:

	bool isObservorOn;

	uint16_t ClockIdImSourcedTo;
	uint8_t Prescaler;

	TaskHandle_t GaurdTaskToObjectExecutionHandle;

	void SetMyObservorType(ObservorType myObservorType);

	static uint16_t NumOfInterpretorsCreatedSoFar;
	static uint16_t MappingIndex[MAXNUMOFOBSERVORS];//Maps base Ids to this derived class Id
	static AEObservorInterpretorBase* InterpretorBasePool[MAXNUMOFINTERPRETORS];

	
	float FrequencyIRefreshAt;
	uint16_t ObservorsOfInfluence[MAXNUMOFOBSERVERINFLUENCES];
	bool* ObservorsOfInfluenceNeedARefeshValues[MAXNUMOFOBSERVERINFLUENCES];
	uint16_t numOfObservorsOfInfluence;
	void AddObserverOfInfluence(uint16_t observorID);

	virtual void InitializeObservor() {};
	  

	//should not instantiate base observors.
	AEObservorBase();

	virtual void AddSignalFlowLink(AESPBObservor * toObservor, uint16_t ToChannel, uint8_t toOutPutFilter = 0);

	virtual void InitializeFilters() = 0;

private:

	uint16_t MyObservorType;

	static void GetAllSPBRecursivelyThisObservorPointsToandCheckIfTheyAreEndChains(AEObservorBase* theObservorToGetSPBs);
	//AECHANGED:
	static bool CheckIfObservorIsEndChain(AEObservorBase* theObservorToCheck);
	//AECHANGEDDONE:

	static void RecursivelySetInfluencedPointedToInterpretors(AEObservorBase* ObservorToChackSet, AEObservorBase* forEndChain);

};


