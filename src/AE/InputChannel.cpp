#include "InputChannel.h"
#include "AEUtils.h"
//InputChannel* local = nullptr;

//InputChannel InputChannel::InputChannelsPool[30];
uint16_t InputChannel::InputChannelsCreatedSoFar = 0;


/*
void InputChannel::init(uint16_t channelId, uint32_t inputSize, uint32_t  countBuffer, bool copyInputSignal)
{


	this->ChannelId = channelId;
	this->InputSize = inputSize;
	this->CopyInputSignal = copyInputSignal;
	this->CountBuffer = countBuffer;
}*/

uint32_t InputChannel::GetCountBufferSize()
{
	return CountBuffer;
}

bool InputChannel::SetInput(float * input)
{
	//first check if this was a double or single float array 
	if (isSingleArray)
	{
		if (IsOnlyInputSize)
		{
			if (CopyInputSignal)
			{
				// if the input size is single, that means that the input coming in is a simple single float.
				//no need for a memcpy copy, I can set the value directly
				ChannelSignalBufferSingle[CountBufferIndex] = input[0];
			}

			else
			{

			}

			CountBufferIndex = CountBufferIndex + 1;
			if (CountBufferIndex >= CountBuffer)
			{

				CountBufferIndex = 0;
				return true;
			}

		}
		else// must be from the IsOnlyCountBuffer is single
		{
			// if the input size is many but the CountBuffer is just one, than a single copy will need to be done.

			//However, if this is the Last channel that the inputting obervor outputs to, then instead of 
			//copying the output buffer, it can simply use the outputbuffer as its own.
			  
			if (CopyInputSignal)
			{
				memcpy(ChannelSignalBufferSingle, input, sizeof(float) * InputSize);
			}
			else
			{
				//do nothing as it will use a reference that was passed in from before.
			}


			CountBufferIndex = CountBufferIndex + 1;
			if (CountBufferIndex >= CountBuffer)
			{
				CountBufferIndex = 0;
				return true;
			}

		}
	}
	else//it must be a double float array
	{

	}



	return false;
}

InputChannel::InputChannel()
{ 
	TriggeringChannel = false;
	HasBeenInitialized = false;
	IsOnlyCountBuffer = false;
	IsOnlyInputSize = false;
}
