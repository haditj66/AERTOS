#pragma once 
 
 



//TODO: time to start bringing in files from the original aertos!! start with what is the most basic need feature.
//bring everything in one at a time and leave out things that were never really needed!! SImplify things as you bring things in.
//NEVER add new feature as you bring things in!!!!!!
	
#define DontCheckForHardDeadlinesInSPBsForEverySetInput
#define AEDontCheckForCorrectActionRequestTemplate
 
//default on
#define Target_stm32f4 

//RTOS configs
#define AEconfigTICK_RATE_HZ 1000
#define AEconfigMINIMAL_STACK_SIZE 928
#define AEconfigTIMER_TASK_STACK_DEPTH 1500
#define AEconfigTOTAL_HEAP_SIZE 56360

//AE configs
#define AOPRIORITYLOWEST 5
#define AOPRIORITYMEDIUM 10
#define AOPRIORITYHIGHEST 29
#define NUMOFACTIVEOBJECTS 20
#define HIGHEST_NUM_OF_EVT_INSTANCES 25

//#define MAXSPB_CHAIN_POOLSIZE 5
#define MAXNUMOFOBSERVORS 30
#define MAXNUMOFINTERPRETORS 15
#define MAXNUMOFSPB 25
#define MAXNUMOFSENSORS 15
#define MAXNUMOFOBSERVERINFLUENCES 25

#define MAXNUMBEROF_FILTERS 5
#define MAXNUMBEROF_FILTERS_From_A_Sensor 2

#define MaxNumOfAELoops 2

#define MAXNUMBEROFINPUTSIGNALS_TO_A_SPB 10
#define MAXNUMBEROFOUTPUTSIGNALS_TO_A_SPB 4

#define MAXNUM_OF_SUBSCRIBERS_To_A_SPB 3
#define MAXNUM_OF_AE_SUBSCRIPTIONS_To_SPBs 3

#define TOTALMAXNUMBEROFOUTPUTSIGNALS_TO_ALL_SPBs 25

#define MAXNUMOFTDUSSETTOTheSameSPB 3
#define SPB_OF_FILTER1_SUBSCRIBED




//#define Config_Check_Build_RTTI
//#define Runtime_Build

//#ifdef TESTWITH_ACTIONREQUEST2
#define configAE_USE_TDUs_AsService  1
#define configAE_USE_U_AsService  1
//#endif
#define configAE_USE_DDSM_AsService  0


 
#define Event1 EventTest1
#define Event1Size 10
#define Event2 EventTest2
#define Event2Size 15
#define Event3 Uart2RecieveEVT
#define Event3Size 20
#define Event4 SPBDecompressionDone
#define Event4Size 5
#define Event5 PCConnecttionCheckEVT
#define Event5Size 5
#define Event6 AENULLEvent
#define Event6Size 0

//place your signals events here. 
#define Signal1 DoneUploading_Sig
#define Signal2 SomeOther_Sig
#define Signal3 Button1_Sig //value for a null signal
#define Signal4 Button2_Sig //value for a null signal
#define Signal5 Button3_Sig //value for a null signal
#define Signal6 1000 //value for a null signal
#define Signal7 1000 //value for a null signal

 

#ifdef TEST_FSM_ACTIVATION
#define AOInclude1 UUartDriver
#define TemplateToAO1 
#define ClassNameOfAO1 UUartDriver
#define TypeOfAO1_1 UUartDriver
#define InstanceNameOfAO1_1 uartDriver
#define TypeOfAO1_2
#define InstanceNameOfAO1_2
#define TypeOfAO1_2
#define InstanceNameOfAO1_2
#define TypeOfAO1_3
#define InstanceNameOfAO1_3
#define TypeOfAO1_4
#define InstanceNameOfAO1_4
#endif
 


//sensors and clocks configurations
#define ClockType1 AEClock<AEObservorSensor, AEObservorInterpretorBaseDUMMY,1,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0>
#define ClockName1 clockForECG
#define ClockType2  
#define ClockName2  
#define ClockType3  
#define ClockName3  
#define ClockType4 
#define ClockName4
#define ClockType5 
#define ClockName5
#define ClockType6 
#define ClockName6

