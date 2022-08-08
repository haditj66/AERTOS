//generated file: SeriesSetup.h
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#pragma once

// this is for board STM32F411RE for the 
// F4 part of it

#include "BoardVendorSetup.h"

//includes
//UserCode_Sectiona
#include "stm32f4xx_hal.h"
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
HAL_Init();
//UserCode_Sectionc_end

	}


	//any things needed to be changed in the BSP to satisfy the RTOS being used
	void RTOS_ToBSP_SpecificCode(){
	BoardVendorSetup::RTOS_ToBSP_SpecificCode();

	//UserCode_Sectiond
NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
//UserCode_Sectiond_end

	}

private: 
};

//UserCode_Sectione
//UserCode_Sectione_end
