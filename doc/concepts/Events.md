
# Events
<!--  
//UserCode_Sectiona
-->
Just as most event-driven architectures, AERTOS has events that you can publish and subscribe to. 
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
- [What are events](#what-are-events)

- [signal_event vs event](#signal_event-vs-event)

- [Publishing an event](#publishing-an-event)

- [Subcribing to an event](#subcribing-to-an-event)

- [Create your own event](#create-your-own-event)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## What are events
<!--  
 //UserCode_Sectionwhatareevents
-->
Only, decision-based AOs can subscribe however. These are [LoopObject](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/LoopObject.md) and [Finite State Machine](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/FSM.md). TDU [Utilities](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/Utilities.md) can wait on an event to trigger however.
<!--  
//UserCode_Sectionwhatareevents_end
-->
## signal_event vs event
<!--  
 //UserCode_Sectionsignal_eventvsevent
 -->
Signals are events that have no data attached to it.  Non-signals are events that can have any data passed to subcribers. You can create your own custom non-signal event's data. 
<!--  
//UserCode_Sectionsignal_eventvsevent_end
-->
## Publishing an event
<!--  
 //UserCode_Sectionpublishinganevent
 -->
The API for publishing Events, signals are different. Also it is different depending on if you are publishing from an Interrupt or not. 
#### For events Not from Interrupt
---
example
```csharp
ButtonChanged* evt = PoolManager->GetEvtFromPool<ButtonChanged>();
evt->ForButton = 0;
evt->isButtonWentDown = DOWN;
this->PublishEvt(evt);
```
So you publish it from the AO instance. (this->). You need to grab an instance of an event from the pool.
		
#### For signals Not from Interrupt
---
```csharp
this->PublishEvt(&Button3_Sig_Instance);	
```

#### For events from Interrupt
---
```csharp
ButtonChanged* evt = PoolManager->GetEvtFromPoolFromISR<ButtonChanged>();
evt->ForButton = 0;
evt->isButtonWentDown = DOWN;
PublishSubscribeManager->PublishEvtFromISR(evt);
``` 
#### For signals from Interrupt
---
```csharp
PublishSubscribeManager->PublishEvtFromISR(&I2CRXCmplt1_Instance);
```
<!--   
//UserCode_Sectionpublishinganevent_end
-->
## Subcribing to an event
<!--  
 //UserCode_Sectionsubcribingtoanevent
 -->
[LoopObject](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/LoopObject.md) and [Finite State Machine](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/FSM.md) are the only object that can subscribe to events. Refer to "create your own" page contents there for how to subscribe to an event.
<!--  
//UserCode_Sectionsubcribingtoanevent_end
-->
## Create your own event
<!--  
 //UserCode_Sectioncreateyourownevent
 -->
### example of creating an event
---
notice how for the example below, I add data ForButton and isButtonWentDown. these fields will be passed with whatever ButtonChanged event you publish.
```csharp
public class ButtonChanged : AEEventEVT<ButtonChanged>
{
    public ButtonChanged() :
        base("ButtonChanged",
        "uint8_t ForButton;", "bool isButtonWentDown;"
        )
    { }
}
```


### example of creating a signal 
---
```csharp
  public class NameOfYourSignal: AEEventSignal<NameOfYourSignal>
    {
        public NameOfYourSignal() :
            base("NameOfYourSignal",
            ""
            )
        { }
    }
``` 
 <!--  
//UserCode_Sectioncreateyourownevent_end
-->


 
