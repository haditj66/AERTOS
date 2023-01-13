
# Finite State Machine
<!--  
//UserCode_Sectiona
-->
Finite state machines are a common pattern used in many software architectures.
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
- [What are FSMs](#what-are-fsms)

- [SubStateMachine feature](#substatemachine-feature)

- [Create your own FSM](#create-your-own-fsm)

- [View FSM graph generated](#view-fsm-graph-generated)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## What are FSMs
<!--  
 //UserCode_Sectionwhatarefsms
 -->
 I wont go too in-depth here as to how they work because there is plenty of literature about the already.  I will explain the way AERTOS FSMs might differ from most other FSMs.

 - AERTOS FSMs have states with an enter and exit callback. These callbacks are called when a state is entered and exited respectively.
 - Each state can opt into having an update function that will be called at a set frequency, similar to an loopObject.
 - Each state can subscribe to multiple events with a callback to each event subscribed to. Each event subscribed to (update, enter and exits are also considered special internal events) will have a transition. This transition will take the state in the FSM to another state. 
	 - Internal transition: This is a non-transition that does not change to another state.
	 - state transition: transition to another state within the state machine.
	 - submachine exit: exit out of a submachine.

<!--  
//UserCode_Sectionwhatarefsms_end
-->
## SubStateMachine feature
<!--  
 //UserCode_Sectionsubstatemachinefeature
 -->
FSMs can have sub-FSMs or Sub-StateMachine that are embedded in a state. These submachines are entered when the state they are embedded in is entered. It an event that the owning FSM subscribed to is triggered, it will then delegate that trigger to the submachine instead. The submachine must be exited in order to reactivate the owning FSM.

You can see an example of an FSM diagram that utilizes the explained above features here.
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/FSM1.PNG) 

here is the submachine for this
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/FSM2.PNG)
<!--  
//UserCode_Sectionsubstatemachinefeature_end
-->
## Create your own FSM
<!--  
 //UserCode_Sectioncreateyourownfsm
 -->
 The FSMs for the diagram above will be used as an example of an FSM to create. Here is the UI Top FSM example that is created in the config ui

```csharp
    public class BlindsUITOPFSM : AEFSM
    {
        public BlindsUITOPFSM(string instanceNameOfMachine, AEPriorities priority)
            : base("AECoreTests", instanceNameOfMachine,

                   new AEState("Idle", 0, null,
                new AEStateEvent(Button1.Instance, "Configuring"),
                new AEStateEvent(Button2.Instance, "NormalOperating"),
                new AEStateEvent(Button3.Instance))

                  , priority, null)
        {
        }

        public override List<AEState> _GetAllStates()
        {
            return new List<AEState>() {
            new AEState("Configuring", 100, "ConfiguringFSM",
                new AEStateEvent(Button1.Instance),
                new AEStateEvent(Button2.Instance),
                new AEStateEvent(Button3.Instance, "Idle")
                ),
            new AEState("NormalOperating", 100, "NormalOperationFSM",
                new AEStateEvent(Button1.Instance),
                new AEStateEvent(Button2.Instance),
                new AEStateEvent(Button3.Instance, "Idle")
                )
            };
        }
    }
```
Notice that It declares to Substatemachines "ConfiguringFSM" embedded in state "Configuring", and "NormalOperationFSM" embedded in state "NormalOperating"

Here is an example of the Config ui FSM that is the substatemachine of BlindsUITOPFSM.
```csharp
    public class ConfiguringFSM : AEFSM
    {
        public ConfiguringFSM(string instanceNameOfMachine, AEPriorities priority)
            : base("AECoreTests", instanceNameOfMachine,

                  new AEState("Idle", 100, null,
                        new AEStateEvent(Button1.Instance),
                        new AEStateEvent(Button2.Instance),
                        new AEStateEvent(Button3.Instance, "SettingTopLimit"))

                  , priority, null)
        {
        }

        public override List<AEState> _GetAllStates()
        {
            return new List<AEState>() {
            new AEState("SettingTopLimit", 100, null,
                new AEStateEvent(Button1.Instance),
                new AEStateEvent(Button2.Instance),
                new AEStateEvent(Button3.Instance, "SettingBottomLimit")
                ),
            new AEState("SettingBottomLimit", 100, null,
                new AEStateEvent(Button1.Instance),
                new AEStateEvent(Button2.Instance),
                new AEStateEvent(Button3.Instance, true)
                )
            };
        }
    }
```    
After you aergenerate your FSMs, go to the respective file in AERTOS and fill in the user sections. You'll notice that the event callbacks are in switch statements (performance reasons).
<!--  
//UserCode_Sectioncreateyourownfsm_end
-->
## View FSM graph generated
<!--  
 //UserCode_Sectionviewfsmgraphgenerated
-->
A useful tool after aegenerating your state machine is that it will also generate a DOTDiagram of your FSMs.  The path to the DOT diagram files is in 
```C:/CodeGenerator/CodeGenerator/MacroProcesses/AESetups/AEProjects/YOUR-Project-Name```
Open the .SVG files, and copy the contents into a DOT file viewer like here 
```https://dreampuf.github.io/GraphvizOnline```
Here is what mine looks like for the example above.
![](https://github.com/haditj66/AERTOS/blob/master/doc/images/FSM3.PNG)
<!--  
//UserCode_Sectionviewfsmgraphgenerated_end
-->


 
