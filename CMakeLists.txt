#-----------------------------------------
# Root 
# Targets: FreeRTOS  BSP 
#-----------------------------------------
cmake_minimum_required(VERSION 3.15)

project(AERTOS LANGUAGES C CXX ASM)


include("cmake/MyCmakeHelpers.cmake")

  add_compile_definitions(AEConfigLocation="C:/visualgdb_projects/AERTOS/src/AE/exeTest/AEConfig.h")

set(clion TRUE)

###################################
#User Options
###################################   

#RTOS used ------------
#set(RTOS_TYPES) 
#set(RTOS USING_FREERTOS  CACHE STRING "Which RTOS to use" FORCE)
#set_property(CACHE RTOS PROPERTY STRINGS ${RTOS_TYPES})
set(USING_FREERTOS TRUE)
#set(LINUX TRUE)
#set(USING_LINUX TRUE)


#Building tests ------------
option(BUILD_TESTS "to build tests, do this" FALSE )
set(BUILD_UNIT_TESTS  TRUE )

if(BUILD_UNIT_TESTS  )
set(TestGroups_Types Test_Group1 Test_Group2 Test_Group3 Test_Group4)
set(TestGroups Test_Group2  CACHE STRING "which test group to activate" FORCE)
set_property(CACHE TestGroups PROPERTY STRINGS ${TestGroups_Types})
endif()


file(WRITE MyCmakeSettingsDeclares.txt "hi")





set(FreeRTOS_HEAP_TYPE)
if(SIMULATION)
set(FreeRTOS_HEAP_TYPE heap_4)
else()
set(FreeRTOS_HEAP_TYPE heap_1)
endif()

 


if(USING_LINUX)
#set(USING_FREERTOS FALSE)  
endif()


if(NOT USING_LINUX)
find_bsp(ID com.sysprogs.arm.stm32
	VERSION 2021.02
	MCU STM32F411RE
	FRAMEWORKS
		com.sysprogs.arm.stm32.freertos
		com.sysprogs.arm.stm32.hal
		com.sysprogs.arm.stm32.ll
		com.sysprogs.embedded.semihosting_and_profiler
	HWREGISTER_LIST_FILE STM32F4xxxx/DeviceDefinitions/stm32f411xe.xml
	FWCONFIGURATION com.sysprogs.bspoptions.stm32.freertos.portcore=CM4F
	FWCONFIGURATION com.sysprogs.bspoptions.stm32.freertos.heap=${FreeRTOS_HEAP_TYPE})

find_test_framework(ID com.sysprogs.unittest.googletest) 
endif()


 ###################################
 #variables
 #declaring all CompileDefines, Sources, and IncludePaths that all subdirectories will inherit from
 ###################################   

  #RTOS vars -----------
 set(RTOS_Defines)
 set(RTOS_IncludePaths)
 set(RTOS_Srcs)

   #this is the path to the files that are needed for the board I am using ie stm32f4xx_hal_conf.h
 set(PATH_TO_BOARD_SPECIFIC_FILES)
 set(BOARD_SPECIFIC_FILES)

 #set(COMPILEDEFINES_Hardware)
 #set(SOURCE_FILES_Hardware)
 #set(INCLUDE_PATHS_Hardware)
#
 #set(COMPILEDEFINES_Simulation)
 #set(SOURCE_FILES_Simulation)
 #set(INCLUDE_PATHS_Simulation)
#
  #set(COMPILEDEFINES_Common)
 #set(SOURCE_FILES_Common)
 #set(INCLUDE_PATHS_Common)
 





 ###################################
 #declaring global definition preprocessors that will be used by all targets
 ###################################   
 add_compile_definitions(MCU_ARM_ARCHITECTURE ${_BSP_BSP_CONFIGURATION_com.sysprogs.bspoptions.arm.core})
 add_compile_definitions(MCU_ARM "${_BSP_MCU}") 
 if(SIMULATION) 
 add_compile_definitions(SIMULATION)
	 if(USING_FREERTOS)
	  add_compile_definitions(USING_FREERTOS)  
	 endif()

 elseif(HARDWARE)
 add_compile_definitions(HARDWARE)
	 if(USING_FREERTOS)
	  add_compile_definitions(USING_FREERTOS)  
	 endif()
  
 elseif(USING_LINUX)
 add_compile_definitions(USING_LINUX)  
 endif()
  
  

  set(COMPILEDEFINES_Hardware)



