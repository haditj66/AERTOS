//generated file: UART_TEST.cpp


#if INTEGRATION_TESTS_FOR_AEHal_Tests1 == UART_TEST
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h" 
#include "AE_Init.h"
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_UART_TEST()
{

//UserCode_Sectionb
AE_Init();  
	
	AEITEST_END_TestsAfterTimer_AEHal_Tests1(5000)
		
	
	uart1->TansmitMsg("hello", 5);
	uart1->SetRxCpltCallback([](char* msgReceived, uint32_t sizeOfReceivedMsg)->void {
		AEPrint("message received from uart: %s \n", msgReceived);
		//uart1->TansmitMsg("message received from uart: %s \n", 20);
		//GpioLed1->GPIO_TogglePin();
		
	});
	
	vTaskStartScheduler();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
//UserCode_Sectionc_end

#endif
