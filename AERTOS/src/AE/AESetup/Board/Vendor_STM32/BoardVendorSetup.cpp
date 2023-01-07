//generated file: BoardVendorSetup.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


// this is for board STM32F411RE for the
// STM32 part of it

#include "BoardVendorSetup.h"

//UserCode_Sectiona
#include "AEIntegrationTesting.h"




extern "C" void HardFault_Handler()
{
	
	//if integration testing is on, then signal a failed because
	//of a hardfault
#ifdef BUILD_TESTS__TRUE
	AEPrint("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*HardFault occured!!!\n");
	AEITEST_END_HARDFAULT_FUNC();
	
#endif
	for (;;)
	{  
	}
}



	
//this function will be implemented in the freertos port.c file
/*extern "C"
void xPortSysTickHandler(void);
 
extern "C"
	void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	
	//osSystickHandler();
	if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
	{ 
		xPortSysTickHandler(); 
	} 
} */
//UserCode_Sectiona_end


//UserCode_Sectionb
//UserCode_Sectionb_end
