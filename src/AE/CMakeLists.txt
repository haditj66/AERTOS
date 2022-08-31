#-----------------------------------------
# AE 
# Targets: AECoreLib
#-----------------------------------------


###################################
#User Options
###################################    
 
#AEPrintOptions--------- 

Cgen_Option(
        NAME PRINT_METHOD
        DESCRIPTION "Method of printing"
        POSSIBLEVALUES NORMAL_PRINTF_WINDOWS NORMAL_PRINTF_LINUX PRINT_SEMIHOSTING PRINT_UART_NON_AE PRINT_UART_AE PRINT_NONE
        CONSTRICTS_LATER_OPTIONS
)

#set(PRINT_METHOD_TYPES PRINT_SEMIHOSTING PRINT_UART_NON_AE PRINT_UART_AE PRINT_NONE)
#set(PRINT_METHOD PRINT_SEMIHOSTING  CACHE STRING "Method of printing" FORCE)
#set_property(CACHE PRINT_METHOD PROPERTY STRINGS ${PRINT_METHOD_TYPES})


set(PRINT_USE_CACHE FALSE CACHE BOOL FALSE FORCE )

if(${PRINT_USE_CACHE})
 add_compile_definitions(PRINT_USE_CACHE)
set(PRINT_CACHE_NUM  4   )
  add_compile_definitions(PRINT_CACHE_NUM=${PRINT_CACHE_NUM})  
endif()



#include the AEHal
Cgen_Option(
        NAME INCLUDE_HAL
        DESCRIPTION "include the AEHAL or not"
        POSSIBLEVALUES TRUE FALSE
        CONSTRICTS_LATER_OPTIONS
)
#option(INCLUDE_HAL "include the AEHAL or not" TRUE )
#set(INCLUDE_HAL  TRUE FORCE)


#set_property(CACHE Include_HAL PROPERTY STRINGS ${Include_HAL})

###################################
 #variables
 ###################################  

 set(AECoreLib_SRCs)
 set(AECoreLib_IncludePaths)
 set(AECoreLib_COMPILEDEFINES)


 #this is the path to the required board files that AECoreLib will need to do things like ie AEPerformanceTimer,h
 set(PATH_TO_REQUIRED_Hal_FILES)
 set(REQUIRED_Hal_FILES)
 #this is the list of files that will be required by AECoreLib
 set(All_Required_Hal_Files 
 AEPerformanceTimer.cpp
 AETimerSimple.h
 AETimerSimple.cpp)



 ###################################
 #get all user config files
 ###################################
 set(USER_CONFIG_FILES ${USER_CONFIG_FILES}) 
 set(USER_CONFIG_FILES ${USER_CONFIG_FILES} 

 #UserBSPConfig.cpp
)
  
 #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



  ###################################
 #get all src files
 ###################################   
  set(AECoreLib_IncludePaths   ${AECoreLib_IncludePaths}
  ${CMAKE_CURRENT_LIST_DIR}
  "${CMAKE_CURRENT_LIST_DIR}/HelperFunctions" 
  "${CMAKE_CURRENT_LIST_DIR}/exeTest"
  )   
 

  set(NeededHAl  AEPerformanceTimer.h)
  

 set(AECoreLib_SRCs  ${AECoreLib_SRCs}  
  #AEConfig.h
  AEDefines.h
 AEUtils.cpp 
 AEUtils.h 
 #AEObjects.h
 AESet.h 
 AECircularBuffer.h
 #PeripheralImplementations.h
 #PeripheralImplementations.cpp

 )
 set(HelperFunctions  
  "HelperFunctions/AEmemcpy.h"  
 "HelperFunctions/ByteSerializer.h" 
 "HelperFunctions/FastSine.h" )


    set(AECoreLib_Managers
 AEPublishSubscribeManager.h
 AEPublishSubscribeManager.cpp
 AEPoolManager.h
 AEPoolManager.cpp
   )

   set(AECoreLib_Integrationtesting
    AEIntegrationTesting.h
 AEIntegrationTesting.cpp
   )

  set(AECoreLib_AE 
   AE.h 
 AE_Init.h
 AE_Init.cpp
 AECore.h
 AEAO.h
 AEAO.cpp)

 set(AECoreLib_Clocks 
 AEClock.h 
 AEClock.cpp)

  set(AECoreLib_EVENTS 
   QueueArgStructures.h
 QueueArgStructures.cpp 
 AEEventBase.h
 AEEventBase.cpp
 EventsForProject.cpp)

   set(AECoreLib_LOOPS
 AELoopObject.h
 AELoopObject.cpp
 AELoop.h
 AELoop.cpp)


