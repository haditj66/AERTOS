#ifndef SIMULATION
#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>				  
#endif // !SIMULATION


#ifdef GOOGLE_TESTING
#include <gtest/gtest.h> 
#endif 

#include "AE_Init.h"

#ifndef SIMULATION
#ifdef __cplusplus
extern "C"
#endif
//void SysTick_Handler(void)
//{
//	HAL_IncTick();
//	HAL_SYSTICK_IRQHandler();
//}
#endif // !SIMULATION



#ifdef SIMULATION
int main(int argc, char *argv[])
{
#else
int main(void)
{
	
	
#endif  
	AE_Init();
	
	//clear the main timers log file since this is a new run
	AEClearContentsOfFile("PerformanceTimes\\MostRecentTimes.txt");
	
#ifdef GOOGLE_TESTING
#ifdef SIMULATION
	testing::InitGoogleTest(&argc, argv);
#else
	char *argv = (char *)"";
	int argc = 1;
	testing::InitGoogleTest(&argc, &argv);
#endif
	
	
	(void)RUN_ALL_TESTS();
#endif
	
	}
