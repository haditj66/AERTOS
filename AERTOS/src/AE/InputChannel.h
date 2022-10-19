#pragma once
#include <cstdint> 
#include "AEUtils.h"
//#include "InputChannelOutputType.h"

#include "FreeRTOS.h"

#include "task.h"


//template<uint16_t CHANNEL_ID, uint32_t INPUTSIZE, uint32_t COUNTBUFFER>
//class InputChannelOutputType;

class InputChannel
{
	friend class AESPBObservor;

	TEMPLATEFOR_AESPBOUTPUT
	friend class AESPBObservorOutputType;

public:

	uint32_t GetCountBufferSize();

	uint32_t InputSize;
	bool CopyInputSignal;

	bool TriggeringChannel;

	uint16_t DivisibilityCounter;
	bool isDivisibleToSlowestChannel;
	uint16_t DivisionOFLargestFrequencyChannel;

	bool isSingleArray;
	bool IsOnlyCountBuffer;
	bool IsOnlyInputSize;

	float* ChannelSignalBufferSingle;
	float** ChannelSignalBufferDouble;

	InputChannel();


	void InitChannelDoublearr(float** signalBuffer, bool toCopy)
	{

		isDivisibleToSlowestChannel = true;
		DivisionOFLargestFrequencyChannel = 0;
		HasBeenInitialized = true;

		CopyInputSignal = toCopy;
		isSingleArray = false;

		if (CopyInputSignal == true)
		{
			ChannelSignalBufferDouble = signalBuffer;
		}
		//assert that InputSize and CountBuffer are not 1
		configASSERT(((InputSize != 1) && (CountBuffer != 1)));

		IsOnlyInputSize = false;
		IsOnlyCountBuffer = false;
	}

	void InitChannelSinglearr(float* signalBuffer, bool toCopy)
	{ 
		DivisibilityCounter = 0;
		isDivisibleToSlowestChannel = true;
		DivisionOFLargestFrequencyChannel = 0;
		HasBeenInitialized = true;

		CopyInputSignal = toCopy;
		isSingleArray = true;

		ChannelSignalBufferSingle = signalBuffer;



		//assert that at least InputSize or CountBuffer is 1
		configASSERT(InputSize == 1 || CountBuffer == 1);

		IsOnlyInputSize = false;
		IsOnlyCountBuffer = false;
		if (InputSize == 1)
		{
			IsOnlyInputSize = true;
		}
		else if (CountBuffer == 1)
		{
			IsOnlyCountBuffer = true;
		}

	}

	void InitChannelidSizeCountBuffer(uint16_t channelId, uint32_t inputSize, uint32_t countBuffer)
	{

		ChannelId = channelId; InputSize = inputSize; CountBuffer = countBuffer;

		CountBufferIndex = 0;
		InputChannelsCreatedSoFar++;

		//assert that the channelId was not a zero 
		configASSERT(channelId != 0);

		//assert that InputSize or CountBuffer are not a zero
		configASSERT(InputSize != 0 || CountBuffer != 0);


	}


	bool SetInput(float* input);

	//virtual void SetInputSignal(float* inputSignal) = 0;

	//template<uint16_t CHANNEL_ID, uint32_t INPUTSIZE, uint32_t  COUNTBUFFER>
	//static InputChannel* GetNewInputChannelFromPool(InputChannelOutputType<CHANNEL_ID, INPUTSIZE, COUNTBUFFER>* inputChannelOutputType);

	//void init(uint16_t channelId, uint32_t inputSize, uint32_t  countBuffer, bool copyInputSignal);

protected:


	bool HasBeenInitialized;

	uint32_t CountBufferIndex;
	uint32_t CountBuffer;

	

	static uint16_t InputChannelsCreatedSoFar;
	//static InputChannel InputChannelsPool[TOTALMAXNUMBEROFOUTPUTSIGNALS_TO_ALL_SPBs];
	uint16_t ChannelId;






	/*
	InputChannel(float* signalBuffer) : InputChannel()
	{
		isSingleArray = true;

		ChannelSignalBufferSingle = signalBuffer;

		//assert that at least InputSize or CountBuffer is 1
		configASSERT(InputSize == 1 || CountBuffer == 1);

		IsOnlyInputSize = false;
		IsOnlyCountBuffer = false;
		if (InputSize == 1)
		{
			IsOnlyInputSize = true;
		}
		else if (CountBuffer == 1)
		{
			IsOnlyCountBuffer = true;
		}
	};

	InputChannel(float** signalBuffer) : InputChannel()
	{
		isSingleArray = false;

		ChannelSignalBufferDouble = signalBuffer;

		//assert that InputSize and CountBuffer are not 1
		configASSERT(InputSize != 1 && CountBuffer != 1);

		IsOnlyInputSize = false;
		IsOnlyCountBuffer = false;
	};*/

	InputChannel(const InputChannel &I) {
		this->ChannelId = I.ChannelId;
		this->InputSize = I.InputSize;
		this->CountBuffer = I.CountBuffer;
		this->CopyInputSignal = I.CopyInputSignal;
	}



};


/*
template<uint16_t CHANNEL_ID, uint32_t INPUTSIZE, uint32_t COUNTBUFFER>
inline InputChannel * InputChannel::GetNewInputChannelFromPool(InputChannelOutputType<CHANNEL_ID, INPUTSIZE, COUNTBUFFER>* inputChannelOutputType)
{

	InputChannelOutputType<CHANNEL_ID, INPUTSIZE, COUNTBUFFER> inputChannelOut;

	InputChannelsPool[InputChannelsCreatedSoFar] = inputChannelOut;

	InputChannel* PoolChannelToReturn = &InputChannelsPool[InputChannelsCreatedSoFar];
	InputChannelsCreatedSoFar++;

	return PoolChannelToReturn;

}
*/

