#include "AESPBObservor.h"
#include "AE.h"
 #include "AELinkSignalFlow.h"
#include <cmath>


#include "TaskPoolForSPBChain.h"

bool taskCreatedForRefreshValueUpdateGaurdTask = false;
TaskHandle_t AESPBObservor::RefreshValueUpdateGaurdTask = nullptr;




uint32_t AESPBObservor::GetOutPutSize()
{
	return OutputSize;
}
AESPBObservor::AESPBObservor( )
{
	this->styleOfSPB = StyleOfSPB::EachSPBTask;//default value

	IndexNumOfObservorsSignalLinkedSoFar = 0;
	isCurrentlyExecuting = false;
	TypeOfSPB = 0;

	//ObservorsSetSoFarIndex = 0;
	//ObservorInputIdsHandedOutSoFar = 0;

	indexOfNumOfInputs = 0;
	numOfDeterministicLinksPointToMe = 0;
	 
	numOfDataSubscribersSoFar = 0;

	/*
	for (int i = 0; i < MAXNUMBEROFINPUTSIGNALS_TO_A_SPB; i++)
	{
		SignalBufferIndex[i] = 0;
		CopyInputSignal[i] = false;
	}
	*/

	for (int i = 0; i < MAXNUMBEROFINPUTSIGNALS_TO_A_SPB; i++)
	{
		InputChannels[i] = nullptr;
	}

	SetMyObservorType(ObservorType::SPB);

	AESPBObservor *pToThisClass = this;

	//create tasks 

	//following task is static and only needs to be done once
	if (taskCreatedForRefreshValueUpdateGaurdTask == false)
	{
		xTaskCreate([](void* p) {static_cast<AESPBObservor*>(p)->RefreshUpdateGaurd(nullptr); }, "RefreshValueUpdateGaurdTask", configMINIMAL_STACK_SIZE, pToThisClass, AOPRIORITYHIGHEST, &RefreshValueUpdateGaurdTask);
		taskCreatedForRefreshValueUpdateGaurdTask = true;
	}


}




void AESPBObservor::InitSPBObserver(StyleOfSPB styleOfSPB, TaskPoolForSPBChain* taskPoolForSPBChain)
{
	if (styleOfSPB == StyleOfSPB::ChainOfSPBsTask)
	{
		//if the style is ChainOfSPBsTask, then you need to give taskPoolForSPBChain argument and not leave it nullptr
		configASSERT(taskPoolForSPBChain != nullptr);
		MyTaskPoolChain = taskPoolForSPBChain;

	}
	else
	{
		//if the style is not ChainOfSPBsTask taskPoolForSPBChain should be left nullptr
		configASSERT(taskPoolForSPBChain == nullptr);
	}
	

	if (this->isInitialized == false)
	{
		this->styleOfSPB = styleOfSPB;
		//SetInputChannelsOVERRIDE(InputChannels);

		SetUpTasks();


		//TODO: do a runtime ASSERTION that the input channels that the user put in were of the correct amount.
		numOfTdusThatAreSetToMyClock = 0;
		uint16_t numOfNOTNullInputChannels = 0;
		for (int i = 0; i < MAXNUMBEROFINPUTSIGNALS_TO_A_SPB; i++)
		{
			numOfNOTNullInputChannels = InputChannels[i] != nullptr ? numOfNOTNullInputChannels + 1 : numOfNOTNullInputChannels;
		}
		configASSERT(numOfNOTNullInputChannels == NumOfInputsSignals);


		//I need to assert that all channels were created in order
		bool FoundANullOutOfOrder = false;
		for (int i = 0; i < NumOfInputsSignals; i++)
		{
			FoundANullOutOfOrder = InputChannels[i] == nullptr;
			if (FoundANullOutOfOrder) { break; }
		}
		configASSERT(!FoundANullOutOfOrder);




		//getting the LowestFrequencyTriggeringInputChannel will be done in the intialization process as I need to know the
		//inputting frequencies to get the channel that will trigger. For now I can just assert that the countbuffers are divisible
		//by the highest countbuffer
		uint32_t highestCountBuffer = 0;
		for (int i = 0; i < NumOfInputsSignals; i++)
		{
			highestCountBuffer = InputChannels[i]->CountBuffer > highestCountBuffer ?
				InputChannels[i]->CountBuffer
				: highestCountBuffer;

			//also assert that every countbuffer the user define is greater then 0.
			configASSERT(InputChannels[i]->CountBuffer > 0);
		}
		//now ASSERT that the input channel's the user created are divisible by the highest.
		for (int i = 0; i < NumOfInputsSignals; i++)
		{
			uint32_t remainder = highestCountBuffer % InputChannels[i]->CountBuffer;

			configASSERT(remainder == 0);
		}
		 

		//TODO: see all RefreshOVERRIDES() except for the one that should be overriden. this will just make sure that the wrong refresh was not overriden
		switch (NumOfInputsSignals)
		{
		case 1:
			//void* theBaseFucntionAddress = &AESPBObservor::RefreshOVERRIDESignal1; 
			//void* theDerivedFucntionAddress = &this->RefreshOVERRIDESignal1;
			//configASSERT( ! == );
			break;
		default:
			break;
		}



		this->isInitialized = true;
	}
	


}

