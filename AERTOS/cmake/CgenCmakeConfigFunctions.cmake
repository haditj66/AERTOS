###############################
#dont change this file from here as it is copied from.
#c:\codegenerator\codegenerator\CgenCmakeGui\CgenCmakeConfigFunctions.cmake
#change it from there instead.
###############################


	#####delimits a string to whatever delimiter you want.
function (ListToString result delim)
    list(GET ARGV 2 temp)
    math(EXPR N "${ARGC}-1")
    foreach(IDX RANGE 3 ${N})
        list(GET ARGV ${IDX} STR)
        set(temp "${temp}${delim}${STR}")
    endforeach()
    set(${result} "${temp}" PARENT_SCOPE)
endfunction(ListToString)


#NAME: name of the option I want to create
#Description: description of that option to create.
#POSSIBLEVALUES: possible values the option can be. example POSSIBLEVALUES SIMULATION REALITY
#CONSTRICTS_LATER_OPTIONS: what options that may pop up does this option restrict
    #MUST BE IN FORMAT OPTIONTYPE*NAMEOFCONSTRICTED*POSSIBLE*POSSIBLE
    #example SIMULATION*SW_HW_DRIVEN*HWIL*SWIL 
function(Cgen_Option )
    set(options)
    set(oneValueArgs NAME  DESCRIPTION  )
    set(multiValueArgs CONSTRICTS_LATER_OPTIONS POSSIBLEVALUES)
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})


    # 1.    check if that option has already been set
    if(DEFINED ${_arg_NAME})
        return()
    endif () 
	
	if(DEFINED CODEGENGUI_PATH) 
	
		# 2.	check if the cgengui has been opened yet
		if(${CGEN_GUI_SET} STREQUAL "TRUE")
				execute_process(COMMAND  CgenCmakeGui.exe
				WORKING_DIRECTORY "${CODEGENGUI_PATH}/bin/Debug/net5.0-windows"
				OUTPUT_VARIABLE outVar 
				ERROR_VARIABLE errorVar
				)
				
				set(CGEN_GUI_SET TRUE)
		endif ()


		# 3.     overwrite the file cgenCmakeConfigNEXT.txt with ...
			ListToString(possibleStr " " ${_arg_POSSIBLEVALUES})
		file(WRITE ${CGEN_NEXTFILE} "NAME ${_arg_NAME}
			DESCRIPTION ${_arg_DESCRIPTION}
			POSSIBLEVALUES ${possibleStr}
			CONSTRICTS_LATER_OPTIONS ${_arg_CONSTRICTS_LATER_OPTIONS}
		")
		
	endif () 

    # 4.    throw a fatal error to end the execution
    message(FATAL_ERROR "cgen: ${_arg_NAME} needs to be set now")


endfunction()







#*************************************************************
#start cgen
#CGEN_PROJECT_DIRECTORY: this is the directory of the root directory for the project you are running. if laeft undefined, it will just use the cmake_source_directory
#CGEN_DIRECTORY_OF_CACHE: use this to specify the RELATIVE DIRECTORY where all cgen related files such as the cache will be placed. you can set different cgen directory configs for different configurations.
#						  the base directory is always ${CMAKE_CURRENT_SOURCE_DIR}/CGensaveFiles/cmakeGui/
#                         the default value, if not specified, for this is the directory  ${PLATFORM}/${CMAKE_BUILD_TYPE}
#CGEN_PROJECT_DIRECTORY: the root directory for the project
macro(Cgen_Start )
    set(options)
    set(oneValueArgs  CGEN_DIRECTORY_OF_CACHE CGEN_PROJECT_DIRECTORY CGEN_CMAKE_SETTINGS_FILE)
    set(multiValueArgs )
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
	

    #0.     add the FromGuiOrProject.cmake file which tells it whether this is 
    #       run from the gui or from the project cmake
	if(DEFINED CODEGENGUI_PATH)
		include("${CODEGENGUI_PATH}/FromGuiOrProject.cmake")
		
		if(DEFINED DIFFERENT_MACHINE_DEPLOYMENT_TARGET)
			if(NOT DEFINED CGEN_CMAKE_CURRENT_SOURCE_DIR)
				message(FATAL_ERROR "cgen: you need to define the CGEN_CMAKE_CURRENT_SOURCE_DIR since the final deployement target will not be on this machine")
			endif()
			if(NOT DEFINED CGEN_CMAKE_CURRENT_BINARY_DIR)
				message(FATAL_ERROR "cgen: you need to define the CGEN_CMAKE_CURRENT_BINARY_DIR since the final deployement target will not be on this machine")
			endif()
 
		endif()
		  
	endif ()
	
	if(NOT DEFINED DIFFERENT_MACHINE_DEPLOYMENT_TARGET)
			set(CGEN_CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
		set(CGEN_CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}) 
		endif()

	add_compile_definitions(CGEN_CMAKE_CURRENT_SOURCE_DIR="${CGEN_CMAKE_CURRENT_SOURCE_DIR}")
	add_compile_definitions(CGEN_CMAKE_CURRENT_BINARY_DIR="${CGEN_CMAKE_CURRENT_BINARY_DIR}")
	

	message("PLATFORM----------------${PLATFORM}")
    message("CMAKE_BUILD_TYPE----------------${CMAKE_BUILD_TYPE}")

	    #if this cmake CMAKE_BUILD_TYPE is not defined, make it so that the user MUST define it. 
    #this is because of the various ways different IDE's might set this variable, causing inconsistent 
    #behaviour when moving from one ide to another.
    if(NOT DEFINED CMAKE_BUILD_TYPE)
        message("PLATFORM----------------${PLATFORM}")
        message("CMAKE_BUILD_TYPE----------------${CMAKE_BUILD_TYPE}")
        message( "CGEN_PROJECT_DIRECTORY  -----  ${CMAKE_CURRENT_SOURCE_DIR}/CGensaveFiles/cmakeGui/PLATFORM/CMAKE_BUILD_TYPE" )
        message(WARNING "HADI: You need to have set the cmake variable CMAKE_BUILD_TYPE. Usually this is \"Debug\". check that if you moved to a 
            different ide that they two ide's dont set CMAKE_BUILD_TYPE differently")
    endif()
	

	
	# PLACE_CACHE_IN_THIS_PROJECT_DIRECTORY: this is the directory that the cgencache will be placed. It is different than the CGEN_PROJECT_DIRECTORY because this directory
	#			will not use the savedoptions
	# CGEN_PROJECT_DIRECTORY: this is the directory that will have the files needed for cgencmakegui to function. like CGEN_NEXTFILE and CGEN_STEP1FILE and the  
	# CGEN_DIRECTORY_OF_CACHE_PROJECT_FILES: this is the directory of the cache file RELATIVE to the PLACE_CACHE_IN_THIS_PROJECT_DIRECTORY. This should not be the same as your project's build directory as this
	#gets cleaned when you do a rebuild.
	#

    # 1.    first check that the cgenCmakeCache.cmake and cgenCmakeConfigNEXT.txt
    #       file exists in location ${CMAKE_SOURCE_DIR}/CGensaveFiles
	  
	if(NOT DEFINED _arg_CGEN_PROJECT_DIRECTORY)
		set(CGEN_PROJECT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}) 
	else()
		set(CGEN_PROJECT_DIRECTORY ${_arg_CGEN_PROJECT_DIRECTORY}) 
	endif() 
	 
	

	if(NOT DEFINED _arg_CGEN_DIRECTORY_OF_CACHE)
		set(CGEN_DIRECTORY_OF_CACHE_PROJECT_FILES "${PLATFORM}/${CMAKE_BUILD_TYPE}")
		set(CGEN_DIRECTORY "${CGEN_PROJECT_DIRECTORY}/CGensaveFiles/cmakeGui/${PLATFORM}/${CMAKE_BUILD_TYPE}" )
	else()
		set(CGEN_DIRECTORY "${CGEN_PROJECT_DIRECTORY}/CGensaveFiles/cmakeGui/${_arg_CGEN_DIRECTORY_OF_CACHE}" )
		set(CGEN_DIRECTORY_OF_CACHE_PROJECT_FILES "${_arg_CGEN_DIRECTORY_OF_CACHE}")
	endif() 

	if(NOT DEFINED CGEN_ORIGINAL_PROJECT_DIRECTORY_ALREADY_SET)
		set(CGEN_ORIGINAL_PROJECT_DIRECTORY ${CGEN_DIRECTORY}) 
		set(CGEN_ORIGINAL_PROJECT_DIRECTORY_ALREADY_SET TRUE) 
	endif()
	
	 
	if(NOT DEFINED CGEN_CMAKE_SETTINGS_FILE_INITIALIZED)#only do this once.
		if(NOT DEFINED _arg_CGEN_CMAKE_SETTINGS_FILE)
			set(CGEN_CMAKE_SETTINGS_FILE "${CGEN_DIRECTORY}") 
		else()
			set(CGEN_CMAKE_SETTINGS_FILE "${_arg_CGEN_CMAKE_SETTINGS_FILE}") 
		endif() 
	set(CGEN_CMAKE_SETTINGS_FILE_INITIALIZED TRUE)
	endif() 

	if(NOT DEFINED AERTOS_BASE_DIR_INITIALIZED)#only do this once. 
		set(AERTOS_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")  
		set(AERTOS_BASE_DIR_INITIALIZED TRUE)
	endif() 
	

	

	#set(CGEN_DIRECTORY2 "${CMAKE_CURRENT_BINARY_DIR}/CGensaveFiles" )
    set(CGEN_CACHEFILE "${CGEN_ORIGINAL_PROJECT_DIRECTORY}/cgenCmakeCache.cmake"  )
    set(CGEN_NEXTFILE "${CGEN_ORIGINAL_PROJECT_DIRECTORY}/cgenCmakeConfigNEXT.txt"  )
	set(CGEN_STEP1FILE "${CMAKE_CURRENT_BINARY_DIR}/CGensaveFiles/Dir_Step1.txt"  )
	 
	#set(PATH_TO_TESTMACRO_FILE "${CGEN_CMAKE_CURRENT_BINARY_DIR}/CGensaveFiles/IntegrationTestMacros.h") 
	set(PATH_TO_TESTMACRO_FILE "${CGEN_ORIGINAL_PROJECT_DIRECTORY}/IntegrationTestMacros.h") 
	add_compile_definitions(PATH_TO_TESTMACRO_FILE="${PATH_TO_TESTMACRO_FILE}")
	
	
    if (NOT EXISTS ${CGEN_DIRECTORY})
        file(MAKE_DIRECTORY ${CGEN_DIRECTORY})
    endif ()
    if (NOT EXISTS ${CGEN_CACHEFILE})
        file(WRITE ${CGEN_CACHEFILE} "")
    endif ()
    if (NOT EXISTS ${CGEN_NEXTFILE})
        file(WRITE ${CGEN_NEXTFILE} "")
    endif ()
	if (NOT EXISTS ${CGEN_STEP1FILE})
        file(WRITE ${CGEN_STEP1FILE} "")
    endif ()
	
	_Write_To_Step1_Dir()

	    message("CGEN_CACHEFILE----------------${CGEN_CACHEFILE}")
			
	#read fromt the options save file cgenCmakeCache.cmake
	include(${CGEN_CACHEFILE})
endmacro()


macro(_Write_To_Step1_Dir)
	
	if(DEFINED CODEGENGUI_PATH)
		
				message("CMAKE_CURRENT_BINARY_DIR----------------${CMAKE_CURRENT_BINARY_DIR}")
                message("CGEN_STEP1FILE----------------${CGEN_STEP1FILE}")
		
				
		#write to the step1 file the directories that the cgencmagui will need
		file(WRITE ${CGEN_STEP1FILE}  "AERTOS_BASE_DIR: ${AERTOS_BASE_DIR}\nCGEN_CMAKE_SETTINGS_FILE: ${CGEN_CMAKE_SETTINGS_FILE}\nCGEN_PROJECT_DIRECTORY: ${CGEN_PROJECT_DIRECTORY}\nCGEN_ORIGINAL_PROJECT_DIRECTORY: ${CGEN_ORIGINAL_PROJECT_DIRECTORY}\nCGEN_DIRECTORY: ${CGEN_DIRECTORY}\nCMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}\nCMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}\nPLATFORM: ${PLATFORM}\nCMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}\nCGEN_DIRECTORY_OF_CACHE_PROJECT_FILES: ${CGEN_DIRECTORY_OF_CACHE_PROJECT_FILES}")
		
			 execute_process(COMMAND  cgen cmakegui
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
				OUTPUT_VARIABLE outVar 
				ERROR_VARIABLE errorVar
				)
	endif()	
	
endmacro()



function(Cgen_sleep seconds) 

message("sleeping for seconds")
  if("${CMAKE_MAJOR_VERSION}" LESS 3)
    if(UNIX)
      execute_process(COMMAND sleep ${seconds} RESULT_VARIABLE res)

      if(NOT "${res}" EQUAL 0)
        message(FATAL_ERROR "sleep failed")
      endif()
      return()
    endif()

    message(WARNING "sleep no available in cmake version ${CMAKE_VERSION}")
    return()
  endif()

  #cmake_lean(-E sleep "${seconds}")
  message("done sleeping")
  return()
endfunction()


	

macro(Cgen_Reset )
    set(options)
    set(oneValueArgs   CGEN_PROJECT_DIRECTORY)
    set(multiValueArgs )
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
	


	if(NOT DEFINED _arg_CGEN_PROJECT_DIRECTORY)
		set(CGEN_PROJECT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}) 
	else()
		set(CGEN_PROJECT_DIRECTORY ${_arg_CGEN_PROJECT_DIRECTORY}) 
	endif() 


	#write to the step 1 directory to be bicked up by the reset.
	_Write_To_Step1_Dir()
	 

	#only reset the gui if the gui is actually open
	 if(${CGEN_GUI_SET} STREQUAL "FALSE") 

					#write a done in the next file signalling that there are no more options to set
		if(DEFINED CODEGENGUI_PATH) 
			file(WRITE ${CGEN_NEXTFILE} "---RESET_GUI---")
			Cgen_sleep(3)
		endif ()

     endif ()



endmacro()

 




function(Cgen_End )
    set(options)
    set(oneValueArgs   )
    set(multiValueArgs )
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
	
	if(DEFINED BUILD_TESTS)
		if(${BUILD_TESTS} STREQUAL "TRUE" )		
			if(DEFINED INTEGRATION_TESTS)
				if(NOT DEFINED INTEGRATION_TESTS_FOR_${INTEGRATION_TESTS})
					message(FATAL_ERROR "cgen: you specified that you wanted to build an integration test for integration test ${INTEGRATION_TESTS} \n however you have not created any specific tests for this integration test. To do that you need to do for example like the following  \n   \n set(All_TEST_NAMES ADC_TEST UART_TEST)  \n IntegrationTest_add_test(FOR_TARGET AEHalexe All_TEST_NAMES ${All_TEST_NAMES})")
				endif()
			endif()
		endif()
	endif()
	
	#write a done in the next file signalling that there are no more options to set
		if(DEFINED CODEGENGUI_PATH) 
			file(WRITE ${CGEN_NEXTFILE} "---OPTIONS_DONE---")
		endif ()
		
endfunction()


function(Cgen_End_Session )
    set(options)
    set(oneValueArgs   )
    set(multiValueArgs )
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
	 
	#write a done in the next file signalling that there are no more options to set
		if(DEFINED CODEGENGUI_PATH) 
			file(WRITE ${CGEN_NEXTFILE} "---OPTIONS_DONE---")
		endif ()
		
endfunction()