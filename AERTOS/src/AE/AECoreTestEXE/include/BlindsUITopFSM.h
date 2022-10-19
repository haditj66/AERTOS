#pragma once


//#include "FreeRTOS.h"
#include "AEClock.h"

#include "AESimpleFSM.h"

#include "ConfigBlindsUIFSM.h"

#include "AEEventBase.h"
//#include "ActionRequestTest2.h"

//#include "HolterMonitorSPBs.h"

//#include "W25Write_AR.h"

#include "NormalUserOperationBlindsFSM.h"

extern int StateTracker;


class BlindsUITopFSM : public AESimpleFSM<BlindsUITopFSM, ConfigBlindsUIFSM, NormalUserOperationBlindsFSM>
{
public:
	BlindsUITopFSM() {};


	static AETransitionType Idle(TypeOfThisFSM* const thisFSM, AEEventDiscriminator_t const * const evt);
	static AETransitionType Configuring(TypeOfThisFSM* const thisFSM, AEEventDiscriminator_t const * const evt);
	static AETransitionType NormalOperating(TypeOfThisFSM* const thisFSM, AEEventDiscriminator_t const * const evt);


	// Inherited via AESimpleFSM
	StateFuncPtr InitialState() override;

};


inline AETransitionType BlindsUITopFSM::Idle(TypeOfThisFSM * const thisFSM, AEEventDiscriminator_t const * const evt)
{
	AETransitionType transitionType = UNHANDLED;

	StateTracker = 10;
	
	auto evtId = evt->GetEvtID();
	switch (evtId)
	{
	case Enter_Sig:
	{
		thisFSM->Subscribe<Button1_Sig>();
		thisFSM->Subscribe<Button2_Sig>();
		thisFSM->Subscribe<Button3_Sig>();
		thisFSM->StartUpdateTimer(100);
		 
  char* bla = "entered idle";
	//uartDriver->RunRequest1<ActionRequestForUARTTransmit>(thisFSM->GetAO_ID(), bla);
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
		AEPrint("\nBlindsUITopFSM:  Idle:Button1\n");
		TRANSITION_TOSTATE(&Configuring)
		break;
	}
	case Button2_Sig:
	{
		AEPrint("\nBlindsUITopFSM:  Idle:Button2\n");
		TRANSITION_TOSTATE(&NormalOperating)
		break;
	}
	case Button3_Sig:
	{
		AEPrint("\nBlindsUITopFSM:  Idle:Button3\n");
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

inline AETransitionType BlindsUITopFSM::Configuring(TypeOfThisFSM * const thisFSM, AEEventDiscriminator_t const * const evt)
{
	AETransitionType transitionType = UNHANDLED;

	auto evtId = evt->GetEvtID();
	switch (evtId)
	{
	case Enter_Sig:
	{
		thisFSM->Subscribe<Button1_Sig>();
		thisFSM->Subscribe<Button2_Sig>();
		thisFSM->Subscribe<Button3_Sig>();
		thisFSM->StartUpdateTimer(100);

		thisFSM->ActivateSubmachine(thisFSM->SubMachine1);
		
		break;
	}
	case Exit_Sig:
	{
		thisFSM->UnSubscribe<Button1_Sig>();
		thisFSM->UnSubscribe<Button2_Sig>();
		thisFSM->UnSubscribe<Button3_Sig>();
		thisFSM->StopUpdateTimer();

		thisFSM->DeActivateSubmachine(thisFSM->SubMachine1);

		break;
	}
	case Button1_Sig:
	{
		AEPrint("\nBlindsUITopFSM:  Configuring:Button1\n");
		break;
	}
	case Button2_Sig:
	{
		AEPrint("\nBlindsUITopFSM:  Configuring:Button2\n");
		break;
	}
	case Button3_Sig:
	{
		AEPrint("\nBlindsUITopFSM:  Configuring:Button3\n");
		TRANSITION_TOSTATE(&Idle)
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

inline AETransitionType BlindsUITopFSM::NormalOperating(TypeOfThisFSM * const thisFSM, AEEventDiscriminator_t const * const evt)
{
	AETransitionType transitionType = UNHANDLED;

	auto evtId = evt->GetEvtID();
	switch (evtId)
	{
	case Enter_Sig:
	{
		thisFSM->Subscribe<Button1_Sig>();
		thisFSM->Subscribe<Button2_Sig>();
		thisFSM->Subscribe<Button3_Sig>();
		thisFSM->StartUpdateTimer(100);

		thisFSM->ActivateSubmachine(thisFSM->SubMachine2);


		break;
	}
	case Exit_Sig:
	{
		thisFSM->UnSubscribe<Button1_Sig>();
		thisFSM->UnSubscribe<Button2_Sig>();
		thisFSM->UnSubscribe<Button3_Sig>();
		thisFSM->StopUpdateTimer();

		thisFSM->DeActivateSubmachine(thisFSM->SubMachine2);

		break;
	}
	case Button1_Sig:
	{
		AEPrint("\nBlindsUITopFSM:  NormalOperating:Button1\n");
		break;
	}
	case Button2_Sig:
	{
		AEPrint("\nBlindsUITopFSM:  NormalOperating:Button2\n");
		break;
	}
	case Button3_Sig:
	{
		AEPrint("\nBlindsUITopFSM:  NormalOperating:Button3\n");
		TRANSITION_TOSTATE(&Idle)
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




inline BlindsUITopFSM::StateFuncPtr BlindsUITopFSM::InitialState()
{
	return CastToStateFuncPtr(&Idle);
}
