

include("${CODEGENGUI_PATH}/CgenCmakeConfigFunctions.cmake")







	#############################################
	#this will configure the AEintegrationTest environment. this is called in AE but will be called again by user project
	#using AE so to override the environment.
	#LOCATION_OF_USER_CONFIG_FILES: the location of the user configuration files. 
	macro(AEintegrationTest_initialize)
		set(options)
		set(oneValueArgs  LOCATION_OF_USER_CONFIG_FILES )
		set(multiValueArgs All_TEST_NAMES)
		cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

		    
		set(PATH_TO_USER_CONFIG_FILES  ${_arg_LOCATION_OF_USER_CONFIG_FILES})


	endmacro()




	#########################
	# each exe target needs user config files. For a user created project, this will be located in the project directory
	#under the 
	#These are config files that the user needs to 
	# define per project. if the exe is for an integration test, the test might need a predefined 
	# user config files that are set for that project. Multiple integration exe targets might share  
	# predefined config files. This is why user config file tempalates are placed in 
	# USER_CONFIG_GROUP: the group of user config files to grab. This is the name of the directory for the user config files
		# located at AERTOSCopy\user_configs
	macro(AE_get_sources_for_integration_test)
		set(options)
		set(oneValueArgs USER_CONFIG_GROUP  )
		set(multiValueArgs )
		cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})


		#the variable SRCS_TO_USER_CONFIG_FILES is used to hold user config source files. source files 
		 file(GLOB SRCS_TO_USER_CONFIG_FILES
		 "${PATH_TO_USER_CONFIG_FILES}/${_arg_USER_CONFIG_GROUP}/*.h"
		 "${PATH_TO_USER_CONFIG_FILES}/${_arg_USER_CONFIG_GROUP}/*.cpp"
		 "${PATH_TO_USER_CONFIG_FILES}/${_arg_USER_CONFIG_GROUP}/*.cc"
		 "${PATH_TO_USER_CONFIG_FILES}/${_arg_USER_CONFIG_GROUP}/*.hpp"
		 "${PATH_TO_USER_CONFIG_FILES}/${_arg_USER_CONFIG_GROUP}/*.c"
	) 

	endmacro()




		#########################
	# creates an integration test instance
	# USER_CONFIG_GROUP: the group of user config files to grab. This is the name of the directory for the user config files
		# located at AERTOSCopy\user_configs
	macro(AEintegrationTest_create_test)
		set(options)
		set(oneValueArgs TEST_NAME FOR_USER_CONFIG_GROUP)
		set(multiValueArgs )
		cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

		#simulate class member variables with the name of instance appended with variable names. example AEI_INST_${_arg_TEST_NAME}
		set(AEI_INST_${_arg_TEST_NAME}_FOR_USER_CONFIG_GROUP ${_arg_FOR_USER_CONFIG_GROUP})
		set(AEI_INST_${_arg_TEST_NAME}_TEST_NAME ${_arg_TEST_NAME})

	endmacro()

 

	#############################################
	#add integration tests to an integration test group.
	#FOR_TARGET: for what target are these integration tests for
	#All_TEST_NAMES: description of that option to create.
	function(AEintegrationTest_add_test)
		set(options)
		set(oneValueArgs  FOR_TARGET )
		set(multiValueArgs All_TEST_NAMES)
		cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})


		Cgen_Option( 
				NAME INTEGRATION_TESTS_FOR_${INTEGRATION_TESTS}
				DESCRIPTION "Available tests for ${_arg_FOR_TARGET} "
				POSSIBLEVALUES ${_arg_All_TEST_NAMES}
				CONSTRICTS_LATER_OPTIONS
		)

		#create the test file chosen if it does not exist yet and generate the contents  of IntegTestPipeline.h
		foreach(TEST_NAME IN LISTS _arg_All_TEST_NAMES)

			#check that an instance of that test was create using the AEintegrationTest_create_test()
	 		if(DEFINED AEI_INST_${TEST_NAME}_TEST_NAME )
			 message(ERROR "HADI: you did not create an instance of the test class ${TEST_NAME} using the AEintegrationTest_create_test() function")
			endif() 

			if(${INTEGRATION_TESTS_FOR_${INTEGRATION_TESTS}} STREQUAL  ${TEST_NAME})
			 

				#add the integration test user config files to the target this test is for. grab the member variable for this test
				#created using AEintegrationTest_create_test()
				AE_get_sources_for_integration_test(USER_CONFIG_GROUP AEI_INST_${TEST_NAME}_FOR_USER_CONFIG_GROUP)
				target_sources(${_arg_FOR_TARGET} PUBLIC ${SRCS_TO_USER_CONFIG_FILES})

				set(TEST_NAME_EXT ${TEST_NAME}.cpp )

				#generate the test file only if it does not exist yet!.
				# if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME_EXT})
				Generate_File_Using_Cgen(
						WORKINGDIRECTORY ${FULL_PATH_TO_TARGET}
						INPUT_FILE_NAME IntegTestTemplate
						OUTPUT_FILE_NAME ${TEST_NAME}
						OUTPUT_FILE_EXTENSION cpp
				)
				#endif ()

				target_sources(${_arg_FOR_TARGET} PUBLIC ${FULL_PATH_TO_TARGET}/${TEST_NAME_EXT})
				
				Set_Sources_in_SourceGroup(NAMEOFGROUP "TestFiles" LISTOFSOURCES   ${FULL_PATH_TO_TARGET}/main.cpp ${FULL_PATH_TO_TARGET}/${TEST_NAME_EXT})

				#generate IntegTestPipeline
				Generate_File_Using_Cgen(
						WORKINGDIRECTORY ${FULL_PATH_TO_TARGET}
						INPUT_FILE_NAME IntegTestPipeline
						OUTPUT_FILE_NAME IntegTestPipeline
						OUTPUT_FILE_EXTENSION h
				)

				target_sources(${_arg_FOR_TARGET} PUBLIC ${FULL_PATH_TO_TARGET}/IntegTestPipeline.h)

			endif()

		endforeach()


	endfunction()
