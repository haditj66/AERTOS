
# AEHal
<!--  
//UserCode_Sectiona
-->
This is AERTOS's Hardware abstraction layer (HAL) . 
<!--  
//UserCode_Sectiona_end
-->

## Table of Contents
- [AERTOS](https://github.com/haditj66/AERTOSCopy)
- [Installation](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Installation.md)
- [Creating an AERTOS project](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Creating_an_AERTOS_project.md)
- [AERTOS concepts](https://github.com/haditj66/AERTOSCopy/blob/master/doc/AERTOS_concepts.md)
    - [Active Objects (AO)](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/AOs.md)
    - [Events](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/Events.md)
    - [LoopObject](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/LoopObject.md)
    - [AEClock](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/AEClock.md)
    - [Observers](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/Observers.md)
        - [Sensors](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/observers/Sensors.md)
        - [Filters](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/observers/Filters.md)
        - [SPB](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/observers/SPB.md)
    - [Utilities](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/Utilities.md)
    - [Finite State Machine](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/FSM.md)
    - [Target PC or embedded device](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/Target_PC_Or_Embed.md)
    - [AEHal](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/AEHal.md)
    - [Integration Testing Debugging](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/IntegrationTesting.md)
    - [Unit Testing](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/UnitTesting.md)
- [Example Projects](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Examples.md)
    - [Example blinky](https://github.com/haditj66/AERTOSCopy/blob/master/doc/example/blinky.md)
    - [Advanced Example Motor speed controller](https://github.com/haditj66/AERTOSCopy/blob/master/doc/example/motor_speed_controller.md)
- [AERTOS Tools](https://github.com/haditj66/AERTOSCopy/blob/master/doc/AERTOS_TOOLS.md)
    - [Upload Data To PC](https://github.com/haditj66/AERTOSCopy/blob/master/doc/tools/UploadDataToPC.md)
 

### Page Contents
- [Overview](#overview)

- [How it works and File structure](#how-it-works-and-file-structure)

- [Using a Hal peripheral in an AO](#using-a-hal-peripheral-in-an-ao)

- [function demos](#function-demos)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## Overview
<!--  
 //UserCode_Sectionoverview
  -->

AEHal abstracts the peripherals on a board. This is needed when you want cross compilation capabilities of the same code base. Now you can have an AO like a utility, take a pwm peripheral and handle that peripheral. This is done in the [blinky](https://github.com/haditj66/AERTOSCopy/blob/master/doc/example/blinky.md) example. In that example a pwmDriver utility is used by take an AEHal pwm peripheral. You can easily switch targets from a stm32 board to a x86 target.
In order to use a Hal peripheral  you need to declare it in your project first. Go to [Creating an AERTOS project](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Creating_an_AERTOS_project.md) and click on peripheral declarations section to see how to do that. 
  AEHal is not necessary for AERTOS. You can turn it off when you select your cmake options with the cgen GUI. the commonHalAOs library has AOs that do rely on AEHal. AEHal is meant to be a simple lite HAL without a lot of features. You can use a different 3rd party HAL if you choose to. 
 


<!-- 
//UserCode_Sectionoverview_end
-->
## How it works and File structure
<!--  
 //UserCode_Sectionhowitworksandfilestructure
 -->
  AEHal works by having a target create derived implementations of base Hal Peripheral classes. If no derivation of a peripheral class is provided for said target, that peripheral is omitted in the Hal for the target. The location of AEHal is here
  ```C:\AERTOS\AERTOS\src\AE\hal``` the files you see here are the base abstract classes.
  Go to the boards directory ```C:\AERTOS\AERTOS\src\AE\hal\boards``` and you will see a list of available targets for the Hal. choose ```C:\AERTOS\AERTOS\src\AE\hal\boards\STM32F411RE``` as an example. you need to provide three directories per target. 
  

 - ```C:\AERTOS\AERTOS\src\AE\hal\boards\STM32F411RE\board_files``` These are just board specific files you'll need for your board. Each board will of course have their own files.
 - ```C:\AERTOS\AERTOS\src\AE\hal\boards\STM32F411RE\AECoreHalRequiredFiles``` These are required files every target must provide.
	 - ```UserDefinedInstances.cpp``` This is a file that declares pin and port definitions as well as DMA initializations .
	 - ```BoardTypes_1.h``` For stm's Hal, every peripheral has a C style handle data structure. This file maps the boards vendor peripheral handle  to AEHals peripheral handle.
	 - ```AETimerSimple.cpp``` Your implementation for AEtimer. This is needed for things like integration testing api.
	 - ```AEPerformanceTimer.cpp``` same as AETimerSimple, you need to implement this for  integration testing api.
	
The ```C:\AERTOS\AERTOS\src\AE\hal\boards\STM32F411RE\AEHalFiles``` directory is where you can provide Hal implementations for peripherals. For example, to implement an SPI hal, you would include a AESPI.h and AESPI.cpp file.
<!--  
//UserCode_Sectionhowitworksandfilestructure_end
-->
## Using a Hal peripheral in an AO
<!--  
 //UserCode_Sectionusingahalperipheralinanao
 -->
 To use a peripheral in an AO, you could simple do this for example with a pwm
 ```cpp
PWMPERIPHERAL_inst1->StartPWM(); 
PWMPERIPHERAL_inst1->ChangeDutyCycle(80); 
```
However notice how I am calling ```PWMPERIPHERAL_inst1``` as in the pwm 1. If I want to use this AO again in another project, i'll be forced to use peripheral 1. For this reason, you want to pass in peripherals as their base abstracted class to the AO. And then initialize it in the this->UserInit() function in AERTOS. For example in configuration file 
 ```cpp
    public class PWMDriverU : AEUtilityService
    {
        public PWMDriverU(string instanceNameOfTDU, int serviceBuffersize, AEPriorities priority, AESPBBase spbIFlowFrom = null)
            : base("commonHalAOs", instanceNameOfTDU, priority, serviceBuffersize,
                  new CppFunctionArgs(
                        new CppFunctionArg("AEPWM*", "pwmThisUses", false)
                        ),
                  new ActionRequest("StartPWMFromSPBLinked", ServiceType.TDU, "AENull", "AENull", "placeholder")
                  )
        {
            if (spbIFlowFrom != null)
            {
                spbIFlowFrom.FlowIntoTDU(this);
            }
            
        }
 

    }
``` 

notice the ```new CppFunctionArg("AEPWM*", "pwmThisUses", false)```
and then you can pass in the instance like so in AERTOS main.cpp
 ```cpp
pWMDriverU->UserInitialize(PWMPERIPHERAL_inst1);
```

<!--  
//UserCode_Sectionusingahalperipheralinanao_end
-->
## function demos
<!--  
 //UserCode_Sectionfunctiondemos
 -->
Here are some function demos of AEHal peripherals

### PWM
```cpp
PWMPERIPHERAL_inst1->StartPWM(); 
PWMPERIPHERAL_inst1->ChangeDutyCycle(80); 
```

### ADC
setting an interrupt callback
```cpp 
	ADCPERIPHERAL_inst1_ch1->SetADC_ConvCpltCallback_t([]()->void {
		adcCountToPrint1++;
		if (adcCountToPrint1 > 1000)
		{
			uint16_t adcValue = ADCPERIPHERAL_inst1_ch1->GetADCData();
			//! [integ test assert]
			AEITEST_AEHalTests("ADC1 test", (adcValue > 1800 && adcValue < 2500), "test adc1 is getting adc value");
			//! [integ test assert]
			AEPrint("adc1 data is %d \n", adcValue);
			adcCountToPrint1 = 0;
		}
	});
```

### SPI
```cpp

```

### I2C
setting an interrupt callback
```cpp
I2CPERIPHERAL_inst1->SetI2C_MasterTxCpltCallback([](AEI2C* i)->void {
	txcmplt = true;
});
```

writing/reading  bytes
```cpp
I2Cbuffer2[0] = 0; 
I2CPERIPHERAL_inst1->WriteBytes(0x68, 0x6B, 1, I2Cbuffer2);

I2CPERIPHERAL_inst1->ReadBytes(0x68, 1, nullptr);
```

### UART
setting an interrupt callback
```cpp 
	UARTPERIPHERAL_inst2->SetRxCpltCallback([](char* msgReceived, uint32_t sizeOfReceivedMsg)->void {
		AEPrint("message received for uart: %s \n", msgReceived);
		//uart1->TansmitMsg("message received from uart: %s \n", 20);
		//GpioLed1->GPIO_TogglePin();
		
	});
```
```cpp 
UARTPERIPHERAL_inst2->TansmitMsg("hello", 5);
```

<!--  
//UserCode_Sectionfunctiondemos_end
-->


 
