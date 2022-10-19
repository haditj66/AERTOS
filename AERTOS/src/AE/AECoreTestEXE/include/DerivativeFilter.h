#pragma once 

#include <cstdint>
#include "AEFilter.h"

class DerivativeFilter : public Filter<DerivativeFilter, 2>
{
  template<class TFilterDerived, uint16_t PastDataBufferSize>
	friend class Filter;

public:
	DerivativeFilter();

protected:
	
	void InitializeImpl(float samplingPeriodOfObservorInSeconds);

private:
	float RunFilter(float newestInput);

};

 
inline DerivativeFilter::DerivativeFilter()
{
	
}
 
inline void DerivativeFilter::InitializeImpl(float samplingPeriodOfObservorInSeconds)
{
	
}

inline float DerivativeFilter::RunFilter(float newestInput)
{
float der = (PastDataCircularBuffer[0] - PastDataCircularBuffer[1]) / this->SamplingPeriodOfObservorInSeconds;
	return der;
}
