#include "PinSelector.h"

PinSelector* PinSelector::instance = 0;
PinSelector* PinSelector::getInstance()
{
	if (instance == 0)
	{
		static PinSelector soleInstance;
		instance = &soleInstance;
	}
	return instance;
}