uint16_t AESPBObservor::GetNumOfInputsSignals() const
{
	return NumOfInputsSignals;
}

float * AESPBObservor::GetOutputAddress() const
{
	return OutputSignal;
}

void AESPBObservor::ConfigureSPBs()
{
	//THIS HAS TO BE DONE AFTER ALL LINKS HAVe BEEN SET
	//the reason for this is because of the scenario where a SPB that is down along the tree, gets its frequency configured BEFORE
	// one of its input frequencies get all of its links. LAter that SPB could change frequencies making the SPB it pointed to frequency not correct
	//as it was configured prematurely.

	//configure the correct frequency values
	//the frequency of the observor it is linking to will always be the lowest of the inputting observors where
	//frequency_lowest = InputtingObservorsFrequency / CountBuffer_ForThatInputtingFrequency


	//I need to start with all sensors. grab all sensors and put them in a list. Now conduct a BREADTH first search of all spbs the sensors
	//points to. Only configure frequencies for the SPBs that have 0 or 1 inputchannels. while you are doing that, collect a list of 
	//the SPBs that have inputchannels greater than 1. than do the thing again recursively for that new list of SPB nodes until you no longer
	//have nodes returned to you.
	AEObservorBase* SPBNodes[MAXNUMOFOBSERVORS];
	uint16_t numOfNodes = 0;
	for (int i = 0; i < AEObservorBase::CurrentId; i++)
	{
		if (ObservorPool[i]->GetMyObservorType() & ObservorType::Sensor)
		{
			SPBNodes[numOfNodes] = (AEObservorSensor*)ObservorPool[i];
			numOfNodes++;
		}
	}

	ConfigureAllSPBsFromNodes(SPBNodes, numOfNodes);

	//keep doing that until I dont get returned any more nodes
	while (numOfNodes > 0)
	{
		ConfigureAllSPBsFromNodes(SPBNodes, numOfNodes);
	}


	/*
	for (int i = 0; i < AEObservorBase::CurrentId; i++)
	{
		if (ObservorPool[i]->GetMyObservorType() & ObservorType::Sensor)
		{
			//go through each SPB observor that this sensor points to
			for (int j = 0; j < ObservorPool[i]->NumOfSPBObservorsIPointTo; j++)
			{
				//TODO: assert that if this is a sensor, then the SPB it points to should only have this ONE sensor pointing to it!
				configASSERT(ObservorPool[i]->SPBObservorsIPointTo[j]->numOfSignalLinksPointToMe == 0);



				//now that this SPB has had its frequency set, I can recursively set all the SPBs it points to.
				ObservorPool[i]->SPBObservorsIPointTo[j]->ConfigureRefreshFrequenciesRecursivelyForSPB(ObservorPool[i]->GetFrequencyIRefreshAt(), 1);


			}
		}

	}
*/


//configure all SPB types
	ConfigureSPBTypesAndInputTypes();

	//after this all SPBs and sensors should have their frequencies Locked in and set
	//so set their frequencies set bool to true
	for (uint16_t i = 0; i < AEObservorBase::CurrentId; i++)
	{
		((AEObservorBase*)ObservorPool[i])->FrequencyHasBeenConfigured = true;
	}


	//run the user defined intializespb if you so have one.
	for (uint32_t i = 0; i < AEObservorBase::CurrentId; i++)
	{
		if (ObservorPool[i]->GetMyObservorType() & ObservorType::SPB)
		{
			((AEObservorBase*)ObservorPool[i])->InitializeObservor();
		}
	}

}


