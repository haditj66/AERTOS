//generated file: SeriesSetup.h


#pragma once

// this is for board STM32F411RE for the 
// F4 part of it

#include "BoardVendorSetup.h"

//includes
//UserCode_Sectiona
//UserCode_Sectiona_end


class SeriesSetup : public BoardVendorSetup
{
public:
	SeriesSetup() {}; 
	
	void RTOSInit(){
	BoardVendorSetup::RTOSInit();
	
	//UserCode_Sectionb
//UserCode_Sectionb_end
	
	}
	
	void BSPInit(){
	BoardVendorSetup::BSPInit();

	//UserCode_Sectionc
//UserCode_Sectionc_end

	}


	//any things needed to be changed in the BSP to satisfy the RTOS being used
	void RTOS_ToBSP_SpecificCode(){
	BoardVendorSetup::RTOS_ToBSP_SpecificCode();

	//UserCode_Sectiond
//UserCode_Sectiond_end

	}

private: 
};

//UserCode_Sectione
//UserCode_Sectione_end
