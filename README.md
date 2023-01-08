AERTOS is a framework and development environment for writing RTOS applications on embedded devices. Currently only supports stm32F4 boards but can be easily ported to be used on almost any dev board that supports FREERTOS.
# Table of Contents
 - [Overview](https://github.com/haditj66/AERTOSCopy)
 - [Installation](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Installation)
 - [Creating an AERTOS project](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Creating_an_AERTOS_project)
 - [Example project: Blinky](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Blinky)
 - [AERTOS concepts](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/AERTOS_concepts)
	 - [AOs](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/AOs)
	 - [Events](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/Events)
	 - [AELoopObject](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/AELoopObject)
	 - [AEClock](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/AEClock)
	 - [Observers](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/Observers)
	 - [Utilities](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/Utilities)
	 - [FSMs](https://github.com/haditj66/AERTOSCopy/blob/master/doc/concepts/FSMs)
 - [Target PC or embedded device](https://github.com/haditj66/AERTOSCopy/blob/master/doc/Target_Switch)
 - [AEHal](https://github.com/haditj66/AERTOSCopy/blob/master/doc/AEHal)
 - [Integration testing/debugging](https://github.com/haditj66/AERTOSCopy/blob/master/doc/IntegrationTesting_Debugging)
 - [Advanced project example: Motor speed controller](https://github.com/haditj66/AERTOSCopy/blob/master/doc/ExampleMotorSpeedController)
 - [AERTOS UploadDataToPC Utility](https://github.com/haditj66/AERTOSCopy/blob/master/doc/UploadDataToPC)

# Overview
AERTOS came about as a need to rapidly prototype embedded applications without having to worry about the details of RTOS mechanisms such as semaphores and tasks. Instead this is abstracted with concepts of a event-driven architecture. Finite state machines, Service calls, signal processing blocks are a few examples of the concepts used in AERTOS. Below is an example of what can be possible with AERTOS. This is a basic on-off control system for maintaining the desired acceleration of whatever you can imagine.

TODO: show image and function calls in this.
