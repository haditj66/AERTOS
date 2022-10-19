#pragma once


#include "AEMultiChannelFilter.h"

template<uint8_t NumOfChannels>
class AEMultiChannelFilterCHANNELSELECT : AEMultiChannelFilter
{
public:
	AEMultiChannelFilterCHANNELSELECT() {
	//initialize inputchannels
		for (uint16_t i = 0; i < NumOfChannels; i++)
		{
			inputsSoFar = 0;
			_NumOfInputs = NumOfChannels;
			InputChannelValues[i] = InputChannels[i];
		}
	};
	virtual float operator()() = 0; 

	virtual void Initialize(float samplingPeriodOfObservorInSeconds) =0;

protected:

	
	float* InputChannels[NumOfChannels];

};

/*
template<uint8_t NumOfChannels>
inline float AEMultiChannelFilterCHANNELSELECT<NumOfChannels>::operator()()
{
	inputsSoFar++;
	if (inputsSoFar >= NumOfChannels)
	{

	}

	return 0.0f;
}*/
