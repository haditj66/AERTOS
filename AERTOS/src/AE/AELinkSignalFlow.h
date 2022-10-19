#pragma once
#include "AELinkBase.h"
#include <cstdint>
//#include "AEObservorBase.h"
#include "AEObservorBase.h"
#include "AESPBObservor.h"

class AELinkSignalFlow : public AELinkBase
{
public:
	friend class AEObservorBase;
	friend class AESPBObservor;

	static void InitAELinkSPBObjectPool(AELinkSignalFlow* links, uint16_t sizeOfLinkArray);


	static AELinkSignalFlow* Links;

	AELinkSignalFlow(); 

protected:

	static uint16_t SizeOfLinkArray;
	static uint16_t CurrentIndex;

	static uint8_t InitializeLinkFromPool(AEObservorBase* observorLinkPointsFrom, AEObservorBase* observorLinkPointsTo);


};

