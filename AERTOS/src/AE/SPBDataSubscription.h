#pragma once
//#include "FreeRTOS.h"
#include "AEUtils.h" 
//#include "SPBSubprivateImp.h"



//this will work by having the subscribing AO (S_AO) copying data over to its 
//executing variable before it is about to start using that variable. 
//problem is that the spb could be writing to the output variable while the S_AO is
//reading from it. I could have a mutex where all S_AOs must take when reading from the output
//variable, however this is not good because it means that multiple AO of different priorities would
//need to take that same mutex giving risk to a priority inversion.
//---instead I should have the spb write to two output variables. one output variable called prevOutput
//will be used by the S_AO if the spb is currently refreshing. the other will be just the normal output 
//variable. this will be used by the S_AO if the spb is not currently executing. It is important that
//the prevOutput variable gets replaced by the current output variable right before the spb starts
//refreshing. it is also important that the spb writes to the output variable While it is still refreshing.

//for some optimization/exceptions:
//spbs that run from interrupt still a chance that the S_AO could
//be in the middle of reading from the output variable when the interupt is triggered. therefore perhaps 
//spbs that run from interrupt should tell the S_AO directly via a bool to reread the output variable
//as it could have been interrupted. 


///
///nameOfSubObject: name of the sub object, just make sure this is different than anything made thus far
///spbToSubto: the spb to subscribe to.
///AOSubscriber: the AO that is subscribing.
///VarAddressToPutSubData: the varibale float address that you want to but the subscribing data into.



 

class SPBDataSubscription
{ 
	

	TEMPLATEFOR_AESPBOUTPUT
	friend class AESPBObservorOutputType;

	friend class SPBSubprivateImp;

	friend class AESPBObservor;

	friend class AELoop;
	
	friend class AELoopObject;

	template<TemplateFor_SimpleFSM_NoDefaults>
	friend class AESimpleFSM;

	template<TemplateFor_RAsAService_NoDefaults>
	friend class AEUtilityAsService;
	
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEService;
	template<TemplateFor_Service_NoDefaults_friend>
		friend class AEAOResourceService;
	
	template<TemplateFor_RAsAPossession_NoDefaults>
	friend class AEUtilityAsPossession;
	template<TemplateFor_AEAOUpdateableAAP_NoDefaults>
	friend class AETDUAsPossession;
	template<TemplateFor_AEAOUpdateableAAS_NoDefaults>
	friend class AETDUAsService;

public: 

	//make this class pool-able 
	static SPBDataSubscription* GetFromPool();
	  

	static void CheckIfAllSubscriptionsAreValid();

private:

	static SPBDataSubscription ObjectPool[MAXNUM_OF_TOTAL_SPB_SUBSCRIPTIONS];
	static uint16_t IndexForObjectPool;

	bool CurrentlyCopyingDataOver;
	bool ReCopyTheData;

	SPBDataSubscription() {
		CurrentlyCopyingDataOver = false;
		ReCopyTheData = false;
	}

	//this is the data address to write to that will be used during the AO execution
	float* ExecutionVariableAddr; 
	 
	bool* isSPBCurrentlyRefreshing;
	float* AddrToTheSPBOutputData;
	float* AddrToTheSPBOutputDataPrev;

	uint32_t sizeOfBuffer;

	//this is to be called by the subscribing AO
	//before it starts a session where it anticipates it will use ExecutionVariable.
	//this will copy data over from the spb outputdata to the variable that will be 
	//used for exectution (data handling).
	void CopyDataOver();
	 

};
