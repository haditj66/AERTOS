//generated file: ModelType2Setup.h


#include "ModelType1Setup.h"


class ModelType2Setup : public ModelType1Setup
{
public:
	ModelType2Setup() {}; 
	
	void RTOSInit(){
	AESetUpBase::RTOSInit();
	
	//UserCode_Section0
//UserCode_Section0_end
	
	}
	
	void BSPInit(){}
	//any things needed to be changed in the BSP to satisfy the RTOS being used
	void RTOS_ToBSP_SpecificCode(){}

private: 
};