#define SensorName1 sensor1
#define SensorName2 sensor2
#define SensorName3 sensor3
#define SensorName4
#define SensorName5
#define SensorName6
#define SensorName7
#define SensorName8
#define SensorName9
#define SensorName10


 
#define AOInclude1 AverageSPB
#define TemplateToAO1 template<bool isSubscribable,  uint32_t CHANNELCOUNTBUFFER1, TEMPLATESPB_Filters>
#define ClassNameOfAO1 AverageSPB
#define TypeOfAO1_1 AverageSPB<false, 10>
#define InstanceNameOfAO1_1 averageSPB
#define TypeOfAO1_2
#define InstanceNameOfAO1_2
#define TypeOfAO1_2
#define InstanceNameOfAO1_2
#define TypeOfAO1_3
#define InstanceNameOfAO1_3
#define TypeOfAO1_4
#define InstanceNameOfAO1_4 

#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testActionRequest
#define AOInclude1 UUartDriver
#define TemplateToAO1 
#define ClassNameOfAO1 UUartDriver
#define TypeOfAO1_1 UUartDriver
#define InstanceNameOfAO1_1 uartDriver
#define TypeOfAO1_2
#define InstanceNameOfAO1_2
#define TypeOfAO1_2
#define InstanceNameOfAO1_2
#define TypeOfAO1_3
#define InstanceNameOfAO1_3
#define TypeOfAO1_4
#define InstanceNameOfAO1_4
#endif

#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testFilters
#define AOInclude1 ThreeDimensionalVector
#define TemplateToAO1 template<TEMPLATESPB_Filters>
#define ClassNameOfAO1 ThreeDimensionalVector
#define TypeOfAO1_1 ThreeDimensionalVector<0>
#define InstanceNameOfAO1_1 velocitySPB
#define TypeOfAO1_2 ThreeDimensionalVector<0>
#define InstanceNameOfAO1_2 accelerationSPB
#define TypeOfAO1_3  
#define InstanceNameOfAO1_3  
#define TypeOfAO1_4
#define InstanceNameOfAO1_4
#endif

#if INTEGRATION_TESTS_FOR_AECoreTestEXE__testSPB
#define AOInclude1 AverageSPB
#define TemplateToAO1 template<uint32_t ChannelCountBuffer, bool IsOutputSubscribeAble, TEMPLATESPB_Filters>
#define ClassNameOfAO1 AverageSPB
#define TypeOfAO1_1 AverageSPB<10, false>
#define InstanceNameOfAO1_1 averageSPB
#define TypeOfAO1_2 AverageSPB<10, false>
#define InstanceNameOfAO1_2 averageSPB2
#define TypeOfAO1_3 AverageSPB<10, false>
#define InstanceNameOfAO1_3 averageSPB3 
#define TypeOfAO1_4
#define InstanceNameOfAO1_4

#define AOInclude2 AdderSPB
#define TemplateToAO2 template< bool IsOutputSubscribeAble = false, TEMPLATESPB_Filters>
#define ClassNameOfAO2 AdderSPB
#define TypeOfAO2_1 AdderSPB<>
#define InstanceNameOfAO2_1 adderSPB
#define TypeOfAO2_2
#define InstanceNameOfAO2_2
#define TypeOfAO2_2
#define InstanceNameOfAO2_2
#define TypeOfAO2_3
#define InstanceNameOfAO2_3
#define TypeOfAO2_4
#define InstanceNameOfAO2_4

#endif


#ifdef sdqwd

//AO configurations
#define AOInclude1 UUartDriver
#define TemplateToAO1 
#define ClassNameOfAO1 UUartDriver
#define TypeOfAO1_1 UUartDriver
#define InstanceNameOfAO1_1 uartDriver
#define TypeOfAO1_2
#define InstanceNameOfAO1_2
#define TypeOfAO1_2
#define InstanceNameOfAO1_2
#define TypeOfAO1_3
#define InstanceNameOfAO1_3
#define TypeOfAO1_4
#define InstanceNameOfAO1_4

