#pragma once

#include "AESPBObservorOutputType.h"
#include "AEUtils.h"
#include "FreeRTOS.h"

#include "AE.h"

template< bool IsOutputSubscribeAble = false, TEMPLATESPB_Filters>
	class AdderSPB :
		public AESPBObservorOutputType<1,
		3,
		IsOutputSubscribeAble,
		TEMPLATESPB_FilterParams,
		1,
		false,
		1,
		false,
		1,
		false,
		1,
		false,
		1,
		false,
		1,
		false,
		1,
		false,
		1,
		false,
		1,
		false,
		1,
		false,
		1,
		false,
		1,
		false>
		//TEMPLATESPB_CHANGEABLE_CountBufferParams(1), subscribeable>
	{
	public:
		AdderSPB();

	private: 
		// Inherited via AESPBObservorOutputType
		void RefreshOVERRIDE(float OutputSignal[1]) override;

	};




template< bool IsOutputSubscribeAble, TEMPLATESPB_FiltersFunctionParams>
	inline AdderSPB <IsOutputSubscribeAble, TEMPLATESPB_FilterParams>::AdderSPB()
	{ 
	}


template< bool IsOutputSubscribeAble, TEMPLATESPB_FiltersFunctionParams>
	inline void AdderSPB <  IsOutputSubscribeAble, TEMPLATESPB_FilterParams>::RefreshOVERRIDE(float OutputSignal[1])
	{

		float* ch1 = this->InputChannels[0]->ChannelSignalBufferSingle;
		float* ch2 = this->InputChannels[1]->ChannelSignalBufferSingle;
		float* ch3 = this->InputChannels[2]->ChannelSignalBufferSingle;
 
 
		OutputSignal[0] = *ch1 + *ch2 + *ch3;
		 
		 
		AEStopTimer(1)
		AELogTimer(1, "adderspb_timertest");
		float timel = AEGetTimerDuration(1); 
		AEITEST_AECoreTestEXE("TimerOfSPBToAdder", timel < 1500000, "time from clock call to final addersbp should be less than time 1.5 millisec"); 
		 
		AEITEST_AECoreTestEXE("averageadder", OutputSignal[0] == 16.5, "should be added.");



	}
