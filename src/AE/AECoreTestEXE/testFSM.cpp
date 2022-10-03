//generated file: testFSM.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testFSM
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h"
#include "AE_Init.h" 
#include "AEClock.h"
#include "AEObjects.h"

#include "ConfigBlindsUIFSM.h"
#include "NormalUserOperationBlindsFSM.h"
#include "BlindsUITopFSM.h"

#include "AELoopObjectTest.h"


DECLARE_ALL_AO_PTR
	
static AELoopObjectTest2 * objectTest;
 
static BlindsUITopFSM* BlindsUIfsm;
static ConfigBlindsUIFSM* ConfigBlindsUIfsm;
static NormalUserOperationBlindsFSM* NormalUserOperationBlindsfsm;

int StateTracker = 0;
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_testFSM()
{

//UserCode_Sectionb
AE_Init();
	
	AEITEST_END_TestsAfterTimer_AECoreTestEXE(5000); 
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("FirstState");
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("SecondState");
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("ThirdState");
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("FourthState");
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("fifthState");
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("sixthState");
	

	static ConfigBlindsUIFSM ConfigBlindsUIfsmL;
	ConfigBlindsUIfsm = &ConfigBlindsUIfsmL;
	ConfigBlindsUIfsm->Init(true);
	
	static NormalUserOperationBlindsFSM NormalUserOperationBlindsfsmL;
	NormalUserOperationBlindsfsm = &NormalUserOperationBlindsfsmL;
	NormalUserOperationBlindsfsm->Init(true);
	
	static BlindsUITopFSM BlindsUIfsmL;
	BlindsUIfsm = &BlindsUIfsmL;
	BlindsUIfsm->Init(false, 1, ConfigBlindsUIfsm, NormalUserOperationBlindsfsm);
	
	static AELoopObjectTest2  objectTest_l;
	objectTest = &objectTest_l;
	objectTest->InitObject(5, AEPriorities::MediumPriority);
	
	AEAO::ConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
//UserCode_Sectionc_end

#endif
