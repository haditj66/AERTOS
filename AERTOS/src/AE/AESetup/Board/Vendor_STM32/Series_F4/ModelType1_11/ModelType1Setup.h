//generated file: ModelType1Setup.h
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#pragma once

// this is for board STM32F411RE for the 
// 11 part of it

#include "SeriesSetup.h"

//includes
//UserCode_Sectiona
//UserCode_Sectiona_end


class ModelType1Setup : public SeriesSetup
{
public:
	ModelType1Setup() {}; 
	
	void RTOSInit(){
	SeriesSetup::RTOSInit();
	
	//UserCode_Sectionb
//sdvs;ldv;sdlvm
//UserCode_Sectionb_end
	
	}
	
	void BSPInit(){
	SeriesSetup::BSPInit();

	//UserCode_Sectionc
//UserCode_Sectionc_end

	}


	//any things needed to be changed in the BSP to satisfy the RTOS being used
	void RTOS_ToBSP_SpecificCode(){
	SeriesSetup::RTOS_ToBSP_SpecificCode();

	//UserCode_Sectiond
//UserCode_Sectiond_end

	}

private: 
};

//UserCode_Sectione
//UserCode_Sectione_end
