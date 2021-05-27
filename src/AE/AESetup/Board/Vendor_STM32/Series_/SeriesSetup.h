//generated file: SeriesSetup.h


#include "AE_Init.h"


class SeriesSetup : public BoardVendorSetup
{
public:
	SeriesSetup() {}; 
	
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
