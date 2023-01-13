
# Example blinky
<!--  
//UserCode_Sectiona
 -->
In this example, you will learn how to create a simple AERTOS blinky project.
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

- [step1 init project](#step1-init-project)

- [step2 config project](#step2-config-project)

- [step3 AERTOS project code](#step3-aertos-project-code)

- [step4 Run your application](#step4-run-your-application)



<!--  
//UserCode_Sectionb
 -->

 <!--  
//UserCode_Sectionb_end
 -->
 
## Overview
<!--  
 //UserCode_Sectionoverview
  -->
You will need an STM32F411xx board.

 This blinky is a little different than the usual. Instead of just blinking an LED, it will fade the LED based on a sinusoidal signal. GPIO Port A Pin 1 being set to high will turn off the LED. An output PWM signal from Port D Pin 12  will control the LED light intensity of the onboard LED.
Make sure you have everything  [installed](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Installation.md).
 <!--  
//UserCode_Sectionoverview_end
-->
## step1 init project
<!--  
 //UserCode_Sectionstep1initproject
  -->
Open a command prompt window and set the working directory to 

    C:/AERTOSProjects/blinky
run the cgen command

    cgen aeinit blinky
    
   ![](https://github.com/haditj66/AERTOS/blob/master/doc/images/Blinky1.PNG)
 <!--  
//UserCode_Sectionstep1initproject_end
-->
## step2 config project
<!--  
 //UserCode_Sectionstep2configproject
  -->
 Go to your configuration project. This is a .Net application that you will use to help generate your AERTOS project. The code is in c# but minimal c#  experience is needed. the project is located here

    C:\AERTOSProjects\AAAConfigProj
double click on the ".sln" file. right click on the solution, and click as shown in the image below
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/Blinky2.PNG)

Now navigate to the blinky project you just initiated. Add the file shown in the image below by choosing "add as link"
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/Blinky3.PNG) 

double click on the file you just added in the solution explorer. right click on the "ConfigProjects" and build your solution. It should build. This blinky.cs file is your config file for your AERTOS. If you want more details of this configuration file, go here [Creating an AERTOS project](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Creating_an_AERTOS_project.md) . For now, take a look at the "defaultTest" function. This is where you will declare Active Objects. The diagram below shows the project.
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/Blinky4.PNG) 

Here is what is going on. The purple clock at the bottom ticks at a frequency of 1000 hz. The sine sensor it set to this clock. This means it too runs at this frequency. At every tick, it will read the sensor signal data (in this case the data comes from a static float array to simulate a sine wave ADC signal). That data will be noisy so it will need to be processed a bit. An Average signal process block is next in the chain. It will buffer 4 signals from the sine sensor, and then take the average of them. 
On the right side, a GPIO sensor will read the state of the gpio port A pin 1 every 250 hz. The left and right signals will then meet at the "If Right On" SPB. This SPB will output the left signal only when the right signal reads true. Finally this is sent to a PWM Controller Utility. This utility will handle the PWM. It will have a service function call that you can call to turn on the PWM controller.
 You want to now configure this diagram in the blinky.cs file. Replace the contents of that file with this code.
 
 
 
```csharp
    using CgenMin.MacroProcesses;
    using commonAOsProject;
    using commonHalAOsProject;
    using System.Collections.Generic;
    
    namespace blinkyProject
    {
    
        public class blinky : AEProject
        {
    		[AEEXETest]
            public void defaultTest()
            {
                AEClock clock1 = new AEClock("clock1", 1000);
    
                AESensor sineSensor = new AESensor("sineSensor", SensorResolution.Resolution16Bit,SensorDataType.int16_T);
                AESensor gpioSensor = new AESensor("sengpioSensorsor2", SensorResolution.Resolution16Bit,SensorDataType.int16_T);
    
                AverageSPB averageSPB = new AverageSPB("averageSPB", StyleOfSPB.EachSPBTask,  false, new SPBChannelUserDefinedCountBuffer(4));
                IfRightOnSPB ifRightOnSPB = new IfRightOnSPB("ifRightOnSPB", StyleOfSPB.EachSPBTask,  false);
                 
                PWMDriverU pWMDriverU = new PWMDriverU("pWMDriverU",10,AEPriorities.MediumPriority, ifRightOnSPB);
    
                //linking ----------
                clock1.
                    FlowIntoSensor(sineSensor, AEClock_PrescalerEnum.PRESCALER1)
                   .FlowIntoSPB(averageSPB,SPBChannelNum.CH0,LinkTypeEnum.Copy);
                averageSPB.FlowIntoSPB(ifRightOnSPB, SPBChannelNum.CH0, LinkTypeEnum.Copy);
    
                clock1.
                    FlowIntoSensor(gpioSensor, AEClock_PrescalerEnum.PRESCALER4)
                   .FlowIntoSPB(ifRightOnSPB, SPBChannelNum.CH1, LinkTypeEnum.Copy);
    
                
    
    
            }
    
            protected override string _GetDirectoryOfLibrary()
            {
                return @"blinky"; 
            }
    
            protected override List<AEEvent> _GetEventsInLibrary()
            {
                return new List<AEEvent>() { };
            }
    
    		protected override List<AEHal> _GetPeripheralsInLibrary()
            {
    		//ADCPERIPHERAL1_CH1.Init(Portenum.PortB, PinEnum.PIN0)
                return new List<AEHal>() {
                    PWMPERIPHERAL1.Init(Portenum.PortD, PinEnum.PIN12),
                    GPIOPERIPHERAL1.Init(Portenum.PortA, PinEnum.PIN1)
                };
            }
    
            protected override List<AEProject> _GetLibrariesIDependOn()
            {
                return new List<AEProject>() {
                new commonAOs(),
                new commonHalAOs()
                };
            }
    		
    		protected override List<string> _GetAnyAdditionalIncludeDirs()
            {
                return new List<string>() { };
            }
    		
    		protected override List<string> _GetAnyAdditionalSRCDirs()
            {
                return new List<string>() {  };
            }
    		
     
        } 
    }
```

build your config project. (control+shift+b) 
Now select and then generate this project by running in cmd

    cgen aeselect blinky defaultTest

    cgen aegenerate

 <!--  
//UserCode_Sectionstep2configproject_end
-->
## step3 AERTOS project code
<!--  
 //UserCode_Sectionstep3aertosprojectcode
  -->
Now go to your AERTOS project. File located here

    C:/AERTOS/AERTOS.sln
You need to build your project with cmake. To do this, you can right click the solution in the solution explorer and select "Reload cmake settings". Afterwards, a GUI will pop up that will help you configure cgen options. You only do this once per project. Select the "Start config Options" button, select the options you want, same to the one in the image below.
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/Blinky5.PNG) 

Verify your project builds by finding the "blinky" target in the solution explorer, right clicking on it and selecting "build target". Or you could to control+shift+b to build. If you have a succeeded build, you can now copy and paste the below code to blinky -> TestFiles ->defaultTest.cpp  . You can only write in //UserCode_Section blocks as everything outside these blocks will get overwritten when you run aegenerate. 
On around line 32 for //UserCode_Sectiona block paste this code

```csharp
    #include "AERand.h"
    const int sinDataSize = 1000;
    static float NoisySineData[sinDataSize];
    static int indexSine = 0;
    static bool  firstTick = false;  
```
On around line 46 for //UserCode_Sectionbeforemainblock paste this code

```csharp
    const float Pi = 3.14159;
    for (int i = 0; i < sinDataSize; i++)
    { 
    	float noise = AE_rand::getRandomGaussianDistribution(0,.01);
    	NoisySineData[i] = (sin((i*  Pi / (sinDataSize ))) + noise);
    	NoisySineData[i] = NoisySineData[i] * 100; //scale it for a pwm value 
    }
```
On around line 108 for //UserCode_Sectionb paste this code

```csharp
    pWMDriverU->UserInitialize(PWMPERIPHERAL_inst1);
```
On around line 121 for //UserCode_Sectionclock1before paste this code

```csharp
    indexSine = indexSine == 1000 ? 0 : indexSine+1;
    sineSensor_data[0] = NoisySineData[indexSine];
    sengpioSensorsor2_data[0] = (int16_t)!GPIOPERIPHERAL_inst1->GPIO_ReadPin();
    
    	if (firstTick == false)
    	{
    		pWMDriverU->StartPWMFromSPBLinked(0,true);
    		firstTick = true;
    	}
```
 <!--  
//UserCode_Sectionstep3aertosprojectcode_end
-->
## step4 Run your application
<!--  
 //UserCode_Sectionstep4runyourapplication
 -->
Now just run your project by clicking the "Start" button at the top, or by pressing F5. if a breakpoint is hit at start, just hit continue. You should see your LED, or whatever is on the receiving  end of the PWM, fade with a sinusoidal pattern. You will see the onboard LED fade as well.
 <!--  
//UserCode_Sectionstep4runyourapplication_end
-->


 
