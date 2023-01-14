
# Upload Data To PC
<!--  
//UserCode_Sectiona
-->
This tool allows you to stream data via uart from a SPB or a utility directly to a matlab or test file on your PC.
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



<!--  
//UserCode_Sectionb
//UserCode_Sectionb_end
 -->
 
## Overview
<!--  
 //UserCode_Sectionoverview
 -->
There are two AOs that facilitate this tool: The "UploadDataToPcU" utility and the "DataToPC_SPB" SPB. They are in the "commonHalAOs" library. See example
 ```cgen aeselect commonHalAOs datauploadTest```
 for a setup of this. You need to call 
 ```cgen aeserial``` before you run your program to have your PC listen to the serial port. It will then stream the variables, and write them to a text file and a matlab file. The files are located in your ```running_project_base_directory/UploadedFiles```
 


To configure this, you need to depend on the commonHalAOs library and initialize the utility. Here is an example
```cpp
/// <param name="instanceNameOfTDU"></param>
        /// <param name="serviceBuffersize"></param>
        /// <param name="priority"></param>
        /// <param name="poolSizeOfSignals"></param>
        /// <param name="comPort">serial port of your usb to serial connection.</param>
        /// <param name="uartIuse"></param>
        /// <param name="bufferThisManyBeforeCallback">this deals with the buffer that the serial utility will have before it actually triggers the callback to 
        /// process the data. NOTE: CHechIfPcConnected service WILL NOT WORK IF THIS VALUE IS NOT 17 !! a higher value may be needed if the utility cannot keep
        /// up with the frequency of data coming in. </param>
        /// <param name="runName">you can save different runs</param>
        /// <param name="sizeOfVar">size of variables you will be uploading. for example you could upload 5 variables with the second variable being of array size 20</param>
         UploadDataToPcU uploadDataToPcU = new UploadDataToPcU
                ("uploadDataToPcU", 10, AEPriorities.MediumPriority,  3, UARTPERIPHERAL2.Instance, 17, "run1", 1, 32, 1); 
```
So there are some limitations of this tool. UART bandwidth is slow. I recommend upping the UART speed to highest it can handle. For me it was 460800 baud rate.
To initialize the SPB you can do this
```cpp
var dataToPC_SPB = DataToPC_SPB.GetDataToPC_SPB("dataToPC_SPB", StyleOfSPB.EachSPBTask, uploadDataToPcU);
```
Now this is for 3 variable streaming SPB because the uploadDataToPcU instance was for 3 variables.


<!-- 
//UserCode_Sectionoverview_end
-->


 
