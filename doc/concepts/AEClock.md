
# AEClock
<!--  
//UserCode_Sectiona
-->
Clocks are what power your AOs to tick at a designated frequency.

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
- [What are AEClocks](#what-are-aeclocks)

- [how to set them](#how-to-set-them)

- [how to flow to other AOs](#how-to-flow-to-other-aos)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## What are AEClocks
<!--  
 //UserCode_Sectionwhatareaeclocks
 -->
clocks are represented graphically with a purple clock icon. The tick at some designated frequency. They can tick from one of two sources

 - From a FREERTOS timer
 - From an interrupt or loopobject.

If it ticks from a FREERTOS timer, you are limited to less than 1000 hz. If it ticks from an interrupt, you have no limit on the frequency however whatever implementation is in those ticks, needs to finish quickly. 

<!--  
//UserCode_Sectionwhatareaeclocks_end
-->
## how to set them
<!--  
 //UserCode_Sectionhowtosetthem
  -->
 As stated, It can tick from two different sources. 
### From a FREERTOS timer
 ---
 in the config file, do this.
 ```csharp
 AEClock aEClock = new AEClock("clock1",100 );
```
The 100 means it will tick at 100 hz

### From an interrupt or loop object

in the config file, do this.
```csharp
AEClockTicksNotFromRtosTimer clock1 = new AEClockTicksNotFromRtosTimer("clock1", 10000);
```
You need to specify the frequency of the source it will tick at. For example if you know the interrupt triggers at 10000 hz. you set it as 10000.  Now in AERTOS, you need to tick the timer manually.  You need to call  TickWithoutTimer in whatever function body it is ticking from.
```csharp
 clock1->TickWithoutTimer();
```
This is needed when you want to run a spb chain from an interrupt. More on that in [SPB](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/observers/SPB.md).

<!--  
//UserCode_Sectionhowtosetthem_end
-->
## how to flow to other AOs
<!--  
 //UserCode_Sectionhowtoflowtootheraos
 -->
 Clocks can flow to either a sensor or a Utility AO to power them. in the config file you can either call
 ```csharp
 clock1.FlowIntoSensor(sensor1, AEClock_PrescalerEnum.PRESCALER1)
 ```
 or you can call
 ```csharp
  clock1.FlowIntoTDU(utility1, AEClock_PrescalerEnum.PRESCALER1)
 ```
 the prescaler divides the frequency. 
 <!--
//UserCode_Sectionhowtoflowtootheraos_end
-->


 
