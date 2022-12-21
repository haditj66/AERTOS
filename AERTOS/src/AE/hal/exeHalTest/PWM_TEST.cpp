//generated file: PWM_TEST.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_exeHalTest__PWM_TEST
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
//Hadi: 
//  -DONE move the aehal define to a place where it makes more sense in the cmake file. also, 
//	-DONE time to make the stm32f4 hal into a standalone library considering you changed the i2c files.
//	-DONE Make tests to capture this nightmare of a peripheral!
//	-  DONE you didnt test AEHAL exe tests with the PC version! first fill in the implementatoin for AEI2C.h and AEI2C.cpp then go through the two hal tests and make sure they work for pc.
//	-DONE move this test to a proper test called I2C_TEST (just copy this contents over to the other main). give back this adc test it's code!
//	-DONE then git commit everything and maybe tag it as a working point!
//	- DONE migrate this project over to the new computer!
//	- DONE change the build folder to make it dependent on the integration exe target location (as well as the cgencmakecache.cmake file).
//	- DONE start on the spi peripheral.	
//	- DONE work on the SPI files for the simulated environment
//  - DONE do the PWM peripheral Quickly
//  - DONE do the PWM test for simulation
//	-Time to refactor everything down! First things first is to turn TDU and action requests into AOs (MAKE THIS AS QUICK AS POSSIBLE!! 1 WEEK MAX!).

#include "AECore.h" 
#include "AE_Init.h"
#include "AELoopObject.h"
#include "AEObjects.h"

DECLARE_ALL_AO_PTR
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_PWM_TEST()
{

//UserCode_Sectionb
AE_Init();
	
AEITEST_END_TestsAfterTimer_exeHalTest(3000)
	 
	
	pwm1->StartPWM();
	
	pwm1->ChangeDutyCycle(80); 
	
	AEITEST_exeHalTest("pwmran", true, "it ran through");
	
	AEITEST_exeHalTest("duty_cycle_changed", pwm1->GetDutyCycle() == 80, "duty cycle 80");
	
	AEConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
//UserCode_Sectionc_end

#endif
