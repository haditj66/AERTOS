//generated file: testActionRequest.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testActionRequest
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h"
#include "AE_Init.h" 
#include "AEClock.h"
#include "AEObservorSensorFilterOut.h"
#include "AEObjects.h"
#include "AELoopObjectTest.h"
static AELoopObjectTest2 * objectTest;

static void clockTimer1(TimerHandle_t xTimerHandle);
DECLARE_ALL_AO_PTR
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_testActionRequest()
{

//UserCode_Sectionb
AE_Init();
	
	AEITEST_END_TestsAfterTimer_AECoreTestEXE(5000); 
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("actionRequestTime");

	//clock setup
	//static AEClock<AEObservorSensor, AEObservorInterpretorBaseDUMMY, 3> clockForECGL(1000, clockTimer1); // 1000  / 100  (ticks/ms) / ticks = 10 Hz 
	//clockForSPBTest = &clockForECGL;
	
	
	
	static AELoopObjectTest2  objectTest_l;
	objectTest = &objectTest_l;
	objectTest->InitObject(20, AEPriorities::MediumPriority);
	
	static UUartDriver uartDriver_L; //3000
	uartDriver = &uartDriver_L;
	
	AEAO::ConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
static void clockTimer1(TimerHandle_t xTimerHandle)
{ 
 
	//clockForSPBTest->Tick();
}
//UserCode_Sectionc_end

#endif
