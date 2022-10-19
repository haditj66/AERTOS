//generated file: SeriesSetup.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


// this is for board STM32F411RE for the
// F4 part of it

#include "SeriesSetup.h"

//UserCode_Sectiona
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


void TIM1_UP_TIM10_IRQHandler(void)
{ 
	//HAL_TIM_IRQHandler(&htim1);

}
//UserCode_Sectiona_end


//UserCode_Sectionb
//UserCode_Sectionb_end
