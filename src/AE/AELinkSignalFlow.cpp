#include "AELinkSignalFlow.h"
//#include "AEObservorInterpretorBase.h"
//#include "AEObservorSensor.h"
//#include "AESPBObservor.h"


AELinkSignalFlow* AELinkSignalFlow::Links = nullptr;
uint16_t AELinkSignalFlow::SizeOfLinkArray = 0;
uint16_t AELinkSignalFlow::CurrentIndex = 0;

void AELinkSignalFlow::InitAELinkSPBObjectPool(AELinkSignalFlow * links, uint16_t sizeOfLinkArray)
{
	Links = links;
	SizeOfLinkArray = sizeOfLinkArray;
}

AELinkSignalFlow::AELinkSignalFlow()
{
}

uint8_t AELinkSignalFlow::InitializeLinkFromPool(AEObservorBase * observorLinkPointsFrom, AEObservorBase * observorLinkPointsTo)
{
	Links[CurrentIndex].SetTheLinkType(LinkType::SignalFlow);
	InitializeBaseObservorsForLink(Links, CurrentIndex, observorLinkPointsFrom, observorLinkPointsTo);


	uint8_t retValue = CurrentIndex;
	CurrentIndex++;

	return retValue;



	/*
	//the observor the deterministic link points from must ALWAYS be an interpretor, never a sensor. So I can cast
	static_cast<AEObservorInterpretorBase*>(observorLinkPointsFrom)->MyDeterministicLinksIPoint[static_cast<AEObservorInterpretorBase*>(observorLinkPointsFrom)->numOfDeterministicLinksIPoint] = &Links[CurrentIndex];
	static_cast<AEObservorInterpretorBase*>(observorLinkPointsFrom)->numOfDeterministicLinksIPoint++;

	observorLinkPointsTo->MyDeterministicLinksPointingToMe[observorLinkPointsTo->numOfDeterministicLinksPointToMe] = &Links[CurrentIndex];
	observorLinkPointsTo->numOfDeterministicLinksPointToMe++;

	CurrentIndex++;
	*/
}