#define AOInclude2 HolterMonitorSPBs
#define TemplateToAO2 template<uint8_t NumOfFilters, uint8_t NUMOFMultiChannelFILTERS, class TFilter1, class TFilter2, uint8_t Filter2LinksFrom, class TFilter3, uint8_t Filter3LinksFrom, class TFilter4, uint8_t Filter4LinksFrom, class TFilter5, uint8_t Filter5LinksFrom> 
#define ClassNameOfAO2 WaveletTransform5_SPB
#define TypeOfAO2_1 WaveletTransform5_SPB<0,0,AENullClass, AENullClass,0, AENullClass,00, AENullClass,0, AENullClass,0>
#define InstanceNameOfAO2_1 waveletTSPB
#define TypeOfAO2_2
#define InstanceNameOfAO2_2
#define TypeOfAO2_2
#define InstanceNameOfAO2_2
#define TypeOfAO2_3
#define InstanceNameOfAO2_3
#define TypeOfAO2_4
#define InstanceNameOfAO2_4

//#define AOInclude3 UIHolterMonitorFSM
#define TemplateToAO3
//#define ClassNameOfAO3 UIHolterMonitorFSM
//#define TypeOfAO3_1 UIHolterMonitorFSM
//#define InstanceNameOfAO3_1 FSMHolterUI
#define TypeOfAO3_2
#define InstanceNameOfAO3_2
#define TypeOfAO3_2
#define InstanceNameOfAO3_2
#define TypeOfAO3_3
#define InstanceNameOfAO3_3
#define TypeOfAO3_4
#define InstanceNameOfAO3_4

#define AOInclude4 w25DriverTDU
#define TemplateToAO4
#define ClassNameOfAO4 w25DriverTDU
#define TypeOfAO4_1 w25DriverTDU
#define InstanceNameOfAO4_1 W25DriverTDU
#define TypeOfAO4_2
#define InstanceNameOfAO4_2
#define TypeOfAO4_2
#define InstanceNameOfAO4_2
#define TypeOfAO4_3
#define InstanceNameOfAO4_3
#define TypeOfAO4_4
#define InstanceNameOfAO4_4

#define AOInclude5 UploadDataToPCTDU
#define TemplateToAO5
#define ClassNameOfAO5 UploadDataToPCTDU
#define TypeOfAO5_1 UploadDataToPCTDU
#define InstanceNameOfAO5_1 UPloadDataToPC_TDU
#define TypeOfAO5_2
#define InstanceNameOfAO5_2
#define TypeOfAO5_2
#define InstanceNameOfAO5_2
#define TypeOfAO5_3
#define InstanceNameOfAO5_3
#define TypeOfAO5_4
#define InstanceNameOfAO5_4
 

#define TemplateToAO6
#define ClassNameOfAO6
#define TypeOfAO6_1
#define InstanceNameOfAO6_1
#define TypeOfAO6_2
#define InstanceNameOfAO6_2
#define TypeOfAO6_2
#define InstanceNameOfAO6_2
#define TypeOfAO6_3
#define InstanceNameOfAO6_3
#define TypeOfAO6_4
#define InstanceNameOfAO6_4

 
#endif

 
//enabling hardware peripherals 
#ifdef IARBuild
//#define Target_RealUART
//#define Target_RealI2C
#define Target_RealSPI
#define Target_RealADC
#define Target_RealGPIO
#define Target_RealButton
#define Target_RealPWM
#endif

//#define UARTPERIPHERAL2 UARTPeripheral<2,PortD, PIN5, PortA, PIN3>//<2,PortA, PIN2, PortA, PIN3>
//#define SPIPERIPHERAL1 SPIPeripheral<1,false,PortA,PIN5,PortA,PIN6,PortA,PIN7,PortA,PIN4> 
//#define ADCPERIPHERAL1 ADCPeripheral<1,PortB, PIN0> 
//#define ButtonPERIPHERAL1 ButtonPeripheral<1,PortD, PIN0> 
//#define PWMPERIPHERAL1 PWMPeripheral<1,PortD, PIN12> 
//#define I2CPERIPHERAL1 I2CPeripheral<1,PortB, PIN6,PortB, PIN7, 20000> 


//#define Using_SPI1Peripheral

//#define SPI1PERIPHERAL SPI1Peripheral<PortA,PIN5,PortA,PIN6,PortA,PIN7>  

//#define Using_ADC1Peripheral
//#define Target_RealADC
//#define ADC1PERIPHERAL ADC1Peripheral<PortB, PIN0> 
 
 


#ifdef Target_RealSPI1
#define Target_RealW25
#endif // Target_RealSPI1


#ifndef USING_LINUX

#ifdef HARDWARE
#ifndef Target_RealUART
#include "UARTConsole.h"
#endif
#endif


#endif











