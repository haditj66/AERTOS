
#include "AE_Init.h"


class BoardVendorSetup : public AESetUpBase
{
public:
	BoardVendorSetup() {}; 
	
	void RTOSInit(){}
	//HAL specific intialization code
	void BSPInit(){}
	//any things needed to be changed in the BSP to satisfy the RTOS being used
	void RTOS_ToBSP_SpecificCode(){}

private: 
};
