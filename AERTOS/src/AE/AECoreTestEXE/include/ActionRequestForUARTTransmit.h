#pragma once
#include "AEUtils.h"
#include "ActionRequestObjectArg.h" 
#include "AECore.h"

//class UUartDriver;
//class ActionRequestForUARTTransmit : public ActionRequestObjectArg1<char const*, bool, 10, UUartDriver*>
//{
//public:
//	static const uint16_t bufferSize = 100;
//
//	char* buffer[bufferSize];
//
//	ActionRequestForUARTTransmit()
//	{
//	};
//
//	// Inherited via ActionRequestObjectArg1
//	void RequestImpl(char const* Argument1) override;
//};


//void ActionRequestForUARTTransmit::RequestImpl(char const* Argument1)
//{
//	AEStopTimer(1);
//	auto tr = AEGetTimerDuration(1);
//	AELogTimer(1, "UtilityRequestTimeToRun");
//	AEITEST_AECoreTestEXE_MUST_PASS_THIS_MANY("actionRequestTime", tr < 500000, "actionRequest timer should be less than .5ms",60);
//	AEPrint(Argument1, 100);
//	 
//}