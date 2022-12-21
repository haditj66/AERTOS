#pragma once

#include "AELoopObject.h"
 
#include "AELoopObjectTest_WVARs.h"

//if currently updating, write to the backup variable
//else write to the main variable
#define AELoopObect_ReadWrite_Float(nameOfVariable)




class AELoopObjectTest : public AELoopObject
{
	
public:
	AELoopObjectTest() {

		WV_PutInConstructor
		//nameOfVariable_needsUpdating = false;
		//nameOfVariable_BeingWrittenTo = false; 
	}
	;

	uint32_t counter;
	float VarThatSubsToSPB;
	float VarThatSubsToSPB_filter;
	WV_PutPublicClassArea

#ifndef WV_PutPublicClassArea
	float  nameOfVariable;
	float  nameOfVariable_Backup;
	bool  nameOfVariable_needsUpdating;
	bool  nameOfVariable_BeingWrittenTo; 
	void WriteTo_nameOfVariable(float ValueToUpdateItWith) {
		if (this->isCurrentlyExecuting == true)
		{ 
			//this Does Not need to be gated by a mutex as if the AO is currently
			// executing, than it would not be changing this backup variable.
			nameOfVariable_Backup = ValueToUpdateItWith;
			nameOfVariable_needsUpdating = true;
			NeedsWritableVariableUpdated = true;
		}
		else {
			//if there was nameOfVariable_needsUpdating = true, than that must have been
			//now not true as there has been a newer update to this variable that has
			// already been written.
			nameOfVariable_BeingWrittenTo = true;
			nameOfVariable_needsUpdating = false;
			nameOfVariable = ValueToUpdateItWith;
			nameOfVariable_BeingWrittenTo = false;
		}
	}
	

	void UpdateWriteableVariables() override {
	
		if (nameOfVariable_needsUpdating == true)
		{
			if (nameOfVariable_BeingWrittenTo == false)
			{
				nameOfVariable = nameOfVariable_Backup;
				nameOfVariable_needsUpdating = false;
			} 
		}

		NeedsWritableVariableUpdated = false;
	}
#endif


protected:
#ifndef SWIL_HWIL_DRIVEN__HWIL
	const uint32_t ToCountTo = 10000000;
#else
	const uint32_t ToCountTo = 20000;
#endif
  


	void Update() override {

#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testTDU
		//AEStartTimer(1); 
		
		PublishEvt(&SomeOther_Sig_Instance);
		
#else
		counter++;
		
		if (counter > 5)
		{
			
			AEITEST_AECoreTestEXE("Looponce", true, "looped once");
		}

		//do some busy work
		uint32_t aff = 0;
		for (uint32_t i = 0; i < ToCountTo; i++)
		{
			aff++;
		}  
#endif
		

	} 
	
};






 
#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testFSM
extern int StateTracker;
#include "AECore.h"
#endif


class AELoopObjectTest2 : public AELoopObject
{
	
public:
	
	int swapperind;
	AELoopObjectTest2() {

		swapperind = 0;
		
		WV_PutInConstructor
		//nameOfVariable_needsUpdating = false;
		//nameOfVariable_BeingWrittenTo = false; 
	}
	;

	uint32_t counter;
	float VarThatSubsToSPB;
	float VarThatSubsToSPB_filter;
	WV_PutPublicClassArea

#ifndef WV_PutPublicClassArea
	float  nameOfVariable;
	float  nameOfVariable_Backup;
	bool  nameOfVariable_needsUpdating;
	bool  nameOfVariable_BeingWrittenTo; 
	void WriteTo_nameOfVariable(float ValueToUpdateItWith) {
		if (this->isCurrentlyExecuting == true)
		{ 
			//this Does Not need to be gated by a mutex as if the AO is currently
			// executing, than it would not be changing this backup variable.
			nameOfVariable_Backup = ValueToUpdateItWith;
			nameOfVariable_needsUpdating = true;
			NeedsWritableVariableUpdated = true;
		}
		else {
			//if there was nameOfVariable_needsUpdating = true, than that must have been
			//now not true as there has been a newer update to this variable that has
			// already been written.
			nameOfVariable_BeingWrittenTo = true;
			nameOfVariable_needsUpdating = false;
			nameOfVariable = ValueToUpdateItWith;
			nameOfVariable_BeingWrittenTo = false;
		}
	}
	

	void UpdateWriteableVariables() override {
	
		if (nameOfVariable_needsUpdating == true)
		{
			if (nameOfVariable_BeingWrittenTo == false)
			{
				nameOfVariable = nameOfVariable_Backup;
				nameOfVariable_needsUpdating = false;
			} 
		}

		NeedsWritableVariableUpdated = false;
	}
#endif


protected:
 


	void Update() override {
	
#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testActionRequest
		AEStartTimer(1); 
		uartDriver->Transmit(this->GetAO_ID(), "hello from uuart service\n"); 
#endif
		
#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testTDU
		AEStartTimer(1); 
		
		//Token* t = uartDriverTDU->RunRequestWithWait4(this->GetAO_ID(), "hello from uuart TDU service\n"); 
		Token* t = uartDriverTDU->TransmitTDU_WithWait(this->GetAO_ID(), "hello from uuart TDU service\n"); 
		auto ret = uartDriverTDU->TransmitTDU_WaitForRequestToFinish(t); 
		uartDriverTDU->TransmitTDU_DoneWithRequest(t);
		
#endif
		
#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testFSM
		
		
		if (swapperind == 0)
		{
			//AEITEST_AECoreTestEXE("FirstState", StateTracker == 0, "initially StateTracker is 0")
			AEITEST_AECoreTestEXE("FirstState", StateTracker == 10, "initially BlindsUI FSM is in idle state")
			PublishEvt(&Button1_Sig_Instance);
		}
		else if (swapperind == 1)
		{
			AEITEST_AECoreTestEXE("SecondState", StateTracker == 20, "ConfigBlindsUI FSM is in idle state")
			PublishEvt(&Button3_Sig_Instance);	
		}
		else if (swapperind == 2)
		{
			AEITEST_AECoreTestEXE("ThirdState", StateTracker == 30, "ConfigBlindsUI FSM is in SettingTopLimit state")
			PublishEvt(&Button3_Sig_Instance);	
		}		
		else if (swapperind == 3)
		{
			AEITEST_AECoreTestEXE("FourthState", StateTracker == 40, "ConfigBlindsUI FSM is in SettingBottomLimit state")
			PublishEvt(&Button3_Sig_Instance);	 
		}
		else if (swapperind == 4)
		{ 
			PublishEvt(&Button3_Sig_Instance);	 
		}
		else if (swapperind == 5)
		{
			AEITEST_AECoreTestEXE("fifthState", StateTracker == 10, "ConfigBlindsUI FSM Has left and entered BlindsUI FSM idle state")
			PublishEvt(&Button2_Sig_Instance);	
			//PublishEvt(&Button2_Sig_Instance);	
		}
		else if (swapperind == 6)
		{
			AEITEST_AECoreTestEXE("sixthState", StateTracker == 50, "ConfigBlindsUI FSM Has left and entered BlindsUI FSM idle state")
			
			//PublishEvt(&Button2_Sig_Instance);	
		}
		
		//swapperind = swapperind > 5 ?  0 : (swapperind +1);
		swapperind++;
		
		
		
#endif
		
	}
	;
};