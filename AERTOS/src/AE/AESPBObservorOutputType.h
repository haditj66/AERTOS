#pragma once
#include "AESPBObservor.h"
#include "AEObservorSensor.h"
#include "AEUtils.h"

#include "AEFilter.h"

//Helper Macros ------------------------------------------------------------------


#define TEMPLATESPB_CHANGEABLE_CountBuffer(forChannel) uint32_t CHANNELCOUNTBUFFER##forChannel
#define TEMPLATESPB_CHANGEABLE_CountBufferParams(forChannel) CHANNELCOUNTBUFFER##forChannel, false

#define TEMPLATESPB_CHANGEABLE_InputSize(forChannel) uint32_t CHANNELINPUTSIZE##forChannel
#define TEMPLATESPB_CHANGEABLE_InputSizeParams(forChannel) CHANNELINPUTSIZE##forChannel, true



//


typedef float* HasEitherSingleInputOrCountBuffer;
typedef float** NOTEitherSingleInputOrCountBuffer;
/*
template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS, uint8_t NUMOFFILTERS,
#if MAXNUMBEROF_FILTERS >= 1
	class TFilter1 = AENull,
	#endif
#if MAXNUMBEROF_FILTERS >= 2
	class TFilter2 = AENull,
#endif
#if MAXNUMBEROF_FILTERS >= 3
	class TFilter3 = AENull,
#endif
#if MAXNUMBEROF_FILTERS >= 4
	class TFilter4 = AENull,
#endif
#if MAXNUMBEROF_FILTERS >= 5
	class TFilter5 = AENull,
#endif

	//uint32_t INPUTSIZE1 = 1, uint32_t COUNTBUFFER1 = 1,
	//uint32_t INPUTSIZE2 = 1, uint32_t COUNTBUFFER2 = 1,
	//uint32_t INPUTSIZE3 = 1, uint32_t COUNTBUFFER3 = 1>
	uint32_t TheParameterNOTone1 = 1, bool isParameterNOToneInputSize1 = true,
	uint32_t TheParameterNOTone2 = 1, bool isParameterNOToneInputSize2 = true,
	uint32_t TheParameterNOTone3 = 1, bool isParameterNOToneInputSize3 = true>*/
template<uint32_t OUTPUTSIZE = 1, uint16_t NUMOFINPUTSIGNALS = 1 , bool IsOutputSubscribeAble = false, uint8_t NUMOFFILTERS = 0,  class TFilter1 = AENullClass, class TFilter2 = AENullClass, uint8_t Filter2LinksFrom = 0, class TFilter3 = AENullClass, uint8_t Filter3LinksFrom = 0, class TFilter4 = AENullClass, uint8_t Filter4LinksFrom = 0, class TFilter5 = AENullClass, uint8_t Filter5LinksFrom = 0,
	uint32_t TheParameterNOTone1 = 1, bool isParameterNOToneInputSize1 = true,
	uint32_t TheParameterNOTone2 = 1, bool isParameterNOToneInputSize2 = true,
	uint32_t TheParameterNOTone3 = 1, bool isParameterNOToneInputSize3 = true,
	uint32_t TheParameterNOTone4 = 1, bool isParameterNOToneInputSize4 = true,
	uint32_t TheParameterNOTone5 = 1, bool isParameterNOToneInputSize5 = true,
	uint32_t TheParameterNOTone6 = 1, bool isParameterNOToneInputSize6 = true,
	uint32_t TheParameterNOTone7 = 1, bool isParameterNOToneInputSize7 = true,
	uint32_t TheParameterNOTone8 = 1, bool isParameterNOToneInputSize8 = true,
	uint32_t TheParameterNOTone9 = 1, bool isParameterNOToneInputSize9 = true,
	uint32_t TheParameterNOTone10 = 1, bool isParameterNOToneInputSize10 = true,
	uint32_t TheParameterNOTone11 = 1, bool isParameterNOToneInputSize11 = true,
	uint32_t TheParameterNOTone12 = 1, bool isParameterNOToneInputSize12 = true
	

>
class AESPBObservorOutputType : public AESPBObservor
{