void AESPBObservor::ConfigureRefreshFrequency()
{
	//THIS HAS TO BE DONE AFTER ALL LINKS HAVe BEEN SET
	//the reason for this is because of the scenario where a SPB that is down along the tree, gets its frequency configured BEFORE
	// one of its input frequencies get all of its links. LAter that SPB could change frequencies making the SPB it pointed to frequency not correct
	//as it was configured prematurely.

	//configure the correct frequency values
	//the frequency of the observor it is linking to will always be the lowest of the inputting observors where
	//frequency_lowest = InputtingObservorsFrequency / CountBuffer_ForThatInputtingFrequency

	float LowestInputtingObservorsFrequency;
	for (uint16_t i = 0; i < NumOfInputsSignals; i++)
	{

		uint32_t index = i;
		//get the inputting channel that the inputting observor connects to
		InputChannel* inputtingChannel = this->InputChannels[index];
		float inputtingFrequency = ObservorPool[this->ObservorsSignalLinkedToMe[index]]->GetFrequencyIRefreshAt();

		//i need to get what the frequency will be AFTER taking into account the buffercount for that channel
		float InputtingFrequencyIRefresh = inputtingFrequency / (float)inputtingChannel->CountBuffer;

		LowestInputtingObservorsFrequency = i == 0 ? InputtingFrequencyIRefresh : LowestInputtingObservorsFrequency;

		//check if this InputtingFrequencyIRefresh is of the slowest inputting frequency thus far
		if ((InputtingFrequencyIRefresh <= LowestInputtingObservorsFrequency))
		{
			LowestInputtingObservorsFrequency = InputtingFrequencyIRefresh;


			//if it is then go ahead and set it as the FrequencyIRefreshAt
			this->FrequencyIRefreshAt
				= InputtingFrequencyIRefresh;

			//also set the clock that this SPB is sourced from
			this->ClockIdImSourcedTo = ObservorPool[this->ObservorsSignalLinkedToMe[index]]->GetClockIdImSourcedTo();
			//set all input channels to nontriggering so to make sure that correct channel to a trigger is the only one set to true
			for (uint16_t iii = 0; iii < NumOfInputsSignals; iii++)
			{
				this->InputChannels[iii]->TriggeringChannel = false;
			}
			this->InputChannels[index]->TriggeringChannel = true;

		}

	}

	//configure filters for this spb
	this->InitializeFilters();


	/*now that those SPB observor frequencies shoudl have been set, recursively set the ones that those SPBs point ot as well
	for (int i = 0; i < this->NumOfSPBObservorsIPointTo; i++)
	{
		this->SPBObservorsIPointTo[i]->ConfigureRefreshFrequenciesRecursivelyForSPB(this->GetFrequencyIRefreshAt(), i + 1);
	}*/
}




 void  AESPBObservor::CheckIfConfiguredProperly()  const  
{

	AEObservorBase::CheckIfConfiguredProperly();
	//assert all i need to assert here

	//make sure all observers linked to me have the same spb style
	for (uint16_t i = 0; i < NumOfInputsSignals; i++)
	{

		if (ObservorPool[this->ObservorsSignalLinkedToMe[i]]->GetMyObservorType() & ObservorType::SPB)
		{
			AESPBObservor* spblinkedToMeToCheck = static_cast<AESPBObservor*>(ObservorPool[this->ObservorsSignalLinkedToMe[i]]);

			//all spbs in the same spb chain must be of the same spb style
			configASSERT(spblinkedToMeToCheck->styleOfSPB == this->styleOfSPB);
		}

	}

};




