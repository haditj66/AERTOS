#pragma once

#include "ActionRequestObjectArgTDU.h"
#include "AECore.h"

class UUartDriverTDU; 
class ActionRequestForUARTTransmitTDU : public ActionRequestObjectArgTDU1<char*,int8_t,10 ,UUartDriverTDU>
{
public: 
 
	char* arg1;
	int32_t timesToPrint;

	ActionRequestForUARTTransmitTDU()
	{
		timesToPrint = 0;
	} 

	// Inherited via ActionRequestObjectArgTDU
	void RequestImpl(char* Argument1) override
	{
		AEStopTimer(1)
		float timel = AEGetTimerDuration(1);
		
		arg1 = Argument1;  
		timesToPrint = 0;
	} 
	
	
	bool Update() override 
	{ 

		
		//print it 10 times before the final print
		if (timesToPrint < 10)
		{
			 
			AEPrint("UART TDU print number: %d \n", timesToPrint);
			timesToPrint++;
			
			AEITEST_AECoreTestEXE_MUST_PASS_THIS_MANY("TDUENTERED", true, "TDU wait for event ran", 100);
			return false;
		}
		else
		{
			bool FlashWasCompletedSuccessfullyWithIntterupt =
			this->WaitForEvent<SomeOther_Sig>(
				[](void* s, AEEventDiscriminator_t* evt)->void {
					//SomeOther_Sig* sssc = (SomeOther_Sig*)evt->evt;
					AEPrint("Event SomeOther_Sig recieved");
					AEITEST_AECoreTestEXE_MUST_PASS_THIS_MANY("TDUWaitForEvent", true, "TDU wait for event ran", 10);
					return;
				}
				, 500);
			

			AEPrint(arg1); 
			SetReturnArg(1); 
			return true;
		}
		
		return false;
		 
	}  
	
	

};
 