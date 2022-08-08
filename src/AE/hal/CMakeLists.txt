#-----------------------------------------
# hal 
# Targets: AEHalLib
#-----------------------------------------

#PATH_TO_REQUIRED_Hal_FILES
#REQUIRED_Hal_FILES
#
#PATH_TO_BOARD_SPECIFIC_FILES 
#BOARD_SPECIFIC_FILES

set(PATH_TO_Hal_FILES "${CMAKE_CURRENT_SOURCE_DIR}/boards/${HalBoardType}/AEHalFiles")

set(AEHALDefinitions)

#############################
#get hal files that exist.  
############################# 

set(Possible_Hal_Files AEGPIOOutput.h AEGPIOInput.h AEDMA.h AEADC.h AEUART.h) 
set(Peripheral_Hal_Files )
set(User_Peripheral_Hal_Files )

#first get all files in the AEHalFiles directory
 file(GLOB User_Peripheral_Hal_Files
     "${PATH_TO_Hal_FILES}/*.h"
     "${PATH_TO_Hal_FILES}/*.cpp"
	 "${PATH_TO_Hal_FILES}/*.cc"
	 "${PATH_TO_Hal_FILES}/*.hpp"
	 "${PATH_TO_Hal_FILES}/*.c"
)

 #make sure that the following files are located here  
foreach(reqFile IN LISTS Possible_Hal_Files) 

if(NOT EXISTS "${PATH_TO_Hal_FILES}/${reqFile}") 
 message(INFO " ${reqFile} does not exist in ${PATH_TO_REQUIRED_Hal_FILES} " 
 "you need to define this file for porting purposes for this board.")
 else()
 #remove extension so to get the  ${MYFILE_WITHOUT_EXT}Peripheral.h file associated with the hal file
 string(REGEX REPLACE "\\.[^.]*$" "" MYFILE_WITHOUT_EXT ${reqFile})
 if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${MYFILE_WITHOUT_EXT}Peripheral.h") 
  message(FATAL_ERROR "${MYFILE_WITHOUT_EXT}Peripheral.h does not exist. Hadi, you need to produce this file" )
 endif() 
  set(Peripheral_Hal_Files ${Peripheral_Hal_Files}  ${MYFILE_WITHOUT_EXT}Peripheral.h) 
  set(AEHALDefinitions ${AEHALDefinitions} USING_${MYFILE_WITHOUT_EXT}) 
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${MYFILE_WITHOUT_EXT}Peripheral.cpp") 
  set(Peripheral_Hal_Files ${Peripheral_Hal_Files}  ${MYFILE_WITHOUT_EXT}Peripheral.cpp)
  endif()
  #set(Peripheral_Hal_Files ${Peripheral_Hal_Files}  ${PATH_TO_Hal_FILES}/${reqFile})
endif()
endforeach()
 
add_bsp_based_library(NAME AEHalLib
	SOURCES
		AEPortAndPin.h
		PinSelector.h
		AEPort.h
		"${PATH_TO_REQUIRED_Hal_FILES}/BoardTypes_1.h"
		BoardTypes.h
		AEPin.h
		AEPeripheral.h
		AllPeripheralObjects.h
		
		)
		 
target_link_libraries(AEHalLib PUBLIC  AECoreLib)  

set(HalLibSrcs "${PATH_TO_REQUIRED_Hal_FILES}/UserDefinedInstances.cpp"  
PinSelector.cpp 
AEPortAndPin.cpp 
AEPort.cpp AEPin.cpp 
AllPeripheralObjects.cpp 
${User_Peripheral_Hal_Files}
${Peripheral_Hal_Files}
)

target_sources(AEHalLib PUBLIC ${HalLibSrcs}
)

Set_Sources_in_SourceGroup(NAMEOFGROUP "UserPeripheralFiles" LISTOFSOURCES  ${User_Peripheral_Hal_Files})
Set_Sources_in_SourceGroup(NAMEOFGROUP "PeripheralFiles" LISTOFSOURCES  ${Peripheral_Hal_Files})


target_include_directories(AEHalLib PUBLIC "${PATH_TO_REQUIRED_Hal_FILES}")  
target_include_directories(AEHalLib PUBLIC "${PATH_TO_Hal_FILES}")  
target_include_directories(AEHalLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")  
target_include_directories(BSP PUBLIC "${PATH_TO_REQUIRED_Hal_FILES}")  
target_include_directories(BSP PUBLIC "${PATH_TO_Hal_FILES}")  
target_include_directories(BSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")  

 
 target_compile_definitions(AEHalLib PUBLIC Using_AEHAL)
 
target_compile_definitions(AECoreLib PUBLIC Using_AEHAL)

 target_compile_definitions(AEHalLib PUBLIC ${AEHALDefinitions})
 target_compile_definitions(AECoreLib PUBLIC ${AEHALDefinitions})
  



#if(${TestGroups} STREQUAL  "Test_Group1")	  
   ##target_compile_definitions(AEHalTests PUBLIC Using_AEHAL)
#endif()
#
 #endif()


# if(${INTEGRATION_TESTS} STREQUAL  "AEHal_Tests1")
 #add_subdirectory(exeHalTest)
#endif()


  

