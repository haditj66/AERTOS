#-----------------------------------------
# test
#-----------------------------------------

find_test_framework(ID com.sysprogs.unittest.googletest)
 

if(NOT SIMULATION)  
	#target_include_directories(FREERTOSTest PUBLIC ${PATH_TO_USER_CONFIG_FILES}) 
	#target_include_directories(FREERTOSTest PUBLIC ${PATH_TO_BOARD_SPECIFIC_FILES})  
	#target_include_directories(BSP PUBLIC ${PATH_TO_USER_CONFIG_FILES})  
	#target_include_directories(BSP PUBLIC ${PATH_TO_BOARD_SPECIFIC_FILES})  
	
	else() 

#target_include_directories(FREERTOSTest PRIVATE ../src/AE)
	#target_include_directories(FREERTOSTest PUBLIC ${PATH_TO_USER_CONFIG_FILES})  
	#target_include_directories(BSP PUBLIC ${PATH_TO_USER_CONFIG_FILES})   
	#target_include_directories(BSP PUBLIC ${FREERTOS_INCLUDES}) 
	#target_link_libraries(FREERTOSTest PRIVATE    BSP_com.sysprogs.arm.stm32.freertos)   

endif()	

add_bsp_based_executable(NAME FREERTOSTest
	SOURCES
		FreertosTest.cpp 
		#${USER_CONFIG_FILES}
		#${BOARD_SPECIFIC_FILES}  
		Test_Template.cpp
		"${CMAKE_CURRENT_SOURCE_DIR}/conf/AEConfig.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/conf/UserBSPConfig.cpp"
		mainUnitTest.cpp
	GENERATE_BIN
	GENERATE_MAP
	BUILD_UNIT_TESTS)
target_include_directories(BSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/conf")

target_link_libraries(FREERTOSTest PUBLIC  BSP)   
target_link_libraries(FREERTOSTest PUBLIC  AECoreLib)   

target_compile_definitions(FREERTOSTest PRIVATE GOOGLE_TESTING)
