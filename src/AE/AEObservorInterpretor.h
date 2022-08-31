#pragma once
#include "AEObservorInterpretorBase.h"
#include "AESPBObservor.h"
#include "AEObservorInterpretorOutputType.h"

#include "AEUtils.h"

#ifdef  Config_Check_Build_RTTI  
#include <typeinfo>
#endif






template<class TObservationType,
	class TChannel1DeterminedType = AENull, uint32_t sizeOfChannel1 = 1,
	class TChannel2DeterminedType = AENull, uint32_t sizeOfChannel2 = 1,
	class TChannel3DeterminedType = AENull, uint32_t sizeOfChannel3 = 1>
	class AEObservorInterpretor : public AEObservorInterpretorOutputType<TObservationType>
{
public:



	//const uint32_t SizeOfChannel1 = sizeOfChannel1;

	void AddDeterministicLinkForChannelOfObservor(uint16_t channelToLinkTo, AEObservorBase* toObservor);// , TChannel1DeterminedType channelInputData);

#ifdef  Config_Check_Build_RTTI  
	//	const std::type_info& GetObservationTypeId()
	char const * GetObservationOutputTypeStr()
	{
		//return typeid(TObservationType).name();

		return this->typeIdForOutObservationType;
	};
#endif

	AEObservorInterpretor();


	//this will get the last observation update since the clock updated that observor.
	//use this when you have a TDU set to the same clock as an observor and want to get the observation
	// of that observor without calling a new update.
	//TObservationType  GetObservationAfterClockUpdates();


protected:

	//AEObservorInterpretorOutputType<TChannel1DeterminedType>* InterpretorForChannel1;
	//AESPBObservor* SPBForChannel1;
	TChannel1DeterminedType determinedValueChannel1[sizeOfChannel1];
	TChannel1DeterminedType* determinedValueChannel1Sourceptr;
	//AEObservorInterpretorOutputType<TChannel2DeterminedType>* InterpretorForChannel2; 
	TChannel2DeterminedType determinedValueChannel2[sizeOfChannel2];
	TChannel2DeterminedType* determinedValueChannel2Sourceptr;
	//AEObservorInterpretorOutputType<TChannel3DeterminedType>* InterpretorForChannel3;
	TChannel3DeterminedType determinedValueChannel3[sizeOfChannel3];
	TChannel3DeterminedType* determinedValueChannel3Sourceptr;

	uint8_t TotalActiveChannels = 0;

	//TODO: either move this or get filters working on interpretors
	void InitializeFilters() override {};

	virtual void Refresh() = 0; // todo: this needs to be CRTP inherited

private:

	void SwapObservationToReadWithTheOneToRefresh() override; // todo: this needs to be CRTP inherited
	void CopyDeterminedValues() override; // todo: this needs to be CRTP inherited

};


//this should not be here as an interpretor feature for the reason explained below.
/*

//TODO: there is a problem here. think of the scensario where if right before this clock ticked,
//an AO called an update which put this into a session. Now instead of updateing a value for this
//particular clock tick, it will update the value of the tick before this one. One way to
//fix this is to make it so that there are observors that get updated ONLY by clock, and everyother AO
//can only call GetobservationAfterClock(), or just GetObservation() on it. But by that point this observor
//is really just a SPB observor. Therefore UpdateObservationIfNeededForClock() should not be here because
//if you were going to use this feature, it should have just been a SPB. You may argue about the
// scenario of the velocity interpretor observor. In this example velocity is updated and passed to a
//tdu by clock. but then what about speedx speey speedz where these are determined for velocity.
//WELL THESE WOULD NEED TO BE CALLED ANYAYS BY THE SAME CLOCK SCHEDULING AS WHEN VELOCITY WAS
// SO THEY TOO SHOULD BE SPBS. if you needed speedx speey speedz SPBs to update faster then velocity SPB (for
//some other AO reading one of them at a faster clock tick), then simply make velocity have a
// longer buffer counter so to divide the clock further.
//the other kind of observor is the one where it is not READ FROM A TDU FROM A PARTICULAR CLOCK TICK. That
//does not mean that it is not set to a clock, but just that THERE IS NO TDU THAT NEEDS TO READ AN UPDATED
//VALUE OF THAT OBSERVOR AT A SET FREQUENCY. these interpretors have their values read at times that are not
//frequency sensitive. These are the kinds of interpretors that can be updated on demand. if the interpretor
//had some value to look out for like a ItsRaining observor, then it could be set to a slow clock but still
//get updated on demand from AO that may need to know about the wheather.

template<class TObservationType>
inline TObservationType  AEObservorInterpretor<TObservationType>::GetObservationAfterClockUpdates()
{
	uint8_t clocksession = CLockSession;
	if (UpdatedSinceClockTick)
	{
		//the clock had already updated the observor so I can just get the observation
		return Observation;
	}
	else
	{
		//the clock must still be working on updating the observation so I need to wait for it to finish
		xSemaphoreTake(MutexHandles[clocksession], portMAX_DELAY);
		xSemaphoreGive(MutexHandles[clocksession]);
		//xQueuePeek(MutexHandles[clocksession], NULL, portMAX_DELAY);
		return Observation;
	}

	return Observation;
}

*/



