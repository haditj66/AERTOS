#pragma once

#include "AEAOResourceAsService.h"
#include "FreeRTOS.h"
#include "AEUtils.h"



template<TemplateFor_AEAOUpdateableAAS>
class AEAOUpdateableAAS : public AEAOResourceAsService<TemplateARGSFor_AEAOUpdateableAAS>
{
	TEMPLATEFORNoDefaults_AEClock
	friend class AEClock;

public:
	
	AEAOUpdateableAAS()
		: AEAOResourceAsService<TemplateARGSFor_AEAOUpdateableAAS>()
	{};

	float GetFrequencyIUpdateAt() { return FrequencyIUpdateAt; };

protected:



	TaskHandle_t GaurdUpdateTask = NULL;
	uint16_t ClockIdImSourcedTo;
	float FrequencyIUpdateAt;
	void SetFrequencyIUpdateAt(float frequencyIUpdateAt);
private:

};

template<TemplateFor_AEAOUpdateableAAS_NoDefaults>
inline void AEAOUpdateableAAS<TemplateARGSFor_AEAOUpdateableAAS>::SetFrequencyIUpdateAt(float frequencyIUpdateAt)
{
		FrequencyIUpdateAt = frequencyIUpdateAt;
	// I also need to set the frequencies of the Action requests.
	//rememebr that if the AO is updateable, which it is cause it is inheriting from
	//here, then it will have TDU action requests that will have frequencies

	this->ActionReq1._frequencyIUpdateAt = frequencyIUpdateAt;

	if (this->ActionReq2.ActionRequestId != false)//just a way to show that this is the AENullActionRequest
	{this->ActionReq2._frequencyIUpdateAt = frequencyIUpdateAt;}
	if (this->ActionReq3.ActionRequestId != false)
	{this->ActionReq3._frequencyIUpdateAt = frequencyIUpdateAt;}
}

















template<TemplateFor_Service>
	class AEAOUpdateable : public AEAOResourceService<TemplateARGSFor_Service>
	{
		TEMPLATEFORNoDefaults_AEClock
		friend class AEClock;

	public:
	
		AEAOUpdateable()
			: AEAOResourceService<TemplateARGSFor_Service>()
		{}
		;

		float GetFrequencyIUpdateAt() { return FrequencyIUpdateAt; }
		;

	protected:



		TaskHandle_t GaurdUpdateTask = NULL;
		uint16_t ClockIdImSourcedTo;
		float FrequencyIUpdateAt;
		void SetFrequencyIUpdateAt(float frequencyIUpdateAt);
	private:

	};

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

