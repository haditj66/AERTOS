//generated file: testTDU.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testTDU
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h"
#include "AE_Init.h" 
#include "AEClock.h"
#include "AEObservorSensorFilterOut.h"
#include "AEObjects.h"
#include "AELoopObjectTest.h"

#include "UUartDriver.h"
static AELoopObjectTest2 * objectTest;
static AELoopObjectTest * objectTest1;

static void clockTimer1(TimerHandle_t xTimerHandle);

DECLARE_ALL_AO_PTR
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_testTDU()
{

//UserCode_Sectionb
AE_Init();
	
	AEITEST_END_TestsAfterTimer_AECoreTestEXE(5000); 
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("TDUWaitForEvent");

	//clock setup
	static AEClock<AEObservorSensorDUMMY, AEObservorInterpretorBaseDUMMY,0,0,1> clockForECGL(1000, clockTimer1); // 1000  / 100  (ticks/ms) / ticks = 10 Hz 
	clockForTDU = &clockForECGL;
	
	static AELoopObjectTest  objectTest1_l;
	objectTest1 = &objectTest1_l;
	objectTest1->InitObject(3, AEPriorities::MediumPriority);
	
	static AELoopObjectTest2  objectTest_l;
	objectTest = &objectTest_l;
	objectTest->InitObject(20, AEPriorities::MediumPriority);
	

	
	static UUartDriverTDU uartDriver_L; uartDriver_L.Init(AEPriorities::MediumPriority);
	uartDriverTDU = &uartDriver_L;
	
	clockForTDU->SetTDUToClock(uartDriverTDU, AEClock_PrescalerEnum::PRESCALER1);
	
	AEAO::ConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
static void clockTimer1(TimerHandle_t xTimerHandle)
{  
	clockForTDU->Tick();
	 
}
//UserCode_Sectionc_end

#endif
