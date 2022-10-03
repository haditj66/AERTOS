//generated file: testFilters.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testFilters
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h"
#include "AE_Init.h" 
#include "AEClock.h"
#include "AEObservorSensorFilterOut.h"
#include "AEObjects.h"

#include "DerivativeFilter.h"


DECLARE_ALL_AO_PTR

 
	 
static uint32_t sensordata1[1];
static uint32_t sensordata2[1];
static uint32_t sensordata3[1]; 

static void clockTimer1(TimerHandle_t xTimerHandle);
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_testFilters()
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
	//TODO:this is not working. look into it?
//	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("VelocityValue");
//	AEITEST_EXPECT_TEST_TO_RUN_AECoreTestEXE("AccelerationValue");

	//clock setup
	static AEClock<AEObservorSensor, AEObservorInterpretorBaseDUMMY, 3> clockForECGL(100, clockTimer1); // 1000  / 100  (ticks/ms) / ticks = 10 Hz 
	clockForSPBTest = &clockForECGL;

	//	//sensor setup
	static AEObservorSensorFilterOut<2, Filter<DerivativeFilter, 2>, Filter<DerivativeFilter, 2>,1> sensor1L((uint32_t*)sensordata1, SensorResolution::Resolution16Bit);
	sensor1 = &sensor1L; 
	static AEObservorSensorFilterOut<2, Filter<DerivativeFilter, 2>, Filter<DerivativeFilter, 2>,1> sensor2L((uint32_t*)sensordata2, SensorResolution::Resolution16Bit);
	sensor2 = &sensor2L; 
	static AEObservorSensorFilterOut<2, Filter<DerivativeFilter, 2>, Filter<DerivativeFilter, 2>,1> sensor3L((uint32_t*)sensordata3, SensorResolution::Resolution16Bit);
	sensor3 = &sensor3L;
	
	
	//spbs
	static ThreeDimensionalVector<0> velocitySPBL; velocitySPBL.InitSPBObserver(); velocitySPBL.isForVel = true;
	velocitySPB = &velocitySPBL;  
	static ThreeDimensionalVector<0> accelerationSPBL; accelerationSPBL.InitSPBObserver(); accelerationSPBL.isForVel = false;
	accelerationSPB = &accelerationSPBL;  
	 
	
	clockForSPBTest->SetObservorToClock(sensor1, AEClock_PrescalerEnum::PRESCALER1);
	clockForSPBTest->SetObservorToClock(sensor2, AEClock_PrescalerEnum::PRESCALER1);
	clockForSPBTest->SetObservorToClock(sensor3, AEClock_PrescalerEnum::PRESCALER1);
	
	

	 
	static float chBuffer1[1];
	static float chBuffer2[1];
	static float chBuffer3[1];
	velocitySPB->AddSignalFlowLinkToChannelWithCopy1(sensor1, chBuffer1, 1); 
	velocitySPB->AddSignalFlowLinkToChannelWithCopy2(sensor2, chBuffer2, 1); 
	velocitySPB->AddSignalFlowLinkToChannelWithCopy3(sensor3, chBuffer3, 1); 
	
	static float chBuffer11[1];
	static float chBuffer22[1];
	static float chBuffer33[1];
	accelerationSPB->AddSignalFlowLinkToChannelWithCopy1(sensor1, chBuffer11, 2); 
	accelerationSPB->AddSignalFlowLinkToChannelWithCopy2(sensor2, chBuffer22, 2); 
	accelerationSPB->AddSignalFlowLinkToChannelWithCopy3(sensor3, chBuffer33, 2); 
	
	AEAO::ConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
static void clockTimer1(TimerHandle_t xTimerHandle)
{ 

	
	sensordata1[0] = sensordata1[0] > 90000 ? 1 : (sensordata1[0] + 1);
	sensordata2[0] = sensordata2[0] > 90000 ? 1 : (sensordata2[0] + 2);
	sensordata3[0] = sensordata3[0] > 90000 ? 1 : (sensordata3[0] + 3);
	 
	clockForSPBTest->Tick();
	 
}
//UserCode_Sectionc_end

#endif
