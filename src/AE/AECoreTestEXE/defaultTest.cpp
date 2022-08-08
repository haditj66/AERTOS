//generated file: defaultTest.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_AECoreTestEXE__defaultTest
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "iostream"

#include "AECore.h" 
#include "AE_Init.h"
#include "FastSine.h"
#include "ByteSerializer.h"



#ifdef RTOS_USED__FREERTOS

#include "AESet.h"
#include "AECircularBuffer.h" 




TaskHandle_t LEDThread1Handle, LEDThread2Handle;

/* Private function prototypes -----------------------------------------------*/
static void LED_Thread1(void const *argument);
static void LED_Thread2(void const *argument);
#endif




DECLARE_ALL_AO_PTR

#include <stdarg.h>
void UART_Printf(const char *pFormat, ...)
{
	char buffer[128];
	va_list lst;
	va_start(lst, pFormat);
	vsnprintf(buffer, sizeof(buffer), pFormat, lst);
	va_end(lst);

}
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_defaultTest()
{

//UserCode_Sectionb
AE_Init();	
	
	//! [timed end]
	AEITEST_END_TestsAfterTimer_AECoreTestEXE(5000)
	//! [timed end]
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("FirstThread")
	
		
		
	//testing fast sine
	static float ak = AE::sin(1.57);
	AEPrint("result is: %f \n", ak);


	//testing byte serializer
	char dataser[30];
	int aa = 2; char bb = 't';
	ByteSerializer2<int, char>::SerializeData(dataser, &aa, &bb);







#ifdef RTOS_USED__FREERTOS
		

		
		
	//testing AESet
	AESet<int, 5> set1(0);
	set1.Insert(4);
		
	//testing AECircularbuffer
	AECircularBuffer<float, 5> cirBuf1;
	cirBuf1.Push(5.7);
	cirBuf1.Push(4.5);
	float dd = *cirBuf1.Peek(); cirBuf1.Pop(); 
			
		
		

		


		
#ifdef SWIL_HWIL_DRIVEN__HWIL
	//TransmitMsg("hi from uart console", 0);
		
	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif
		 
			
	/* Thread 1 definition */ 
	//osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
	 /*  Thread 2 definition */
//osThreadDef(LED2, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
/* Start thread 1 */
//LEDThread1Handle = osThreadCreate(osThread(LED1), NULL); 
		
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
		
#endif
	for (;;) ;
//UserCode_Sectionb_end

}


//UserCode_Sectionc
#ifndef USING_LINUX
static void LED_Thread1(void const *argument)
{
	(void) argument;
  
#ifdef SWIL_HWIL_DRIVEN__HWIL
	for (;;)
	{
		
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		
		//osDelay(2000);
		TickType_t ticks2 = 500 / portTICK_PERIOD_MS; 
		vTaskDelay(ticks2 ? ticks2 : 1);   
		
		//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		/*
		//osThreadSuspend(LEDThread2Handle);
		//osDelay(2000);
		
		vTaskSuspend(LEDThread2Handle);
		TickType_t ticks = 2000 / portTICK_PERIOD_MS; 
		vTaskDelay(ticks ? ticks : 1);   
		
		//osThreadResume(LEDThread2Handle);
		vTaskResume(LEDThread2Handle);*/
	}

#else
	for (;;)
	{
		AEITEST_AECore_Tests1("FirstThread", true, "has entered this for loop")
			
		//vTaskSuspend(LEDThread2Handle);
		//TickType_t ticks = 2000 / portTICK_PERIOD_MS; 
		//vTaskDelay(ticks ? ticks : 1);  
		AEPrint("ela\n");
			
	}

#endif


}



static void LED_Thread2(void const *argument)
{
	uint32_t count;
	(void) argument;
  
	//static float ak = sintest(1.57);
	for (;;)
	{
			
#ifdef SWIL_HWIL_DRIVEN__HWIL
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
#endif
		AEPrint("ela\n");
		//osDelay(200);

#ifdef RTOS_USED__FREERTOS
		TickType_t ticks2 = 500 / portTICK_PERIOD_MS; 
		vTaskDelay(ticks2 ? ticks2 : 1);
#endif
	}
}


#endif
//UserCode_Sectionc_end

#endif
