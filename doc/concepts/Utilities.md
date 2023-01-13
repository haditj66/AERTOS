
# Utilities
<!--  
//UserCode_Sectiona
-->
Utility Active objects are a way to manage a shared resource for other AOs to access. 
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
- [What are Utilities](#what-are-utilities)

- [Service types](#service-types)

- [Set to clock or spb](#set-to-clock-or-spb)

- [Waiting for event](#waiting-for-event)

- [Create your own utility](#create-your-own-utility)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## What are Utilities
<!--  
 //UserCode_Sectionwhatareutilities
  -->
Utilities protect shared resources and by wrapping the actions done on said resource by a service call. For example, a UARTDriver Utility might be an AO that wraps a UART peripheral on the board. Use utilities whenever you want to manage a shared resource between different AOs. AOs may request these services by invoking these services. The utility will then queue all  requests. It will then execute these requests based on the priorities of the requests in queue. Higher priority requests get executed first. Check the image below for a visual representation of this.
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/utility1.PNG) 

When an AO requests a service, The utilities priority is changed to inherit the callers priority. This is done to avoid priority inversion.
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/utility2.PNG)
 
<!--  
//UserCode_Sectionwhatareutilities_end
-->
## Service types
<!--  
 //UserCode_Sectionservicetypes
-->
There are two types of services. 

 - Time dependent utility (TDU): This is a service that updates at a set frequency. It is time dependent because it will take time, have to  update, or wait for an event to finish. TDUs have extra capabilities. Like
	-	Can await events: They can wait for events with timeouts.
	-	Can be canceled via a utilityName->cancelAllRequests() or utilityName->cancelRequest().
	-	Are able to be run indefinitely as long as the end goal of that service is never reached or until it is cancelled
 - Normal: This is a normal service that will basically be like a function call. It is a one shot execution of a function.



<!--  
//UserCode_Sectionservicetypes_end
-->
## Set to clock or spb
<!--  
 //UserCode_Sectionsettoclockorspb
 -->
As mentioned, TDUs update at a set frequency until the end goal is reached. That means they need to be set to a frequency source. You can set them to a SPB or a clock. You do this in the configuration file. 
to set a Utility to a clock, do this 
```csharp
clock1.FlowIntoTDU(myutility1, AEClock_PrescalerEnum.PRESCALER1);
```
To set it to a spb, do this
```csharp
spb1.FlowIntoTDU(myutility1, 3);
```
Why the 3 in this case? Because the 3 means I want it to use the output from that SPBs third filter. When you set a utility to a spb, you can grab the value of the spb from the variable
```csharp 
this->LinkedSPBData[0]
```

<!--  
//UserCode_Sectionsettoclockorspb_end
-->
## Waiting for event
<!--  
 //UserCode_Sectionwaitingforevent
 -->
you can wait for events during your updates. Do this like this 
```csharp
bool eventreceived = request->WaitForEvent(this->evtToWaitFor, [](void* p, AEEventDiscriminator_t* evt)->void
	   { //your callback of when the event is triggered.
	   },1000);
```
The timeout of 1000 means that it will move on after 1 second of waiting and eventreceived  will be false. You can also wait with multiple timeout callbacks before it fails. This means that it will trigger that callback X amount of times before it fails to wait. Do this like this
```csharp
void CallBackForEvtWaitTimeout(ActionRequestObjectArgTDU1<bool , bool, 10, UploadDataToPcU>* request)
{ 
	//callback when timeout.
}

//then in your update function somewhere
request->WaitForEventWithTimeOutAttempts(this->evtToWaitFor,
[](void* p, AEEventDiscriminator_t* evt)->void
{
    //your callback of when the event is triggered.
},
1000, 5, CallBackForEvtWaitTimeout);
```
the 5 is how many timeout fails it take before it moves on as a fail. Each time there is a timeout, the CallBackForEvtWaitTimeout callback is called.
<!--  
//UserCode_Sectionwaitingforevent_end
-->
## Create your own utility
<!--  
 //UserCode_Sectioncreateyourownutility
-->

In the config file, do this 
```csharp 
    class UARTDriverU : AEUtilityService
    {
        public UARTDriverTDU(string instanceNameOfTDU, AEPriorities priority)
            : base("AECoreTests", instanceNameOfTDU, priority, 10,
                  null,
                  new ActionRequest("Transmit", ServiceType.Normal, "bool", "char const*", "msg"),
                  new ActionRequest("TransmitTDU", ServiceType.TDU, "bool", "char const*", "msg")
                  )
        {
        }
    }
```
So you will notice in the example above that there are two services: transmit and TransmitTDU. After you aegenerate this code, you to the file in AERTOS project. You will see that for the normal service, a ```_Trasmit()``` function is generated. This is what will be called when the service executes.
For the TDU generated however, there will be three functions generated. 
```_TrasmitTDU()``` : this is called once at the beginning of a new service request execution.
```_TrasmitTDUUpdate()``` : this is called at every tick of the utility's frequency source.
```_TrasmitTDUCancelCleanup()``` : this is when a cancellation is requested of the service call.


<!--  
//UserCode_Sectioncreateyourownutility_end
-->


 
