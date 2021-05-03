#include <gtest/gtest.h>
#include <stdio.h>


#include "AE_Init.h"

#ifdef HARDWARE
#include <TestResourceManager.h>		  
#endif // HARDWARE


/*
	This is a very basic sample demonstrating the GoogleTest framework.
	Read more about CppUTest syntax here: https://github.com/google/googletest
*/


TEST(FastSine2, SuccessfulTest1)
{
	//This test should succeed
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}


TEST(FastSine2, SuccessfulTest2)
{
	//This test should succeed;
	printf("Hello from Test #2");
}

