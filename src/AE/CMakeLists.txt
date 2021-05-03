#-----------------------------------------
# AE 
# Targets: AECoreLib
#-----------------------------------------



###################################
#User Options
###################################    
 
#AEPrintOptions---------
set(PRINT_METHOD_TYPES PRINT_SEMIHOSTING PRINT_UART_NON_AE PRINT_UART_AE PRINT_NONE)
set(PRINT_METHOD PRINT_SEMIHOSTING  CACHE STRING "Method of printing" FORCE)
set_property(CACHE PRINT_METHOD PROPERTY STRINGS ${PRINT_METHOD_TYPES})


set(PRINT_USE_CACHE FALSE CACHE BOOL FALSE FORCE )
  add_compile_definitions(PRINT_METHOD "${PRINT_METHOD}")
  
if(${PRINT_USE_CACHE})
 add_compile_definitions(PRINT_USE_CACHE)
set(PRINT_CACHE_NUM  4   )
  add_compile_definitions(PRINT_CACHE_NUM=${PRINT_CACHE_NUM})  
endif()



#include the AEHal
option(INCLUDE_HAL "include the AEHAL or not" TRUE )
set(INCLUDE_HAL  TRUE FORCE) 
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
 AEPerformanceTimer.cpp)



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
 AE.h 
  #AEConfig.h
  AEDefines.h
 AEUtils.cpp 
 AEUtils.h 
 AEObjects.h
 AE_Init.h
 AE_Init.cpp
 AESet.h 
 AECircularBuffer.h

 )
 set(HelperFunctions  
  "HelperFunctions/AEmemcpy.h"  
 "HelperFunctions/ByteSerializer.h" 
 "HelperFunctions/FastSine.h" )





 if(${USING_FREERTOS})
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
 message(FATAL_ERROR "${reqFile} does not exist in ${PATH_TO_REQUIRED_Hal_FILES} "
 "you need to define this file for porting purposes for this board.")
 else()
  set(REQUIRED_Hal_FILES ${REQUIRED_Hal_FILES} ${PATH_TO_REQUIRED_Hal_FILES}/${reqFile})
endif()

endforeach()

 
 #set(BOARD_SPECIFIC_FILES ${BOARD_SPECIFIC_FILES}  ${BOARD_REQUIRED_SPECIFIC_FILES})
 #set(PATH_TO_BOARD_SPECIFIC_FILES ${PATH_TO_BOARD_SPECIFIC_FILES} PATH_TO_REQUIRED_BOARD_SPECIFIC_FILES)


  


 


 ###################################
 #AECoreLib
 ###################################
  


 if(NOT USING_LINUX)
 
 	 add_bsp_based_library(NAME AECoreLib
	SOURCES
		${AECoreLib_SRCs}
		${USER_CONFIG_FILES}
		${BOARD_SPECIFIC_FILES}
		${REQUIRED_Hal_FILES}
		${HelperFunctions}
		${NeededHAl}
		) 
	#Always do this for BSP targets. I dont really understand why yet you need this
	target_include_directories(BSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")  

	
 else()

 add_library(AECoreLib  		
		${AECoreLib_SRCs}
		${USER_CONFIG_FILES}
		${BOARD_SPECIFIC_FILES}
		${REQUIRED_Hal_FILES}
		${HelperFunctions}
		${NeededHAl})

 endif()

 Set_Sources_in_SourceGroup(NAMEOFGROUP "HelperFunctions" LISTOFSOURCES  ${HelperFunctions})


	 


target_include_directories(AECoreLib PUBLIC ${AECoreLib_IncludePaths}) 
target_include_directories(AECoreLib PUBLIC ${PATH_TO_BOARD_SPECIFIC_FILES})  
target_include_directories(AECoreLib PUBLIC ${PATH_TO_REQUIRED_Hal_FILES}) 
 



 if(NOT USING_LINUX)


 target_link_libraries(AECoreLib PRIVATE    BSP_com.sysprogs.arm.stm32.freertos) 

  endif()
  
 
 #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  

 if(BUILD_UNIT_TESTS) 
 #create_tests_for_target(
  #TestsForTarget AECoreLib 
  #NameOfTestTarget AECoreTests 
  #ForUserConfigNum 2) 
  endif()

 #if(${TestGroups} STREQUAL  "Test_Group2")	 
 add_subdirectory(exeTest)
 #endif()   




if(NOT USING_LINUX)

 ################################### 
 #get AEHal
 ################################### 
 if(INCLUDE_HAL)
 #add_subdirectory(hal)
 endif()


endif()