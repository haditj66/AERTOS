//generated file: SPBSamples.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_AESamples__SPBSamples
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h"
#include "AE_Init.h" 
#include "AEClock.h"
#include "AEObservorSensorFilterOut.h"
#include "AEObjects.h" 


DECLARE_ALL_AO_PTR
	
	static void clockTimer1(TimerHandle_t xTimerHandle);
static uint32_t sensordata1[1];


//Hadi:
//- DONE: change all ActionRequestObjectArg1 so that they work with funciton pointers now!
//- DONE: I will need to code generate all service helper functions and put them into a .h file I can include.
//		Have a define that will be put in the constructor and function section!  Do the same
//		thing for tdus! (2 days)
//- DONE: quick test the tdus still work after code generated. (with new api)
// -DONE: refactor spbs now QUICKLY! no more than (3 days)!!
	//NOTE I dont think there is much to do here honestly. Everything seems good enough for SPBS and filters!
	 
// -DONE: code generate an intialization of projects quickly and only if it is easy enough to do so!!! no more than (4 days)!!!!
	//NOTE it would be nice to have it generated but I think it is NOT PRACTILCAL. There are just too many choices! only if I were able to hire someone to do it, but for now,
	//it is what it is. The best way to do this is to draw it out like before. maybe have a png for every exe test.
	
//	-I NEED AN INITIALIZATION!!! It takes way to long to do even simple things. To do it, I can use macro2 to help generate it.
	//However every initialization generation will be its own Macro2 script. Every AO will have it's own class. The user (you)
	//will fill out these classes and the macro2 will automatically generate the initilaization for every object using the 
	//.cgenMM files (i think. if that is easiest!)

// - rebuild MOST IMPORTANT stuff into modules that I will use from now on! DONT DO STUFF LIKE THE ARDUINO STUFF!!! its not worth it anymore! (3 days!)
		//also mqtt stuff is NOT WORTH IT. remmeber that MCUs are meant to be fast. MQTT does not fit here. I dont plan to do iot. a uart will suffice to 
		//send data to a PC that can, if needed, usher the data to a central PC via MQTT for processing. 
// - finally start on my next new big thing!! make sure it is something big I believe in. No small projects anymore!!
//
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_SPBSamples()
{

//UserCode_Sectionb
AE_Init();
	 
	AEITEST_END_TestsAfterTimer_AESamples(5000);
	AEITEST_EXPECT_TEST_TO_RUN_AESamples("averagespp");
	
	static AEClock<AEObservorSensor, AEObservorInterpretorBaseDUMMY, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>
		clockForECGL(1000, clockTimer1); // 1000  / 100  (ticks/ms) / ticks = 10 Hz 
	clockForECG = &clockForECGL;
	
	static AEObservorSensorFilterOut<0> ECGDataL((uint32_t*)sensordata1, SensorResolution::Resolution16Bit);
	sensor1 = &ECGDataL;
	
	
	static AverageSPB<false, 10> AverageSPBL; AverageSPBL.InitSPBObserver(); 
	averageSPB = &AverageSPBL; 
	
	
	clockForECG->SetObservorToClock(sensor1, AEClock_PrescalerEnum::PRESCALER1);
	
	static float bufferaveragespb[10]; 
	averageSPB->AddSignalFlowLinkToChannelWithCopy1(sensor1, bufferaveragespb);
	//averageSPB->AddSignalFlowLinkToChannelWithReference((AESPBObservor*)sensor1,1,0);
	 
	
	
	AEAO::ConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
static void clockTimer1(TimerHandle_t xTimerHandle)
{ 
	sensordata1[0]++;
	sensordata1[0] = sensordata1[0] % 10;
	clockForECG->Tick();
}
//UserCode_Sectionc_end

#endif
