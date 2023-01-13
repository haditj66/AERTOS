
# Integration Testing Debugging
<!--  
//UserCode_Sectiona
-->
This will explain how to Integration test in AERTOS.
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

- [How to use integration functions](#how-to-use-integration-functions)

- [Log timers](#log-timers)

- [Other helpful functions](#other-helpful-functions)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## Overview
<!--  
 //UserCode_Sectionoverview
 -->
Every project can have many tests. From a config file, each  function decorated with [AEEXETest] is an integration test. When you run a project, the test APIs you put it in are the tests.
 
####  If you want to turn this off integration tests
You can do so during the cgen cmake gui initialization. For option BUILDTESTS, choose false. Or in the file ```cgenCmakeCache_CAERTOSAERTOS.cmake``` file located in your project cgensave files, for example for blinky it is located here ```C:\AERTOSProjects\blinky\CGensaveFiles\cmakeGui\blinky_STM32F411RE\DEBUG```
Go to that file and set ```set(BUILD_TESTS TRUE)``` to ```set(BUILD_TESTS FALSE)```.
<!--  
//UserCode_Sectionoverview_end
-->
## How to use integration functions
<!--  
 //UserCode_Sectionhowtouseintegrationfunctions
 -->
Here is the api for integration tests. To find the integration test file for tests, go to directory  
```C:\AERTOS\AERTOS\TestResources\IntegrationTestResults```  . All test results are automatically written to this file (from the microcontroller) when an integration test ender is called.

An important concept of AERTOS integration tests is that there needs to be at least on integration test ender function call. This is when all results are written to file. The most common one is the timer ender. 

## Test enders
#### This will end the test after a specified amount of time.
```cpp
AEITEST_END_TestsAfterTimer_YourProjectName(5000); 
```
#### This will end the test when called
```cpp
AEITEST_END_YourProjectName(); 
```

#### This will end the test if it fails even once.
```cpp
AEITEST_EndTestsIfFalseAssertion_blinky("testName", isThingTrue == true, "the thing was not true. test ends here.");
```

## Other tests
#### If you want a expect a test of name to need to run at least once.
```cpp
AEITEST_EXPECT_TEST_TO_RUN_YourProjectName("futureTestName");
```

#### A simple test that must pass
```cpp
 AEITEST_YourProjectName("testName", someCondition < 500000, "test example is less than 500000");
```
#### A simple test that must be executed and pass X amount of times
```cpp
 AEITEST_YourProjectName_MUST_PASS_THIS_MANY("actionRequestTime", tr < 500000, "actionRequest timer should be less than .5ms", 60);
```
#### This ignore the first X amount of passes of a test 
```cpp
AEITEST_blinky_IgnoreFirstTests("testName", 1 < 500000, "test will skip the first 3 passes",3); 
```


<!--  
//UserCode_Sectionhowtouseintegrationfunctions_end
-->
## Log timers
<!--  
 //UserCode_Sectionlogtimers
  -->
You can Log performance Timers and even test against those times. Here is how you would create a timer and log it. To find the log file for timer tests, go to directory ```C:\AERTOS\AERTOS\TestResources\PerformanceTimes\Hardware``` for not simulation.
```C:\AERTOS\AERTOS\TestResources\PerformanceTimes\Simulation``` for simulation.
Pick the name of the log name. All times are in nanoseconds.

#### Here is an example of starting, stopping,  and logging a timer.
```cpp
	   AEStartTimer(1);//1 for as in timer one. (there are three to choose from)
	   // some function you want to time.
	   AEStopTimer(1);
	   auto tr = AEGetTimerDuration(1);//again 1 for timer 1
	   AELogTimer(1, "UtilityRequestTimeToRun"); //log the timer with the log name
```
log file located here ```C:\AERTOS\AERTOS\TestResources\PerformanceTimes\Hardware\UtilityRequestTimeToRun\UtilityRequestTimeToRun.txt```
 

<!--  
//UserCode_Sectionlogtimers_end
-->
## Other helpful functions
<!--  
 //UserCode_Sectionotherhelpfulfunctions
 -->

You can print to console like this 
```cpp
AEPrint("%s thing to write %d", "some string", 5);
```
print all current timers values to console
```cpp
AEPrint("%s thing to write %d", "some string", 5);
```





#### runtime assertions
You can do runtime assertions. These are NOT tests but assertions that will end the program if failed.
```cpp
AEAssertRuntime(1 < 50, "assertion message"); 
AEAssertRuntimeNoMsg(1 < 50); 
```

<!--  
//UserCode_Sectionotherhelpfulfunctions_end
-->


 