void AESPBObservor::ConfigureSPBTypesAndInputTypes()
{


	//go through each SPB and determine its type of SPB and its input's types as well
	for (uint32_t i = 0; i < AEObservorBase::CurrentId; i++)
	{
		if (ObservorPool[i]->GetMyObservorType() & ObservorType::SPB)
		{
			AESPBObservor* spb = static_cast<AESPBObservor*>(ObservorPool[i]);
			//I only care about SPBs that have NumOfinputSignals that are greater than 1
			if (spb->NumOfInputsSignals > 1)
			{

				//THE EXPLANATION FLOW DIAGRAM FOR THIS IS EXPLAINED IN ONENOTE IN THE OBSERVORES->"OBSERVORS AS A SIGNAL PROCESSING BLOCK"


				uint16_t PreviousClockId;
				bool DifferentClockSourceFound = false;
				//do all inputSPBs come from the same clock source?
				//check for if amy ClockIds are different from the inputting observors
				for (uint32_t i = 0; i < spb->NumOfInputsSignals; i++)
				{
					uint16_t CurrentClockId = ObservorPool[spb->ObservorsSignalLinkedToMe[i]]->GetClockIdImSourcedTo();
					if (i > 0)//so to not do this before previousclocksource is set.
					{
						//check if this is the same or different than the previous clocksource Id
						if (PreviousClockId != CurrentClockId)
						{
							DifferentClockSourceFound = true;
							break;
						}
					}
					PreviousClockId = CurrentClockId;

				}




				//check for if any of the input channels have the same or different frequencies
				bool AreAnyInputsOfDifferentFrequencies = false;
				bool AreAllChannelsFrequenciesDivisibleByTheSlowest = true;
				for (uint32_t i = 0; i < spb->NumOfInputsSignals; i++)
				{
					// I dont have inputting channel frequencies however I can calculate it. 
					//float InputtingFrequencyIRefresh = inputtingFrequency / (float)inputtingChannel->CountBuffer;
					float inputtingFrequency = ObservorPool[spb->ObservorsSignalLinkedToMe[i]]->GetFrequencyIRefreshAt();
					float InputtingFrequencyThisChannelHas = inputtingFrequency / spb->InputChannels[i]->GetCountBufferSize();

					//check if this frequency is different than the spb frequency
					if (InputtingFrequencyThisChannelHas != spb->GetFrequencyIRefreshAt())
					{
						AreAnyInputsOfDifferentFrequencies = true;
					}

					//I need to set that channel's DivisionOFLargestFrequencyChannel by dividing it by the largest frequency. The largest 
					//frequency is simple the spb's frequency since that was configured from before as the largest inputting frequency
					//if it does NOT divides cleanly, then give it a value of zero
					float remainder = fmodf((InputtingFrequencyThisChannelHas), (spb->GetFrequencyIRefreshAt()));
					if (remainder == 0)
					{

						spb->InputChannels[i]->isDivisibleToSlowestChannel = true;
						spb->InputChannels[i]->DivisionOFLargestFrequencyChannel = InputtingFrequencyThisChannelHas / spb->GetFrequencyIRefreshAt();
					}
					else {
						AreAllChannelsFrequenciesDivisibleByTheSlowest = false;
						spb->InputChannels[i]->isDivisibleToSlowestChannel = false;
						spb->InputChannels[i]->DivisionOFLargestFrequencyChannel = 0;
					}

				}


				//check that if AreAllChannelsFrequenciesDivisibleByTheSlowest, that there are no frequencies that are equal
				float freqSoFar[MAXNUMBEROFINPUTSIGNALS_TO_A_SPB];
				bool DuplicateFrequencies = false;
				for (uint32_t i = 0; i < spb->NumOfInputsSignals; i++)
				{
					// I dont have inputting channel frequencies however I can calculate it. 
					//float InputtingFrequencyIRefresh = inputtingFrequency / (float)inputtingChannel->CountBuffer;
					float inputtingFrequency = ObservorPool[spb->ObservorsSignalLinkedToMe[i]]->GetFrequencyIRefreshAt();
					float InputtingFrequencyThisChannelHas = inputtingFrequency / spb->InputChannels[i]->GetCountBufferSize();
					freqSoFar[i] = InputtingFrequencyThisChannelHas;

					for (int j = i - 1; j >= 0; j--)
					{
						if (freqSoFar[j] == InputtingFrequencyThisChannelHas)
						{
							DuplicateFrequencies = true;
						}
					}

				}


				//check if any channels are pass-by-reference
				bool AreAnyChannelsPassByReference = false;
				for (uint32_t i = 0; i < spb->NumOfInputsSignals; i++)
				{
					AreAnyChannelsPassByReference = AreAnyChannelsPassByReference == true ?
						AreAnyChannelsPassByReference :
						!spb->InputChannels[i]->CopyInputSignal;
				}


				//make first assertion that channels may not be from different clock sources AND of same frequencies
				configASSERT(!(DifferentClockSourceFound && !AreAnyInputsOfDifferentFrequencies));

				//may not be from different clock sources, and have any input channels pass by reference
				configASSERT(!(DifferentClockSourceFound && AreAnyChannelsPassByReference));

				//same clock, different frequencies, not diviesible, but has some pass by reference is not possible
				configASSERT(!(!DifferentClockSourceFound && AreAnyInputsOfDifferentFrequencies && !AreAllChannelsFrequenciesDivisibleByTheSlowest && AreAnyChannelsPassByReference));

				//same clock, different frequencies, diviesible, but some are duplicated
				configASSERT(!(!DifferentClockSourceFound && AreAnyInputsOfDifferentFrequencies && AreAllChannelsFrequenciesDivisibleByTheSlowest && DuplicateFrequencies));


				//if has same clock source and is of same frequencies, than is type one.
				if (!DifferentClockSourceFound && !AreAnyInputsOfDifferentFrequencies)
				{
					spb->TypeOfSPB = 1;
				}
				//if has same clock source, different frequencies, and all frequencies are divisible by slowest.
				if (!DifferentClockSourceFound && AreAnyInputsOfDifferentFrequencies && AreAllChannelsFrequenciesDivisibleByTheSlowest)
				{
					spb->TypeOfSPB = 2;
				}
				//if like the previous except NOT all frequencies are divisible by slowest AND no channels are pass by reference.
				if (!DifferentClockSourceFound && AreAnyInputsOfDifferentFrequencies && !AreAllChannelsFrequenciesDivisibleByTheSlowest && !AreAnyChannelsPassByReference)
				{
					spb->TypeOfSPB = 3;
				}
				//if different clock source, different frequency, and non are pass-by-reference
				if (DifferentClockSourceFound && AreAnyInputsOfDifferentFrequencies && !AreAnyChannelsPassByReference)
				{
					spb->TypeOfSPB = 3;
				}


			}
		}

	}

}