template<class TObservationType, class TChannel1DeterminedType, uint32_t sizeOfChannel1, class TChannel2DeterminedType, uint32_t sizeOfChannel2, class TChannel3DeterminedType, uint32_t sizeOfChannel3>
inline void AEObservorInterpretor<TObservationType, TChannel1DeterminedType, sizeOfChannel1, TChannel2DeterminedType, sizeOfChannel2, TChannel3DeterminedType, sizeOfChannel3>
::AddDeterministicLinkForChannelOfObservor(uint16_t channelToLinkTo, AEObservorBase* toObservor)//, TChannel1DeterminedType channelInputData)
{
	//first assert that the channel I am linking to is actually defined by the user
	//TODO: change these to static ASSERTS as theTypeChecker::IsAENull is doing its check at compile time
	switch (channelToLinkTo)
	{
	case 0:
		configASSERT(false); //should not be zero channels
		break;

	case 1:
		//make sure that the type for that channel was not AENull; 
		//static_assert(!TypeChecker::IsAENull<TChannel1DeterminedType>());
		configASSERT(!TypeChecker::IsAENull<TChannel1DeterminedType>());
		break;
	case 2:
		configASSERT(!TypeChecker::IsAENull<TChannel2DeterminedType>());
		break;
	case 3:
		configASSERT(!TypeChecker::IsAENull<TChannel3DeterminedType>());
		break;
	default:
		break;
	}


	//I need to now assert that the type that the toObservor's output signal/observation/sensorData will be of the
	//same type that this interpretors channelToLinkTo type will be.
	switch (channelToLinkTo)
	{
	case 0:
		configASSERT(false); //should not be zero channels
		break;


		//case 1 -----------------------------------------------------------------------
	case 1:
		//if the observer is a sensor type, I know the type of observation will be either a uint32* uint16* or uint8*
		if (toObservor->GetMyObservorType() & ObservorType::Sensor)
		{
			//TODO: have it so that sensors can also be templated or at least have an enum that gives what type it will be.
			//for now just assume it will be type uint32* 
			configASSERT(TypeChecker::Isuint32_tPtr<TChannel1DeterminedType>());
			//TODO: now make sure the size of that array is the same size of the one from the sensor. I need to
			//put that information in sensor for that though

			//set the address of the observors observation value to the channel 
			//observation will be located on observation type. I know the output of that type must be the type of this channel since 
			//I already asserted and confirmed that.
			determinedValueChannel1Sourceptr = reinterpret_cast<TChannel1DeterminedType*>(static_cast<AEObservorSensor*>(toObservor)->GetDataAddress());


		}
		//if the observer is a SPB type, I know the type of observation will be of output type float* OutputSignal;
		//and I know the size of that signal will be of uint32_t OutputSize;
		  //so I need to make sure this channel type is also a float*
		else if (toObservor->GetMyObservorType() & ObservorType::SPB)
		{
			configASSERT(TypeChecker::IsfloatPtr<TChannel1DeterminedType>());

			configASSERT(static_cast<AESPBObservor*>(toObservor)->GetOutPutSize() == sizeOfChannel1);

			determinedValueChannel1Sourceptr = reinterpret_cast<TChannel1DeterminedType*>(static_cast<AESPBObservor*>(toObservor)->GetOutputAddress());

		}
		//if its an interpretor that I am getting my deterministic data from, than the data could be anything.
		//I can check
		else if (toObservor->GetMyObservorType() & ObservorType::Interpretors)
		{

			//TODO: figure this out 
			//I cant find a way to do this without using RTTI. I may need to have to different builds. One build that 
			//just checks configuration using RTTI, and one build that skips configuration checking and just goes to runtime
			//without RTTI 
#ifdef  Config_Check_Build_RTTI   
			//the char* type of the output observation to the interpretor that will be linked to 
			const char * str1 = static_cast<AEObservorInterpretor*>(toObservor)->GetObservationOutputTypeStr();
			//my channel inputting type that the will be linking to that observor
			const char * str2 = typeid(TChannel1DeterminedType).name();
			uint32_t cmp = strcmp(str1, str2);
			configASSERT(cmp == 0);
#endif //  Config_Check_Build_RTTI 
			uint32_t sizeOfToObservorChannel = static_cast<AEObservorInterpretorBase*>(toObservor)->GetSizeOfChannel1();//static_cast<AEObservorInterpretor*>(toObservor)->SizeOfChannel1;
			configASSERT(sizeOfToObservorChannel == this->SizeOfChannel1);


			//set the address of the observors observation value to the channel 
			//observation will be located on observation type. I know the output of that type must be the type of this channel since 
			//I already asserted and confirmed that.
			determinedValueChannel1Sourceptr = static_cast<AEObservorInterpretorOutputType<TChannel1DeterminedType>*>(toObservor)->GetObservationAddress();


		}
		break;



		//case 2 -----------------------------------------------------------------------
	case 2:
		//if the observer is a sensor type, I know the type of observation will be either a uint32* uint16* or uint8*
		if (toObservor->GetMyObservorType() & ObservorType::Sensor)
		{
			//TODO: have it so that sensors can also be templated or at least have an enum that gives what type it will be.
			//for now just assume it will be type uint32* 
			configASSERT(TypeChecker::Isuint32_tPtr<TChannel2DeterminedType>());
			//TODO: now make sure the size of that array is the same size of the one from the sensor. I need to
			//put that information in sensor for that though

			//set the address of the observors observation value to the channel 
			//observation will be located on observation type. I know the output of that type must be the type of this channel since 
			//I already asserted and confirmed that.
			determinedValueChannel2Sourceptr = reinterpret_cast<TChannel2DeterminedType*>(static_cast<AEObservorSensor*>(toObservor)->GetDataAddress());


		}
		//if the observer is a SPB type, I know the type of observation will be of output type float* OutputSignal;
		//and I know the size of that signal will be of uint32_t OutputSize;
		//so I need to make sure this channel type is also a float*
		else if (toObservor->GetMyObservorType() & ObservorType::SPB)
		{
			configASSERT(TypeChecker::IsfloatPtr<TChannel2DeterminedType>());

			configASSERT(static_cast<AESPBObservor*>(toObservor)->GetOutPutSize() == sizeOfChannel2);

			determinedValueChannel2Sourceptr = reinterpret_cast<TChannel2DeterminedType*>(static_cast<AESPBObservor*>(toObservor)->GetOutputAddress());

		}
		//if its an interpretor that I am getting my deterministic data from, than the data could be anything.
		//I can check
		else if (toObservor->GetMyObservorType() & ObservorType::Interpretors)
		{

			//TODO: figure this out 
			//I cant find a way to do this without using RTTI. I may need to have to different builds. One build that 
			//just checks configuration using RTTI, and one build that skips configuration checking and just goes to runtime
			//without RTTI 
#ifdef  Config_Check_Build_RTTI   
			//the char* type of the output observation to the interpretor that will be linked to 
			const char * str1 = static_cast<AEObservorInterpretor*>(toObservor)->GetObservationOutputTypeStr();
			//my channel inputting type that the will be linking to that observor
			const char * str2 = typeid(TChannel2DeterminedType).name();
			uint32_t cmp = strcmp(str1, str2);
			configASSERT(cmp == 0);
#endif //  Config_Check_Build_RTTI 
			uint32_t sizeOfToObservorChannel = static_cast<AEObservorInterpretorBase*>(toObservor)->GetSizeOfChannel2();//static_cast<AEObservorInterpretor*>(toObservor)->SizeOfChannel1;
			configASSERT(sizeOfToObservorChannel == this->SizeOfChannel2);


			//set the address of the observors observation value to the channel 
			//observation will be located on observation type. I know the output of that type must be the type of this channel since 
			//I already asserted and confirmed that.
			determinedValueChannel2Sourceptr = static_cast<AEObservorInterpretorOutputType<TChannel2DeterminedType>*>(toObservor)->GetObservationAddress();


		}
		break;



		//case 3 -----------------------------------------------------------------------
	case 3:
		//if the observer is a sensor type, I know the type of observation will be either a uint32* uint16* or uint8*
		if (toObservor->GetMyObservorType() & ObservorType::Sensor)
		{
			//TODO: have it so that sensors can also be templated or at least have an enum that gives what type it will be.
			//for now just assume it will be type uint32* 
			configASSERT(TypeChecker::Isuint32_tPtr<TChannel3DeterminedType>());
			//TODO: now make sure the size of that array is the same size of the one from the sensor. I need to
			//put that information in sensor for that though

			//set the address of the observors observation value to the channel 
			//observation will be located on observation type. I know the output of that type must be the type of this channel since 
			//I already asserted and confirmed that.
			determinedValueChannel3Sourceptr = reinterpret_cast<TChannel3DeterminedType*>(static_cast<AEObservorSensor*>(toObservor)->GetDataAddress());


		}
		//if the observer is a SPB type, I know the type of observation will be of output type float* OutputSignal;
		//and I know the size of that signal will be of uint32_t OutputSize;
		//so I need to make sure this channel type is also a float*
		else if (toObservor->GetMyObservorType() & ObservorType::SPB)
		{
			configASSERT(TypeChecker::IsfloatPtr<TChannel3DeterminedType>());

			configASSERT(static_cast<AESPBObservor*>(toObservor)->GetOutPutSize() == sizeOfChannel3);

			determinedValueChannel3Sourceptr = reinterpret_cast<TChannel3DeterminedType*>(static_cast<AESPBObservor*>(toObservor)->GetOutputAddress());

		}
		//if its an interpretor that I am getting my deterministic data from, than the data could be anything.
		//I can check
		else if (toObservor->GetMyObservorType() & ObservorType::Interpretors)
		{

			//TODO: figure this out 
			//I cant find a way to do this without using RTTI. I may need to have to different builds. One build that 
			//just checks configuration using RTTI, and one build that skips configuration checking and just goes to runtime
			//without RTTI 
#ifdef  Config_Check_Build_RTTI   
			//the char* type of the output observation to the interpretor that will be linked to 
			const char * str1 = static_cast<AEObservorInterpretor*>(toObservor)->GetObservationOutputTypeStr();
			//my channel inputting type that the will be linking to that observor
			const char * str2 = typeid(TChannel3DeterminedType).name();
			uint32_t cmp = strcmp(str1, str2);
			configASSERT(cmp == 0);
#endif //  Config_Check_Build_RTTI 
			uint32_t sizeOfToObservorChannel = static_cast<AEObservorInterpretorBase*>(toObservor)->GetSizeOfChannel3();//static_cast<AEObservorInterpretor*>(toObservor)->SizeOfChannel1;
			configASSERT(sizeOfToObservorChannel == this->SizeOfChannel3);


			//set the address of the observors observation value to the channel 
			//observation will be located on observation type. I know the output of that type must be the type of this channel since 
			//I already asserted and confirmed that.
			determinedValueChannel3Sourceptr = static_cast<AEObservorInterpretorOutputType<TChannel3DeterminedType>*>(toObservor)->GetObservationAddress();


		}
		break;
	}


	//now that configasserts have been done, add the link.
	this->AddDeterministicLink(toObservor);

}



