
# Filters
<!--  
//UserCode_Sectiona
-->
Filters are simple blocks that will take a single sample data streaming in, run an algorithm on it with a past history of data, and output a single sample float data. 
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
- [What are filters ](#what-are-filters-)

- [how to set them](#how-to-set-them)

- [create your own filter](#create-your-own-filter)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## What are filters 
<!--  
 //UserCode_Sectionwhatarefilters
 -->
Graphically filters are represented as an orange block. Filters are used when you want to process data as it comes streaming in. This is the block to use when you want to implement something like a moving average. Moving averages need the most recent data point with a history of the previous data. SPBs in contrast do not hold a history of past data. Also filters run within the same task as the observer they originate from so are a good choice when you are outputting data of size one and don't need to set it to an spb of multiple input channels or an input channel with a count buffer.
<!--  
//UserCode_Sectionwhatarefilters_end
-->
## how to set them
<!--  
 //UserCode_Sectionhowtosetthem
  -->
In the config file, you dont create an instance of them but instead flow to a filter.
```cpp 
            clockFormpudata.FlowIntoSensor(sensorForAccelx, AEClock_PrescalerEnum.PRESCALER1)
                .FlowIntoFilter(new GainFilter(-accelUnitConversion)); 
```
If your filter flows to multiple Observers, you need to grab the instance of it like this
```cpp 
        var filter1 = clockFormpudata.FlowIntoSensor(sensorForAccelx, AEClock_PrescalerEnum.PRESCALER1)
                .FlowIntoFilter(new GainFilter(-accelUnitConversion)); 
       filter1.FlowIntoSPB(spb1,SPBChannelNum.CH0, LinkTypeEnum.Copy);
       filter1.FlowIntoSPB(spb2,SPBChannelNum.CH0, LinkTypeEnum.Copy);
```


<!--  
//UserCode_Sectionhowtosetthem_end
-->
## create your own filter
<!--  
 //UserCode_Sectioncreateyourownfilter
  -->
In the config file do this for example
```cpp
    public class GainFilter : AEFilter_ConstructorArg<float>
    {
        public GainFilter(float arg1Value)
            : base("gain", arg1Value, "commonAOs", 1)
        {
        }
    }
```
So notice how I inherited from  ```AEFilter_ConstructorArg<float>``` This is because in that gain filter I wanted to pass in an argument called gain field at constructor of the object which is a single float field. I can also pass in an int and float arg like this ```AEFilter_ConstructorArg<uint32_t, float>``` 

Now after you aegenerate this, go to your AERTOS project, reload cmake and go to the filter file it generated. You can fill in the implementation of your filter. Remember to stay within the usercode sections. In my example of the gain filter, It is a very simple implementation in the RunFilter function
```cpp
inline float GainFilter< _gain >::RunFilter(float newestInput)
{   
	return G_gain * newestInput;  
}
```
<!--  
//UserCode_Sectioncreateyourownfilter_end
-->


 