void AESPBObservor::ConfigureSPBRecursivelyForFrequency(AESPBObservor * spb, AEObservorBase ** newNodesList, uint16_t & newnodes)
{

	//captures newnodes and newNodesList so they are in scope still
	auto CheckForDupesAndAdd = [&newNodesList, &newnodes](AESPBObservor* spbToCheckAndadd)-> void
	{
		//only add the spb if it has not been added already.
		bool addedAlready = false;
		for (uint16_t i = 0; i < newnodes; i++)
		{
			if (newNodesList[i]->ObservorId == spbToCheckAndadd->ObservorId)
			{
				addedAlready = true;
				break;
			}
		}
		if (addedAlready == false)
		{
			newNodesList[newnodes] = spbToCheckAndadd;
			newnodes++;
		}

	};

	//configure this spb if it is numofInputSize = 1
	if (spb->NumOfInputsSignals == 1)
	{
		spb->ConfigureRefreshFrequency();
	}
	else
	{
		CheckForDupesAndAdd(spb);
	}

	//go through each spb this spb points to and run the ConfigureSPBRecursivelyForFrequency
	//on it while configuring the ones that have inputchannels = 1
	for (int i = 0; i < spb->NumOfSPBObservorsIPointTo; i++)
	{
		AESPBObservor* spbThisSPBPointsTo = spb->SPBObservorsIPointTo[i];
		if (spbThisSPBPointsTo->GetNumOfInputsSignals() == 1)
		{
			spbThisSPBPointsTo->ConfigureRefreshFrequency();// (spb->GetFrequencyIRefreshAt(), i);
			ConfigureSPBRecursivelyForFrequency(spbThisSPBPointsTo, newNodesList, newnodes);
		}
		else
		{
			//if has more than 1 inputsignal, just add it to the node list
			CheckForDupesAndAdd(spbThisSPBPointsTo);
		}
	}
}

void AESPBObservor::ConfigureAllSPBsFromNodes(AEObservorBase * (&nodes)[MAXNUMOFOBSERVORS], uint16_t& nodeListSize)
{
	uint16_t newnodes = 0;
	AEObservorBase* newNodesList[MAXNUMOFOBSERVORS];


	//first configure the frequencies for the nodes, if the node types are NOT sensors
	for (uint16_t i = 0; i < nodeListSize; i++)
	{
		if ((nodes)[i]->GetMyObservorType() & ObservorType::SPB)
		{
			static_cast<AESPBObservor*>((nodes)[i])->ConfigureRefreshFrequency();
		}
	}


	//go through each node and configure spbs recursively that the nodes point to
	for (uint16_t i = 0; i < nodeListSize; i++)
	{
		for (int j = 0; j < (nodes)[i]->NumOfSPBObservorsIPointTo; j++)
		{
			ConfigureSPBRecursivelyForFrequency((nodes)[i]->SPBObservorsIPointTo[j], newNodesList, newnodes);
		}
	}


	//set the new nodelist and nodelistsize
	uint16_t observorIdsSoFar[MAXNUMOFOBSERVORS];
	for (uint16_t i = 0; i < newnodes; i++)
	{
		nodes[i] = newNodesList[i];
	}
	nodeListSize = newnodes;
}





