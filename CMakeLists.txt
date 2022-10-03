#-----------------------------------------
# Root 
# Targets: FreeRTOS  BSP 
#-----------------------------------------

 
cmake_minimum_required(VERSION 3.15)
  




set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --save-temps")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --save-temps")


set(NAME_OF_THIS_MP_GROUP "somepub")
set(USER_SECTIONS_POSSIBLE
        za zb zc zd ze zf zg zh zi zj zk zl zm zn zo zp zq zr zs zt zu zv zw zx zy zz )
set(USER_SECTIONS_SO_FAR 0)


#set(_arg_WITH_VALUE "some stuff ")

 add_compile_options(-Wl,-verbose, -lC:/Users/Hadi/AppData/Local/VisualGDB/EmbeddedBSPs/arm-eabi/com.sysprogs.arm.stm32)

    add_compile_definitions(aehal)  


set(_arg_WITH_VALUE "some stuff ##UserCode")
 
string(FIND "${_arg_WITH_VALUE}" "##UserCode" isFound)

if(${isFound} STREQUAL "-1")
else()
 #increment and unique name
 MATH(EXPR USER_SECTIONS_SO_FAR "${${NAME_OF_NODE}_ALL_SO_FAR}+1")
 list(GET USER_SECTIONS_POSSIBLE ${USER_SECTIONS_SO_FAR} APPENDCODE)

 set(NAME_FOR_USER_SECTION "${NAME_OF_THIS_MP_GROUP}${APPENDCODE}")

endif()
 string(REPLACE "##UserCode" "##UserCode_${NAME_FOR_USER_SECTION}" _arg_WITH_VALUE ${_arg_WITH_VALUE}) 

###################################
#User Options
###################################
 

#platform WINDOWS_SWIL_FREERTOS

#platforms consist of Build_System-TOOLCHAIN_USED
# the platform will build within its own build directory so to have all the necessary build files
# for the build system and toolchain already located in that build directory.
# OSUSED_TOOLCHAINUSED
if(${PLATFORM} STREQUAL "VSGDBCmakeNinja_mingw" )

    #set(Build_System VSGDBCmake_Ninja)
    #add_compile_definitions(Build_System "${Build_System}")
    #set(TOOLCHAIN_USED mingw)
    #add_compile_definitions(TOOLCHAIN_USED "${TOOLCHAIN_USED}")
#
#
    #set(AERTOS_ENVIRONMENT RTOS_PC)
    #add_compile_definitions(AERTOS_ENVIRONMENT "${AERTOS_ENVIRONMENT}")
#
    #set(OS_USED WINDOWS)
    #add_compile_definitions(OS_USED "${OS_USED}")
    #set(SWIL_HWIL_DRIVEN SWIL)
    #add_compile_definitions(SWIL_HWIL_DRIVEN "${SWIL_HWIL_DRIVEN}")
    #set(BOARD_USED X64)
    #add_compile_definitions(BOARD_USED "${BOARD_USED}")




elseif(${PLATFORM} STREQUAL "CmakeUnixMakefiles_gnu" )


#    set(Build_System Cmake_UnixMakefiles)
#    add_compile_definitions(Build_System "${Build_System}")
#    set(TOOLCHAIN_USED gnu)
#    add_compile_definitions(TOOLCHAIN_USED "${TOOLCHAIN_USED}")
#
#
#    set(RTOS_USED NONE)
#    add_compile_definitions(RTOS_USED "${RTOS_USED}")
#    set(OS_USED UBUNTU)
#    add_compile_definitions(OS_USED "${OS_USED}")

#    set(USING_LINUX 1)
#    add_compile_definitions(USING_LINUX "${USING_LINUX}")


elseif(${PLATFORM} STREQUAL "VSGDBCmakeNinja_armnoneabiid" )

    #set(Build_System VSGDBCmake_Ninja)
    #add_compile_definitions(Build_System "${Build_System}")
    #set(TOOLCHAIN_USED arm_non_eabi_id)
    #add_compile_definitions(TOOLCHAIN_USED "${TOOLCHAIN_USED}")
