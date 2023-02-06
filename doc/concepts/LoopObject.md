
# LoopObject
<!--  
//UserCode_Sectiona
-->
Loop objects are the most fundamental AO that  has one looping task that updates at a frequency you specify. 
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
- [What are LoopObjects](#what-are-loopobjects)

- [how to subscribe to events](#how-to-subscribe-to-events)

- [Create your own LoopObject](#create-your-own-loopobject)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## What are LoopObjects
<!--  
 //UserCode_Sectionwhatareloopobjects
 -->
Think of Loop objects as a decision maker in your application. It is the object that utilizes utilities, sequences actions, and subscribes subscribe to events. You can then specify callbacks for the events it subscribes too. 
<!--  
//UserCode_Sectionwhatareloopobjects_end
-->
## how to subscribe to events
<!--  
 //UserCode_Sectionhowtosubscribetoevents
  -->
You do that in the created Loopobject header file. In the StartAOLoopObject function.  you need to use the following "AELoopSubscribe" macro. 
```csharp
    void StartAOLoopObject()  override
	{ 
		AELoopSubscribe(Button1, AELoopObject1Test, Button1_Callback); 
	}
	
	void Button1_Callback(AEEventDiscriminator_t* evt )
	{
		
	}
```
in that scenario, Button1 is the event name, AELoopObject1Test is the name of the LoopObject, and Button1_Callback is the callback function you want to trigger when that event is called.
<!--  
//UserCode_Sectionhowtosubscribetoevents_end
-->
## Create your own LoopObject
<!--  
 //UserCode_Sectioncreateyourownloopobject
 -->
example 
```csharp
    public class MyLoopObject: AELoopObject
    {
        public MyLoopObject(string instanceName, AEPriorities priority, int freqOfLoop)
            : base("AECoreTests", instanceName, priority, freqOfLoop,
                  new CppFunctionArgs (
                      new CppFunctionArg("SomeClassType", "someClassType",false))
                  )
        {  }
    }
```
The CppFunctionArgs  is a way to be able to pass in contructor arguments that will later be called with the Userintialize() function. 
 <!--  
//UserCode_Sectioncreateyourownloopobject_end
-->


 
