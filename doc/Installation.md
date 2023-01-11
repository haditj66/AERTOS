
# Installation
<!--  
//UserCode_Sectiona
-->
Installation instructions for AERTOS.
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
- [Prerequisites](#prerequisites)

- [Installing visualgdb](#installing-visualgdb)

- [installing CGEN](#installing-cgen)

- [Installing AERTOS](#installing-aertos)

- [Installing AERTOS projects](#installing-aertos-projects)



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## Prerequisites
<!--  
 //UserCode_Sectionprerequisites
 -->
 

 - Windows 7 or higher
 - Visual studio 2019 or higher
 - VisualGDB 
 - CGEN
 - AERTOS config project

 <!--  
//UserCode_Sectionprerequisites_end
-->
## Installing visualgdb
<!--  
 //UserCode_Sectioninstallingvisualgdb
  -->
 You are unfortunately going to need VisualGDB.  AERTOS can run without it but for now support for that is not there. They have a 30 day free trial and a discount for students. You can get it here 
 https://visualgdb.com/

 <!--  
//UserCode_Sectioninstallingvisualgdb_end
-->
## installing CGEN
<!--  
 //UserCode_Sectioninstallingcgen
   -->
This is a developer utility I wrote to help with code generation and other tools. This is what code generated AERTOS projects. You dont actually need it to run AERTOS but without it you would have to manually write an AERTOS project AOs which would be a hassle. You can get it here by following instructions there.
https://github.com/haditj66/CodeGenerator

 <!--  
//UserCode_Sectioninstallingcgen_end
-->
## Installing AERTOS
<!--  
 //UserCode_Sectioninstallingaertos
    -->

In your C:/ directory run the following commands  
  `git clone https://github.com/haditj66/AERTOS` 
  or for ssh use 
  `git clone git@github.com:haditj66/AERTOS.git` 
 <!--  
//UserCode_Sectioninstallingaertos_end
-->
## Installing AERTOS projects
<!--  
 //UserCode_Sectioninstallingaertosprojects
 -->
 This has some sample libraries you can use but more importantly has a config .NET project that you will use to write preliminary c# code that will generate the final C/C++ AERTOS code.
  You can get it by going in your C:/ directory and running the following commands  
  
    git clone https://github.com/haditj66/AERTOS2Projects.git  
  
  or for ssh use  

    git clone git@github.com:haditj66/AERTOS2Projects.git 
    
Now make sure to rename that base directory from 

    C:/AERTOS2Projects
    to 
    C:/AERTOSProjects
<!--  
//UserCode_Sectioninstallingaertosprojects_end
-->


 
