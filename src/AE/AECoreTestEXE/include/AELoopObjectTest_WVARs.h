//generated file: AELoopObjectTest_WVARs.h


#pragma once 


#define TypeOfVar1 float
#define TypeOfVar2 uint32_t
#define TypeOfVar3 
#define TypeOfVar4 
#define TypeOfVar5 
#define TypeOfVar6 
#define TypeOfVar7 



 #define WV_PutInConstructor \
  nameOfVariable_needsUpdating = false; nameOfVariable_BeingWrittenTo = false;    TestVariable2_needsUpdating = false; TestVariable2_BeingWrittenTo = false;   




#define WV_PutPublicClassArea \
	private:\
	TypeOfVar2  TestVariable2;\
	TypeOfVar2 TestVariable2_Backup;\
	bool  TestVariable2_needsUpdating;\
	bool  TestVariable2_BeingWrittenTo; \
  public:\
	void WriteTo_TestVariable2(TypeOfVar2 ValueToUpdateItWith) {\
		if (this->isCurrentlyExecuting == true)\
		{ \
			TestVariable2_Backup = ValueToUpdateItWith;\
			TestVariable2_needsUpdating = true;\
			NeedsWritableVariableUpdated = true;\
		}\
		else {\
			TestVariable2_BeingWrittenTo = true;\
			TestVariable2_needsUpdating = false;\
			TestVariable2 = ValueToUpdateItWith;\
			TestVariable2_BeingWrittenTo = false;\
		}\
	}\
	private:\
	TypeOfVar1  nameOfVariable;\
	TypeOfVar1 nameOfVariable_Backup;\
	bool  nameOfVariable_needsUpdating;\
	bool  nameOfVariable_BeingWrittenTo; \
  public:\
	void WriteTo_nameOfVariable(TypeOfVar1 ValueToUpdateItWith) {\
		if (this->isCurrentlyExecuting == true)\
		{ \
			nameOfVariable_Backup = ValueToUpdateItWith;\
			nameOfVariable_needsUpdating = true;\
			NeedsWritableVariableUpdated = true;\
		}\
		else {\
			nameOfVariable_BeingWrittenTo = true;\
			nameOfVariable_needsUpdating = false;\
			nameOfVariable = ValueToUpdateItWith;\
			nameOfVariable_BeingWrittenTo = false;\
		}\
	}\
	void UpdateWriteableVariables() override{ \
		 if (nameOfVariable_needsUpdating == true) \
		{\
			if (nameOfVariable_BeingWrittenTo == false)\
			{\
				nameOfVariable = nameOfVariable_Backup;\
				nameOfVariable_needsUpdating = false;\
			} \
		} if (TestVariable2_needsUpdating == true) \
		{\
			if (TestVariable2_BeingWrittenTo == false)\
			{\
				TestVariable2 = TestVariable2_Backup;\
				TestVariable2_needsUpdating = false;\
			} \
		}NeedsWritableVariableUpdated = false;\
	}



	 