message("_BSP_MCU -----------------${_BSP_MCU}")
message(" _BSP_BSP_CONFIGURATION_com.sysprogs.bspoptions.arm.core ----------------- ${_BSP_BSP_CONFIGURATION_com.sysprogs.bspoptions.arm.core}") 
message("CMAKE_BUILD_TYPE -----------------${CMAKE_BUILD_TYPE}")
message("PLATFORM -----------------${PLATFORM}")



 
if(NOT USING_LINUX)

	 ###################################  
	 #FreeRTOS
	#getting freertos Sources for Hardware and simulation mingw 
	 ###################################  
	 if(${USING_FREERTOS})

	set(FREERTOS_EXTRA_SRCS #"${CMAKE_SOURCE_DIR}/src/AE/FreeRTOSConfig.h"
	#"${CMAKE_SOURCE_DIR}/src/AE/FreeRTOSConfigFiles/BoardSpecificFreeRTOSDefines.h"
	#"${CMAKE_SOURCE_DIR}/FreeRTOSConfigFiles/FreeRTOSSetUpFunctions.h"
	#"${CMAKE_SOURCE_DIR}/FreeRTOSConfigFiles/FreeRTOSSetUpFunctions.cpp" 
	)
	set(FREERTOS_EXTRA_INCLUDES 
	#"${CMAKE_SOURCE_DIR}"
	#"${CMAKE_SOURCE_DIR}/src/AE"
	#"${CMAKE_SOURCE_DIR}/FreeRTOSConfigFiles"
	)
	if(SIMULATION) 
	include("cmake/GetFREERTOS_MINGW.cmake") 

	 endif()

	 set(RTOS_Defines ${RTOS_Defines} RTOS_FREERTOS)
	 set(RTOS_IncludePaths ${RTOS_IncludePaths}  ${FREERTOS_INCLUDES} "${CMAKE_SOURCE_DIR}/src/AE/FreeRTOSConfigFiles")
 

	 endif()
  
  endif()




  

  
###################################
 # BSP
 ###################################  


  
  #get files associated with board specific files that AE will need
  set(HalBoardType)  
  if(SIMULATION OR  USING_LINUX)
 set(HalBoardType simulated) 
 else()
  set(HalBoardType ${_BSP_MCU}) 
 endif()
 set(PATH_TO_BOARD_SPECIFIC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/AE/hal/boards/${HalBoardType}/board_files")

  #just get whatever files are located in the boards/${HalBoardType} area
 file(GLOB BOARD_SPECIFIC_FILES
     "${PATH_TO_BOARD_SPECIFIC_FILES}/*.h"
     "${PATH_TO_BOARD_SPECIFIC_FILES}/*.cpp"
	 "${PATH_TO_BOARD_SPECIFIC_FILES}/*.cc"
	 "${PATH_TO_BOARD_SPECIFIC_FILES}/*.hpp"
	 "${PATH_TO_BOARD_SPECIFIC_FILES}/*.c"
)

 if(NOT USING_LINUX)

  if(NOT SIMULATION)  
     

target_include_directories(BSP PUBLIC ${PATH_TO_BOARD_SPECIFIC_FILES})   
 endif() 



target_include_directories(BSP PUBLIC  ${RTOS_IncludePaths})

endif()

#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 



 


 if(BUILD_UNIT_TESTS)
 #add_subdirectory("test")
 endif()


 add_subdirectory("src/AE")