set(AECoreLib_SPBS
 AESPBObservor.h
 AESPBObservor.cpp
 AESPBObservorOutputType.h
 SPBDataSubscription.h
 SPBDataSubscription.cpp
 InputChannel.h
 InputChannel.cpp
 InputChannelOutputType.h
 TaskPoolForSPBChain.h
 )

 set(AECoreLib_Observors
AEObservorBase.h
AEObservorBase.cpp
AEObservorSensor.h
AEObservorSensor.cpp
AEObservorTypes.h
AEObservorSensorFilterOut.h
 )

  set(AECoreLib_Links
  AELinkSignalFlow.h
  AELinkSignalFlow.cpp
  AELinkDeterministic.h
  AELinkDeterministic.cpp
  AELinkBase.h
  AELinkBase.cpp
 )


   set(AECoreLib_Interpretors
AEObservorInterpretorOutputType.h
AEObservorInterpretorBase.h
AEObservorInterpretorBase.cpp
AEObservorInterpretor.h
 )

    set(AECoreLib_Filters
 AEFilter.h
 AEMultiChannelFilter.h
 AEMultiChannelFilter.cpp
 AEMultiChannelFilterCHANNELSELECT.h
 )



if(${RTOS_USED} STREQUAL "FREERTOS" )



 set(AECoreLib_IncludePaths   ${AECoreLib_IncludePaths} 
  "${CMAKE_CURRENT_LIST_DIR}/FreeRTOSConfigFiles"

  )   
 set(AECoreLib_SRCs  ${AECoreLib_SRCs}   
 "FreeRTOSConfigFiles/FreeRTOSSetUpFunctions.cpp"    
  "FreeRTOSConfigFiles/FreeRTOSConfig.h"    
 )
 endif()


 ################################### 
 #get all required hardware specific files for AECorelib  
 ################################### 
  
 set(PATH_TO_REQUIRED_Hal_FILES "${CMAKE_CURRENT_SOURCE_DIR}/hal/boards/${HalBoardType}/AECoreHalRequiredFiles")
  

 #make sure that the following files are located here 
 foreach(reqFile IN LISTS All_Required_Hal_Files)

if(NOT EXISTS "${PATH_TO_REQUIRED_Hal_FILES}/${reqFile}")
    FILE(WRITE "${PATH_TO_REQUIRED_Hal_FILES}/${reqFile}" "")
 message(WARNING "${reqFile} does not exist in ${PATH_TO_REQUIRED_Hal_FILES} "
 ". Creating this file for porting purposes for this board. You need to implement this file though")

 else()
  set(REQUIRED_Hal_FILES ${REQUIRED_Hal_FILES} ${PATH_TO_REQUIRED_Hal_FILES}/${reqFile})
endif()

# generate the template file in cgen
strip_file_extension(MYFILE ${reqFile})
set(reqFile_NoExt ${OUT_VAR})
get_file_extension(MYFILE ${reqFile} )
set(reqFile_ext ${OUT_VAR})
Generate_File_Using_Cgen(
        WORKINGDIRECTORY ${PATH_TO_REQUIRED_Hal_FILES}
        INPUT_FILE_NAME ${reqFile_NoExt}${reqFile_ext}
        OUTPUT_FILE_NAME ${reqFile_NoExt}
        OUTPUT_FILE_EXTENSION ${reqFile_ext}
)

endforeach()

 
 #set(BOARD_SPECIFIC_FILES ${BOARD_SPECIFIC_FILES}  ${BOARD_REQUIRED_SPECIFIC_FILES})
 #set(PATH_TO_BOARD_SPECIFIC_FILES ${PATH_TO_BOARD_SPECIFIC_FILES} PATH_TO_REQUIRED_BOARD_SPECIFIC_FILES)


  


 


 ###################################
 #AECoreLib
 ###################################