	friend class SPBDataSubscription;
	friend class SPBSubprivateImp;
public:


#if MAXNUMBEROF_FILTERS >= 1 
	TFilter1 Filter1;
#endif 
#if MAXNUMBEROF_FILTERS >= 2 
	TFilter2 Filter2;
#endif 
#if MAXNUMBEROF_FILTERS >= 3 
	TFilter3 Filter3;
#endif
#if MAXNUMBEROF_FILTERS >= 4
	TFilter4 Filter4;
#endif
#if MAXNUMBEROF_FILTERS >= 5
	TFilter5 Filter5;
#endif

	InputChannel channels[NUMOFINPUTSIGNALS];
	//float channelbuffer1[TheParameterNOTone1];
	//float channelbuffer2[TheParameterNOTone2];
	//float channelbuffer3[TheParameterNOTone3];

	float LargestCountBufferLinkedSoFar;

	static const uint32_t OUTPUTSIZE_Static = OUTPUTSIZE;

	AESPBObservorOutputType();


	void AddSignalFlowLinkToChannelWithCopy1(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone1], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy2(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone2], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy3(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone3], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy4(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone4], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy5(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone5], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy6(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone6], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy7(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone7], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy8(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone8], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy9(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone9], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy10(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone10], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy11(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone11], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithCopy12(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone12], uint8_t toOutPutFilter = 0);
	void AddSignalFlowLinkToChannelWithReference(AESPBObservor * fromObservor, uint32_t toChannel, uint8_t toOutPutFilter = 0);


	 
	float GetObservationFromFilter(uint8_t filterNum);

	

protected:

	 


	uint16_t _ObservorsSignalLinkedToMe[NUMOFINPUTSIGNALS];


	void RefreshGaurd(void * pvParameters);
	void _Refresh(); 
	void _RefreshFromBaseClass() override;
	virtual void RefreshOVERRIDE(float OutputSignal[OUTPUTSIZE]) = 0;


	virtual void CheckIfConfiguredProperly()  const override;

	void InitializeFilters() override;


	

private:

	

	void _UpdateFilters(float OutputSignal);

	void _PrivateAddLinkWithCopy(AEObservorBase * fromObservor, float* channelBuffer, uint8_t toOutPutFilter, uint8_t index);

	float OutputsOfFilters[(NUMOFFILTERS == 0) + NUMOFFILTERS];
	float OutPutSignalBuffer[OUTPUTSIZE]; 
	 

	//stuff dealing with data subscribing ---------------------------------------- 
	//if subscribeable, make it output size. if not, make it one
	float OutPutSignalBufferPrev[((IsOutputSubscribeAble == true) * (OUTPUTSIZE)) + (IsOutputSubscribeAble == false)];
	  
#ifdef	SPB_OF_FILTER1_SUBSCRIBED
float filter1Prev;
#endif 
#ifdef	SPB_OF_FILTER2_SUBSCRIBED
	float filter2Prev;
#endif 
#ifdef	SPB_OF_FILTER3_SUBSCRIBED
	float filter3Prev;
#endif 
#ifdef	SPB_OF_FILTER4_SUBSCRIBED
	float filter4Prev;
#endif 
#ifdef	SPB_OF_FILTER5_SUBSCRIBED
	float filter5Prev;
#endif  

	//---------------------------------------------------------------------------------






	void SetUpTasks() override;

};

 



TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::CheckIfConfiguredProperly()  const
{
	AESPBObservor::CheckIfConfiguredProperly();

	configASSERT(isInitialized == true);
}



TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::SetUpTasks()
{ 

	if (styleOfSPB == StyleOfSPB::EachSPBTask)
	{
		//create the tasks 
		AESPBObservorOutputType *pToThisClass = this;
		xTaskCreate([](void* p) {static_cast<AESPBObservorOutputType*>(p)->RefreshGaurd(nullptr); }, "RefreshGaurdTask", 500, pToThisClass, AOPRIORITYMEDIUM, &GaurdTaskToObjectExecutionHandle);

	}

}

