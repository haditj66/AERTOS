#include "SPBDataSubscription.h"

#include "AEAO.h"

 

SPBDataSubscription SPBDataSubscription::ObjectPool[MAXNUM_OF_TOTAL_SPB_SUBSCRIPTIONS];
uint16_t SPBDataSubscription::IndexForObjectPool = 0;


SPBDataSubscription * SPBDataSubscription::GetFromPool( )
{ 
	//increase the MAXNUM_OF_TOTAL_SPB_SUBSCRIPTIONS in the AEconfig
	configASSERT(IndexForObjectPool < MAXNUM_OF_TOTAL_SPB_SUBSCRIPTIONS);
	 
	SPBDataSubscription* subToReturn = &SPBDataSubscription::ObjectPool[IndexForObjectPool];
	IndexForObjectPool++;
	

	return subToReturn;
}

void SPBDataSubscription::CheckIfAllSubscriptionsAreValid()
{
	bool isDupe = false;
	//go through all subscriptions in the pool and check if there are any duplicate ExecutionVariableAddr 
	for (uint32_t i = 0; i < MAXNUM_OF_TOTAL_SPB_SUBSCRIPTIONS-1; i++)
	{
		for (size_t j = i+1; j < MAXNUM_OF_TOTAL_SPB_SUBSCRIPTIONS; j++)
		{
			if (ObjectPool[i].ExecutionVariableAddr == nullptr)
			{
				break;
			}

			isDupe = ObjectPool[i].ExecutionVariableAddr == ObjectPool[j].ExecutionVariableAddr;
			if (isDupe == true){
				// you had a duplicate ExecutionVariableAddr  in your spb subcriptions. You cant have a 
				//ExecutionVariableAddr  subscribed to two different spbs.
				configASSERT(isDupe == false);
				break;}
		}
		if (isDupe == true) { break; }
	}  
}

void SPBDataSubscription::CopyDataOver()
{ 

		//if the spb is not currently refreshing than copy the data from its normal outputbuffer

	if (*isSPBCurrentlyRefreshing == false)
	{
		CurrentlyCopyingDataOver = true;
		memcpy(ExecutionVariableAddr, AddrToTheSPBOutputData, sizeOfBuffer * 4);
		CurrentlyCopyingDataOver = false;
	}
	else
	{
		CurrentlyCopyingDataOver = true;
		memcpy(ExecutionVariableAddr, AddrToTheSPBOutputDataPrev, sizeOfBuffer * 4);
		CurrentlyCopyingDataOver = false;
	}

	//if ReCopyTheData = true, then that means the spb that refreshed from an interrupt has told it to redo the copy
	//as it may have been interrupted mid copying
	if (ReCopyTheData == true)
	{
		memcpy(ExecutionVariableAddr, AddrToTheSPBOutputData, sizeOfBuffer * 4);
		ReCopyTheData = false;
	}

}