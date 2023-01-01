#pragma once

#include "SPBDataSubscription.h"
#include "AEAO.h"


#define AE_SubscribeToSPB(spbToSubto, AOSubscriber, VarAddressToPutSubData, toFilter)\
SubscribeToSPBOutputData(SPBDataSubscription::GetFromPool(), spbToSubto, AOSubscriber, VarAddressToPutSubData, toFilter);



class SPBSubprivateImp
{
	template<class SPBType>
	friend void SubscribeToSPBOutputData(SPBDataSubscription* spbSubObjectSPBType, SPBType* spbToSubscribeTo, AEAO* AOThatItSubscribing, float *SubscribingDataAddr, uint32_t toFilter);

	template<class SPBType>
	friend void SubscribeToSPBOutputData(SPBDataSubscription* spbSubObjectSPBType, SPBType* spbToSubscribeTo, AEAO* AOThatItSubscribing, float(*SubscribingDataAddr)[SPBType::OUTPUTSIZE_Static]);

	friend class SPBDataSubscription;

	TEMPLATEFOR_AESPBOUTPUT
		friend class AESPBObservorOutputType;

	template<class TFilterDerived, uint16_t PastDataBufferSize >
	friend class Filter;


private:

	SPBSubprivateImp();

	template<class SPBType>
	static void SubscribeToSPBOutputData_IMPL(SPBDataSubscription* spbSubObjectSPBType, SPBType* spbToSubscribeTo, AEAO* AOThatItSubscribing, float* SubscribingDataAddr, uint32_t toFilter);


};


template<class SPBType>
void SubscribeToSPBOutputData(SPBDataSubscription* spbSubObjectSPBType, SPBType* spbToSubscribeTo, AEAO* AOThatItSubscribing, float(*SubscribingDataAddr)[SPBType::OUTPUTSIZE_Static])
{
	SPBSubprivateImp::SubscribeToSPBOutputData_IMPL(spbSubObjectSPBType, spbToSubscribeTo, AOThatItSubscribing, SubscribingDataAddr, 0);
	return;
}

template<class SPBType>
void SubscribeToSPBOutputData(SPBDataSubscription* spbSubObjectSPBType, SPBType* spbToSubscribeTo, AEAO* AOThatItSubscribing, float *SubscribingDataAddr, uint32_t toFilter )
{
	//make sure that, if using this overload, that the spb's output size is of size one.
	configASSERT(SPBType::OUTPUTSIZE_Static == 1);

	SPBSubprivateImp::SubscribeToSPBOutputData_IMPL(spbSubObjectSPBType, spbToSubscribeTo, AOThatItSubscribing, SubscribingDataAddr, toFilter);

}

template<class SPBType>
inline void SPBSubprivateImp
::SubscribeToSPBOutputData_IMPL(SPBDataSubscription* spbSubObjectSPBType, SPBType * spbToSubscribeTo, AEAO * AOThatItSubscribing, float * SubscribingDataAddr, uint32_t toFilter)
{
	//populate needed data of subscription object
	spbSubObjectSPBType->ExecutionVariableAddr = SubscribingDataAddr;
	if (toFilter == 0)
	{
		spbSubObjectSPBType->AddrToTheSPBOutputData = spbToSubscribeTo->OutPutSignalBuffer;
		spbSubObjectSPBType->AddrToTheSPBOutputDataPrev = spbToSubscribeTo->OutPutSignalBufferPrev;
	}
	else
	{
		//assert that the proper filter define was turned on in the aeconfigs
		bool filter1DefineSet = false;
#ifdef	SPB_OF_FILTER1_SUBSCRIBED 
		filter1DefineSet = true;
#endif
		bool filter2DefineSet = false;
#ifdef	SPB_OF_FILTER2_SUBSCRIBED 
		filter2DefineSet = true;
#endif
		bool filter3DefineSet = false;
#ifdef	SPB_OF_FILTER3_SUBSCRIBED 
		filter3DefineSet = true;
#endif
		bool filter4DefineSet = false;
#ifdef	SPB_OF_FILTER4_SUBSCRIBED 
		filter4DefineSet = true;
#endif
		bool filter5DefineSet = false;
#ifdef	SPB_OF_FILTER5_SUBSCRIBED 
		filter5DefineSet = true;
#endif 
		//assert that the proper filter define was turned on in the aeconfigs
		if (toFilter == 1) { configASSERT(filter1DefineSet == true); }
		if (toFilter == 2) { configASSERT(filter2DefineSet == true); }
		if (toFilter == 3) { configASSERT(filter3DefineSet == true); }
		if (toFilter == 4) { configASSERT(filter4DefineSet == true); }
		if (toFilter == 5) { configASSERT(filter5DefineSet == true); }


		//set the filter's output and prevoutput to the proper values
		if (toFilter == 1) {
#ifdef	SPB_OF_FILTER1_SUBSCRIBED 
			spbSubObjectSPBType->AddrToTheSPBOutputData = spbToSubscribeTo->Filter1.GetOutputDataAddress();
			spbSubObjectSPBType->AddrToTheSPBOutputDataPrev = &spbToSubscribeTo->filter1Prev;
#endif 
		}
		if (toFilter == 2) {
#ifdef	SPB_OF_FILTER2_SUBSCRIBED 
			spbSubObjectSPBType->AddrToTheSPBOutputData = spbToSubscribeTo->Filter2.GetOutputDataAddress();
			spbSubObjectSPBType->AddrToTheSPBOutputDataPrev = &spbToSubscribeTo->filter2Prev;
#endif 
		}
		if (toFilter == 3) {
#ifdef	SPB_OF_FILTER3_SUBSCRIBED 
			spbSubObjectSPBType->AddrToTheSPBOutputData = spbToSubscribeTo->Filter3.GetOutputDataAddress();
			spbSubObjectSPBType->AddrToTheSPBOutputDataPrev = &spbToSubscribeTo->filter3Prev;
#endif 
		}
		if (toFilter == 4) {
#ifdef	SPB_OF_FILTER4_SUBSCRIBED 
			spbSubObjectSPBType->AddrToTheSPBOutputData = spbToSubscribeTo->Filter4.GetOutputDataAddress();
			spbSubObjectSPBType->AddrToTheSPBOutputDataPrev = &spbToSubscribeTo->filter4Prev;
#endif 
		}
		if (toFilter == 5) {
#ifdef	SPB_OF_FILTER5_SUBSCRIBED 
			spbSubObjectSPBType->AddrToTheSPBOutputData = spbToSubscribeTo->Filter5.GetOutputDataAddress();
			spbSubObjectSPBType->AddrToTheSPBOutputDataPrev = &spbToSubscribeTo->filter5Prev;
#endif 
		}
	}


	
	spbSubObjectSPBType->isSPBCurrentlyRefreshing = &spbToSubscribeTo->isCurrentlyExecuting;
	spbSubObjectSPBType->sizeOfBuffer = SPBType::OUTPUTSIZE_Static;


	spbToSubscribeTo->AddSubscriber(spbSubObjectSPBType);
	AOThatItSubscribing->AddSubscribtionToSPB(spbSubObjectSPBType);
}


