//generated file: ModelType2Setup.h
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#pragma once

// this is for board STM32F411RE for the 
// RE part of it

#include "ModelType1Setup.h"

//includes
//UserCode_Sectiona
//UserCode_Sectiona_end


class ModelType2Setup : public ModelType1Setup
{
public:
	ModelType2Setup() {}; 
	
	void RTOSInit(){
	ModelType1Setup::RTOSInit();
	
	//UserCode_Sectionb
//UserCode_Sectionb_end
	
	}
	
	void BSPInit(){
	ModelType1Setup::BSPInit();

	//UserCode_Sectionc
//UserCode_Sectionc_end

	}


	//any things needed to be changed in the BSP to satisfy the RTOS being used
	void RTOS_ToBSP_SpecificCode(){
	ModelType1Setup::RTOS_ToBSP_SpecificCode();

	//UserCode_Sectiond
//UserCode_Sectiond_end

	}

private: 
};

//UserCode_Sectione
//UserCode_Sectione_end
