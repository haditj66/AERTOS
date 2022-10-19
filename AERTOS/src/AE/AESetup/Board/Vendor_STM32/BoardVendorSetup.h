//generated file: BoardVendorSetup.h
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#pragma once

// this is for board STM32F411RE for the 
// STM32 part of it

#include "AESetUpBase.h"

//includes
//UserCode_Sectiona
#include "cmsis_os.h"
#include "UARTConsole.h" 

//the clock should be implemented in AEConfig
extern void SystemClock_Config(void);
//UserCode_Sectiona_end


class BoardVendorSetup : public AESetUpBase
{
public:
	BoardVendorSetup() {}; 
	
	void RTOSInit(){
	AESetUpBase::RTOSInit();
	
	//UserCode_Sectionb
//UserCode_Sectionb_end
	
	}
	
	void BSPInit(){
	AESetUpBase::BSPInit();

	//UserCode_Sectionc
SystemClock_Config();  
		
#ifndef Target_RealUART
		//	UARTConsole_InitTypeDef uARTConsole_InitTypeDef;
		//	uARTConsole_InitTypeDef.BaudRate = 115200;
		//	Init_UARTConsole(&uARTConsole_InitTypeDef);
		//	TransmitMsg("hi from uart console", 0);
#endif
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