/*


	//float inputtingFrequency = this->GetFrequencyIRefreshAt();

	for (int i = 0; i < this->NumOfSPBObservorsIPointTo; i++)
	{
		//get the inputting channel that the inputting observor connects to
		InputChannel* inputtingChannel = this->InputChannels[forChannelid];

		//i need to get what the frequency will be AFTER taking into account the buffercount for that channel
		float InputtingFrequencyIRefresh = inputtingFrequency / (float)inputtingChannel->CountBuffer;


		//check if this InputtingFrequencyIRefresh is of the lowest inputting frequency thus far
		if ((inputtingFrequency < this->SPBObservorsIPointTo[i]->LowestInputtingObservorsFrequency) || !LowestInputtingFrequencyAlreadySet)
		{
			this->SPBObservorsIPointTo[i]->LowestInputtingObservorsFrequency = inputtingFrequency;
			this->SPBObservorsIPointTo[i]->LowestInputtingFrequencyAlreadySet = true;

			//if it is then go ahead and set it as the FrequencyIRefreshAt
			this->SPBObservorsIPointTo[i]->FrequencyIRefreshAt
				= InputtingFrequencyIRefresh;
		}
	}

	//now that those SPB observor frequencies shoudl have been set, recursively set the ones that those SPBs point ot as well
	for (int i = 0; i < this->NumOfSPBObservorsIPointTo; i++)
	{
		this->SPBObservorsIPointTo[i]->ConfigureRefreshFrequenciesRecursivelyForSPB(this->GetFrequencyIRefreshAt(),i);
	}


*/



void AESPBObservor::AddSignalFlowLink(AESPBObservor * toObservor, uint16_t ToChannel, uint8_t toOutPutFilter)
{
	AEObservorBase::AddSignalFlowLink(toObservor, ToChannel, toOutPutFilter);

	//assert that the channel the SPB is trying to link to, is even active
	configASSERT(ToChannel <= toObservor->NumOfInputsSignals);

	//assert that the output size of the from SPB, matches the input size of the channel it is linking to.
	configASSERT(this->OutputSize == toObservor->InputChannels[ToChannel - 1]->InputSize);



	IndexNumOfObservorsSignalLinkedSoFar++;
}


inline void AESPBObservor::_RefreshCheckStyle()
{
	if (this->styleOfSPB == EachSPBTask)
	{
		xTaskNotifyGive(GaurdTaskToObjectExecutionHandle);
	}
	else if (this->styleOfSPB == ChainOfSPBsFromInterrupt)
	{
		//check here for any subscribing AO that were in the midst of copying and tell them to recopy 
		for (uint16_t i = 0; i < this->numOfDataSubscribersSoFar; i++)
		{
			if (DataSubscribers[i]->CurrentlyCopyingDataOver == true)
			{
				DataSubscribers[i]->ReCopyTheData = true;
			}
		}

		this->_RefreshFromBaseClass();
	}
	else if (this->styleOfSPB == ChainOfSPBsTask)
	{
		//if this is an spb that is the starting spb of the chain (as in has a sensorobservor linked to it)  then I need to 
		// call it spbPoolchain's HaveTaskFromPoolRunRefreshOfThisSPB
		if (this->IsStartingSPB == true)
		{
			MyTaskPoolChain->HaveTaskFromPoolRunRefreshOfThisSPB(this);
		}
		else
		{
			//if it is not a starting spb then it must be a taskchainpool so it can call a refresh directly.
			this->_RefreshFromBaseClass();
		}

		
	}
}



