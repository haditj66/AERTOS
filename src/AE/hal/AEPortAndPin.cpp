#include "AEPortAndPin.h"

uint32_t AEPortAndPin::_numPortsAndPinsCreatedSoFar = 0;
AEPortAndPin* AEPortAndPin::ALLPortsAndPins[MaxNumOfGPIOPinsToUse]; 