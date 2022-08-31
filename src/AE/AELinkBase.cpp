#include "AELinkBase.h"



void AELinkBase::InitializeBaseObservorsForLink(AELinkBase * Links, uint16_t CurrentIndex, AEObservorBase * observorLinkPointsFrom, AEObservorBase * observorLinkPointsTo)
{ 

	//set observor I point FROM. 
	if (observorLinkPointsFrom->GetMyObservorType() & ObservorType::Interpretors)
	{
		//Links[CurrentIndex].SetTheInterpretorObservorIPointFrom((AEObservorInterpretorBase*)observorLinkPointsFrom);
		Links[CurrentIndex].SetTheInterpretorObservorIPointFrom(static_cast<AEObservorInterpretorBase*>(observorLinkPointsFrom));
		Links[CurrentIndex].LinkPointsFromObservorOfType = ObservorType::Interpretors;
	}
	if (observorLinkPointsFrom->GetMyObservorType() & ObservorType::Sensor)
	{
		Links[CurrentIndex].SetTheSensorObservorIPointFrom(static_cast<AEObservorSensor*>(observorLinkPointsFrom));
		Links[CurrentIndex].LinkPointsFromObservorOfType = ObservorType::Sensor;
	}
	if (observorLinkPointsFrom->GetMyObservorType() & ObservorType::SPB)
	{
		Links[CurrentIndex].SetTheSPBObservorIPointFrom(static_cast<AESPBObservor*>(observorLinkPointsFrom));
		Links[CurrentIndex].LinkPointsFromObservorOfType = ObservorType::SPB;
	}
	Links[CurrentIndex].SetTheObservorIPointFrom(observorLinkPointsFrom);


	//set observor I point TO
	if (observorLinkPointsTo->GetMyObservorType() & ObservorType::Interpretors)
	{
		observorLinkPointsFrom->numOfDeterministicLinksIPointThatAreInterpretors++;
		Links[CurrentIndex].SetTheInterpretorObservorIPointTo(static_cast<AEObservorInterpretorBase*>(observorLinkPointsTo));
		Links[CurrentIndex].LinkPointsToObservorOfType = ObservorType::Interpretors;
	}
	if (observorLinkPointsTo->GetMyObservorType() & ObservorType::Sensor)
	{
		Links[CurrentIndex].SetTheSensorObservorIPointTo(static_cast<AEObservorSensor*>(observorLinkPointsTo));
		Links[CurrentIndex].LinkPointsToObservorOfType = ObservorType::Sensor;
	}
	if (observorLinkPointsTo->GetMyObservorType() & ObservorType::SPB)
	{
		Links[CurrentIndex].SetTheSPBObservorIPointTo(static_cast<AESPBObservor*>(observorLinkPointsTo));
		Links[CurrentIndex].LinkPointsToObservorOfType = ObservorType::SPB;
	}
	Links[CurrentIndex].SetTheObservorIPointTo(observorLinkPointsTo);
}

AELinkBase::AELinkBase()
{
}

 