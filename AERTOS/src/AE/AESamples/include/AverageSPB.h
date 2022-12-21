#pragma once


#include "AESPBObservorOutputType.h"
#include "AEUtils.h"
#include "FreeRTOS.h"
#include "AEFilter.h"

#include "AEIntegrationTesting.h"

template<bool isSubscribable, TEMPLATESPB_CHANGEABLE_CountBuffer(1), TEMPLATESPB_Filters>
	class AverageSPB :
		public AESPBObservorOutputType<1,
		1,
		isSubscribable,
		TEMPLATESPB_FilterParams,
		TEMPLATESPB_CHANGEABLE_CountBufferParams(1)>
	{
	public:
		AverageSPB();

	private:
		//bool odd;

		void RefreshOVERRIDE(float OutputSignal[1]) override;

	};




template<bool isSubscribable, uint32_t CHANNEL1COUNTBUFFER, TEMPLATESPB_FiltersFunctionParams >
	inline AverageSPB<isSubscribable, CHANNEL1COUNTBUFFER, TEMPLATESPB_FilterParams>::AverageSPB()
	{
		//odd = false;
	}

template<bool isSubscribable, uint32_t CHANNEL1COUNTBUFFER, TEMPLATESPB_FiltersFunctionParams >
	inline void AverageSPB<isSubscribable, CHANNEL1COUNTBUFFER, TEMPLATESPB_FilterParams>::RefreshOVERRIDE(float OutputSignal[1])
	{

		float* ch1 = this->InputChannels[0]->ChannelSignalBufferSingle;

		float average = 0;

		//go through channel1's buffer and take the average 
		for (int i = 0; i < CHANNEL1COUNTBUFFER; i++)
		{
			average += ch1[i];
		}

		
		
		OutputSignal[0] = average / CHANNEL1COUNTBUFFER;

		AEITEST_AESamples("averagespp", OutputSignal[0] == 4.5, "average spb should be 45");
	}