void AESPBObservor::InputSignal(float * input, uint16_t toChannelId)
{
	uint16_t index = toChannelId - 1;

	//this assert is triggered because a "InputSignal()" was called on this spb while the spb is still updating. This does not mean that this input signal
	//will trigger the refresh but it does mean that it will change one of the buffer elements of this spb. this  will can change the buffer value
	//of the spb while it is using those values in the update. You need to either lower the update frequency of this spb, or significantly reduce
	// processing time of it. //the times where this is acceptable is if the user copies the buffer into a seperate buffer that the spb processes.
	//if this is the case, 
	//1. the user should assure that speed is being optimized for the compiler he is using (like in IAR go to options-> optimizations and select speed in the 
	//drop down menu) and 
	//2. if there are more than one buffer being copied, buffers are copied from the AEmemcpyManyFromBottomUp() this will copy elements from first elements,
	//so that they are not clipped from the first elements as new inputs change the buffers.
#ifndef DontCheckForHardDeadlinesInSPBsForEverySetInput
	configASSERT(this->isCurrentlyExecuting == false);
#endif

	//if this is a type
	switch (TypeOfSPB)
	{
	case 0:
	{
		//if the spb is  type zero then it must have just 1 input channel. 

		//if the channel returns a true, then that means the count buffer has been reached,
		//and a refresh is needed. 
		bool iscountBufferFilled0 = InputChannels[index]->SetInput(input);
		if (iscountBufferFilled0)
		{

			//this spb is Going to attempt to trigger a refresh while this spb is already refreshing. This should never happen either 
			//lower the update frequency of this spb, or significantly reduce  processing time of it.
			configASSERT(this->isCurrentlyExecuting == false);


			//run the refresh
			_RefreshCheckStyle();


		}
	}
	break;
	case 1:
	{
		//this spb has all input channels of the same clock source and frequency, therfore
		//I will need to wait for all channels to finish their setinput as it should be happening at the same time

		bool iscountBufferFilled1 = InputChannels[index]->SetInput(input);
		if (iscountBufferFilled1)
		{

			//TODO: THIS IS A POSSIBLE RACE CONDITION. TWO AO SPBS COULD COME IN AT THE SAME TIME TO INPUT A SIGNAL INTO 
			//THWO CHANNELS THAN THEY COULD TRY TO DO INDEXOFNUMOFINPUTS++; WHICH IS A WRITE TO A SHARED MEMORY. THIS NEEDS TO
			//PERHAPS NEED TO BE ENCLOSED IN A MUTEX!
			indexOfNumOfInputs++;
			 
			//I will need to check if all input channels have had theirs filled before I can do a refresh
			if (indexOfNumOfInputs >= NumOfInputsSignals)
			{
				//if indexOfNumOfInputs is > NumOfInputsSignals than that is a sign that a race condition did indeed occur
				configASSERT(indexOfNumOfInputs == NumOfInputsSignals);
				indexOfNumOfInputs = 0;

				//this spb is Going to attempt to trigger a refresh while this spb is already refreshing. This should never happen either 
				//lower the update frequency of this spb, or significantly reduce  processing time of it.
				configASSERT(this->isCurrentlyExecuting == false);

				//if all count buffers have been reached for all channels, then I need to do a refresh
				_RefreshCheckStyle();
			}
		}
	}
	break;
	case 2:
	{
		//this type of spb has input channels that are divisible by the largest one. This means that, like type 1, 
		//all channels will trigger together, however for the divisible channels, their setinputs can be ignored until
		//their last divisible positions

		//I should not even consider doing a refresh if the divisible channels have not reached their last divisibility.



		//so if the slowest triggering channel was triggered, you can do a refresh ONLY if the other chennels have also 
		if (InputChannels[index]->TriggeringChannel == true)
		{
			bool iscountBufferFilled = InputChannels[index]->SetInput(input);
			if (iscountBufferFilled)
			{
				//set that the triggering input channel has triggered, in case the other channels have not finished their inputs yet.
				indexOfNumOfInputs++;
				if (indexOfNumOfInputs >= NumOfInputsSignals)
				{

					//this spb is Going to attempt to trigger a refresh while this spb is already refreshing. This should never happen either 
					//lower the update frequency of this spb, or significantly reduce  processing time of it.
					configASSERT(this->isCurrentlyExecuting == false);

					indexOfNumOfInputs = 0;
					_RefreshCheckStyle();
				}
			}
		}
		else
		{
			bool iscountBufferFilled = InputChannels[index]->SetInput(input);
			if (iscountBufferFilled)
			{
				InputChannels[index]->DivisibilityCounter++;
				//if the counter has reached the DivisionOFLargestFrequencyChannel, than it is ready to trigger
				if (InputChannels[index]->DivisibilityCounter >= InputChannels[index]->DivisionOFLargestFrequencyChannel)
				{
					InputChannels[index]->DivisibilityCounter = 0;
					indexOfNumOfInputs++;
					if (indexOfNumOfInputs >= NumOfInputsSignals)
					{
						//this spb is Going to attempt to trigger a refresh while this spb is already refreshing. This should never happen either 
					   //lower the update frequency of this spb, or significantly reduce  processing time of it.
						configASSERT(this->isCurrentlyExecuting == false);
						indexOfNumOfInputs = 0;
						_RefreshCheckStyle();
					}
				}
			}

		}

	}
	break;
	case 3:
	{
		//for a type 3, the set input is ignored when this SPB is in the midst of updating.
		bool iscountBufferFilled3 = false;
		if (isCurrentlyExecuting == false)
		{
			iscountBufferFilled3 = InputChannels[index]->SetInput(input);
		}
		//remmeber that only the triggering channel can trigger the refresh
		if ((iscountBufferFilled3 == true) && (InputChannels[index]->TriggeringChannel == true))
		{

			//this spb is Going to attempt to trigger a refresh while this spb is already refreshing. This should never happen either 
			//lower the update frequency of this spb, or significantly reduce  processing time of it.
			configASSERT(this->isCurrentlyExecuting == false);
			_RefreshCheckStyle();
		}
	}
	break;
	default:
		break;
	}





}


