

 set(PathToConf  "${CMAKE_SOURCE_DIR}/test/Test_Group1")
 set(SRCsForTestsUserConf  	
  "${PathToConf}/AEConfig.h"
  "${PathToConf}/UserBSPConfig.cpp")

 

if(${IsFindTestFrameworkRan} STREQUAL "FALSE" ) 
find_test_framework(
	ID com.sysprogs.unittest.googletest)
endif()

 add_bsp_based_executable(
	NAME AEHalexe
	SOURCES main.cpp ${SRCS_TO_USER_CONFIG_FILES}
	GENERATE_BIN
	GENERATE_MAP
	BUILD_UNIT_TESTS)

 set(All_TEST_NAMES ADC_TEST UART_TEST)
 AEintegrationTest_add_test(FOR_TARGET AEHalexe All_TEST_NAMES ${All_TEST_NAMES})

 set(ALL_SOURCES)
 get_all_sources_of_target(AEHalexe ALL_SOURCES)
 #message("ALL_SOURCES ------------------------------${ALL_SOURCES}")

	 #add_executable(AEHalexe
	#main.cpp
	#"../PinSelector.cpp"
	#"../AEPortAndPin.cpp"
	#"../AEPort.cpp"
	#"${PATH_TO_REQUIRED_Hal_FILES}/UserDefinedInstances.cpp"
	#"../AllPeripheralObjects.cpp"
	#${SRCS_TO_USER_CONFIG_FILES})
	 
	 target_compile_definitions(AEHalexe PUBLIC Using_AEHAL)
	  target_compile_definitions(AEHalexe PUBLIC ${AEHALDefinitions})

#Always do this for BSP targets. I dont really understand why yet you need this
target_include_directories(BSP PUBLIC "${PATH_TO_TEST_CONFIG}")
#target_include_directories(BSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}") 

target_link_libraries(AEHalexe PUBLIC  AEHalLib)     
#target_link_libraries(AEHalexe PRIVATE  AECoreLib)   
#target_link_libraries(AEHalexe PRIVATE  BSP)   



target_include_directories(AEHalexe  PUBLIC "${PATH_TO_TEST_CONFIG}")

#target_include_directories(AEHalexe PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
#target_include_directories(AEHalexe PUBLIC "../${CMAKE_CURRENT_SOURCE_DIR}")

Set_Sources_in_SourceGroup(NAMEOFGROUP "UserAEConf" LISTOFSOURCES  ${SRCS_TO_USER_CONFIG_FILES})

 