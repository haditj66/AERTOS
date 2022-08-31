#pragma once

#include <cstdint>
#include "AECircularBuffer.h"

template<class TFilterDerived, uint16_t PastDataBufferSize = 1>
class Filter
{
	template<TEMPLATESPB_FiltersFunctionParams>
	friend class AEObservorSensorFilterOut;


      
TEMPLATEFOR_AESPBOUTPUT
		friend class AESPBObservorOutputType;

friend class   SPBSubprivateImp;

public: 
	uint16_t BufferSize;
        float SamplingPeriodOfObservorInSeconds;
        
	Filter();

	float operator()(float a);

	void Initialize(float samplingPeriodOfObservorInSeconds) ;

	

protected:

	//only meant to be called by AEObservorSensorFilterOut GetObservationFromFilter() function.
	float GetObservation();

	AECircularBuffer<float, PastDataBufferSize> PastDataCircularBuffer;

	float FilterOutputValue;

	float* GetOutputDataAddress();
};



template<class TFilterDerived, uint16_t PastDataBufferSize>
inline float Filter<TFilterDerived, PastDataBufferSize>::GetObservation()
{
	return FilterOutputValue;
}

template<class TFilterDerived, uint16_t PastDataBufferSize>
inline float * Filter<TFilterDerived, PastDataBufferSize>::GetOutputDataAddress()
{
	return &FilterOutputValue;
}


template<class TFilterDerived, uint16_t PastDataBufferSize>
inline Filter<TFilterDerived, PastDataBufferSize>::Filter()
{
	BufferSize =PastDataBufferSize;
  FilterOutputValue = 0;
}

template<class TFilterDerived, uint16_t PastDataCircularBuffer>
inline float Filter<TFilterDerived, PastDataCircularBuffer>::operator()(float a)
{ 
	TFilterDerived& derivedFilter =  static_cast<TFilterDerived&>(*this);

	//push this new past value into the circular bufer for that filter.
	PastDataCircularBuffer.Push(a, false);

	FilterOutputValue = derivedFilter.RunFilter(a);

	return FilterOutputValue;
}

template<class TFilterDerived, uint16_t PastDataBufferSize>
inline void Filter<TFilterDerived, PastDataBufferSize>::Initialize(float samplingPeriodOfObservorInSeconds)
{
	TFilterDerived& derivedFilter = static_cast<TFilterDerived&>(*this);

	SamplingPeriodOfObservorInSeconds = samplingPeriodOfObservorInSeconds;

	derivedFilter.InitializeImpl(samplingPeriodOfObservorInSeconds);
}

