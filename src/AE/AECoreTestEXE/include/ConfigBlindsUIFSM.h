#pragma once


//#include "FreeRTOS.h"
#include "AEClock.h"

#include "AESimpleFSM.h"


#include "AEEventBase.h"
//#include "ActionRequestTest2.h"

//#include "HolterMonitorSPBs.h"

//#include "W25Write_AR.h"

extern int StateTracker;

class ConfigBlindsUIFSM : public AESimpleFSM<ConfigBlindsUIFSM>
{
public:
	ConfigBlindsUIFSM() {};


	static AETransitionType Idle(TypeOfThisFSM* const thisFSM, AEEventDiscriminator_t const * const evt);
	static AETransitionType SettingTopLimit(TypeOfThisFSM* const thisFSM, AEEventDiscriminator_t const * const evt);
	static AETransitionType SettingBottomLimit(TypeOfThisFSM* const thisFSM, AEEventDiscriminator_t const * const evt);
	

	// Inherited via AESimpleFSM
	StateFuncPtr InitialState() override;

};


inline AETransitionType ConfigBlindsUIFSM::Idle(TypeOfThisFSM * const thisFSM, AEEventDiscriminator_t const * const evt)
{
	AETransitionType transitionType = UNHANDLED;

	auto evtId = evt->GetEvtID();
	switch (evtId)
	{
	case Enter_Sig:
	{  
		
		StateTracker = 20;
		
		thisFSM->Subscribe<Button1_Sig>();
		thisFSM->Subscribe<Button2_Sig>();
		thisFSM->Subscribe<Button3_Sig>();
		thisFSM->StartUpdateTimer(100);
		break;
	}
	case Exit_Sig:
	{
		thisFSM->UnSubscribe<Button1_Sig>();
		thisFSM->UnSubscribe<Button2_Sig>();
		thisFSM->UnSubscribe<Button3_Sig>();
		thisFSM->StopUpdateTimer();
		break;
	}
	case Button1_Sig:
	{
		AEPrint("\nConfigBlind:  Idle:Button1\n");
		break;
	}
	case Button2_Sig:
	{
		AEPrint("\nConfigBlind:  Idle:Button2\n");
		break;
	}
	case Button3_Sig:
	{ 
		AEPrint("\nConfigBlind:  Idle:Button3\n"); 

		TRANSITION_TOSTATE(&SettingTopLimit)
		break; 
	}
	case Update_Sig:
	{
		break;
	} 
	default:
		break;
	}

	return transitionType;
}

inline AETransitionType ConfigBlindsUIFSM::SettingTopLimit(TypeOfThisFSM * const thisFSM, AEEventDiscriminator_t const * const evt)
{
	AETransitionType transitionType = UNHANDLED;

	auto evtId = evt->GetEvtID();
	switch (evtId)
	{
	case Enter_Sig:
	{
		StateTracker = 30;
		
		thisFSM->Subscribe<Button1_Sig>();
		thisFSM->Subscribe<Button2_Sig>();
		thisFSM->Subscribe<Button3_Sig>();
		thisFSM->StartUpdateTimer(100);
		break;
	}
	case Exit_Sig:
	{
		thisFSM->UnSubscribe<Button1_Sig>();
		thisFSM->UnSubscribe<Button2_Sig>();
		thisFSM->UnSubscribe<Button3_Sig>();
		thisFSM->StopUpdateTimer();
		break;
	}
	case Button1_Sig:
	{
		AEPrint("\nConfigBlind:  SettingTopLimit:Button1\n");
		break;
	}
	case Button2_Sig:
	{
		AEPrint("\nConfigBlind:  SettingTopLimit:Button2\n");
		break;
	}
	case Button3_Sig:
	{
		AEPrint("\nConfigBlind:  SettingTopLimit:Button3\n");
		TRANSITION_TOSTATE(&SettingBottomLimit)
		break;
	}
	case Update_Sig:
	{
		break;
	}
	default:
		break;
	}

	return transitionType;
}

inline AETransitionType ConfigBlindsUIFSM::SettingBottomLimit(TypeOfThisFSM * const thisFSM, AEEventDiscriminator_t const * const evt)
{
	AETransitionType transitionType = UNHANDLED;

	auto evtId = evt->GetEvtID();
	switch (evtId)
	{
	case Enter_Sig:
	{
		
		StateTracker = 40;
		
		thisFSM->Subscribe<Button1_Sig>();
		thisFSM->Subscribe<Button2_Sig>();
		thisFSM->Subscribe<Button3_Sig>();
		thisFSM->StartUpdateTimer(100);
		break;
	}
	case Exit_Sig:
	{
		thisFSM->UnSubscribe<Button1_Sig>();
		thisFSM->UnSubscribe<Button2_Sig>();
		thisFSM->UnSubscribe<Button3_Sig>();
		thisFSM->StopUpdateTimer();
		break;
	}
	case Button1_Sig:
	{
		AEPrint("\nConfigBlind:  SettingBottomLimit:Button1\n");
		break;
	}
	case Button2_Sig:
	{
		AEPrint("\nConfigBlind:  SettingBottomLimit:Button2\n");
		break;
	}
	case Button3_Sig:
	{
		AEPrint("\nConfigBlind:  SettingBottomLimit:Button3\n");
		AE_EXIT()
		break;
	}
	case Update_Sig:
	{
		break;
	}
	default:
		break;
	}

	return transitionType;
}




inline ConfigBlindsUIFSM::StateFuncPtr ConfigBlindsUIFSM::InitialState()
{
	return CastToStateFuncPtr(&Idle);
}