TEMPLATEFOR_AESPBOUTPUT
inline AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>
::AESPBObservorOutputType() 
{

	isInitialized = false;

	this->IsStartingSPB = false;

	this->isOutputsubscribable = IsOutputSubscribeAble;

	//create the tasks 
	//AESPBObservorOutputType *pToThisClass = this;
	//xTaskCreate([](void* p) {static_cast<AESPBObservorOutputType*>(p)->RefreshGaurd(nullptr); }, "RefreshGaurdTask", 500, pToThisClass, AOPRIORITYMEDIUM, &GaurdTaskToObjectExecutionHandle);


	ObservorsSignalLinkedToMe = _ObservorsSignalLinkedToMe;

	NumOfInputsSignals = NUMOFINPUTSIGNALS;

	OutputSize = OUTPUTSIZE;

	OutputSignal = OutPutSignalBuffer;
	OutputSignalPrev = OutPutSignalBufferPrev;

	isSingleOutputCopyOuputAlreadySet = false;
	LargestCountBufferLinkedSoFar = 0;


	//initialize all input channels
	for (uint32_t i = 0; i < NUMOFINPUTSIGNALS; i++)
	{
		InputChannels[i] = &channels[i];
	}

	//initialize all input channels that this SPB has activated. however I am not able to initialize them 
	//with the array buffers that they have yet because the decision of whether to copy or pass by reference is still not
	//decided. It is decided by the user at the SPBLinking point.
	if (NUMOFINPUTSIGNALS > 0)
	{
		if (isParameterNOToneInputSize1)
		{
			channels[0].InitChannelidSizeCountBuffer(1, TheParameterNOTone1, 1);
		}
		else
		{
			channels[0].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone1);
		}
	}
	if (NUMOFINPUTSIGNALS > 1)
	{
		if (isParameterNOToneInputSize2)
		{
			channels[1].InitChannelidSizeCountBuffer(1, TheParameterNOTone2, 1);
		}
		else
		{
			channels[1].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone2);
		}
	}
	if (NUMOFINPUTSIGNALS > 2)
	{
		if (isParameterNOToneInputSize3)
		{
			channels[2].InitChannelidSizeCountBuffer(1, TheParameterNOTone3, 1);
		}
		else
		{
			channels[2].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone3);
		}
	}

	if (NUMOFINPUTSIGNALS > 3)
	{
		if (isParameterNOToneInputSize4)
		{
			channels[3].InitChannelidSizeCountBuffer(1, TheParameterNOTone4, 1);
		}
		else
		{
			channels[3].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone4);
		}
	}
	if (NUMOFINPUTSIGNALS > 4)
	{
		if (isParameterNOToneInputSize5)
		{
			channels[4].InitChannelidSizeCountBuffer(1, TheParameterNOTone5, 1);
		}
		else
		{
			channels[4].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone5);
		}
	}
	if (NUMOFINPUTSIGNALS > 5)
	{
		if (isParameterNOToneInputSize6)
		{
			channels[5].InitChannelidSizeCountBuffer(1, TheParameterNOTone6, 1);
		}
		else
		{
			channels[5].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone6);
		}
	}
	if (NUMOFINPUTSIGNALS > 6)
	{
		if (isParameterNOToneInputSize7)
		{
			channels[6].InitChannelidSizeCountBuffer(1, TheParameterNOTone7, 1);
		}
		else
		{
			channels[6].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone7);
		}
	}
	if (NUMOFINPUTSIGNALS > 7)
	{
		if (isParameterNOToneInputSize8)
		{
			channels[7].InitChannelidSizeCountBuffer(1, TheParameterNOTone8, 1);
		}
		else
		{
			channels[7].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone8);
		}
	}
	if (NUMOFINPUTSIGNALS > 8)
	{
		if (isParameterNOToneInputSize9)
		{
			channels[8].InitChannelidSizeCountBuffer(1, TheParameterNOTone9, 1);
		}
		else
		{
			channels[8].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone9);
		}
	}
	if (NUMOFINPUTSIGNALS > 9)
	{
		if (isParameterNOToneInputSize10)
		{
			channels[9].InitChannelidSizeCountBuffer(1, TheParameterNOTone10, 1);
		}
		else
		{
			channels[9].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone10);
		}
	}
	if (NUMOFINPUTSIGNALS > 10)
	{
		if (isParameterNOToneInputSize11)
		{
			channels[10].InitChannelidSizeCountBuffer(1, TheParameterNOTone11, 1);
		}
		else
		{
			channels[10].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone11);
		}
	}
	if (NUMOFINPUTSIGNALS > 11)
	{
		if (isParameterNOToneInputSize12)
		{
			channels[11].InitChannelidSizeCountBuffer(1, TheParameterNOTone12, 1);
		}
		else
		{
			channels[11].InitChannelidSizeCountBuffer(1, 1, TheParameterNOTone12);
		}
	}


	//assert that at least one of a channels inputsize or countbuffer is greater than 1. if they are both 1, then this should not have
	//been a SPB
	for (uint32_t i = 0; i < NUMOFINPUTSIGNALS; i++)
	{
		//this does not need to happen though if the SPB in question has multiple inputs, as the inputs with 1 input size and 1 cpuntbuffer
		//size will be ignored.
		if (NUMOFINPUTSIGNALS == 1)
		{
			//configASSERT(!(InputChannels[i]->InputSize == 1 && InputChannels[i]->GetCountBufferSize() == 1));
		}

	}



}




TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy1(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone1], uint8_t toOutPutFilter)
{
	uint32_t index = 1;

	_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}

TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy2(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone2], uint8_t toOutPutFilter)
{
	uint32_t index = 2;

	_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}

TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy3(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone3], uint8_t toOutPutFilter)
{
	uint32_t index = 3;

	_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}

TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy4(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone4], uint8_t toOutPutFilter)
{
	uint32_t index = 4;

	_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}
TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy5(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone5], uint8_t toOutPutFilter)
{
uint32_t index = 5;

_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}
TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy6(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone6], uint8_t toOutPutFilter)
{
uint32_t index = 6;

_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}
TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy7(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone7], uint8_t toOutPutFilter)
{
uint32_t index = 7;

_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}
TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy8(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone8], uint8_t toOutPutFilter)
{
uint32_t index = 8;

_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}
TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy9(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone9], uint8_t toOutPutFilter)
{
uint32_t index = 9;

_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}
TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy10(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone10], uint8_t toOutPutFilter)
{
uint32_t index = 10;

_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}
TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy11(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone11], uint8_t toOutPutFilter)
{
uint32_t index = 11;

_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}
TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithCopy12(AEObservorBase * fromObservor, float(&channelBuffer)[TheParameterNOTone12], uint8_t toOutPutFilter)
{
uint32_t index = 12;

_PrivateAddLinkWithCopy(fromObservor, channelBuffer, toOutPutFilter, index);
}





TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::_PrivateAddLinkWithCopy(AEObservorBase * fromObservor, float* channelBuffer, uint8_t toOutPutFilter, uint8_t index)
{
	this->ObservorsSignalLinkedToMe[IndexNumOfObservorsSignalLinkedSoFar] = fromObservor->ObservorId;
	IndexNumOfObservorsSignalLinkedSoFar++;

	//assert that the channel the observor is linking to has not been linked to yet.
	configASSERT(channels[index - 1].HasBeenInitialized == false);

	this->InputChannels[index - 1]->InitChannelSinglearr(channelBuffer, true);



	//next will finish
	//I know already that the toObservor is a AESPBObservor. however i do not know what the fromobservor is. It could be a sensor observor.
	// I need to check before casting so that I can call the correct overrided AddSignalFlowLink
	if (fromObservor->GetMyObservorType() & ObservorType::SPB)
	{
		fromObservor->AddSignalFlowLink(static_cast<AESPBObservor*>(this), index, toOutPutFilter);
	}
	else if (fromObservor->GetMyObservorType() & ObservorType::Sensor)
	{
		this->IsStartingSPB = true;
		static_cast<AEObservorBase*>(fromObservor)->AddSignalFlowLink(static_cast<AESPBObservor*>(this), index, toOutPutFilter);
	}
}




TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::AddSignalFlowLinkToChannelWithReference(AESPBObservor * fromObservor, uint32_t toChannel, uint8_t toOutPutFilter)
{
	uint32_t index = toChannel - 1;
	uint32_t countbufferOfTHisLinkedToChannel = this->InputChannels[index]->CountBuffer;

	this->ObservorsSignalLinkedToMe[IndexNumOfObservorsSignalLinkedSoFar] = fromObservor->ObservorId;
	IndexNumOfObservorsSignalLinkedSoFar++;

	//assert that the channel the observor is linking to has not been linked to yet.
	configASSERT(channels[index].HasBeenInitialized == false);
	channels[index].InitChannelSinglearr(fromObservor->GetOutputAddress(), false);


	//no need for casting as I know that this is a spbobservor
	fromObservor->AddSignalFlowLink(static_cast<AESPBObservor*>(this), toChannel, toOutPutFilter);


	//i need to make my asserts for if this is a single output size.
	//if the  fromObservor is a single output, than the first out channel needs to be to the SPB with the largest countbuffer. 
	//However I do not know if the user will do any other links, so the user MUST provide the pass-to-reference links first.
	if (fromObservor->GetOutPutSize() == 1)
	{
		//It is not possible for single output single input SPBs to pass by reference. This is because the fromSPB only sends one
		//float and does not have a outputsignal cappable of holding the buffer.
		configASSERT(fromObservor->NumOfSPBObservorsIPointTo > 1);
		//make sure that this signal flow link being set for pass-by-copy has not been done yet as a copy for a single output
		//can only be done once.
		configASSERT(fromObservor->isSingleOutputCopyOuputAlreadySet == false);

		//make sure that the channel this is linking to, is the biggest countbuffer linked to so far.
		configASSERT((countbufferOfTHisLinkedToChannel) > LargestCountBufferLinkedSoFar);
		//now make sure this countBuffer is divisible by all countbuffers linked so far.
		for (uint32_t i = 0; i < fromObservor->NumOfSPBObservorsIPointTo - 1; i++)
		{

			uint32_t countbuffersizeOfOtherLinkedChannels = fromObservor->SPBObservorsIPointTo[i]->InputChannels[fromObservor->ChannelIdsIConnectTo[i]]->GetCountBufferSize(); // 
																																											   //make sure it is divisible
			configASSERT((countbufferOfTHisLinkedToChannel % countbuffersizeOfOtherLinkedChannels) == 0);
		}
		//

		fromObservor->isSingleOutputCopyOuputAlreadySet = true;
	}

	//i need to make my asserts for if this is a multiple output size.
	else if (fromObservor->GetOutPutSize() > 1)
	{
		//the only real condition for if it is multiple output size is if that no linking toobservor modifys the input buffer. 
		//this can be done later perhaps by passing a const instead. however for now, no asserts need to be done.
	}
}



TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>
::_RefreshFromBaseClass()
{
	_Refresh();
}

TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>
::_Refresh()
{

	//only do something if this observor is on.
	if (this->isObservorOn)
	{

		//TimeForEnteringAndReenteringAndPrintAll(1)

		//before this spb starts updating, it needs to fill the prevOututvariable
		//if has any S_AO
		if (this->numOfDataSubscribersSoFar > 0)
		{
			memcpy(OutPutSignalBufferPrev, OutPutSignalBuffer, OutputSize * 4);

			//write to all previous filters that were subscribed to
#ifdef	SPB_OF_FILTER1_SUBSCRIBED
			filter1Prev = Filter1.FilterOutputValue;
#endif 
#ifdef	SPB_OF_FILTER2_SUBSCRIBED
			filter2Prev = Filter2.FilterOutputValue;
#endif 
#ifdef	SPB_OF_FILTER3_SUBSCRIBED
			filter3Prev = Filter3.FilterOutputValue;
#endif 
#ifdef	SPB_OF_FILTER4_SUBSCRIBED
			filter4Prev = Filter4.FilterOutputValue;
#endif 
#ifdef	SPB_OF_FILTER5_SUBSCRIBED
			filter5Prev = Filter5.FilterOutputValue;
#endif 

		}


		//if this spb is supscribing to any spbs, update that data
		AE_UpdateALLSPBSubscriptions

			isCurrentlyExecuting = true;
		RefreshOVERRIDE(OutputSignal);
		if (NUMOFFILTERS > 0)
		{
			//to use filters on an spb, the OUTPUTSIZE needs to be one
			configASSERT(OUTPUTSIZE == 1);
			_UpdateFilters(OutputSignal[0]);
		}
		isCurrentlyExecuting = false;



		//TimeForEnteringAndReenteringAndPrintAll(1)// 16us for an average spb of 10 bufercount



 //if this is an EndOfChain observor, update the chain for a refresh
 //REMEMBER THAT IF THIS IS AN ENDCHAIN, IT NEEDS TO BE SET TO A FIXED HIGHEST PRIORITY!
 //However I dont want the RefreshOVERRIDE() to also run as highest proiority because what if it is long running.
 // I need a seperate STATIC task IF it is endchain only.
		if (IsEndChain == true)
		{

			//but what about if another task calls this. wouldnt it overwrite since it is not a queue?
			//It shouldnt because this is highest priority. as soon as this task runs, it will preempt all other tasks
			// making it impossible for another task to call it without it finishing first. This of course only works by making
			//sure other SPB observors that are already of highest priority DONT call this task and instead just run the code in that
			// task directly.

			//TODO: get this if statement working
			//if (AO_Priority != HIGHEST_PRIORITY)
			//{
			xTaskNotify(RefreshValueUpdateGaurdTask, ObservorId, eSetValueWithoutOverwrite);
			//}
			//else
			//{
			//for (int i = 0; i < numOfObservorsOfInfluence; i++)
			//{
			//*ObservorsOfInfluenceNeedARefeshValues[i] = true;
			//}
			//} 

		}


		//send the output signal to any SPBs that I point to
		//check if there are any filters that will need to be accounted for.

		if (NUMOFFILTERS > 0)
		{
			for (uint16_t i = 0; i < NumOfSPBObservorsIPointTo; i++)
			{
				//this 0xff means that it is not set to a filter
				if (OutputFilterThatSignalGoesFrom[i] == 0xff)
				{
					SPBObservorsIPointTo[i]->InputSignal(OutputSignal, ChannelIdsIConnectTo[i]);

				}
				else
				{
					float arrFil[1];
					arrFil[0] = OutputsOfFilters[OutputFilterThatSignalGoesFrom[i]];
					SPBObservorsIPointTo[i]->InputSignal(arrFil, ChannelIdsIConnectTo[i]);
				}

			}
		}
		else
		{
			for (uint16_t i = 0; i < NumOfSPBObservorsIPointTo; i++)
			{
				SPBObservorsIPointTo[i]->InputSignal(OutputSignal, ChannelIdsIConnectTo[i]);
			}
		}
		
		//notify all tdus that I flow into that they need to update
		if (this->numOfTdusThatAreSetToMyClock > 0)
		{
			for (uint16_t i = 0; i < this->numOfTdusThatAreSetToMyClock; i++)
			{
				xTaskNotifyGive(*UpdateTasksForTDUsIFlowTo[i]);
			}
			
		}
		 


	}
}



TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>
::RefreshGaurd(void * pvParameters)
{
	uint32_t ulNotifiedValueCurrentSession;

	while (true)
	{
              //tasknotifies take 80us 
		xTaskNotifyWait(pdFALSE, pdTRUE, &ulNotifiedValueCurrentSession, portMAX_DELAY);
 
		_Refresh();
	}
}





TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>
::_UpdateFilters(float OutputSignal)
{

	switch (NUMOFFILTERS)
	{
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 1 
	case 1:
		//static int16_t df = (int16_t)*this->Dataptr;
		OutputsOfFilters[0] = this->Filter1(OutputSignal);


		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 2
	case 2:
		//filter1 cannot link from any other output except for the main one. so

		this->OutputsOfFilters[0] = this->Filter1(OutputSignal);

		//check if the output of filter connects FROM another filter
		// a value of zero means that it does not.
		if (Filter2LinksFrom != 0)
		{
			OutputsOfFilters[1] = Filter2(OutputsOfFilters[Filter2LinksFrom - 1]);
		}
		else
		{
			OutputsOfFilters[1] = Filter2(OutputSignal);
		}
#ifdef IARBuild
		StopTimer(2)
#endif // DEBUG


			break;

#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 3
	case 3:
		//filter1 cannot link from any other output except for the main one. so
		OutputsOfFilters[0] = Filter1(OutputSignal());

		//check if the output of filter connects FROM another filter
		// a value of zero means that it does not.
		if (Filter2LinksFrom != 0)
		{
			OutputsOfFilters[1] = Filter2(OutputsOfFilters[Filter2LinksFrom]);
		}
		else
		{
			OutputsOfFilters[1] = Filter2(OutputSignal);
		}

		if (Filter3LinksFrom != 0)
		{
			OutputsOfFilters[2] = Filter3(OutputsOfFilters[Filter3LinksFrom]);
		}
		else
		{
			OutputsOfFilters[2] = Filter3(OutputSignal);
		}


		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 4
	case 4:
		//filter1 cannot link from any other output except for the main one. so
		OutputsOfFilters[0] = Filter1(OutputSignal);

		//check if the output of filter connects FROM another filter
		// a value of zero means that it does not.
		if (Filter2LinksFrom != 0)
		{
			OutputsOfFilters[1] = Filter2(OutputsOfFilters[Filter2LinksFrom]);
		}
		else
		{
			OutputsOfFilters[1] = Filter2(OutputSignal);
		}

		if (Filter3LinksFrom != 0)
		{
			OutputsOfFilters[2] = Filter3(OutputsOfFilters[Filter3LinksFrom]);
		}
		else
		{
			OutputsOfFilters[2] = Filter3(OutputSignal);
		}

		if (Filter4LinksFrom != 0)
		{
			OutputsOfFilters[3] = Filter4(OutputsOfFilters[Filter4LinksFrom]);
		}
		else
		{
			OutputsOfFilters[3] = Filter4(OutputSignal);
		}


		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 5
	case 5:
		//filter1 cannot link from any other output except for the main one. so
		OutputsOfFilters[0] = Filter1(OutputSignal);

		//check if the output of filter connects FROM another filter
		// a value of zero means that it does not.
		if (Filter2LinksFrom != 0)
		{
			OutputsOfFilters[1] = Filter2(OutputsOfFilters[Filter2LinksFrom]);
		}
		else
		{
			OutputsOfFilters[1] = Filter2(OutputSignal);
		}

		if (Filter3LinksFrom != 0)
		{
			OutputsOfFilters[2] = Filter3(OutputsOfFilters[Filter3LinksFrom]);
		}
		else
		{
			OutputsOfFilters[2] = Filter3(OutputSignal);
		}

		if (Filter4LinksFrom != 0)
		{
			OutputsOfFilters[3] = Filter4(OutputsOfFilters[Filter4LinksFrom]);
		}
		else
		{
			OutputsOfFilters[3] = Filter4(OutputSignal);
		}

		if (Filter5LinksFrom != 0)
		{
			OutputsOfFilters[4] = Filter5(OutputsOfFilters[Filter5LinksFrom]);
		}
		else
		{
			OutputsOfFilters[4] = Filter5(OutputSignal);
		}

		break;
#endif 
	default:
		break;
	}




	/*input the data into all SPbs that I signalflowlink to
	for (int i = 0; i < NumOfSPBObservorsIPointTo; i++)
	{
		float arr[1];
		arr[0] = OutputsOfFilters[OutputFilterThatSignalGoesFrom[i]];
		SPBObservorsIPointTo[i]->InputSignal(arr, ChannelIdsIConnectTo[i]);

	}*/
}



TEMPLATEFOR_AESPBOUTPUT
inline float AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::GetObservationFromFilter(uint8_t filterNum)

{
	switch (filterNum)
	{
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 1  
	case 1:
		return Filter1.GetObservation();
		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 2  
	case 2:
		return Filter2.GetObservation();
		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 3 
	case 3:
		return Filter3.GetObservation();
		break;
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 4
	case 4:
		return Filter4.GetObservation();
		break;
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 5
	case 5:
		return Filter5.GetObservation();
		break;
#endif 

	default:
		break;
	}

	//a valid filter was not chosen
	configASSERT(false);
	return 1;
}


TEMPLATEFOR_AESPBOUTPUT
inline void AESPBObservorOutputType<TEMPLATEFOR_AESPBOUTPARAMS>::InitializeFilters()
{
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 1  
	Filter1.Initialize(1 / GetFrequencyIRefreshAt());
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 2  
	Filter2.Initialize(1 / GetFrequencyIRefreshAt());
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 3 
	Filter3.Initialize(1 / GetFrequencyIRefreshAt());
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 4
	Filter4.Initialize(1 / GetFrequencyIRefreshAt());
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 5
	Filter5.Initialize(1 / GetFrequencyIRefreshAt());
#endif 
}

























