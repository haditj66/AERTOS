
# SPB
<!--  
//UserCode_Sectiona
-->
Signal processing blocks (SPB) are blocks that take signals, potentially buffer that signal,  process, and output it. are similar to filter blocks except in two ways. 
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
- [What are SPBs ](#what-are-spbs-)

- [Sampling frequency reduces](#sampling-frequency-reduces)

- [Pass by reference or copy](#pass-by-reference-or-copy)

- [Channel connect limitations](#channel-connect-limitations)

- [style of spb efficiencies](#style-of-spb-efficiencies)

- [subscribe to the output of spb](#subscribe-to-the-output-of-spb)

- [create your own spb](#create-your-own-spb)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## What are SPBs 
<!--  
 //UserCode_Sectionwhatarespbs
 -->
These are represented by green blocks. Signal processing blocks (SPB) are similar to filters except for these differences

 - You can buffer the signal before processing. This is called the count buffer. You are able to specify what that count buffer will be. For example, in the [example blinky](https://github.com/haditj66/AERTOSCopy/blob/master/doc/example/blinky.md) the averageSPB is buffered by 4. This means a signal needs to pass in four times before the average of those 4 signals are averaged. Then the average is outputted. 
 - An SPB can have multiple inputs channels. This means that every channel needs to have a signal flowed to it to satisfy the SPB algorithm.  
 - You can choose how the SPB implements the processing. Either in it's own FREERTOS task or a task being shared throughout the chain. 
 - Input channels can also take signals larger than a size of just one float array of size one.

<!--  
//UserCode_Sectionwhatarespbs_end
-->
## Sampling frequency reduces
<!--  
 //UserCode_Sectionsamplingfrequencyreduces
 -->
 Because SPBs can buffer the signal before processing, it also has the effect of reducing the output sampling frequency of that signal. Going back to the [blinky](https://github.com/haditj66/AERTOSCopy/blob/master/doc/example/blinky.md) example, you can see that after the averageSPB block, it reduces the frequency by dividing it by the count buffer. in the example it took the 1000 hz signal down to 1000/4 = 250 hz.
<!--  
//UserCode_Sectionsamplingfrequencyreduces_end
-->
## Pass by reference or copy
<!--  
 //UserCode_Sectionpassbyreferenceorcopy
 -->
You have the option to pass by reference or by copy when making an SPB channel. Choosing a pass-by-copy means that the count buffer will be it's own separate array of memory that the signal that flows into it will be copied into. 
pass-by-reference means that the data from the inputting signal will not be copied to the count buffer. Instead the SPB will use the data of the inputting signal directly from its referenced address. Generally you would choose this if, for one the count buffer needs to be one, and two you feel that the inputting signal will not change or be written to within the SPB processing it. Remember that the same  signal can go to other SPBs. If any of those SPBs change the signal, you will get corrupt data. This is a good choice however if the inputting data has a very large size, and you want to save memory by not having to copy it to a count buffer.


You can check rules for when you can pass by reference here
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/spb1_ref1.PNG) 
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/spb1_ref2.PNG) 

 <!--  
//UserCode_Sectionpassbyreferenceorcopy_end
-->
## Channel connect limitations
<!--  
 //UserCode_Sectionchannelconnectlimitations
 -->
 You have to satisfy a few rules of SPBs in order to satisfy their algorithm. 
 

 - An Input channel may not have both the count buffer and the input data size more than one. At least one of these values needs to be one. 
 - All input channels need to have a signal flow linked.
 
 There is a concept of SPB type that needs to be discussed to understand their limitations. SPBs can be of type 1, 2, or 3. Depending on their type, they will have different limitations to them. The logic diagram below helps identify the SPB type and the limitations of it. 
 ![](https://github.com/haditj66/AERTOS/blob/master/doc/images/spb1.PNG) 

<!-- 
//UserCode_Sectionchannelconnectlimitations_end
-->
## style of spb efficiencies
<!--  
 //UserCode_Sectionstyleofspbefficiencies
 -->

There are different styles a SPB can execute. A style of execution either 

 - (ChainOfSPBsFromInterrupt): Entire chain executes within the same chain.
 - (EachSPBTask): Each SPB runs within it's own task. 
It can be difficult to identify which style to choose. By default, if you do not know, just choose EachSPBTask. If you want to better the performance of your execution, you can look at the image below that  shows a guide into when you are able to choose ChainOfSPBsFromInterrupt. IMPORTANT NOTE: remember that when one spb has been chosen as ChainOfSPBsFromInterrupt, the entire chain must be the same style.
 ![Guide into when you are able to choose ChainOfSPBsFromInterrupt](https://github.com/haditj66/AERTOS/blob/master/doc/images/spb2.PNG) 




 <!--  
//UserCode_Sectionstyleofspbefficiencies_end
-->
## subscribe to the output of spb
<!--  
 //UserCode_Sectionsubscribetotheoutputofspb
 -->
 If you have an AO that need the data of the output to an SPB but does not need to have the data signal flow to it, you can subscribe to the output.
example in the config file.
```cpp
SomeAO.SubscribeToSPB(someSPBToSubscribeTo, "CurrentPosition", 0);
```
The zero there indicates the filter number it wants to subscribe to. in this case no filter is chosen. The CurrentPosition is a float class member of the subcribing AO. This field will automatically be written to from the subscribed SPB.

 <!--  
//UserCode_Sectionsubscribetotheoutputofspb_end
-->
## create your own spb
<!--  
 //UserCode_Sectioncreateyourownspb
 -->
 SPBs can be configured in many different ways. Some SPBs have multiple  input channels that are "locked" into the design. Some have multiple input channels that are meant to be chosen by the user. This is further complicated by being able to have either "locked in" or "user defined" count buffers or input data size. Here are some examples of how to do some of these variants. These are for the config file.

#### single channel /locked in :::  count buffer/user defined ::: size of input channel data/locked in ::: output size/locked in 
```csharp
    public class AverageSPB : AESPBBase
    {
        public AverageSPB(string nameOfSPB, StyleOfSPB styleOfSPB, string templateType, bool isSubscribable, SPBChannelUserDefinedCountBuffer ch1)
            : base("AECoreTests", nameOfSPB, styleOfSPB, "", templateType, isSubscribable,  new SizeOfSPBOutput(1, false), ch1)
        {

        }
    }
```
#### multiple channel/user defined :::  count buffer/user defined ::: size of input channel data/locked in ::: output size/locked in 
```csharp
    public class AdderSPB : AESPBBase
    {
        public AdderSPB(string nameOfSPB, StyleOfSPB styleOfSPB, bool isSubscribable, int numOfChannels, SPBChannelUserDefinedCountBuffer channelAllSame)
            : base("AECoreTests", nameOfSPB, styleOfSPB, "", "", isSubscribable,  new SizeOfSPBOutput(1, false), numOfChannels, channelAllSame)
        {   } 
    }
```


#### single channel/locked in :::  count buffer/locked in ::: size of input channel data/user defined ::: output size/locked in    Also has cpp constructor arguments.
```csharp
    public class PID_SPB : AESPBBase
    {
        public PID_SPB(string nameOfSPB, StyleOfSPB styleOfSPB,   bool isSubscribable, SPBChannelUserDefinedChannelConsumptionSize ch1)
            : base("commonAOs", nameOfSPB, styleOfSPB, "", "", isSubscribable, new SizeOfSPBOutput(1, false), ch1)
        { 
        }

        //uint8_t kpfrom0to100, uint8_t  kifrom0to100, uint8_t kdfrom0to100, 
        //float maxPossibleError, float maxpossibleRateOfChangeOfControlVariable, float desiredInput,
        //        float mapOutputTOMin = -100000, float mapOutputTOMax = 100000, float offsetFromZero = 0)
        protected override CppFunctionArgs SetcppConstructorArgs() 
        {
            CppFunctionArgs ret = new CppFunctionArgs(
                new CppFunctionArg(CppTypeEnum.uint8_t, "kpfrom0to100", false),
                new CppFunctionArg(CppTypeEnum.uint8_t, "kifrom0to100", false),
                new CppFunctionArg(CppTypeEnum.uint8_t, "kdfrom0to100", false),
                new CppFunctionArg(CppTypeEnum.float_t, "maxPossibleError", false),
                new CppFunctionArg(CppTypeEnum.float_t, "maxpossibleRateOfChangeOfControlVariable", false),
                new CppFunctionArg(CppTypeEnum.float_t, "desiredInput", false),
                new CppFunctionArg(CppTypeEnum.float_t, "mapOutputTOMin", false, "-100000"),
                new CppFunctionArg(CppTypeEnum.float_t, "mapOutputTOMax", false, "100000"),
                new CppFunctionArg(CppTypeEnum.float_t, "offsetFromZero", false, "0")
                );
            return ret;
        }
    }
```

You can create your own variants of course.
### The AERTOS generated cpp file

 After you aegenerate your project, you can go to the spb file generated and fill in the user sections code. The update() function is what will be called every tick. The ```OutputSignal``` variable is what you set. This is what will be outputted. 

<!--
//UserCode_Sectioncreateyourownspb_end
-->


 
