
/* Includes ------------------------------------------------------------------*/
#ifndef SIMULATION
#include <stm32f4xx_hal.h>
#endif
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"



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
 

uint32_t adcCountToPrint1 = 0;
uint32_t adcCountToPrint2 = 0;
uint32_t adcCountToPrint3 = 0;

int main(void)
{ 

	
	
	AE_Init();  
	AEPrint("asd");
	
	uart1->TansmitMsg("hello", 5);
	uart1->SetRxCpltCallback([](char* msgReceived, uint32_t sizeOfReceivedMsg)->void {
		//		AEPrint("message received from uart: %s \n", msgReceived);
		uart1->TansmitMsg("message received from uart: %s \n",10);
		GpioLed1->GPIO_TogglePin();
		
	});
	
	adc1->SetADC_ConvCpltCallback_t([]()->void {
		adcCountToPrint1++;
		if (adcCountToPrint1 > 1000)
		{
			AEPrint("adc1 data is %d \n", adc1->GetADCData());
			adcCountToPrint1 = 0;
		}
	});
	
	adc2->SetADC_ConvCpltCallback_t([]()->void {
		adcCountToPrint2++;
		if (adcCountToPrint2 > 1000)
		{
			AEPrint("adc2 data is %d \n", adc2->GetADCData());
			adcCountToPrint2 = 0;
		}
	});
	
	adc3->SetADC_ConvCpltCallback_t([]()->void {
//		if (adc3->GetADCData() > 2000)
//		{ GpioLed1->GPIO_SetHigh(); }
//		else
//		{ GpioLed1->GPIO_SetLow(); }
		adcCountToPrint3++;
		if (adcCountToPrint3 > 1000)
		{
			AEPrint("adc3 data is %d \n", adc3->GetADCData());
			adcCountToPrint3 = 0;
		}
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

		
	/* Start scheduler */ 
	vTaskStartScheduler();
		
		
	for (;;) ;
}


extern "C" void HardFault_Handler()
{
	
	int y = 0;
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


