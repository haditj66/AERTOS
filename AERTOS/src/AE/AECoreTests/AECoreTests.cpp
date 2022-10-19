#include <gtest/gtest.h>
#include <stdio.h>


#include "AE_Init.h"
#include "AEUtils.h"

#ifdef HARDWARE
#include <TestResourceManager.h>		  
#endif // HARDWARE



/*
	This is a very basic sample demonstrating the GoogleTest framework.
	Read more about CppUTest syntax here: https://github.com/google/googletest
*/


//################################### 
//AEPrint
//################################### 

TEST(AEPrint, simple_print)
{
	//This test should succeed
	AEPrint("Hello test print");
	
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}


TEST(AEPrint, simple_print_with_nums)
{
	
	AEPrint("Hello test print with numbers %d num2 %d",2 ,4);
	
}





//################################### 
//AEPerformanceTimer
//################################### 
#include <string> 
TEST(AEPerformanceTimer, simple_timer_test)
{ 
	AEStartTimer(1)
	int ii = 0;
	while (ii++ < 30000) { 
		asm("");
	}
	AEStopTimer(1);
	AELogTimer(1, "simple_timer_test");
	
	float timel = AEGetTimerDuration(1);
	
	#ifdef Simulation
	EXPECT_TRUE(timel < 550000);
	#else
	EXPECT_TRUE(timel < 5500000);
	#endif
}



TEST(AEPerformanceTimer, simple_EnterAndReenter)
{ 
	AETimerForEnteringAndReEntering_AndPrint(1)
	int ii = 0;
	while (ii++ < 30000) { 
		asm("");
	}
	AETimerForEnteringAndReEntering_AndPrint(1);
	
	float timel = AEPerfTimer1->GetElapsedTimeInNanoSeconds();
	
	
#ifdef Simulation
	EXPECT_TRUE(timel < 550000);
#else
	EXPECT_TRUE(timel < 5500000);
#endif
}



TEST(AEPerformanceTimer, multiple_Timers)
{ 
	AEStartTimer(1)
	int i = 0;
	while (i++ < 30000) { 
		asm("");
	}
	AEStopTimer(1);
	
	AEStartTimer(2)
	int ii = 0;
	while (ii++ < 30000) { 
		asm("");
	}
	AEStopTimer(2);
	
	AEStartTimer(3)
	int iii = 0;
	while (iii++ < 30000) { 
		asm("");
	}
	AEStopTimer(3);
	
	float timel = AEPerfTimer1->GetElapsedTimeInNanoSeconds();
	float time2 = AEPerfTimer2->GetElapsedTimeInNanoSeconds();
	float time3 = AEPerfTimer3->GetElapsedTimeInNanoSeconds();
	
	
#ifdef Simulation
	EXPECT_TRUE(timel < 550000);
	EXPECT_TRUE(time2 < 550000);
	EXPECT_TRUE(time3 < 550000);
#else
	EXPECT_TRUE(timel < 5500000);
	EXPECT_TRUE(time2 < 5500000);
	EXPECT_TRUE(time3 < 5500000);
#endif
}
