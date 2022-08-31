#pragma once
#include "AEObservorBase.h"
#include "InputChannel.h"
#include "AEUtils.h" 

#include "SPBDataSubscription.h"

//forward declare
class TaskPoolForSPBChain;


class AESPBObservor : public AEObservorBase
{

	TEMPLATEFOR_AESPBOUTPUT
	friend class AESPBObservorOutputType;
	friend class AEObservorBase;
	TEMPLATEFORNoDefaults_AEClock
	friend class AEClock;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults_friend>
	friend class AEAOUpdateableAAP;
	friend class TaskSPBChain;

public:

	bool isSingleOutputCopyOuputAlreadySet;

	uint16_t TypeOfSPB;

	uint32_t GetOutPutSize();

	AESPBObservor( );

	void InitSPBObserver(StyleOfSPB styleOfSPB = StyleOfSPB::EachSPBTask, TaskPoolForSPBChain* taskPoolForSPBChain = nullptr);

	float* GetOutputAddress() const;
	uint16_t GetNumOfInputsSignals() const;
	
	uint16_t* ObservorsSignalLinkedToMe;

	static void ConfigureSPBs();

	//uint16_t ObservorInputIdsHandedOutSoFar;
	//void SetObservorIPointTo(AESPBObservor * sPBObservorsIPointTo);
	void InputSignal(float * input, uint16_t toChannelId);

protected:


	StyleOfSPB styleOfSPB;

	bool IsStartingSPB;
	bool isInitialized;
	bool isCurrentlyExecuting;

	TaskPoolForSPBChain* MyTaskPoolChain;

	uint16_t numOfDataSubscribersSoFar;

 	uint16_t NumOfInputsSignals;
	//virtual void SetInputChannelsOVERRIDE(InputChannel* ChannelsToSet[MAXNUMBEROFINPUTSIGNALS_TO_A_SPB]) = 0;
	InputChannel* InputChannels[MAXNUMBEROFINPUTSIGNALS_TO_A_SPB];
	InputChannel* LowestFrequencyTriggeringInputChannel;

	//counts the number of observors that have been signal linked to this observor so far.
	uint16_t IndexNumOfObservorsSignalLinkedSoFar;
	void AddSignalFlowLink(AESPBObservor * toObservor, uint16_t ToChannel, uint8_t toOutPutFilter = 0) override;
	void AddFilterToOutput();
	 
	virtual void _RefreshFromBaseClass() = 0; 


	static void ConfigureSPBTypesAndInputTypes();
	static void ConfigureAllSPBsFromNodes(AEObservorBase* (&nodes)[MAXNUMOFOBSERVORS], uint16_t& nodeListSize);
	 
	uint8_t numOfTdusThatAreSetToMyClock; 
	template<class TTDUToSetToThisClock> 
	void SetTDUToMyClock(TTDUToSetToThisClock TDUSetToThisSPBClock);

	virtual void CheckIfConfiguredProperly()  const override;

	virtual void SetUpTasks() = 0;


	//virtual uint32_t SetOutputSizeOVERRIDE() = 0;
	//uint32_t InputSize[MAXNUMBEROFINPUTSIGNALS_TO_A_SPB];
	//uint32_t CountBuffer[MAXNUMBEROFINPUTSIGNALS_TO_A_SPB];


	//bool CopyInputSignal[MAXNUMBEROFINPUTSIGNALS_TO_A_SPB];

	uint32_t OutputSize;
	float* OutputSignal;
	float* OutputSignalPrev;

	bool isOutputsubscribable;

	//stuff dealing with data subscribing ---------------------------------------- 
//if subscribeable, make it output size. if not, make it one 
	SPBDataSubscription* DataSubscribers[MAXNUM_OF_SUBSCRIBERS_To_A_SPB];

	void AddSubscriber(SPBDataSubscription* dataSubscribers)
	{
		//needs to be set to IsOutputSubscribeAble in the template
		configASSERT(isOutputsubscribable == true);

		DataSubscribers[this->numOfDataSubscribersSoFar] = dataSubscribers;
		this->numOfDataSubscribersSoFar++;

		configASSERT(this->numOfDataSubscribersSoFar <= MAXNUM_OF_SUBSCRIBERS_To_A_SPB);
	}
	//---------------------------------------------------------------------------------




