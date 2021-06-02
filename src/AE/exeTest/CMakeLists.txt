#-----------------------------------------
# AECoreEXE
#-----------------------------------------

 
 ###################################
 #AECore:EXE
 ################################### 
 



if(${Build_System} STREQUAL "VSGDBCmake_Ninja" )

 add_bsp_based_executable(NAME AECore
	SOURCES 
		 main.cpp 
		${SRCS_TO_TEST_CONFIG}
	GENERATE_BIN
	GENERATE_MAP) 
	 
		#Always do this for BSP targets. I dont really understand why yet you need this
	target_include_directories(BSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/conf")


	else()

	 add_executable( AECore 
		 main.cpp 
		${SRCS_TO_TEST_CONFIG}
		) 


		target_include_directories(AECoreLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/conf")

	endif()
	 

target_link_libraries(AECore PUBLIC  AECoreLib)    


 
 
 #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  
	 