template<class TObservationType, class TChannel1DeterminedType, uint32_t sizeOfChannel1, class TChannel2DeterminedType, uint32_t sizeOfChannel2, class TChannel3DeterminedType, uint32_t sizeOfChannel3>
inline void AEObservorInterpretor<TObservationType, TChannel1DeterminedType, sizeOfChannel1, TChannel2DeterminedType, sizeOfChannel2, TChannel3DeterminedType, sizeOfChannel3>
::CopyDeterminedValues()
{



	switch (TotalActiveChannels)
	{
	case 1:
		memcpy(&determinedValueChannel1, determinedValueChannel1Sourceptr, sizeOfChannel1* sizeof(TChannel1DeterminedType));
		break;
	case 2:
		memcpy(&determinedValueChannel1, determinedValueChannel1Sourceptr, sizeOfChannel1 * sizeof(TChannel1DeterminedType)); 
		memcpy(&determinedValueChannel2, determinedValueChannel2Sourceptr, sizeOfChannel2 * sizeof(TChannel2DeterminedType)); 
		break; 
	case 3:
		memcpy(&determinedValueChannel1, determinedValueChannel1Sourceptr, sizeOfChannel1 * sizeof(TChannel1DeterminedType));
		memcpy(&determinedValueChannel2, determinedValueChannel2Sourceptr, sizeOfChannel2 * sizeof(TChannel2DeterminedType));
		memcpy(&determinedValueChannel3, determinedValueChannel3Sourceptr, sizeOfChannel3 * sizeof(TChannel3DeterminedType));
		break;  
	default:
		break;
	}

}


 

