#include "AEMultiChannelFilter.h"
#include "FreeRTOS.h"

void AEMultiChannelFilter::SetInputtingFilterToChannel(float* FilterOutputValues, uint8_t toChannel)
{
	//assert that the tochannel  does not exceed the numofChannels
	//configASSERT(toChannel <= _NumOfInputs);
	//InputChannelValues[toChannel - 1] = FilterOutputValues;
}
