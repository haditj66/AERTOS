
# Creating an AERTOS project
<!--  
//UserCode_Sectiona
-->
 These are the components to creating an AERTOS project.
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
- [Overview](#overview)

- [CGEN commands for AERTOS](#cgen-commands-for-aertos)

- [The Config file](#the-config-file)

- [AEConfig](#aeconfig)

- [ProjectTests](#projecttests)

- [Declaring events in project](#declaring-events-in-project)

- [peripheral declaration](#peripheral-declaration)

- [Libraries project depends on](#libraries-project-depends-on)

- [additional include and src files](#additional-include-and-src-files)

- [write your own cmake for a project](#write-your-own-cmake-for-a-project)

- [the cmakegui for cmake options](#the-cmakegui-for-cmake-options)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## Overview
<!--  
 //UserCode_Sectionoverview 
 -->
 
There are three components to AERTOS. To walk through a full example of creating a simple project, see  [Example blinky](https://github.com/haditj66/AERTOSCopy/blob/master/doc/example/blinky.md).

 - CGEN: A .NET application that aids with code generating your AERTOS project.
 - AERTOS config project: A .NET application that you use to write c# code that CGEN will use to code generate.
 - AERTOS: The actual AERTOS project that will run on your embedded target. 
 
 

 
    
   ![](https://github.com/haditj66/AERTOS/tree/master/doc/images/Blinky1.png)
 
 <!--  
//UserCode_Sectionoverview_end
-->
## CGEN commands for AERTOS
<!--  
 //UserCode_Sectioncgencommandsforaertos
 -->
 
 
 To create a brand new AERTOS project, run the following command in the directory you want the project to be. Make sure to be in the AERTOS base directory of C:/AERTOSProjects

     cgen aeinit <name>

----
To select a project you want to work in

    cgen aeselect <nameOfProject> <nameOfProjectTest> 
Make sure to reload cmake so the project updates in AERTOS after running this command.
   
  ---
  To code generate your currently selected project based on your config project

    cgen aegenerate
Make sure to reload cmake so the project updates in AERTOS after running this command.
   <!--  
//UserCode_Sectioncgencommandsforaertos_end
-->
## The Config file
<!--  
 //UserCode_Sectiontheconfigfile
 -->
 you will find your config file, which is a c# script, in the conf folder of you AERTOS project. To use it in your config project located here 

     C:/AERTOSProjects/AAAConfigProj

<!--  
//UserCode_Sectiontheconfigfile_end
-->
## AEConfig
<!--  
 //UserCode_Sectionaeconfig
  -->
 In your config project, you can set AERTOS  settings per project test. To do this, look at the 
 [AEEXETest] attribute. You can open  parenthesis and intellesense will give you some settings you can set. For example doing this

    [AEEXETest(aEconfigTOTAL_HEAP_SIZE:85000)]
   gives the setting that the total available size of AERTOS will be 85000 bytes.

<!--  
//UserCode_Sectionaeconfig_end
-->
## ProjectTests
<!--  
 //UserCode_Sectionprojecttests
   -->
 Look at the  [AEEXETest] attribute in a config project. This signifies that the function below it is a AERTOS test. You can create more than one test. To make another test, just write another function. Name it the name of your test, and give it the above attribute. Like this
```csharp
      [AEEXETest]
     public void NameOfYourNewTest()
     {  }
```
build your config project to update everything. 
dont forget to do 

    cgen aeselect NameOfYourNewTest
if you want to select this test to work in. run cgen aegenerate when necessary.
<!--  
//UserCode_Sectionprojecttests_end
-->
## Declaring events in project
<!--  
 //UserCode_Sectiondeclaringeventsinproject
 -->
 Every project needs to declare all events it will be using or will need to use. All depending libraries will automatically have the events they use be imported in. To include events, do so in your config project within"_GetEventsInLibrary" function.
Here is an example of me includeing ButtonChanged event. the 2 means that I expect I will need no more than 2 instances of that event set to a pool.
```csharp
    protected override List<AEEvent> _GetEventsInLibrary()
            {
                return new List<AEEvent>() {
                    ButtonChanged.Init(2) 
                };
            }
```       

<!--  
//UserCode_Sectiondeclaringeventsinproject_end
-->
## peripheral declaration
<!--  
 //UserCode_Sectionperipheraldeclaration
  -->
Same as events, you need to declare the peripherals that your project will use. Do this in function _GetPeripheralsInLibrary. Here is an example from the blinky project that includes a gpio and a pwm peripheral
```csharp
	protected override List<AEHal> _GetPeripheralsInLibrary()
    { 
        return new List<AEHal>() {
            PWMPERIPHERAL1.Init(Portenum.PortD, PinEnum.PIN12),
            GPIOPERIPHERAL1.Init(Portenum.PortA, PinEnum.PIN1)
        };
    }
```
<!--  
//UserCode_Sectionperipheraldeclaration_end
-->
## Libraries project depends on
<!--  
 //UserCode_Sectionlibrariesprojectdependson
 -->
You can easily import other libraries other people have created or that you created yourself. Do this in the _GetLibrariesIDependOn function. An exmple from the blinky project looks like this
```csharp
        protected override List<AEProject> _GetLibrariesIDependOn()
        {
            return new List<AEProject>() {
            new commonAOs(),
            new commonHalAOs()
            };
        }
``` 
Notice how here I use the commonAOs and the commonHalAOs library. Of course make sure the config files of libraries you depend on are also linked in the config project.

<!--  
//UserCode_Sectionlibrariesprojectdependson_end
-->
## additional include and src files
<!--  
 //UserCode_Sectionadditionalincludeandsrcfiles
 -->
Sometimes you want to include other 3rd party libraries like all header libraries like Eigen. You cant put all source files in the include directory so you might need to add additional header and source directories. For eigen, for example. I did so like this.
 

```csharp
	protected override List<string> _GetAnyAdditionalIncludeDirs()
    {
        return new List<string>() { "eigen3/Eigen", "matlab_common" , "Rot2EulAngle" , "Angle2Quat", "EllipseFit" };
    }

    protected override List<string> _GetAnyAdditionalSRCDirs()
    {
        return new List<string>() { "matlab_common", "Rot2EulAngle", "Angle2Quat", "EllipseFit" };
    }
``` 


<!--  
//UserCode_Sectionadditionalincludeandsrcfiles_end
-->
## write your own cmake for a project
<!--  
 //UserCode_Sectionwriteyourowncmakeforaproject
 -->
if you need to write you own custom cmake stuff for perhaps adding a third party c++ library that is not header only, or needs some cmake initialization, you can do so in the file 

    AEConfigProjectUser.cmake
located in the base directory of your project. For example, if you project is blinky, it will be located here

    C:\AERTOSProjects\blinky\AEConfigProjectUser.cmake

<!--  
//UserCode_Sectionwriteyourowncmakeforaproject_end
-->
## the cmakegui for cmake options
<!--  
 //UserCode_Sectionthecmakeguiforcmakeoptions
  -->
the cmake gui is a way to aid in helping you select cmake options a project might need to run. It pops up automatically when you run reload cmake if you are missing some options that have not been selected yet. You can create your own cmake options in the AEConfigProjectUser.cmake file for a particular project like this 

    Cgen_Option( 
            NAME MY_CUSTOM_OPTION
            DESCRIPTION "what environment is this AE application set in"
            POSSIBLEVALUES MY_POSSIBLE_VALUE1 MY_POSSIBLE_VALUE2 MY_POSSIBLE_VALUE3
            CONSTRICTS_LATER_OPTIONS
    )

the gui will automatically read this and represent your option  as a selection.

<!-- 
//UserCode_Sectionthecmakeguiforcmakeoptions_end
-->


 
