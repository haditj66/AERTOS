#include <gtest/gtest.h>
#include <stdio.h>



#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "FastSine.h"

#include "AEUtils.h"

#include "AE_Init.h"

#ifdef HARDWARE
#include <TestResourceManager.h>		  
#endif // HARDWARE



/*
	This is a very basic sample demonstrating the GoogleTest framework.
	Read more about CppUTest syntax here: https://github.com/google/googletest
*/

TaskHandle_t LEDThread1Handle, LEDThread2Handle;
 
static void LED_Thread1(void const *argument);
 

 
TEST(FastSine, FastSineValuesCorrect)
{
	//	LEDThread1Handle =  (TaskHandle_t)xTaskCreate((TaskFunction_t)LED_Thread1,
	//		(const portCHAR *)"LED1",
	//		configMINIMAL_STACK_SIZE,
	//		NULL,
	//		10,
	//		NULL); 
#ifdef   blabla
		AE_Init(); s
#endif
	
#ifdef HARDWARE
	auto hInputs = TRMCreateFile("inputstxt.txt", sfmCreateOrTruncateWriteOnly);
	auto hOutputs = TRMCreateFile("outputs.dat", sfmCreateOrTruncateWriteOnly);
	ssize_t done = TRMWriteFile(hInputs, "kokokok", sizeof("kokokok"));
	TRMCloseFile(hInputs);
	TRMCloseFile(hOutputs);
		  
#endif // HARDWARE


	
	float errMax = 0;
	float ans;
	float ans2;
	float x_value_at_max_error = 0;
	

	//PrintTimerDuration(1)
		
	for (float x = -10; x < 10; x = x +.0001) 
	{
		ans = cos(x);
		ans2 = AE::cos(x);
 
		if ((abs(ans - ans2)) > errMax)
		{
			errMax = (abs(ans - ans2));  
			x_value_at_max_error = x;
		}
		else { 
			errMax = errMax; 
		}
	}
	

		
	//TimeForEnteringAndReenteringAndPrintAll(1)
	
	//.00121 with err checks
	//.00138 without err checks
	EXPECT_TRUE(errMax < .002); 
	//EXPECT_FLOAT_EQ(fastSineResult, sineResult,.000001);
	
//	printf("before thread starts");
//	//vTaskStartScheduler();
//	EXPECT_EQ(1, 1);
//	EXPECT_EQ(1, 2); 	//<= This test should fail here
}

TEST(FastSine, SuccessfulTest1)
{
	//This test should succeed
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}


TEST(FastSine, SuccessfulTest2)
{
	//This test should succeed;
	printf("Hello from Test #2");
}





static void LED_Thread1(void const *argument)
{
	
	printf("hi from task1");
}