	//uint16_t ChannelIConnectTo[MAXNUMBEROFOUTPUTSIGNALS_TO_A_SPB];
	//AESPBObservor* SPBObservorsIPointTo[MAXNUMBEROFOUTPUTSIGNALS_TO_A_SPB]; 
	//uint16_t NumOfSPBObservorsIPointTo;



	//TaskHandle_t RefreshGaurdTask;
	static TaskHandle_t RefreshValueUpdateGaurdTask; 

	


	/*
	virtual void RefreshOVERRIDESignal1(float** TheInputSignals1, float* outputSignal);//for the user to specify what to do with the input signal
	virtual void RefreshOVERRIDESignal2(float** TheInputSignals1, float** TheInputSignals2, float* outputSignal);//for the user to specify what to do with the input signal
	virtual void RefreshOVERRIDESignal3(float** TheInputSignals1, float** TheInputSignals2, float** TheInputSignals3, float* outputSignal);//for the user to specify what to do with the input signal
	virtual void RefreshOVERRIDESignal4(float** TheInputSignals1, float** TheInputSignals2, float** TheInputSignals3, float** TheInputSignals4, float* outputSignal);//for the user to specify what to do with the input signal
	virtual void RefreshOVERRIDESignal5(float** TheInputSignals1, float** TheInputSignals2, float** TheInputSignals3, float** TheInputSignals4, float** TheInputSignals5, float* outputSignal);//for the user to specify what to do with the input signal
	virtual void RefreshOVERRIDESignal6(float** TheInputSignals1, float** TheInputSignals2, float** TheInputSignals3, float** TheInputSignals4, float** TheInputSignals5, float** TheInputSignals6, float* outputSignal);//for the user to specify what to do with the input signal
	virtual void RefreshOVERRIDESignal7(float** TheInputSignals1, float** TheInputSignals2, float** TheInputSignals3, float** TheInputSignals4, float** TheInputSignals5, float** TheInputSignals6, float** TheInputSignals7, float* outputSignal);//for the user to specify what to do with the input signal
	virtual void RefreshOVERRIDESignal8(float** TheInputSignals1, float** TheInputSignals2, float** TheInputSignals3, float** TheInputSignals4, float** TheInputSignals5, float** TheInputSignals6, float** TheInputSignals7, float** TheInputSignals8, float* outputSignal);//for the user to specify what to do with the input signal
	virtual void RefreshOVERRIDESignal9(float** TheInputSignals1, float** TheInputSignals2, float** TheInputSignals3, float** TheInputSignals4, float** TheInputSignals5, float** TheInputSignals6, float** TheInputSignals7, float** TheInputSignals8, float** TheInputSignals9, float* outputSignal);//for the user to specify what to do with the input signal
	virtual void RefreshOVERRIDESignal10(float** TheInputSignals1, float** TheInputSignals2, float** TheInputSignals3, float** TheInputSignals4, float** TheInputSignals5, float** TheInputSignals6, float** TheInputSignals7, float** TheInputSignals8, float** TheInputSignals9, float** TheInputSignals10, float* outputSignal);//for the user to specify what to do with the input signal
	*/

	static void RefreshUpdateGaurd(void * pvParameters);

private:

	//counts the number of inputs that have reached their countbuffer
	uint16_t indexOfNumOfInputs;

	//uint32_t SignalBufferIndex[MAXNUMBEROFINPUTSIGNALS_TO_A_SPB];
	//float** SignalBuffer[MAXNUMBEROFINPUTSIGNALS_TO_A_SPB];

	void _RefreshCheckStyle();



	//void IncrementSignalBuffer(uint16_t forChannelId);
	
	//AECHANGED:
	void   ConfigureRefreshFrequency();
	static void   ConfigureSPBRecursivelyForFrequency(AESPBObservor* spb, AEObservorBase** newNodesList, uint16_t& newnodes);
	//AECHANGEDDONE:


};

 




template<class TTDUToSetToThisClock>
inline void AESPBObservor::SetTDUToMyClock(TTDUToSetToThisClock TDUSetToThisSPBClock)
{
	
	//TDUSetToMeRefreshers[numOfTdusThatAreSetToMyClock] = &(TDUSetToThisSPBClock->SPBIamSetToHasbeenRefreshed);

	//numOfTdusThatAreSetToMyClock++;
}
