#include "AELinkDeterministic.h"
#include "AEObservorInterpretorBase.h"
#include "AEObservorSensor.h"
//#include "AESPBObservor.h"  

AELinkDeterministic* AELinkDeterministic::Links = nullptr;
uint16_t AELinkDeterministic::SizeOfLinkArray = 0;
uint16_t AELinkDeterministic::CurrentIndex = 0;

void AELinkDeterministic::InitAELinkDeterministicObjectPool(AELinkDeterministic * links, uint16_t sizeOfLinkArray)
{
	Links = links;
	SizeOfLinkArray = sizeOfLinkArray;
}



uint8_t AELinkDeterministic::InitializeLinkFromPool(AEObservorBase * observorLinkPointsFrom, AEObservorBase * observorLinkPointsTo)
{
	Links[CurrentIndex].SetTheLinkType(LinkType::Deterministic);
	InitializeBaseObservorsForLink(Links, CurrentIndex, observorLinkPointsFrom, observorLinkPointsTo);

	/* 

	//set observor I point FROM
	if (observorLinkPointsFrom->GetMyObservorType() == ObservorType::Interpretors)
	{
		//Links[CurrentIndex].SetTheInterpretorObservorIPointFrom((AEObservorInterpretorBase*)observorLinkPointsFrom);
		Links[CurrentIndex].SetTheInterpretorObservorIPointFrom(static_cast<AEObservorInterpretorBase*>(observorLinkPointsFrom));
		Links[CurrentIndex].LinkPointsFromObservorOfType = ObservorType::Interpretors;
	}
	if (observorLinkPointsFrom->GetMyObservorType() == ObservorType::Sensor)
	{
		Links[CurrentIndex].SetTheSensorObservorIPointFrom(static_cast<AEObservorSensor*>(observorLinkPointsFrom));
		Links[CurrentIndex].LinkPointsFromObservorOfType = ObservorType::Sensor;
	}
	Links[CurrentIndex].SetTheObservorIPointFrom(observorLinkPointsFrom);


	//set observor I point TO
	if (observorLinkPointsTo->GetMyObservorType() == ObservorType::Interpretors)
	{
		observorLinkPointsFrom->numOfDeterministicLinksIPointThatAreInterpretors++;
		Links[CurrentIndex].SetTheInterpretorObservorIPointTo(static_cast<AEObservorInterpretorBase*>(observorLinkPointsTo));
		Links[CurrentIndex].LinkPointsToObservorOfType = ObservorType::Interpretors;
	}
	if (observorLinkPointsTo->GetMyObservorType() == ObservorType::Sensor)
	{
		Links[CurrentIndex].SetTheSensorObservorIPointTo(static_cast<AEObservorSensor*>(observorLinkPointsTo));
		Links[CurrentIndex].LinkPointsToObservorOfType = ObservorType::Sensor;
	}
	Links[CurrentIndex].SetTheObservorIPointTo(observorLinkPointsTo);
	 
	*/

	uint8_t retValue = CurrentIndex;
	CurrentIndex++;

	return retValue;



	//the observor the deterministic link points from must ALWAYS be an interpretor, never a sensor. So I can cast
	/*
	static_cast<AEObservorInterpretorBase*>(observorLinkPointsFrom)->MyDeterministicLinksIPoint[static_cast<AEObservorInterpretorBase*>(observorLinkPointsFrom)->numOfDeterministicLinksIPoint] = &Links[CurrentIndex];
	static_cast<AEObservorInterpretorBase*>(observorLinkPointsFrom)->numOfDeterministicLinksIPoint++;

	observorLinkPointsTo->MyDeterministicLinksPointingToMe[observorLinkPointsTo->numOfDeterministicLinksPointToMe] = &Links[CurrentIndex];
	observorLinkPointsTo->numOfDeterministicLinksPointToMe++;

	CurrentIndex++;
	*/
}


 