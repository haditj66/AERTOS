#pragma once

#include "AELoop.h"
//#include "AEObjects.h"



//if currently updating, write to the backup variable
//else write to the main variable
#define AELoopObect_ReadWrite_Float(nameOfVariable)\
float  nameOfVariable;\
float  nameOfVariable##_Backup;\
void WriteTo##nameOfVariable(float ValueToUpdateItWith){\
if (isCurrentlyExecuting == true) \
{\
nameOfVariable##_Backup = ValueToUpdateItWith;\
}\
else{\
nameOfVariable = ValueToUpdateItWith;\
}\
}
constexpr int FloatCounts = 1;


//these objects have an AELoop that is set up to a clock
class AELoopObject : public AEAO
{
public:



	friend class AELoop;

	AELoopObject() {
		initializedAEObject = false;
		LoopForThisObject = AELoop::GetFromPoolNoInitYet();
		LoopForThisObject->hasAEObject = true;
	}

	
void CheckIfConfiguredProperly() const override {
	 
		if (initializedAEObject == false)
		{
			// you did not initialize one of your AEobjects
			configASSERT(false);
		}
		 

}

	void InitObject(uint32_t frequencyOfClock, AEPriorities priority, uint32_t stackSizeOfLoop = 350) {
		LoopForThisObject = AELoop::InitPoolForAEObject(LoopForThisObject, this, frequencyOfClock, priority, stackSizeOfLoop);
		//AELoop::InitializeLoop(InitializeLoop);
		initializedAEObject = true;
		isCurrentlyExecuting = false;
	};



	 

protected:

	bool initializedAEObject;
	AELoop* LoopForThisObject;


	virtual void Update() = 0;
	void PreUpdate() {
		AE_UpdateALLSPBSubscriptions

		AE_UpdateALLWritableVariables

		this->isCurrentlyExecuting = true;
		Update();
		this->isCurrentlyExecuting = false;
	}
	 

private:





};
