//generated file: ModelType1Setup.h


#include "SeriesSetup.h"


class ModelType1Setup : public SeriesSetup
{
public:
	ModelType1Setup() {}; 
	
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
