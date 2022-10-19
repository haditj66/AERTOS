#pragma once


//#include "FreeRTOS.h"
#include "AEClock.h"

#include "AESimpleFSM.h"


#include "AEEventBase.h"
//#include "ActionRequestTest2.h"

//AECHANGED
//#include "UPloadDataToPCTDU.h"
//AECHANGEDDONE

//#include "HolterMonitorSPBs.h"

//#include "W25Write_AR.h"

extern int StateTracker;

class NormalUserOperationBlindsFSM : public AESimpleFSM<NormalUserOperationBlindsFSM>
{
public:
	NormalUserOperationBlindsFSM() {};


	static AETransitionType Idle(TypeOfThisFSM* const thisFSM, AEEventDiscriminator_t const * const evt);
	static AETransitionType MovingToPoint(TypeOfThisFSM* const thisFSM, AEEventDiscriminator_t const * const evt);
	

	// Inherited via AESimpleFSM
	StateFuncPtr InitialState() override;

};


inline AETransitionType NormalUserOperationBlindsFSM::Idle(TypeOfThisFSM * const thisFSM, AEEventDiscriminator_t const * const evt)
{
	AETransitionType transitionType = UNHANDLED;

	auto evtId = evt->GetEvtID();
	switch (evtId)
	{
	case Enter_Sig:
	{ 
		StateTracker = 50;
			
		thisFSM->Subscribe<Button1_Sig>();
		thisFSM->Subscribe<Button2_Sig>();
		thisFSM->Subscribe<Button3_Sig>();
		break;
	}
	case Exit_Sig:
	{
		thisFSM->UnSubscribe<Button1_Sig>();
		thisFSM->UnSubscribe<Button2_Sig>();
		thisFSM->UnSubscribe<Button3_Sig>();
		break;
	}
	case Button1_Sig:
	{
		AEPrint("\nNormalUserOperationBlindsFSM:  Idle:Button1\n"); 
			break;
	}
	case Button2_Sig:
	{
		AEPrint("\nNormalUserOperationBlindsFSM:  Idle:Button2\n"); 
			break;
	}
	case Button3_Sig:
	{
		AEPrint("\nNormalUserOperationBlindsFSM:  Idle:Button3\n");
		TRANSITION_TOSTATE(&MovingToPoint)
		break;
	}
	default:
		break;
	}

	return transitionType;
}

inline AETransitionType NormalUserOperationBlindsFSM::MovingToPoint(TypeOfThisFSM * const thisFSM, AEEventDiscriminator_t const * const evt)
{
	AETransitionType transitionType = UNHANDLED;

	auto evtId = evt->GetEvtID();
	switch (evtId)
	{
	case Enter_Sig:
	{ 
		thisFSM->Subscribe<Button1_Sig>();
		thisFSM->Subscribe<Button2_Sig>(); 
		break;
	}
	case Exit_Sig:
	{
		thisFSM->UnSubscribe<Button1_Sig>();
		thisFSM->UnSubscribe<Button2_Sig>(); 
		break;
	}
	case Button1_Sig:
	{
		AEPrint("\NormalUserOperationBlindsFSM:  MovingToPoint:Button1\n");
		TRANSITION_TOSTATE(&Idle)
			break;
	}
	case Button2_Sig:
	{
		AEPrint("\NormalUserOperationBlindsFSM:  MovingToPoint:Button2\n");
		TRANSITION_TOSTATE(&Idle)
			break;
	}
	default:
		break;
	}


	return transitionType;
}


inline NormalUserOperationBlindsFSM::StateFuncPtr NormalUserOperationBlindsFSM::InitialState()
{
	return CastToStateFuncPtr(&Idle);
}