/*

template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS, uint32_t TheParameterNOTone1, bool isParameterNOToneInputSize1, uint32_t TheParameterNOTone2, bool isParameterNOToneInputSize2, uint32_t TheParameterNOTone3, bool isParameterNOToneInputSize3>
inline void AESPBObservorOutputType<OUTPUTSIZE, NUMOFINPUTSIGNALS, TheParameterNOTone1, isParameterNOToneInputSize1, TheParameterNOTone2, isParameterNOToneInputSize2, TheParameterNOTone3, isParameterNOToneInputSize3>::AddSignalFlowLinkToChannel(AESPBObservor * toObservor)
{
	toObservor.
}

template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS, uint32_t INPUTSIZE1, uint32_t COUNTBUFFER1, uint32_t INPUTSIZE2, uint32_t COUNTBUFFER2, uint32_t INPUTSIZE3, uint32_t COUNTBUFFER3>
inline void AESPBObservorOutputType<OUTPUTSIZE, NUMOFINPUTSIGNALS, INPUTSIZE1, COUNTBUFFER1, INPUTSIZE2, COUNTBUFFER2, INPUTSIZE3, COUNTBUFFER3>::AddSignalFlowLinkToChannel1(AESPBObservor * fromObservor, InputChannel & channel1)
{
	//assert that the number of input signals this SPB has is less than the NUMOFINPUTSIGNALS
	configASSERT(NUMOFINPUTSIGNALS <= 1);

	//assert that the INPUTSIZE1 is the same as the input size of the inputchannel that is passed in.
	configASSERT(channel1.InputSize == INPUTSIZE1);
	//assert that the countbuffer is the same as the countbuffer of the inputchannel that is passed in.
	configASSERT(channel1.GetCountBufferSize() == COUNTBUFFER1);

	//set the buffer provided into the proper input channel
	InputChannels[0]->ChannelSignalBufferSingle = channelbuffer;

}

template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS,
	uint32_t TheParameterNOTone1, uint32_t TheParameterThatIsone1,
	uint32_t TheParameterNOTone2, uint32_t TheParameterThatIsone2,
	uint32_t TheParameterNOTone3, uint32_t TheParameterThatIsone3>
inline void AESPBObservorOutputType<OUTPUTSIZE, NUMOFINPUTSIGNALS, TheParameterNOTone1, TheParameterThatIsone1, TheParameterNOTone2, TheParameterThatIsone2, TheParameterNOTone3, TheParameterThatIsone3>::AddSignalFlowLinkToChannel1(AESPBObservor * fromObservor, float channelbuffer[TheParameterNOTone1])
{
	//assert that the number of input signals this SPB has is less than the NUMOFINPUTSIGNALS
	configASSERT(NUMOFINPUTSIGNALS <= 1);

	//assert that the INPUTSIZE1 is the same as the input size of the input channel that is passed in.
	configASSERT(NUMOFINPUTSIGNALS <= 1);

	//set the buffer provided into the proper input channel
	//channels[0].
	InputChannels[0]->ChannelSignalBufferSingle = channelbuffer;



}

template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS, uint32_t TheParameterNOTone1, uint32_t TheParameterThatIsone1, uint32_t TheParameterNOTone2, uint32_t TheParameterThatIsone2, uint32_t TheParameterNOTone3, uint32_t TheParameterThatIsone3>
inline void AESPBObservorOutputType<OUTPUTSIZE, NUMOFINPUTSIGNALS, TheParameterNOTone1, TheParameterThatIsone1, TheParameterNOTone2, TheParameterThatIsone2, TheParameterNOTone3, TheParameterThatIsone3>::AddSignalFlowLinkToChannel2(AESPBObservor * fromObservor, float channelbuffer[TheParameterNOTone2])
{
}

template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS, uint32_t TheParameterNOTone1, uint32_t TheParameterThatIsone1, uint32_t TheParameterNOTone2, uint32_t TheParameterThatIsone2, uint32_t TheParameterNOTone3, uint32_t TheParameterThatIsone3>
inline void AESPBObservorOutputType<OUTPUTSIZE, NUMOFINPUTSIGNALS, TheParameterNOTone1, TheParameterThatIsone1, TheParameterNOTone2, TheParameterThatIsone2, TheParameterNOTone3, TheParameterThatIsone3>::AddSignalFlowLinkToChannel3(AESPBObservor * fromObservor, float channelbuffer[TheParameterNOTone3])
{
}


 */