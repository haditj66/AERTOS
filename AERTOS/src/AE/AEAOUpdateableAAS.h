#pragma once

#include "AEAOResourceAsService.h"
#include "FreeRTOS.h"
#include "AEUtils.h"
#include "AESPBObservor.h"

//
//
//template<TemplateFor_AEAOUpdateableAAS>
//class AEAOUpdateableAAS : public AEAOResourceAsService<TemplateARGSFor_AEAOUpdateableAAS>
//{
//	TEMPLATEFORNoDefaults_AEClock
//	friend class AEClock;
//
//public:
//	
//	AEAOUpdateableAAS()
//		: AEAOResourceAsService<TemplateARGSFor_AEAOUpdateableAAS>()
//	{};
//
//	float GetFrequencyIUpdateAt() { return FrequencyIUpdateAt; };
//
//protected:
//
//
//
//	TaskHandle_t GaurdUpdateTask = NULL;
//	uint16_t ClockIdImSourcedTo;
//	float FrequencyIUpdateAt;
//	void SetFrequencyIUpdateAt(float frequencyIUpdateAt);
//private:
//
//};
//
//template<TemplateFor_AEAOUpdateableAAS_NoDefaults>
//inline void AEAOUpdateableAAS<TemplateARGSFor_AEAOUpdateableAAS>::SetFrequencyIUpdateAt(float frequencyIUpdateAt)
//{
//		FrequencyIUpdateAt = frequencyIUpdateAt;
//	// I also need to set the frequencies of the Action requests.
//	//rememebr that if the AO is updateable, which it is cause it is inheriting from
//	//here, then it will have TDU action requests that will have frequencies
//
//	this->ActionReq1._frequencyIUpdateAt = frequencyIUpdateAt;
//
//	if (this->ActionReq2.ActionRequestId != false)//just a way to show that this is the AENullActionRequest
//	{this->ActionReq2._frequencyIUpdateAt = frequencyIUpdateAt;}
//	if (this->ActionReq3.ActionRequestId != false)
//	{this->ActionReq3._frequencyIUpdateAt = frequencyIUpdateAt;}
//}
//












template<TemplateFor_Service>
	class AEAOUpdateable : public AEAOResourceService<TemplateARGSFor_Service>
	{
		TEMPLATEFORNoDefaults_AEClock
		friend class AEClock;
		
		friend class AESPBObservor;
		 

	public:
	
		AEAOUpdateable()
			: AEAOResourceService<TemplateARGSFor_Service>()
		{
			SPBIamSetToHasbeenRefreshed = false;
			IsSetToAnSPBRefresh = false;
			OnFirstupdate = true; 
			IndexUpdateClockCount = 0;
			ExtraTicks = 0;
		}
		;

		float GetFrequencyIUpdateAt() { return FrequencyIUpdateAt; }
		;
		
		void SetToSPBTick(AESPBObservor * spb, uint16_t filterNum = 0);

		
			
	protected:
 
		TaskHandle_t GaurdUpdateTask = NULL;
		uint16_t ClockIdImSourcedTo;
		float FrequencyIUpdateAt;
		 
		float* ReferenceOfLinkedSPBOutput; 

		//set to spb ticking stuff
		bool IsSetToAnSPBRefresh; 
		bool SPBIamSetToHasbeenRefreshed; 
		uint32_t UpdateClockCount;
		uint32_t IndexUpdateClockCount;
		uint32_t ExtraTicks;
		uint16_t LinkedSPBOutPutSize;
		float LinkedSPBData[MAX_OUTPUT_SIZE_OF_SPB_SET_TO_TDU];//[(InputChannelSize == 0) + InputChannelSize];
		bool OnFirstupdate;
		AESPBObservor* spbIFlowTo;
		
		void SetFrequencyIUpdateAt(float frequencyIUpdateAt);
	private:
		
		
	};


template<TemplateFor_Service_NoDefaults>
	inline void AEAOUpdateable<TemplateARGSFor_Service>
	::SetToSPBTick(AESPBObservor * spb, uint16_t filterNum)
	{ 
		this->IsSetToAnSPBRefresh = true;
		spbIFlowTo = spb;
		
		if (filterNum == 0)
		{
			LinkedSPBOutPutSize = spb->GetOutPutSize();
			ReferenceOfLinkedSPBOutput = spb->GetOutputSignalAddr();  
		}
		else if (filterNum == 1)
		{
			LinkedSPBOutPutSize = 1;
			ReferenceOfLinkedSPBOutput = spb->GetOutputSignalAddrFilter(1);  
		}
		else if (filterNum == 2)
		{
			LinkedSPBOutPutSize = 1;
			ReferenceOfLinkedSPBOutput = spb->GetOutputSignalAddrFilter(2);  
		}
		else if (filterNum == 3)
		{
			LinkedSPBOutPutSize = 1;
			ReferenceOfLinkedSPBOutput = spb->GetOutputSignalAddrFilter(3);  
		}
		else if (filterNum == 4)
		{
			LinkedSPBOutPutSize = 1;
			ReferenceOfLinkedSPBOutput = spb->GetOutputSignalAddrFilter(4);  
		}
		else if (filterNum == 5)
		{
			LinkedSPBOutPutSize = 1;
			ReferenceOfLinkedSPBOutput = spb->GetOutputSignalAddrFilter(5);  
		}
		
		
		this->ActionReq4.LinkedSPBData = LinkedSPBData;
		
		
		
		SetFrequencyIUpdateAt(spb->GetFrequencyIRefreshAt());
		
		spb->SetTDUToMySPBClock(this);

		if (this->ActionReq5.ActionRequestId != false)//just a way to show that this is the AENullActionRequest
		{
			this->ActionReq5.LinkedSPBData = LinkedSPBData;
		}
		if (this->ActionReq6.ActionRequestId != false)
		{
			this->ActionReq6.LinkedSPBData = LinkedSPBData;
		}

	}

template<TemplateFor_Service_NoDefaults>
	inline void AEAOUpdateable<TemplateARGSFor_Service>::SetFrequencyIUpdateAt(float frequencyIUpdateAt)
	{
		FrequencyIUpdateAt = frequencyIUpdateAt;
		// I also need to set the frequencies of the Action requests.
		//rememebr that if the AO is updateable, which it is cause it is inheriting from
		//here, then it will have TDU action requests that will have frequencies 

		if (this->ActionReq4.ActionRequestId != false)//just a way to show that this is the AENullActionRequest
		{this->ActionReq4._frequencyIUpdateAt = frequencyIUpdateAt; }
		if (this->ActionReq5.ActionRequestId != false)//just a way to show that this is the AENullActionRequest
		{this->ActionReq5._frequencyIUpdateAt = frequencyIUpdateAt; }
		if (this->ActionReq6.ActionRequestId != false)
		{this->ActionReq6._frequencyIUpdateAt = frequencyIUpdateAt; }
	}



 