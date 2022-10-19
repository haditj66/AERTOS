//generated file: testAELoop.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testAELoop
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h"
#include "AE_Init.h"
#include "AEClock.h"
#include "AELoopObjectTest.h"

#include "AEObjects.h"

static AELoopObjectTest * objectTest;
//static AELoop * objectTest;
//#include "AEObjects.h"

DECLARE_ALL_AO_PTR 
//static AEClock<AEObservorSensorDUMMY, AEObservorInterpretorBaseDUMMY, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0> * clockForAccelerometer;

//GlobalPtrToClock_1

static void clockTimer1(TimerHandle_t xTimerHandle);
static uint32_t datax[1];
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_testAELoop()
{

//UserCode_Sectionb
AE_Init();
	
int periodOfClock1 = 100;
	static AEClock<AEObservorSensorDUMMY, AEObservorInterpretorBaseDUMMY, 1> clockForAccelerometerL(configTICK_RATE_HZ / periodOfClock1, clockTimer1); // 1000  / 100  (ticks/ms) / ticks = 10 Hz 
	clockForAccelerometer = &clockForAccelerometerL;

	AEITEST_END_TestsAfterTimer_AECoreTestEXE(5000);
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("Looponce");
	
//	static AEObservorSensorFilterOut<0> accelSensorL(datax, SensorResolution::Resolution16Bit);
//	accelSensor = &accelSensorL;
//
//	//setup spbs 
//	static AverageSPB<true, 10, 1, Filter<DerivativeFilter, 2>> averageSPBL; averageSPBL.InitSPBObserver();
//	averageSPB = &averageSPBL;
//
//	static float buffer1[10];
//	averageSPB->AddSignalFlowLinkToChannelWithCopy1(accelSensor, buffer1);
//
//	clockForAccelerometer->SetObservorToClock(accelSensor);
//
	static AELoopObjectTest  objectTest_l;
 	objectTest = &objectTest_l;
	objectTest->InitObject(10, AEPriorities::MediumPriority);
	
//	static AELoop  objectTest_l;
//	objectTest = &objectTest_l;
//	objectTest->InitObject(10, AEPriorities::MediumPriority);
	
//
//	AE_SubscribeToSPB(averageSPB, objectTest, &objectTest->VarThatSubsToSPB, 0)
//	AE_SubscribeToSPB(averageSPB, objectTest, &objectTest->VarThatSubsToSPB_filter, 1)
	
	AEAO::ConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
static void clockTimer1(TimerHandle_t xTimerHandle)
{
	datax[0] = datax[0] + 1; // std::rand() % 4095;
	clockForAccelerometer->Tick();
	objectTest->WriteTo_nameOfVariable(5.5);
}
//UserCode_Sectionc_end

#endif
