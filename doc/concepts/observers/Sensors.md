
# Sensors
<!--  
//UserCode_Sectiona
-->
Sensors are your entry point for data that will either come from an ADC, in memory data, or anything else you can read from.
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
- [Example Projects](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Examples.md)
    - [Example blinky](https://github.com/haditj66/AERTOSCopy/blob/master/doc/example/blinky.md)
    - [Advanced Example Motor speed controller](https://github.com/haditj66/AERTOSCopy/blob/master/doc/example/motor_speed_controller.md)
- [AERTOS Tools](https://github.com/haditj66/AERTOSCopy/blob/master/doc/AERTOS_TOOLS.md)
    - [Upload Data To PC](https://github.com/haditj66/AERTOSCopy/blob/master/doc/tools/UploadDataToPC.md)
 

### Page Contents
- [What are sensors](#what-are-sensors)

- [how to set them](#how-to-set-them)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## What are sensors
<!--  
 //UserCode_Sectionwhataresensors
 -->
 Sensors are represented graphically as a red block. They have an output of a float array of size one. They must be powered from a AEClock.
 <!--  
//UserCode_Sectionwhataresensors_end
-->
## how to set them
<!--  
 //UserCode_Sectionhowtosetthem
 -->
you can set a clock from an ADC or any other source. 
#### From an ADC
---
In the config project, do this
```cpp
AESensor opticalsensor1 = 
new AESensor("opticalsensor1",  ADCPERIPHERAL1_CH1.Instance, 0, 100);
```
the "ADCPERIPHERAL1_CH1.Instance" in that example is an instance of the ADC you want to use. The 0, 100) means that the output of the data will be mapped from 0 to 100.

#### From another source
```cpp
 sensorForAccelx = 
 new AESensor("sensorForAccelx", SensorResolution.Resolution16Bit, SensorDataType.int16_T);
```
You can set the sensor to have any integer datatype you want. In this case it is a int16_T with a 16 bit resolution set.
<!--  
//UserCode_Sectionhowtosetthem_end
-->


 