template<class TObservationType, class TChannel1DeterminedType, uint32_t sizeOfChannel1, class TChannel2DeterminedType, uint32_t sizeOfChannel2, class TChannel3DeterminedType, uint32_t sizeOfChannel3>
inline AEObservorInterpretor<TObservationType, TChannel1DeterminedType, sizeOfChannel1, TChannel2DeterminedType, sizeOfChannel2, TChannel3DeterminedType, sizeOfChannel3>::AEObservorInterpretor()
{
	this->SetMyObservorType(ObservorType::Interpretors);

	this->SizeOfChannel1 = sizeOfChannel1;
	this->SizeOfChannel2 = sizeOfChannel2;
	this->SizeOfChannel3 = sizeOfChannel3;


	//assert that there are no gaps of AENulls to an active channel.As in, all
		//active channels need to be in order. you cant skip a channel
	//and get the size of total activechannels and 
	TotalActiveChannels = 0;
	bool AllIsInOrder = true;
	bool channelHasBeenFoundActiveAlready = false;
	channelHasBeenFoundActiveAlready = !TypeChecker::IsAENull<TChannel3DeterminedType>();
	TotalActiveChannels = channelHasBeenFoundActiveAlready ? TotalActiveChannels+1 : TotalActiveChannels;

	AllIsInOrder = !AllIsInOrder ? AllIsInOrder : 
		channelHasBeenFoundActiveAlready ? channelHasBeenFoundActiveAlready & !TypeChecker::IsAENull<TChannel2DeterminedType>() : 
		 true;
	channelHasBeenFoundActiveAlready = channelHasBeenFoundActiveAlready ? channelHasBeenFoundActiveAlready : !TypeChecker::IsAENull<TChannel2DeterminedType>();
	TotalActiveChannels = channelHasBeenFoundActiveAlready ? TotalActiveChannels+1 : TotalActiveChannels;


	AllIsInOrder = !AllIsInOrder ? AllIsInOrder :
		channelHasBeenFoundActiveAlready ? channelHasBeenFoundActiveAlready & !TypeChecker::IsAENull<TChannel1DeterminedType>() :
		true;
	channelHasBeenFoundActiveAlready = channelHasBeenFoundActiveAlready ? channelHasBeenFoundActiveAlready : !TypeChecker::IsAENull<TChannel1DeterminedType>();
	TotalActiveChannels = channelHasBeenFoundActiveAlready ? TotalActiveChannels+1 : TotalActiveChannels;


	configASSERT(AllIsInOrder);

	 



#ifdef  Config_Check_Build_RTTI  
	this->typeIdForOutObservationType = typeid(TObservationType).name();
#endif 

	AEObservorInterpretor *pToThisClass = this;

	//create tasks
	xTaskCreate([](void* p) {static_cast<AEObservorInterpretor*>(p)->RefreshObservationGaurd(nullptr); }, "RefreshObservationGaurdTask", configMINIMAL_STACK_SIZE, pToThisClass, AOPRIORITYMEDIUM, &this->GaurdTaskToObjectExecutionHandle);




}

