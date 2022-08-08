//generated file: ADC_TEST.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_exeHalTest__ADC_TEST
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h" 
#include "AE_Init.h"





uint32_t adcCountToPrint1 = 0;
uint32_t adcCountToPrint2 = 0;
uint32_t adcCountToPrint3 = 0;
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_ADC_TEST()
{

//UserCode_Sectionb
AE_Init();  
	
	//! [timed end]
 	AEITEST_END_TestsAfterTimer_exeHalTest(5000)
	//! [timed end]
		
	//! [expect to run]
	AEITEST_EXPECT_TEST_TO_RUN_exeHalTest("ADC1_random test")
	//! [expect to run]
		
//	AEITestLogData* scsc = 0;
//	scsc->ID = 90;
//	auto svvs = scsc->pcFileName;
//	auto svvss = scsc->ID;
		 
		
	adc1->SetADC_ConvCpltCallback_t([]()->void {
		adcCountToPrint1++;
		if (adcCountToPrint1 > 1000)
		{
			uint16_t adcValue = adc1->GetADCData();
			//! [integ test assert]
			AEITEST_exeHalTest("ADC1 test", (adcValue > 1800 && adcValue < 2500), "test adc1 is getting adc value");
			//! [integ test assert]
			AEPrint("adc1 data is %d \n", adcValue);
			adcCountToPrint1 = 0;
		}
	});
	
	adc2->SetADC_ConvCpltCallback_t([]()->void {
		adcCountToPrint2++;
		if (adcCountToPrint2 > 1000)
		{
			uint16_t adcValue = adc2->GetADCData();
			AEITEST_exeHalTest("ADC2 test", (adcValue > 900 && adcValue < 1500), "test adc2 is getting adc value");
			AEPrint("adc2 data is %d \n", adcValue);
			adcCountToPrint2 = 0;
		}
	});
	
	adc3->SetADC_ConvCpltCallback_t([]()->void {
		//		if (adc3->GetADCData() > 2000)
		//		{ GpioLed1->GPIO_SetHigh(); }
		//		else
		//		{ GpioLed1->GPIO_SetLow(); }
		adcCountToPrint3++;
		if (adcCountToPrint3 > 1000)
		{
			uint16_t adcValue = adc3->GetADCData();
			AEITEST_exeHalTest("ADC3 test", (adcValue > 1600 && adcValue < 2300), "test adc3 is getting adc value");
			AEPrint("adc3 data is %d \n", adcValue);
			adcCountToPrint3 = 0;
		}
	});
		
		
	/* Start scheduler */ 
	AEConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
//UserCode_Sectionc_end

#endif
