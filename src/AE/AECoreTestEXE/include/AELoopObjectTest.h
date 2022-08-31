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
	}
	;
};