/*
template<class TObservationType, class TChannel1DeterminedType, uint32_t sizeOfChannel1, class TChannel2DeterminedType, uint32_t sizeOfChannel2, class TChannel3DeterminedType, uint32_t sizeOfChannel3>
inline TObservationType AEObservorInterpretor<TObservationType, TChannel1DeterminedType, sizeOfChannel1, TChannel2DeterminedType, sizeOfChannel2, TChannel3DeterminedType, sizeOfChannel3>::GetObservationAfterClockUpdates()
{
	return TObservationType();
}*/

/*
template<class TObservationType, class TChannel1DeterminedType, uint32_t sizeOfChannel1, class TChannel2DeterminedType, uint32_t sizeOfChannel2, class TChannel3DeterminedType, uint32_t sizeOfChannel3>
inline TObservationType AEObservorInterpretor<TObservationType, TChannel1DeterminedType, sizeOfChannel1, TChannel2DeterminedType, sizeOfChannel2, TChannel3DeterminedType, sizeOfChannel3>::UpdateObservationIfNeededAndGet(int & inSession)
{
	//local currentsession to make sure it is not changed while within this funcion
	uint8_t currentSessionL = CurrentSession;

	if (AlreadyInSession)
	{
		inSession = 0;
		xSemaphoreTake(MutexHandles[currentSessionL], portMAX_DELAY);
		xSemaphoreGive(MutexHandles[currentSessionL]);
		//xQueuePeek(MutexHandles[currentSessionL], NULL, portMAX_DELAY);
		return Observation;
		//todo: return observation; I need a template for this somehow
	}
	else if (DoINeedARefresh == false)
	{
		inSession = 1;
		//if it doesnt even need a refresh, then just return the observation
		return Observation;
	}

	//NO LONGER VALID
	//if This observor pointed to some deterministic interpretors, Then I would need to call Updates on those to make sure
	// they had not gone stale. however, if it has no interpretor that it depends on and if HasThereBeenARefreshOAnyDeterministicObservors
	//is false, then there would be nothing to check and I can be sure that HasThereBeenARefreshOAnyDeterministicObservors == false
	//is in fact false.
	//else if (HasThereBeenARefreshOAnyDeterministicObservors == false && numOfDeterministicLinksIPointThatAreInterpretors == 0)
	//{
	//	return Observation;
	//}
	else
	{// if it is not in a session then go ahead and start a new session and wait for an incremented currentsession
		inSession = 3;
		xTaskNotify(RefreshObservationGaurdTask, currentSessionL, eSetValueWithOverwrite);
		xSemaphoreTake(MutexHandles[currentSessionL], portMAX_DELAY);
		xSemaphoreGive(MutexHandles[currentSessionL]);
		//xQueuePeek(MutexHandles[currentSessionL], NULL, portMAX_DELAY);
		return Observation;
		//todo: return observation; I need a template for this somehow

		//Set the notification value of the task referenced by xTask4Handle to 0xfff,
		//but only if to do so would not overwrite the task's existing notification
		//value before the task had obtained it (by a call to xTaskNotifyWait()
		//or ulTaskNotifyTake()).
		//if (xTaskNotify(RefreshObservationGaurdTask, currentSessionL, ); == pdPASS)

	}

}



template<class TObservationType, class TChannel1DeterminedType, uint32_t sizeOfChannel1, class TChannel2DeterminedType, uint32_t sizeOfChannel2, class TChannel3DeterminedType, uint32_t sizeOfChannel3>
inline TObservationType AEObservorInterpretor<TObservationType, TChannel1DeterminedType, sizeOfChannel1, TChannel2DeterminedType, sizeOfChannel2, TChannel3DeterminedType, sizeOfChannel3>::GetObservation()
{
	return Observation;
}

*/

template<class TObservationType, class TChannel1DeterminedType, uint32_t sizeOfChannel1, class TChannel2DeterminedType, uint32_t sizeOfChannel2, class TChannel3DeterminedType, uint32_t sizeOfChannel3>
inline void AEObservorInterpretor<TObservationType, TChannel1DeterminedType, sizeOfChannel1, TChannel2DeterminedType, sizeOfChannel2, TChannel3DeterminedType, sizeOfChannel3>::SwapObservationToReadWithTheOneToRefresh()
{
	this->Observation = this->ObservationToChangeInRefresh;
}

