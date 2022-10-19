#-----------------------------------------
# AECoreTestEXE
#-----------------------------------------

 
 ###################################
 #AECoreTestEXE:EXE
 ################################### 
 

 
 #AE_GET_SOURCES_FOR_INTEGRATION_TEST(USER_CONFIG_GROUP Test_Group1)

if(${Build_System} STREQUAL "VSGDBCmake_Ninja" )

 add_bsp_based_executable(
	NAME AECoreTestEXE
	SOURCES main.cpp ${SRCS_TO_USER_CONFIG_FILES}
	${CMAKE_CURRENT_SOURCE_DIR}/conf/UserBSPConfig.cpp
	GENERATE_BIN
	GENERATE_MAP) 
	 
		#Always do this for BSP targets. I dont really understand why yet you need this
	target_include_directories(BSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/conf") 


	else()

	 add_executable( AECoreTestEXE 
		 main.cpp 
		${SRCS_TO_USER_CONFIG_FILES}
		) 


		target_include_directories(AECoreLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/conf")

	endif()
	 
	AEintegrationTest_create_test(
	TEST_NAME defaultTest 
	FOR_USER_CONFIG_GROUP  Test_Group1)  
   AEintegrationTest_add_test(
   FOR_TARGET AECoreTestEXE 
   All_TEST_NAMES  defaultTest)

target_link_libraries(AECoreTestEXE PUBLIC  AECoreLib)    


 
 
 #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  
	 