#
#
    #set(AERTOS_ENVIRONMENT RTOS_MICRO)
    #add_compile_definitions(AERTOS_ENVIRONMENT "${AERTOS_ENVIRONMENT}")
    #set(OS_USED NONE)
    #add_compile_definitions(OS_USED "${OS_USED}")
    #set(SWIL_HWIL_DRIVEN HWIL)
    #add_compile_definitions(SWIL_HWIL_DRIVEN "${SWIL_HWIL_DRIVEN}")



endif()

#if(NOT ${OS_USED} STREQUAL "UBUNTU")
    if (WIN32)
    set(CODEGENGUI_PATH "C:/CodeGenerator/CgenCmakeGui")
    FILE(READ "${CODEGENGUI_PATH}/CgenCmakeConfigFunctions.cmake" contentsOut)
    FILE(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CgenCmakeConfigFunctions.cmake" ${contentsOut})
    endif()
#endif()
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/CgenCmakeConfigFunctions.cmake")
Cgen_Start()

###################################
#add all cmake files needed for AE
###################################
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/AEIntegrationTestsManager.cmake")


###################################



###################################
#initialize any cmake environments
###################################

####AE integration test 
##set up AE integration test environment. This will be called again and override by user
# project that initialize this again. 
AEintegrationTest_initialize(LOCATION_OF_USER_CONFIG_FILES "${CMAKE_SOURCE_DIR}/user_configs" )


 ###################################




Cgen_Option(
        NAME AEPLATFORM
        DESCRIPTION "what platform is this for (this is chosen by IDE command line -D variable)"
        POSSIBLEVALUES VSGDBCmakeNinja_mingw VSGDBCmakeNinja_armnoneabiid CmakeUnixMakefiles_gnu
        CONSTRICTS_LATER_OPTIONS
)

Cgen_Option( 
        NAME AERTOS_ENVIRONMENT
        DESCRIPTION "what environment is this AE application set in"
        POSSIBLEVALUES RTOS_MICRO RTOS_PC ROS_MICRO ROS_PC
        CONSTRICTS_LATER_OPTIONS
)


#the Build_System consists of the CmakeStyle_Generator
Cgen_Option(
        NAME Build_System
        DESCRIPTION "what kind of build environment are you using"
        POSSIBLEVALUES VSGDBCmake_Ninja AmentCmake_colcon Cmake_UnixMakefiles Cmake_MinGWMakefiles
        CONSTRICTS_LATER_OPTIONS
)

Cgen_Option(
        NAME RTOS_USED
        DESCRIPTION "is an RTOS used"
        POSSIBLEVALUES FREERTOS NONE
        CONSTRICTS_LATER_OPTIONS
) 


 
Cgen_Option(
        NAME OS_USED
        DESCRIPTION "what OS is used"
        POSSIBLEVALUES WINDOWS UBUNTU NONE
        CONSTRICTS_LATER_OPTIONS
)

Cgen_Option(
        NAME SIM_REAL
        DESCRIPTION "are input/outputs data coming from real sensors or from a simulated environment"
        POSSIBLEVALUES REALITY SIMULATION
        CONSTRICTS_LATER_OPTIONS
)

Cgen_Option(
        NAME SWIL_HWIL_DRIVEN
        DESCRIPTION "is this software or hardware in the loop. (is HAL being used or a mock)"
        POSSIBLEVALUES SWIL HWIL
        CONSTRICTS_LATER_OPTIONS
)

Cgen_Option(
        NAME BOARD_USED
        DESCRIPTION "what device board is being used"
        POSSIBLEVALUES RPI4B JetsonNano X64 STM32F411RE
        CONSTRICTS_LATER_OPTIONS
)

#toolchain consists of the Ccompiler, c++compiler, and  debugger package used
Cgen_Option(
        NAME TOOLCHAIN_USED
        DESCRIPTION
        POSSIBLEVALUES arm_non_eabi_id mingw gnu
        CONSTRICTS_LATER_OPTIONS
)

Cgen_Option(
        NAME BUILD_TESTS
        DESCRIPTION "if True the integration functions located IntegrationTestMacros.h will be turned on. if false, will not do anything"
        POSSIBLEVALUES TRUE FALSE
        CONSTRICTS_LATER_OPTIONS
)

Cgen_Option(
        NAME BUILD_UNIT_TESTS
        DESCRIPTION "to build all UNIT tests under the test group chosen"
        POSSIBLEVALUES TRUE FALSE
        CONSTRICTS_LATER_OPTIONS
)


if(${TOOLCHAIN_USED} STREQUAL "arm_non_eabi_id")

##for now always have this set to 
set(ARM_COMPILER_VENDOR SysGCC_ARM)
    Cgen_Option(
            NAME ARM_COMPILER_VENDOR
            DESCRIPTION "There are different vendors that have implemented the arm-none-eabi-gcc compiler. Choose the one you want to use."
            POSSIBLEVALUES GNU_ARM IAR_ARM SysGCC_ARM
            CONSTRICTS_LATER_OPTIONS
    )

        Cgen_Option(
            NAME ARM_OPTIMIZATION_SETTINGS
            DESCRIPTION "compiler optimization options. Go here for explanations. https://developer.arm.com/documentation/100748/0607/fnb1472741490155"
            POSSIBLEVALUES level0 level1 level2 level3 levelfast
            CONSTRICTS_LATER_OPTIONS
    )

    
endif()


#write the proper toolchain file to its build location since VSGDB auto generates the toolchain file. I want to write over it.
if(NOT ${OS_USED} STREQUAL "UBUNTU")
SET(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/toolchains/${TOOLCHAIN_USED}/toolchain.cmake" )


    if (NOT EXISTS "${CMAKE_TOOLCHAIN_FILE}")
        message(FATAL_ERROR "Hadi: The toolchain file ${CMAKE_TOOLCHAIN_FILE} does not exist")
    endif ()
     

    file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/build/${PLATFORM}/debug/toolchain.cmake" "include(${CMAKE_TOOLCHAIN_FILE})")
     
endif()




 if(${PLATFORM} STREQUAL "CmakeUnixMakefiles_gnu" )
    if (NOT WIN32)
project(AERTOS LANGUAGES C CXX ASM)
 endif()
 else()
 project(AERTOS LANGUAGES C CXX ASM)
  endif()


  if(${TOOLCHAIN_USED} STREQUAL "arm_non_eabi_id") 
      #NEVERMIND ABUOT THE FOLLOWING. JUST Set(CMAKE_C_COMPILER) here
      #i need to change the CMakeCCompiler.cmake and the CMakeCXXCompiler.cmake in the binary folder the  Set(CMAKE_C_COMPILER)
      if(${ARM_COMPILER_VENDOR} STREQUAL "SysGCC_ARM")   
        set(CMAKE_C_COMPILER "C:/SysGCC/arm-eabi/bin/arm-none-eabi-gcc.exe") 
        set(CMAKE_CXX_COMPILER "C:/SysGCC/arm-eabi/bin/arm-none-eabi-g++.exe")
      elseif(${ARM_COMPILER_VENDOR} STREQUAL "GNU_ARM")
        set(CMAKE_CXX_COMPILER "C:/Program Files (x86)/GNU Tools ARM Embedded/6 2017-q2-update/bin/arm-none-eabi-g++.exe")
        set(CMAKE_C_COMPILER "C:/Program Files (x86)/GNU Tools ARM Embedded/6 2017-q2-update/bin/arm-none-eabi-gcc.exe")

      elseif(${ARM_COMPILER_VENDOR} STREQUAL "IAR_ARM")
      message(FATAL_ERROR "you need to specify the path for this")
      endif()


      #set compile options for compiler speed
      #go here for compile options speed setting meanings
      #https://developer.arm.com/documentation/100748/0607/fnb1472741490155
      if(${ARM_OPTIMIZATION_SETTINGS} STREQUAL          "level0")  
       add_compile_options(  -O0)
       elseif(${ARM_OPTIMIZATION_SETTINGS} STREQUAL     "level1")
        add_compile_options(  -O1)
        elseif(${ARM_OPTIMIZATION_SETTINGS} STREQUAL    "level2")
         add_compile_options(  -O2)
        elseif(${ARM_OPTIMIZATION_SETTINGS} STREQUAL    "level3")
         add_compile_options(  -O3)
        elseif(${ARM_OPTIMIZATION_SETTINGS} STREQUAL    "levelfast")
         add_compile_options(  -Ofast)
        endif()
      

  endif()

include("cmake/MyCmakeHelpers.cmake")


  

message("workspaceRoot-------------------------${VS_DEBUGGER_WORKING_DIRECTORY}")
 


  #add_compile_definitions(AEConfigLocation="C:/visualgdb_projects/AERTOS/src/AE/exeTest/AEConfig.h")

set(clion TRUE)



#this will generate all those board config files located at  ${CMAKE_SOURCE_DIR}/src/AE/AESetup/Board
#put all those board specific function implementations needed in those files.
include("cmake/GetBoardMetaTypes.cmake")


Set_Sources_in_SourceGroup(NAMEOFGROUP "GeneratorInputFiles" LISTOFSOURCES  ${AESetupFiles})



################
#Not chosen by user
################


#this variable indicates whether find_test_framework(ID com.sysprogs.unittest.googletest) 
#for google tests has been run yet
set(IsFindTestFrameworkRan FALSE)


#if(${BUILD_TESTS} STREQUAL "TRUE" )
#
    #Cgen_Option( 
            #NAME TestGroups
            #DESCRIPTION "what test group do you wanna enable" 
            #POSSIBLEVALUES Test_Group1 Test_Group2 Test_Group3 Test_Group4
            #CONSTRICTS_LATER_OPTIONS
    #)  
#
#endif()
# 
#if(${BUILD_UNIT_TESTS} STREQUAL "TRUE" )
#
    #Cgen_Option( 
            #NAME TestGroups
            #DESCRIPTION "what test group do you wanna enable"
            #POSSIBLEVALUES Test_Group1 Test_Group2 Test_Group3 Test_Group4
            #CONSTRICTS_LATER_OPTIONS
    #)
#
#endif()





#set(PATH_TO_USER_CONFIG_FILES  "${CMAKE_SOURCE_DIR}/test/${TestGroups}")
#set(SRCS_TO_USER_CONFIG_FILES  "${PATH_TO_USER_CONFIG_FILES}/AEConfig.h"
        #"${PATH_TO_TEST_CONFIG}/UserBSPConfig.cpp")




set(FreeRTOS_HEAP_TYPE)
if(${SWIL_HWIL_DRIVEN} STREQUAL "SWIL" )
    set(FreeRTOS_HEAP_TYPE heap_4)

else(${SWIL_HWIL_DRIVEN} STREQUAL "HWIL" )
    set(FreeRTOS_HEAP_TYPE heap_1)
endif()



################
#VSGDB initialize
################

if(${Build_System} STREQUAL "VSGDBCmake_Ninja" )
find_bsp(
	ID com.sysprogs.arm.stm32
	VERSION 2022.08
	MCU STM32F411RE
	FRAMEWORKS com.sysprogs.embedded.semihosting_and_profiler
	HWREGISTER_LIST_FILE STM32F4xxxx/DeviceDefinitions/stm32f411xe.xml
	CONFIGURATION "com.sysprogs.toolchainoptions.arm.libctype=--specs=nano.specs -u _printf_float")

find_test_framework(ID com.sysprogs.unittest.googletest) 
set(IsFindTestFrameworkRan TRUE)


endif()




 ###################################
 # adding all 3rd party frameworks
 ###################################   
 
#if is it BOARD_USED is STM32F411RE, then import all stm32f4 hal files
if(${BOARD_USED} STREQUAL "STM32F411RE" )
            import_framework(NAME stm32half4 PATH "${CMAKE_CURRENT_SOURCE_DIR}/frameworks/stm32half4")

            
             add_compile_definitions(STM32F411xE) #this is needed in the stm32 library to select the stm32f4xx_hal.h file.
            import_framework(NAME stm32f4ll PATH  "${CMAKE_CURRENT_SOURCE_DIR}/frameworks/stm32f4ll")
            get_target_property(stm32f4ll_INCLUDES_DIRS stm32f4ll INTERFACE_INCLUDE_DIRECTORIES)
            include_directories(${stm32f4ll_INCLUDES_DIRS})

            #include_directories(  "${CMAKE_SOURCE_DIR}/frameworks/stm32f4ll/STM32F4xx_HAL_Driver/Inc")
            #include_directories(  "${CMAKE_SOURCE_DIR}/frameworks/stm32f4ll/STM32F4xx_HAL_Driver/Inc/Legacy")
            #include_directories( "${CMAKE_SOURCE_DIR}/frameworks/stm32f4ll/CMSIS_HAL/Device/ST/STM32F4xx/Include")
            #include_directories(  "${CMAKE_SOURCE_DIR}/frameworks/stm32f4ll/CMSIS_HAL/Core/Include")
            #include_directories( "${CMAKE_SOURCE_DIR}/frameworks/stm32f4ll/CMSIS_HAL/Include")
			#include_directories( "${CMAKE_SOURCE_DIR}/src/AE/hal/boards/STM32F411RE/board_files") 
            
endif()





  #RTOS vars -----------
 set(RTOS_Defines)
 set(RTOS_IncludePaths)
 set(RTOS_Srcs)

   #this is the path to the files that are needed for the board I am using ie stm32f4xx_hal_conf.h
 set(PATH_TO_BOARD_SPECIFIC_FILES)
 set(BOARD_SPECIFIC_FILES)



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
# add_compile_definitions(MCU_ARM_ARCHITECTURE ${_BSP_BSP_CONFIGURATION_com.sysprogs.bspoptions.arm.core})
# add_compile_definitions(MCU_ARM "${_BSP_MCU}")




#  set(COMPILEDEFINES_Hardware)



message("_BSP_MCU -----------------${_BSP_MCU}")
message(" _BSP_BSP_CONFIGURATION_com.sysprogs.bspoptions.arm.core ----------------- ${_BSP_BSP_CONFIGURATION_com.sysprogs.bspoptions.arm.core}") 
message("CMAKE_BUILD_TYPE -----------------${CMAKE_BUILD_TYPE}")
message("PLATFORM -----------------${PLATFORM}")




###################################
#FreeRTOS
#getting freertos Sources for SWIL mingw
###################################

if(${RTOS_USED} STREQUAL "FREERTOS" )
    if(${SWIL_HWIL_DRIVEN} STREQUAL "SWIL" )


                #set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore CM4F)#look at line of the freertos framework.cmake file
            #add_compile_definitions(USE_FREERTOS) #this is needed for visualgdb 
            ##import_framework(NAME FreeRTOS PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Framework1")
            #import_framework(NAME FreeRTOS PATH "${CMAKE_CURRENT_SOURCE_DIR}/frameworks/FreeRTOS")
            #get_target_property(FreeRTOS_DIRS FreeRTOS INTERFACE_INCLUDE_DIRECTORIES)
            #include_directories(${FreeRTOS_DIRS})


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

        #include("cmake/GetFREERTOS_MINGW.cmake")

                    set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore MSVC)#look at line of the freertos framework.cmake file
                    set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap heap_5)
                    set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.cmsis NONE)
            add_compile_definitions(USE_FREERTOS) #this is needed for visualgdb 
            #import_framework(NAME FreeRTOS PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Framework1")
            import_framework(NAME FreeRTOS PATH "${CMAKE_CURRENT_SOURCE_DIR}/frameworks/FreeRTOS")
            get_target_property(FreeRTOS_DIRS FreeRTOS INTERFACE_INCLUDE_DIRECTORIES)
            include_directories(${FreeRTOS_DIRS})
            include_directories("${CMAKE_CURRENT_SOURCE_DIR}/frameworks/FreeRTOS")


    else() #if it is HWIL i will use the standalone version of freertos. TODO: might want to also set the heap version you want to use. I think heap4?
      
            set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore CM4F)#look at line of the freertos framework.cmake file
            set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.cmsis CMSIS_RTOS)
            add_compile_definitions(USE_FREERTOS) #this is needed for visualgdb 
            #import_framework(NAME FreeRTOS PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Framework1")
            import_framework(NAME FreeRTOS PATH "${CMAKE_CURRENT_SOURCE_DIR}/frameworks/FreeRTOS")
            get_target_property(FreeRTOS_DIRS FreeRTOS INTERFACE_INCLUDE_DIRECTORIES)
            include_directories(${FreeRTOS_DIRS})
            #include_directories("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Framework1/include")
            #include_directories("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Framework1/portable/MemMang")
            #include_directories("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Framework1/portable/GCC/ARM_CM4F")

    endif ()

        set(RTOS_Defines ${RTOS_Defines} RTOS_FREERTOS)
        set(RTOS_IncludePaths ${RTOS_IncludePaths}  ${FREERTOS_INCLUDES} "${CMAKE_SOURCE_DIR}/src/AE/FreeRTOSConfigFiles")