void AESPBObservor::RefreshUpdateGaurd(void * pvParameters)
{

	uint32_t ulNotifiedValueCurrentSession;

	while (true)
	{
		//this task of highest priority is called when an endchain observor has finished its update. This means that
		//all observors down the chain should be set such that they are in need of an update as well. 
		xTaskNotifyWait(pdFALSE, pdTRUE, &ulNotifiedValueCurrentSession, portMAX_DELAY);

		bool** refreshValuesToUpdate = ObservorPool[ulNotifiedValueCurrentSession]->GetObservorsOfInfluenceNeedARefeshValues();
		auto numOfObservors = ObservorPool[ulNotifiedValueCurrentSession]->GetnumOfObservorsOfInfluence();

		for (int i = 0; i < numOfObservors; i++)
		{
			*refreshValuesToUpdate[i] = true;
		}
	}

}


/*
void AESPBObservor::SetObservorIPointTo(AESPBObservor * sPBObservorsIPointTo)
{
	SPBObservorsIPointTo[NumOfSPBObservorsIPointTo] = sPBObservorsIPointTo;
	ChannelIConnectTo[NumOfSPBObservorsIPointTo] = sPBObservorsIPointTo->ObservorInputIdsHandedOutSoFar;
	sPBObservorsIPointTo->ObservorInputIdsHandedOutSoFar++;
	NumOfSPBObservorsIPointTo++;
}*/




//TODO: make it so that these run an error as a static assert during compile time if the one overriden was not the correct number of inputs one.

/*
void AESPBObservor::RefreshOVERRIDESignal1(float ** TheInputSignals1, float * outputSignal)
{
	//
	configASSERT(true);
}

void AESPBObservor::RefreshOVERRIDESignal2(float ** TheInputSignals1, float ** TheInputSignals2, float * outputSignal)
{
}

void AESPBObservor::RefreshOVERRIDESignal3(float ** TheInputSignals1, float ** TheInputSignals2, float ** TheInputSignals3, float * outputSignal)
{
}

void AESPBObservor::RefreshOVERRIDESignal4(float ** TheInputSignals1, float ** TheInputSignals2, float ** TheInputSignals3, float ** TheInputSignals4, float * outputSignal)
{
}

void AESPBObservor::RefreshOVERRIDESignal5(float ** TheInputSignals1, float ** TheInputSignals2, float ** TheInputSignals3, float ** TheInputSignals4, float ** TheInputSignals5, float * outputSignal)
{
}

void AESPBObservor::RefreshOVERRIDESignal6(float ** TheInputSignals1, float ** TheInputSignals2, float ** TheInputSignals3, float ** TheInputSignals4, float ** TheInputSignals5, float ** TheInputSignals6, float * outputSignal)
{
}

void AESPBObservor::RefreshOVERRIDESignal7(float ** TheInputSignals1, float ** TheInputSignals2, float ** TheInputSignals3, float ** TheInputSignals4, float ** TheInputSignals5, float ** TheInputSignals6, float ** TheInputSignals7, float * outputSignal)
{
}

void AESPBObservor::RefreshOVERRIDESignal8(float ** TheInputSignals1, float ** TheInputSignals2, float ** TheInputSignals3, float ** TheInputSignals4, float ** TheInputSignals5, float ** TheInputSignals6, float ** TheInputSignals7, float ** TheInputSignals8, float * outputSignal)
{
}

void AESPBObservor::RefreshOVERRIDESignal9(float ** TheInputSignals1, float ** TheInputSignals2, float ** TheInputSignals3, float ** TheInputSignals4, float ** TheInputSignals5, float ** TheInputSignals6, float ** TheInputSignals7, float ** TheInputSignals8, float ** TheInputSignals9, float * outputSignal)
{
}

void AESPBObservor::RefreshOVERRIDESignal10(float ** TheInputSignals1, float ** TheInputSignals2, float ** TheInputSignals3, float ** TheInputSignals4, float ** TheInputSignals5, float ** TheInputSignals6, float ** TheInputSignals7, float ** TheInputSignals8, float ** TheInputSignals9, float ** TheInputSignals10, float * outputSignal)
{
}
*/