if(${Build_System} STREQUAL "VSGDBCmake_Ninja" )
 
 
 	 add_bsp_based_library(NAME AECoreLib
	SOURCES
        ${AESetupFiles}
		
		${USER_CONFIG_FILES}
		${BOARD_SPECIFIC_FILES}
		${REQUIRED_Hal_FILES}
		${HelperFunctions}
		${NeededHAl}

		${AECoreLib_LOOPS}
		${AECoreLib_AE}
		${AECoreLib_Integrationtesting}
		${AECoreLib_Managers}
		${AECoreLib_SRCs}
		${AECoreLib_Clocks}
		${AECoreLib_EVENTS}
		${AECoreLib_SPBS}
		${AECoreLib_Observors}
		${AECoreLib_Interpretors}
		${AECoreLib_Filters}
		${AECoreLib_Links}
		) 
	#Always do this for BSP targets. I dont really understand why yet you need this
	target_include_directories(BSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")  

	
 else()

 add_library(AECoreLib
        ${AESetupFiles}
		
		${USER_CONFIG_FILES}
		${BOARD_SPECIFIC_FILES}
		${REQUIRED_Hal_FILES}
		${HelperFunctions}
		${NeededHAl}

		${AECoreLib_LOOPS}
		${AECoreLib_AE}
		${AECoreLib_Integrationtesting}
		${AECoreLib_Managers}
		${AECoreLib_SRCs}
		${AECoreLib_Clocks}
		${AECoreLib_EVENTS}
		${AECoreLib_SPBS}
		${AECoreLib_Observors}
		${AECoreLib_Interpretors}
		${AECoreLib_Filters}
		${AECoreLib_Links}
		)

 endif()

Set_Sources_in_SourceGroup(NAMEOFGROUP "HelperFunctions" LISTOFSOURCES  ${HelperFunctions})
Set_Sources_in_SourceGroup(NAMEOFGROUP "SetupFiles" LISTOFSOURCES  ${AESetupFiles})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AEClocks" LISTOFSOURCES  ${AECoreLib_Clocks})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AEEvents" LISTOFSOURCES  ${AECoreLib_EVENTS})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AELoops" LISTOFSOURCES  ${AECoreLib_LOOPS})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AE" LISTOFSOURCES  ${AECoreLib_AE})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AEIntegrationTesting" LISTOFSOURCES  ${AECoreLib_Integrationtesting})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AEManagers" LISTOFSOURCES  ${AECoreLib_Managers})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AESPBS" LISTOFSOURCES  ${AECoreLib_SPBS})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AEObservors" LISTOFSOURCES  ${AECoreLib_Observors})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AEInterpretors" LISTOFSOURCES  ${AECoreLib_Interpretors})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AEFilters" LISTOFSOURCES  ${AECoreLib_Filters})
Set_Sources_in_SourceGroup(NAMEOFGROUP "AELinks" LISTOFSOURCES  ${AECoreLib_Links})

target_sources(AECoreLib PUBLIC ${AESetupFiles})

#set(PATH_TO_GeneratorFiles "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles")
#file(GLOB GeneratorFiles
#        "${PATH_TO_GeneratorFiles}/*.*.*"
#        )
#target_sources(AECoreLib PUBLIC ${GeneratorFiles})


target_include_directories(AECoreLib PUBLIC ${AECoreLib_IncludePaths}) 
target_include_directories(AECoreLib PUBLIC ${PATH_TO_BOARD_SPECIFIC_FILES})  
target_include_directories(AECoreLib PUBLIC ${PATH_TO_REQUIRED_Hal_FILES}) 
target_include_directories(AECoreLib PUBLIC ${AESetupFiles_PATHS})




if(${RTOS_USED} STREQUAL "FREERTOS" )
        target_link_libraries(AECoreLib PRIVATE    BSP_com.sysprogs.arm.stm32.freertos)
endif()
  
 
 #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



 #TODO. first test out the hal works again and then start moving hal and any exe and unit tests to the 
 #src/hal  for the hal. and 
 #src/exe  for the executable targets. (including integration tests.)
 #in a executable target, will also have unit tests for it. for example
 #AECoretestexe with the defaultTest running will have unit tests as well. So
 #src/exe/AECoretests/exe/defaulttest
 #src/exe/AECoretests/exe/defaulttest/conf
 #src/exe/AECoretests/exe/someothertest
 #src/exe/AECoretests/exe/someothertest/conf
  #src/exe/AECoretests/unittests


 



  ################################### 
 #get AEHal
 ###################################  

if(${INCLUDE_HAL} STREQUAL  "TRUE")
add_subdirectory(hal)
endif()




