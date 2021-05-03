

 set(PathToConf  "${CMAKE_SOURCE_DIR}/test/conf_group1")
 set(SRCsForTestsUserConf  	
  "${PathToConf}/AEConfig.h"
  "${PathToConf}/UserBSPConfig.cpp")

 add_bsp_based_executable(NAME AEHalexe
	SOURCES 
		main.cpp
	#"../PinSelector.cpp"
	#"../AEPortAndPin.cpp"
	#"${PATH_TO_REQUIRED_Hal_FILES}/UserDefinedInstances.cpp"

	#"../AEPort.cpp" 
	#"../AllPeripheralObjects.cpp"
	${SRCsForTestsUserConf}
	GENERATE_BIN
	GENERATE_MAP ) 

	 #add_executable(AEHalexe
	#main.cpp
	#"../PinSelector.cpp"
	#"../AEPortAndPin.cpp"
	#"../AEPort.cpp"
	#"${PATH_TO_REQUIRED_Hal_FILES}/UserDefinedInstances.cpp"
	#"../AllPeripheralObjects.cpp"
	#${SRCsForTestsUserConf}) 
	 
	 target_compile_definitions(AEHalexe PUBLIC Using_AEHAL)
	  target_compile_definitions(AEHalexe PUBLIC ${AEHALDefinitions})

#Always do this for BSP targets. I dont really understand why yet you need this
target_include_directories(BSP PUBLIC "${PathToConf}")
#target_include_directories(BSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}") 

target_link_libraries(AEHalexe PUBLIC  AEHalLib)     
#target_link_libraries(AEHalexe PRIVATE  AECoreLib)   
#target_link_libraries(AEHalexe PRIVATE  BSP)   



target_include_directories(AEHalexe  PUBLIC "${PathToConf}")

#target_include_directories(AEHalexe PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
#target_include_directories(AEHalexe PUBLIC "../${CMAKE_CURRENT_SOURCE_DIR}")

Set_Sources_in_SourceGroup(NAMEOFGROUP "UserAEConf" LISTOFSOURCES  ${SRCsForTestsUserConf})

 