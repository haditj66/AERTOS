
/* Includes ------------------------------------------------------------------*/
//#if SWIL_HWIL_DRIVEN == HWIL
////#include <stm32f4xx_hal.h>
//#endif



#include "AECore.h"
#include "IntegTestPipeline.h"
 
#include "AE_Init.h"


//#include "AEPortAndPin.h"
//#include "AEPort.h"
//#include "PinSelector.h"
//#include <stdio.h>

	TaskHandle_t LEDThread1Handle, LEDThread2Handle;

/* Private function prototypes -----------------------------------------------*/
static void LED_Thread1(void const *argument);
static void LED_Thread2(void const *argument);


DECLARE_ALL_AO_PTR
 
#include <stdarg.h>
	
#include "iostream"
 

class test
{
public:
	int* arr;
	test()
	{
		arr = new int(10);
		arr[0] = 4;
	}
	void grow()
	{
		int* arr2 = new int[20];
		memcpy(arr2, arr, sizeof(int) * 10);  
		arr = arr2;
	}
}
;
        

int main(void)
{  
	
	test* aaa = new test();
	aaa->grow();
	
	RunSelectedIntegrationTest();
	
	uart1->TansmitMsg("hello", 5);
	uart1->SetRxCpltCallback([](char* msgReceived, uint32_t sizeOfReceivedMsg)->void {
		//		AEPrint("message received from uart: %s \n", msgReceived);
		uart1->TansmitMsg("message received from uart: %s \n",10);
		GpioLed1->GPIO_TogglePin();
		
	});
	
	
//	static auto sfaf = ADCPERIPHERAL1_Instance->ADCdata[0];
//	adc1->GetADCData();
		
	Gpiobutton1->SetextiCallback_t([]()->void { 
		GpioLed1->GPIO_TogglePin();
	});
	
	Gpiobutton2->SetextiCallback_t([]()->void {
		GpioLed3->GPIO_TogglePin();
	});
	
		
LEDThread1Handle = (TaskHandle_t) xTaskCreate((TaskFunction_t)LED_Thread1,
		(const portCHAR *)"LED1",
		configMINIMAL_STACK_SIZE,
		NULL,
		10,
		NULL); 
  
		
	LEDThread2Handle = (TaskHandle_t) xTaskCreate((TaskFunction_t)LED_Thread2,
		(const portCHAR *)"LED2",
		configMINIMAL_STACK_SIZE,
		NULL,
		10,
		NULL); 

		

		
		
	for (;;) ;
}







static void LED_Thread1(void const *argument)
{
	(void) argument;
  
#ifndef SIMULATION
	for (;;)
	{ 
		
		//osDelay(2000);
//		GpioLed1->GPIO_TogglePin();
		
		TickType_t ticks2 = 2000 / portTICK_PERIOD_MS; 
		vTaskDelay(ticks2 ? ticks2 : 1);   
		  
	}
#endif
}



static void LED_Thread2(void const *argument)
{
	uint32_t count;
	(void) argument;
   
	for(;  ;)
	{ 
		AEPrint("ela\n"); 
		GpioLed2->GPIO_TogglePin();
		TickType_t ticks2 = 2000 / portTICK_PERIOD_MS; 
		vTaskDelay(ticks2 ? ticks2 : 1);   
	}
}


