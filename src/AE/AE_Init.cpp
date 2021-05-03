
#include "AE_Init.h"

#include "AEPerformanceTimer.h"


AEPerformanceTimer* AEPerfTimer1;
AEPerformanceTimer* AEPerfTimer2;
AEPerformanceTimer* AEPerfTimer3;

void AE_Init(void)
{  
	BSPInit();  

	//create instances of the performance timers
	static AEPerformanceTimer AEPerfTimer1L;AEPerfTimer1L._init();
	static AEPerformanceTimer AEPerfTimer2L;AEPerfTimer2L._init();
	static AEPerformanceTimer AEPerfTimer3L;AEPerfTimer3L._init();
	AEPerfTimer1 = &AEPerfTimer1L;
	AEPerfTimer2 = &AEPerfTimer2L;
	AEPerfTimer3 = &AEPerfTimer3L;
	
	RTOSInit();
	RTOS_ToBSP_SpecificCode();

#ifdef Using_AEHAL 
	InitializeAllPeripheral
		
// ADCPERIPHERAL1_Instance = ADCPERIPHERAL1::getInstance(); ADCPERIPHERAL1_Instance->initializePeripheral();  
//	ADCPERIPHERAL1_Name_CH1 = ADCPERIPHERAL1_Instance->GetPeripheralInstanceCh1(); 
#endif

		
}

 





//############################################
//Poratable implementations for ROS intitializeaions
//############################################


//######################
//For stm32f411RE
//###################### 
#if (MCU_ARM == STM32F411RE)
 





//hardware--------------------------
#ifdef HARDWARE

#include "task.h"
#include "UARTConsole.h"

 
//the clock should be implemented in AEConfig
extern void SystemClock_Config(void);

void RTOSInit()
{  
}


void BSPInit()
{
	HAL_Init();
	
	SystemClock_Config();  
	 
	
#ifndef Target_RealUART
//	UARTConsole_InitTypeDef uARTConsole_InitTypeDef;
//	uARTConsole_InitTypeDef.BaudRate = 115200;
//	Init_UARTConsole(&uARTConsole_InitTypeDef);
//	TransmitMsg("hi from uart console", 0);
#endif
	
	
	
}


#ifdef USING_FREERTOS


	
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


#include "cmsis_os.h"

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
void TIM1_UP_TIM10_IRQHandler(void)
{ 
	//HAL_TIM_IRQHandler(&htim1);

}
}


void RTOS_ToBSP_SpecificCode()
{
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
}

#endif
#endif








//simulation--------------------------
#ifdef SIMULATION

extern 	void prvInitialiseHeap();  

void RTOSInit()
{ 
	 
	prvInitialiseHeap();  
}


void BSPInit()
{ 
}


#ifdef USING_FREERTOS
void RTOS_ToBSP_SpecificCode()
{
	
}
#endif








#endif


#endif
//###################### stm32f411RE










//###################### LINUX
#ifdef USING_LINUX
 

	void RTOSInit()
	{ 
	  
	}


	void BSPInit()
	{ 
	}

 
	void RTOS_ToBSP_SpecificCode()
	{
	
	} 
#endif








