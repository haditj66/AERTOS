![enter image description here](https://github.com/haditj66/AERTOSCopy/blob/master/doc/images/logo.PNG)
# AERTOS
<!--  
//UserCode_Sectiona
 -->
AERTOS is a framework and development environment for writing RTOS applications on embedded devices. It can be thought of as a sort of Arduino but for RTOS applications. It uses visual programming to aid you with rapid prototyping, even if you are not a very experienced programmer. Currently only supports stm32F4 boards but can be easily ported to be used on almost any dev board that supports FREERTOS.
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

- [Example](#example)

- [License](#license)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## Overview
<!--  
 //UserCode_Sectionoverview
   -->
 AERTOS came about as a need to rapidly prototype embedded applications without having to worry about the details of RTOS mechanisms such as semaphores and tasks. Instead, this is abstracted with concepts of an event-driven architecture. Finite state machines, Service calls, and signal processing blocks are a few examples of the concepts used in AERTOS. Go here for a begginer project to get started [Example blinky](https://github.com/haditj66/AERTOSCopy/blob/master/doc/example/blinky.md) .

<!-- 
//UserCode_Sectionoverview_end
-->
## Example
<!--  
 //UserCode_Sectionexample
  -->
 Below is an example of what can be possible with AERTOS. This example shows the creation of a basic on-off control system for maintaining the desired acceleration of whatever system you can imagine. For this case,  we are looking at a small autonomous robotic car. It has two sensors to get it current position. The rotational position is obtained from an encoder on the wheel. This sensor is susceptible to dead reckoning error (errors that cumulate over time). To get a better state estimate of the robot, a second sensor is used. This is the ultrasound sensor. However this sensor is not very accurate. Sensor fusion is used to combine the two readings with a complementary algorithm. Afterwards the signal is differentiated twice to get the acceleration in the x direction. Finally the On-Off utility block will up the power of the motor (via a PWM) when the acceleration is below the desired value and lower the power when it is above.
![enter image description here](https://github.com/haditj66/AERTOSCopy/blob/master/doc/images/About_img1.PNG)

Below is how you would configure this setup.  It is done in an intuitive c# api. CGEN will then generate the  C/C++ AERTOS project that you can tweak or add more functionality. When everything is to your liking, you can start and debug the application directly on your board (assuming your board has a programmer with debugging).
```csharp 
            AEClock aEClock1 = new AEClock("clock1", 1000);
            AEClock aEClock2 = new AEClock("clock2", 500);
            AESensor sensor1 = new AESensor("Ultraviolet", ADC1);
            AESensor sensor2 = new AESensor("Rotational", ADC2); 



            AverageSPB averageSPB1 = new AverageSPB("averageSPB1", StyleOfSPB.EachSPBTask, " ", false, new SPBChannelUserDefinedCountBuffer(10));
            AverageSPB averageSPB2 = new AverageSPB("averageSPB2", StyleOfSPB.EachSPBTask, " ", false, new SPBChannelUserDefinedCountBuffer(5));

            Complementary complementary = new Complementary("complementary", StyleOfSPB.EachSPBTask, " ", false);


            OnOffUtility onOffUtility = new OnOffUtility("onOffUtility", AEPriorities.MediumPriority);
 
			//linking AO by flowing 
            aEClock1
            .FlowIntoSensor(sensor1, AEClock_PrescalerEnum.PRESCALER1)
            .FlowIntoSPB(averageSPB1, SPBChannelNum.CH0, LinkTypeEnum.Copy);
            aEClock2
            .FlowIntoSensor(sensor2, AEClock_PrescalerEnum.PRESCALER1)
            .FlowIntoSPB(averageSPB2, SPBChannelNum.CH0, LinkTypeEnum.Copy);

            averageSPB1
            .FlowIntoSPB(complementary, SPBChannelNum.CH0, LinkTypeEnum.Copy);

            averageSPB2
            .FlowIntoSPB(complementary, SPBChannelNum.CH1, LinkTypeEnum.Copy); 

            complementary
            .FlowIntoFilter(new DerivativeFilter())
            .FlowIntoFilter(new DerivativeFilter())
            .FlowIntoTDU(OnOffUtility); 
```       

 <!--  
//UserCode_Sectionexample_end
-->
## License
<!--  
 //UserCode_Sectionlicense
 -->
 AERTOS is an open source GPLv3. However dual-licensing for commerial License is also available. 
 Contact this email address for enquiries: haditjuta@gmail.com
 <!--  
//UserCode_Sectionlicense_end
-->


 
