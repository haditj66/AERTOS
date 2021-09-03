//generated file: BoardVendorSetup.cpp


// this is for board STM32F411RE for the
// STM32 part of it

#include "BoardVendorSetup.h"

//UserCode_Sectiona
#include "AEIntegrationTesting.h"

extern "C"
{ 
	//extern TIM_HandleTypeDef htim1;

	void SysTick_Handler(void)
	{
		/* USER CODE BEGIN SysTick_IRQn 0 */

		/* USER CODE END SysTick_IRQn 0 */
		osSystickHandler();
		HAL_IncTick();
		HAL_SYSTICK_IRQHandler();
		/* USER CODE BEGIN SysTick_IRQn 1 */

		/* USER CODE END SysTick_IRQn 1 */
	}

}



extern "C" void HardFault_Handler()
{
	
	//if integration testing is on, then signal a failed because
	//of a hardfault
#if BUILD_TESTS == TRUE
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
