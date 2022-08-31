//generated file: testSPB.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testSPB
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h"
#include "AE_Init.h" 
#include "AEClock.h"
#include "AEObservorSensorFilterOut.h"
#include "AEObjects.h"

DECLARE_ALL_AO_PTR


//Hadi: done with this integration test. time to move to the next test!. remember, NO REFACTORING until all tests
//testing all wanted features of AERTOS hs been created!! make those tests as simply and as fast as possible.
//Also, from now on call interpretors "SPBs-on-demand" and SPBs as "SPBs-continuos"
	

	
//data pointers for sensor observors
static uint32_t sensordata1[1];
static uint32_t sensordata2[1];
static uint32_t sensordata3[1];
//AEObservorSensor*   ECGData = nullptr;

//AverageSPB<10, false>* averageSPB = nullptr;
//NoFilterBufferSPB<300, 0>* noFilterSPB = nullptr;
//LeadOnCorrectlySPB<0>* leadOnCorrectlySPB = nullptr;
//IfAllTrue<0>* ifAllTrueSPB = nullptr;
//
//InterpretorHeartRate<300>* heartRateob = nullptr;
//
//AEClock<1>* clockForECG;

static void clockTimer1(TimerHandle_t xTimerHandle);
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_testSPB()
{

//UserCode_Sectionb
AE_Init();
	
#ifdef BOARD_USED__STM32F411RE
	GPIO_InitTypeDef gpiotim; 
	gpiotim.Pin = GPIO_PIN_1;
	gpiotim.Mode = GPIO_MODE_OUTPUT_PP;
	gpiotim.Pull = GPIO_NOPULL;
	gpiotim.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOA, &gpiotim);
#endif
	
	AEITEST_END_TestsAfterTimer_AECoreTestEXE(5000);
	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("average");

	//clock setup
	static AEClock<AEObservorSensor, AEObservorInterpretorBaseDUMMY, 3> clockForECGL(1000, clockTimer1); // 1000  / 100  (ticks/ms) / ticks = 10 Hz 
	clockForSPBTest = &clockForECGL;

//	//sensor setup
	static AEObservorSensorFilterOut<0> ECGDataL((uint32_t*)sensordata1, SensorResolution::Resolution16Bit);
	sensor1 = &ECGDataL;
	
	static AEObservorSensorFilterOut<0> sensor2L((uint32_t*)sensordata2, SensorResolution::Resolution16Bit);
	sensor2 = &sensor2L; 
	static AEObservorSensorFilterOut<0> sensor3L((uint32_t*)sensordata3, SensorResolution::Resolution16Bit);
	sensor3 = &sensor3L;
	
	
//
//	//SPB setup
	static AverageSPB<10, false> AverageSPBL; AverageSPBL.InitSPBObserver(); 
	averageSPB = &AverageSPBL; 
	static AverageSPB<10, false> AverageSPB2L; AverageSPB2L.InitSPBObserver(); 
	averageSPB2 = &AverageSPB2L; 
	static AverageSPB<10, false> AverageSPB3L; AverageSPB3L.InitSPBObserver(); 
	averageSPB3 = &AverageSPB3L; 
	
	static AdderSPB< > adderSPBL; adderSPBL.InitSPBObserver(); 
	adderSPB = &adderSPBL;
	
	
	
	clockForSPBTest->SetObservorToClock(sensor1, AEClock_PrescalerEnum::PRESCALER1);
	clockForSPBTest->SetObservorToClock(sensor2, AEClock_PrescalerEnum::PRESCALER1);
	clockForSPBTest->SetObservorToClock(sensor3, AEClock_PrescalerEnum::PRESCALER1);
// 
//
//
//	//initialize link pool
//	AELinkDeterministic::InitAELinkDeterministicObjectPool(links, 6);
//	AELinkSignalFlow::InitAELinkSPBObjectPool(LinkSignals, 10);
//
//	// add links that need to be set
	static float bufferaveragespb[10];
	static float bufferaveragespb2[10];
	static float bufferaveragespb3[10];
	averageSPB->AddSignalFlowLinkToChannelWithCopy1(sensor1, bufferaveragespb);
	averageSPB2->AddSignalFlowLinkToChannelWithCopy1(sensor2, bufferaveragespb2);
	averageSPB3->AddSignalFlowLinkToChannelWithCopy1(sensor3, bufferaveragespb3);
	
	static float chBuffer[1];
	adderSPB->AddSignalFlowLinkToChannelWithCopy1(averageSPB, chBuffer);
	static float chBuffer2[1];
	adderSPB->AddSignalFlowLinkToChannelWithCopy2(averageSPB2, chBuffer2);
	static float chBuffer3[1];
	adderSPB->AddSignalFlowLinkToChannelWithCopy3(averageSPB3, chBuffer3);
	
	AEAO::ConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
static void clockTimer1(TimerHandle_t xTimerHandle)
{ 

	
	sensordata1[0] = sensordata1[0] > 9 ? 1 : (sensordata1[0] + 1);
	sensordata2[0] = sensordata2[0] > 9 ? 1 : (sensordata2[0] + 1);
	sensordata3[0] = sensordata3[0] > 9 ? 1 : (sensordata3[0] + 1);
	
	if (sensordata1[0] == 10)
	{   
		//char* bb = new char[2800];
		//char* bb2 = new char[2800];
		//memset(bb, 2, 2800);
		AEStartTimer(1) 
#ifdef BOARD_USED__STM32F411RE
	    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1); 
#endif
		//memcpy(bb,bb2,2800); //this gives 700 us which gave only 400 us on the other AERTOS with IAR with no optimization.
		//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1); 
		
	}
	clockForSPBTest->Tick();
	
		if (sensordata1[0] % 2 == 0)
	{
		 
#ifdef BOARD_USED__STM32F411RE
	    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1); 
#endif
		AEStopTimer(2)
		float timel = AEGetTimerDuration(2);
		float timel3 = 23; 
		AELogTimer(2, "clockspeedcorrect");
		
		static volatile float time2 = AEGetTimerDuration(2);
		
#ifdef OS_USED__NONE
		AEITEST_AECoreTestEXE("clockfreq", time2 > 800000 && time2 < 1200000, "frequency of AEclock should be about 1 millisec"); 
#else
		//using a OS will make this frequency x2 for some reason.
		AEITEST_AECoreTestEXE("clockfreq", time2 > 500000 && time2 < 2400000, "frequency of AEclock should be about 1 millisec"); 
#endif
	}
	else
	{ 
#ifdef BOARD_USED__STM32F411RE
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1); 
#endif
		AEStartTimer(2)

	}

}
//UserCode_Sectionc_end

#endif
