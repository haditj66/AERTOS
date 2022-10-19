#pragma once

#include "AESPBObservorOutputType.h"
#include "AEUtils.h"
#include "FreeRTOS.h"

#include "AE.h"

template<uint32_t ChannelCountBuffer, bool IsOutputSubscribeAble = false, TEMPLATESPB_Filters>
	class AverageSPB :
		public AESPBObservorOutputType<1, 1, IsOutputSubscribeAble,
	TEMPLATESPB_FilterParams,
	ChannelCountBuffer,false,
	1,false,
	1, false,
	1, false,
	1, false,
	1, false,
	1, false,
	1, false,
	1, false,
	1, false,
	1, false,
	1, false>
	//TEMPLATESPB_CHANGEABLE_CountBufferParams(1), subscribeable>
{
public:
	AverageSPB();

private:
	bool odd;

	//void SetInputChannelsOVERRIDE(InputChannel * ChannelsToSet[MAXNUMBEROFINPUTSIGNALS_TO_A_SPB]) override;



	// Inherited via AESPBObservorOutputType
	//virtual void RefreshOVERRIDE(float * OutputSignal) override;



	// Inherited via AESPBObservorOutputType
	void RefreshOVERRIDE(float OutputSignal[1]) override;

};




template<uint32_t ChannelCountBuffer, bool IsOutputSubscribeAble, TEMPLATESPB_FiltersFunctionParams>
	inline AverageSPB<ChannelCountBuffer, IsOutputSubscribeAble , TEMPLATESPB_FilterParams>::AverageSPB()
{
	odd = false;
}

template<uint32_t ChannelCountBuffer, bool IsOutputSubscribeAble, TEMPLATESPB_FiltersFunctionParams>
	inline void AverageSPB<ChannelCountBuffer, IsOutputSubscribeAble, TEMPLATESPB_FilterParams>::RefreshOVERRIDE(float OutputSignal[1])
{

	float* ch1 = this->InputChannels[0]->ChannelSignalBufferSingle;

	float average = 0;

	//go through channel1's buffer and take the average 
	for (int i = 0; i < ChannelCountBuffer; i++)
	{ 
		average += ch1[i];
	} 
        
	OutputSignal[0] = average / ChannelCountBuffer;
	
	AEITEST_AECoreTestEXE("average", OutputSignal[0] != 0, "should be entered.");



}