endif ()

  

  
###################################
 # BSP
 ###################################  


  
  #get files associated with board specific files that AE will need
  set(HalBoardType)  
  if(${SWIL_HWIL_DRIVEN} STREQUAL "SWIL" )
 set(HalBoardType simulated) 
 else()
  set(HalBoardType ${BOARD_USED})
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

if(${Build_System} STREQUAL "VSGDBCmake_Ninja" )
    target_include_directories(BSP PUBLIC ${PATH_TO_BOARD_SPECIFIC_FILES})
    target_include_directories(BSP PUBLIC  ${RTOS_IncludePaths})
endif()


#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 





 
 #add_subdirectory("test") 


 add_subdirectory("src/AE")


  

#
 #CREATE_TARGET_UNITTESTS(
  #NameOfTestTarget AECoreTests
  #LibrariesToLinkTo AECoreLib
  #LOCATION_OF_TARGET "${CMAKE_CURRENT_SOURCE_DIR}/src/AE"
 #)



 if(INCLUDE_HAL STREQUAL "TRUE")


  CREATE_TARGET_UNITTESTS(
 NameOfTestTarget AEHalTests
 LibrariesToLinkTo AECoreLib AEHalLib  
 LOCATION_OF_TARGET "${CMAKE_CURRENT_SOURCE_DIR}/src/AE/hal"
  )   
 endif()


 CREATE_TARGET_INTEGRATIONEXE(NAME_OF_TARGET exeHalTest
 LOCATION_OF_TARGET "${CMAKE_CURRENT_SOURCE_DIR}/src/AE/hal"
 LibrariesToLinkTo AECoreLib AEHalLib   
 LIST_OF_TESTS ADC_TEST UART_TEST I2C_TEST
 ) 
 #target_link_libraries(exeHalTest PUBLIC  AEHalLib)     

 CREATE_TARGET_INTEGRATIONEXE(NAME_OF_TARGET AECoreTestEXE
 LOCATION_OF_TARGET "${CMAKE_CURRENT_SOURCE_DIR}/src/AE"
 LibrariesToLinkTo AECoreLib 
 LIST_OF_TESTS defaultTest testAELoop testSPB testFilters testActionRequest testTDU testFSM
 ) 

 #get_target_property(MAIN_CFLAGS AECoreTestEXE COMPILE_OPTIONS)
 #message("-- Target compiler flags are: ${MAIN_CFLAGS}")
  



 CGEN_END()
