
#include "AE_Init.h"

#include "AEPerformanceTimer.h"


AEPerformanceTimer* AEPerfTimer1;
AEPerformanceTimer* AEPerfTimer2;
AEPerformanceTimer* AEPerfTimer3;

void AE_Init(void)
{
    setup.BSPInit();

	

	//create instances of the performance timers
	static AEPerformanceTimer AEPerfTimer1L;AEPerfTimer1L._init();
	static AEPerformanceTimer AEPerfTimer2L;AEPerfTimer2L._init();
	static AEPerformanceTimer AEPerfTimer3L;AEPerfTimer3L._init();
	AEPerfTimer1 = &AEPerfTimer1L;
	AEPerfTimer2 = &AEPerfTimer2L;
	AEPerfTimer3 = &AEPerfTimer3L;

    setup.RTOSInit();
    setup.RTOS_ToBSP_SpecificCode();

	

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
#if (1)//(BOARD_USED == STM32F411RE)
 






//simulation--------------------------
#if SWIL_HWIL_DRIVEN == SWIL

extern 	void prvInitialiseHeap();  

void RTOSInit()
{
#if RTOS_USED == FREERTOS
	prvInitialiseHeap();
#endif
}


void BSPInit()
{ 
}


#if RTOS_USED == FREERTOS
void RTOS_ToBSP_SpecificCode()
{
	
}
#endif








#endif


#endif
//###################### stm32f411RE

















