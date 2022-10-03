#pragma once


#include "AESPBObservorOutputType.h"
#include "AEUtils.h" 

#include "AEIntegrationTesting.h"

#include <math.h>


template<TEMPLATESPB_Filters>
class ThreeDimensionalVector : public AESPBObservorOutputType<4, 3,false, TEMPLATESPB_FilterParams, 1, true, 1, true, 1, true>
{
public:
	ThreeDimensionalVector();
	
	bool isForVel;

private: 

	//just for the integration test
	

	// Inherited via AESPBObservorOutputType
	virtual void RefreshOVERRIDE(float OutputSignal[4]) override;

};


template<TEMPLATESPB_FiltersFunctionParams>
inline ThreeDimensionalVector< TEMPLATESPB_FilterParams>::ThreeDimensionalVector()
{
}

template<TEMPLATESPB_FiltersFunctionParams>
inline void ThreeDimensionalVector< TEMPLATESPB_FilterParams>::RefreshOVERRIDE(float OutputSignal[4])
{ 

	//check if all values of channel 1 are above zero for true
	float* ch1 = this->InputChannels[0]->ChannelSignalBufferSingle;
	float* ch2 = this->InputChannels[1]->ChannelSignalBufferSingle;
	float* ch3 = this->InputChannels[2]->ChannelSignalBufferSingle;


	float magnitude = sqrtf((ch1[0] * ch1[0]) + (ch2[0] * ch2[0]) + (ch3[0] * ch3[0]));
	float u = magnitude == 0 ? 1 : ch1[0] / magnitude;
	float v = magnitude == 0 ? 0 : ch2[0] / magnitude;
	float w = magnitude == 0 ? 0 : ch3[0] / magnitude;

	OutputSignal[0] = magnitude;
	OutputSignal[1] = u;
	OutputSignal[2] = v;
	OutputSignal[3] = w;
	 
	if (isForVel == true)
	{
		AEITEST_AECoreTestEXE_IgnoreFirstTests("VelocityValue",
			AE_FloatApproximatelyEqual(magnitude, 374.165741,.1)  && 
			AE_FloatApproximatelyEqual(u, 0.267261237,.1),
			"velocity should be 374  ",
			3);		 
	}
	else
	{
		AEITEST_AECoreTestEXE_IgnoreFirstTests("AccelerationValue", magnitude == 0 && u == 1, "acceeration should be zero since velocity is not changing", 3);
	}
	 
}


