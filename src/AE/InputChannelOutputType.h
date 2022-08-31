#pragma once

#include "InputChannel.h"
/*
template<uint16_t CHANNEL_ID, uint32_t INPUTSIZE, uint32_t  COUNTBUFFER>
class InputChannelOutputType : public InputChannel
{
public:

  
	float ThisChannelsInputSignalBuffer[COUNTBUFFER][INPUTSIZE];

	InputChannelOutputType();


};



template<uint16_t CHANNEL_ID, uint32_t INPUTSIZE, uint32_t COUNTBUFFER>
inline InputChannelOutputType<CHANNEL_ID, INPUTSIZE, COUNTBUFFER>::InputChannelOutputType()
{

	for (uint32_t i = 0; i < INPUTSIZE; i++)
	{
		//ChannelSignalBufferAddress = ThisChannelsInputSignalBuffer;
	} 

	this->ChannelId = CHANNEL_ID;
	this->InputSize = INPUTSIZE;
	this->CountBuffer = COUNTBUFFER;
	this->CopyInputSignal = true;

}

*/

/*
// use this class if your input size is one. this way I dont have to use up all that memmor to hold pointers of size counterBuffer
//to all those float arrays of size one.

template<uint16_t CHANNEL_ID, uint32_t  COUNTBUFFER>
class InputChannelOutputType : public InputChannel
{
public:


	float ThisChannelsInputSignalBuffer[COUNTBUFFER];

	InputChannelOutputType();


};*/