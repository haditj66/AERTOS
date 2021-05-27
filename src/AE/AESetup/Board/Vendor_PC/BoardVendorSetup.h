//generated file: BoardVendorSetup.h


#pragma once

// this is for board X64 for the 
// PC part of it

#include "AESetUpBase.h"

//includes
//UserCode_Sectiona
extern 	void prvInitialiseHeap();
//UserCode_Sectiona_end


class BoardVendorSetup : public AESetUpBase
{
public:
	BoardVendorSetup() {}; 
	
	void RTOSInit(){
	AESetUpBase::RTOSInit();
	
	//UserCode_Sectionb
prvInitialiseHeap();
//UserCode_Sectionb_end
	
	}
	
	void BSPInit(){
	AESetUpBase::BSPInit();

	//UserCode_Sectionc
//UserCode_Sectionc_end

	}


	//any things needed to be changed in the BSP to satisfy the RTOS being used
	void RTOS_ToBSP_SpecificCode(){
	AESetUpBase::RTOS_ToBSP_SpecificCode();

	//UserCode_Sectiond
//UserCode_Sectiond_end

	}

private: 
};

//UserCode_Sectione
//UserCode_Sectione_end
