#pragma once
#include <cstdint>
 
class AEMultiChannelFilter
{
public:
	

	AEMultiChannelFilter() {};

	void SetInputtingFilterToChannel(float* FilterOutputValues, uint8_t toChannel);

	virtual float operator()() = 0;

	virtual void Initialize(float samplingPeriodOfObservorInSeconds) = 0;
	 
	float** InputChannelValues;

	uint8_t inputsSoFar;

	uint8_t _NumOfInputs;
protected:
	
};