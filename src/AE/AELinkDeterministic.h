#pragma once
#include <cstdint>
#include "AELinkBase.h"
#include "AEObservorBase.h"

class AELinkDeterministic : public AELinkBase
{
public:
	friend class AEObservorInterpretorBase;

	static AELinkDeterministic* Links;

	AELinkDeterministic() {};
	static void InitAELinkDeterministicObjectPool(AELinkDeterministic* links, uint16_t sizeOfLinkArray);

protected:


	static uint16_t SizeOfLinkArray;
	static uint16_t CurrentIndex;

	


	//this checks to see if there has been a refresh from the pointed to observor since the last time
	//the pointing from observor had refreshed.
	//this is updated by the pointing FROM observor to false when it refreshes and 
	//is updated by the pointing TO observor to true when it is refreshed.  
	static uint8_t InitializeLinkFromPool(AEObservorBase* observorLinkPointsFrom, AEObservorBase* observorLinkPointsTo);
};

