//generated file: C:/AERTOS/AERTOS/src/AE/AECoreTests\testAELoop.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.

//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################


 
#if INTEGRATION_TESTS_FOR_AECoreTests__testAELoop
 
#include "IntegTestPipeline.h"


#include "AECore.h"
#include "AE_Init.h" 
#include "AEClock.h" 
#include "AEObjects.h" 

DECLARE_ALL_AO_PTR

#include "AELoopObjectTest.h"
static AELoopObjectTest* objectTest;




//UserCode_Sectiona
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_testAELoop()
{

AE_Init();
 //UserCode_Sectionbeforemain
	AEITEST_END_TestsAfterTimer_AECoreTests(5000);
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTests("Looponce");
//UserCode_Sectionbeforemain_end






static AELoopObjectTest objectTest_l;
objectTest = &objectTest_l;
objectTest->InitObject(10, AEPriorities::MediumPriority);



//UserCode_Sectionbeforelinks
//UserCode_Sectionbeforelinks_end



//UserCode_Sectionbeforeclock
//UserCode_Sectionbeforeclock_end


//AEITEST_END_TestsAfterTimer_AECoreTests(5000);
//UserCode_Sectionb
//UserCode_Sectionb_end

AEAO::ConfigureAndStart();
}


//UserCode_Sectionc
//UserCode_Sectionc_end





#endif