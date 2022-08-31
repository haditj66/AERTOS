#pragma once

#include "AEObservorBase.h"
#include "AEObservorSensor.h"
#include "AEObservorInterpretor.h"
#include "AESPBObservor.h"

#include "FreeRTOS.h"
#include "AEObservorTypes.h"



enum LinkType
{
	Deterministic,
	Correlation,
	SignalFlow,
	Gate

};

//class AEObservorInterpretorBase;
//class AEObservorSensor;
//class AEObservorBase;
//class AESPBObservor;

class AELinkBase
{
public:

	//friend class AEObservorInterpretorBase;


	//AEObservorBase* TheObservorImLinkedTo;
	PropertyGetProtectedSet(AEObservorBase*, TheObservorIPointFrom)
		PropertyGetProtectedSet(AEObservorBase*, TheObservorIPointTo)
		PropertyGetProtectedSet(AEObservorInterpretorBase*, TheInterpretorObservorIPointFrom)
		PropertyGetProtectedSet(AEObservorInterpretorBase*, TheInterpretorObservorIPointTo)
		PropertyGetProtectedSet(AEObservorSensor*, TheSensorObservorIPointFrom)
		PropertyGetProtectedSet(AEObservorSensor*, TheSensorObservorIPointTo)
		PropertyGetProtectedSet(AESPBObservor*, TheSPBObservorIPointFrom)
		PropertyGetProtectedSet(AESPBObservor*, TheSPBObservorIPointTo)
		PropertyGetProtectedSet(LinkType, TheLinkType)

		ObservorType LinkPointsToObservorOfType;
	ObservorType LinkPointsFromObservorOfType;



protected:

	static void InitializeBaseObservorsForLink(AELinkBase* Links, uint16_t CurrentIndex, AEObservorBase * observorLinkPointsFrom, AEObservorBase * observorLinkPointsTo);


	AELinkBase();

	/*
	AELinkBase(AEObservorBase* observorLinkPointsFrom, AEObservorBase* observorLinkPointsTo) {
		SetTheObservorIPointFrom(observorLinkPointsFrom);
		SetTheObservorIPointTo(observorLinkPointsTo);
	}*/

	//PropertySet(LinkType, TheLinkType)
	//PropertySet(AEObservorBase*, TheObservorImLinkedTo)


};

