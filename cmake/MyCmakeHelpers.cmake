




function(target_link_libraries _target)
    set(_mode "PUBLIC")
    foreach(_arg IN LISTS ARGN)
        if (_arg MATCHES "INTERFACE|PUBLIC|PRIVATE|LINK_PRIVATE|LINK_PUBLIC|LINK_INTERFACE_LIBRARIES")
            set(_mode "${_arg}")
        else()
            if (NOT _arg MATCHES "debug|optimized|general")
                set_property(GLOBAL APPEND PROPERTY GlobalTargetDepends${_target} ${_arg})
            endif()
        endif()
    endforeach()
    _target_link_libraries(${_target} ${ARGN})
endfunction()


#########################
#this will get all dependency libraries a target depends on. (make sure to use this at end file to get all linked libraries)
#########################
function(get_link_dependencies _target _listvar)
    set(_worklist ${${_listvar}})
    if (TARGET ${_target})
        list(APPEND _worklist ${_target})
        get_property(_dependencies GLOBAL PROPERTY GlobalTargetDepends${_target})
        foreach(_dependency IN LISTS _dependencies)
            if (NOT _dependency IN_LIST _worklist)
                get_link_dependencies(${_dependency} _worklist)
            endif()
        endforeach()
        set(${_listvar} "${_worklist}" PARENT_SCOPE)
    endif()
endfunction()


#########################
#this will get all sources of a target that it depends on.
#########################
function(get_all_sources_of_target _target _all_sources_out) 
set(_worklist ${${_all_sources_out}})
get_link_dependencies(${_target} _deps)
foreach(_dep IN LISTS _deps)
    get_target_property(_srcs ${_dep} SOURCES)
    get_target_property(_src_dir ${_dep} SOURCE_DIR)
    foreach(_src IN LISTS _srcs)
        #message("${_src_dir}/${_src}")
        set(_worklist ${_worklist} "${_src_dir}/${_src}") 
        
    endforeach()
endforeach()
set(${_all_sources_out} "${_worklist}" PARENT_SCOPE) 
endfunction()

 


#########################
#this will Put your files in a source group with a name that you specify
#########################
function(Set_Sources_in_SourceGroup ) 
set(options)
set(oneValueArgs NAMEOFGROUP)
set(multiValueArgs LISTOFSOURCES) 
cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

foreach(source IN LISTS _arg_LISTOFSOURCES)
source_group("${_arg_NAMEOFGROUP}" FILES "${source}")
endforeach()
endfunction()
 




 


#########################
#generate a cgen macro file given a .in file located in the GeneratedFiles folder
#INPUT_FILE_NAME: the .in file name in the GeneratedFiles folder that will be used to generate the file
#OUTPUT_FILE_NAME: the name of the file outputted. (just name without extension not including path )
#OUTPUT_FILE_EXTENSION: extension of output file
#WORKINGDIRECTORY the directory to put the generated file

#########################
function(Generate_File_Using_Cgen )
    set(options)
    set(oneValueArgs WORKINGDIRECTORY INPUT_FILE_NAME OUTPUT_FILE_NAME OUTPUT_FILE_EXTENSION)
    set(multiValueArgs)
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

     
    #if generated file does not exist yet, create it
    #if(NOT EXISTS "${_arg_WORKINGDIRECTORY}/${_arg_OUTPUT_FILE_NAME}.${OUTPUT_FILE_EXTENSION}")
        #file(WRITE "${_arg_WORKINGDIRECTORY}/${_arg_OUTPUT_FILE_NAME}.${OUTPUT_FILE_EXTENSION}" "newfile")
        #ctest_sleep(5)
    #endif()
     
    #first make sure the input file even exists. if not, dont do anything
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/GeneratedFiles/${_arg_INPUT_FILE_NAME}.cgenM.in) 
        message(WARNING "HADI: the input file ${CMAKE_SOURCE_DIR}/GeneratedFiles/${_arg_INPUT_FILE_NAME}.cgenM.in  did not exist when
                attempting to cgen generate macro.")
        return()
    endif ()

    #generate the file
    configure_file(${CMAKE_SOURCE_DIR}/GeneratedFiles/${_arg_INPUT_FILE_NAME}.cgenM.in
            ${_arg_WORKINGDIRECTORY}/${_arg_OUTPUT_FILE_NAME}.cgenM @ONLY)


    #run cgen macro in this directory to generate the cmake generated file
    execute_process(COMMAND  cgen macro
            WORKING_DIRECTORY ${_arg_WORKINGDIRECTORY}
            OUTPUT_VARIABLE outVar 
            ERROR_VARIABLE errorVar)
             
if(NOT EXISTS "${_arg_WORKINGDIRECTORY}/${_arg_OUTPUT_FILE_NAME}.${OUTPUT_FILE_EXTENSION}")
                execute_process(COMMAND  cgen macro
            WORKING_DIRECTORY ${_arg_WORKINGDIRECTORY}
            OUTPUT_VARIABLE outVar
            ERROR_VARIABLE errorVar)

    endif()



endfunction()



#########################
#strip file name of its extension
#MYFILE:
#OUT_VAR
#########################
function(strip_file_extension)
    set(options)
    set(oneValueArgs MYFILE)
    set(multiValueArgs)
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
string(REGEX REPLACE "\.[^.]*$" "" OUT_VAR ${_arg_MYFILE})

    set(OUT_VAR ${OUT_VAR} PARENT_SCOPE)
endfunction()


#########################
#get file extension
#MYFILE:
#OUT_VAR
#########################
function(get_file_extension )
    set(options)
    set(oneValueArgs MYFILE  )
    set(multiValueArgs)
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    string(REGEX MATCH "\.[^.]*$"  OUT_VAR ${_arg_MYFILE})
    string(REGEX REPLACE "[\.]" "" OUT_VAR ${OUT_VAR})
    set(OUT_VAR ${OUT_VAR} PARENT_SCOPE)

endfunction()









####################################################################################################
#                           Unit tests helper functions
####################################################################################################





#########################
#Add a test to Target you choose. The test will be placed 
#in directory ${TestsForTarget}_Tests with file names ${NameOfTestTarget}.cpp
#TestsForTarget: the target that these tests are meant for. for example AECoreLib
#########################
function(CREATE_TARGET_UNITTESTS) 
set(options)
set(oneValueArgs  NameOfTestTarget  LOCATION_OF_TARGET)
set(multiValueArgs LibrariesToLinkTo LISTOF_EXTRA_SOURCES) 
cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

if(${BUILD_UNIT_TESTS} STREQUAL "TRUE" )

#no more doing this with ForUserConfigNum. Instead setting files are pulled from the "conf" directory 
#if(${TestGroups} STREQUAL  "Test_Group${_arg_ForUserConfigNum}")	 

set(FULL_PATH_TO_TARGET ${_arg_LOCATION_OF_TARGET}/${_arg_NameOfTestTarget})

set(USER_CONFIG_FILES
"${_arg_LOCATION_OF_TARGET}/${_arg_NameOfTestTarget}/conf/UserBSPConfig.cpp" 
"${_arg_LOCATION_OF_TARGET}/${_arg_NameOfTestTarget}/conf/AEConfig.h" 
)

 add_bsp_based_executable(NAME ${_arg_NameOfTestTarget}
	SOURCES
         ${_arg_LISTOF_EXTRA_SOURCES}
         #${AESetupFiles}
         ${USER_CONFIG_FILES}  
		"${_arg_LOCATION_OF_TARGET}/${_arg_NameOfTestTarget}/${_arg_NameOfTestTarget}.cpp"  
		"${CMAKE_SOURCE_DIR}/test/mainUnitTest.cpp"
	GENERATE_BIN
	GENERATE_MAP
	BUILD_UNIT_TESTS)
#target_include_directories(BSP PUBLIC "${_arg_LOCATION_OF_TARGET}/${_arg_TestsForTargets}_Tests/conf")
target_include_directories(BSP PUBLIC "${FULL_PATH_TO_TARGET}/conf")
target_include_directories(${_arg_NameOfTestTarget}  PUBLIC "${FULL_PATH_TO_TARGET}/conf") 
target_include_directories(${_arg_NameOfTestTarget}  PUBLIC "${_arg_LOCATION_OF_TARGET}")

Set_Sources_in_SourceGroup(NAMEOFGROUP "UserAEConf" LISTOFSOURCES  ${USER_CONFIG_FILES})

target_link_libraries(${_arg_NameOfTestTarget} PUBLIC  BSP)  
#link all targets these tests will use.
foreach(tar ${_arg_LibrariesToLinkTo})
#target_link_libraries(${_arg_NameOfTestTarget} PUBLIC  ${_arg_TestsForTargets})  
target_link_libraries(${_arg_NameOfTestTarget} PUBLIC  ${tar})  
endforeach() 
target_compile_definitions(${_arg_NameOfTestTarget} PRIVATE GOOGLE_TESTING)

endif()
#endif()

endfunction()









 

include("${CMAKE_SOURCE_DIR}/cmake/AEIntegrationTestsManager.cmake")

####################################################################################################
#                           integration/exe tests helper functions
####################################################################################################
macro(CREATE_TARGET_INTEGRATIONEXE) 
set(options)
set(oneValueArgs NAME_OF_TARGET LOCATION_OF_TARGET LIST_OF_TESTS)
set(multiValueArgs LibrariesToLinkTo) 
cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN}) 


Cgen_Option(
        NAME INTEGRATION_TESTS
        DESCRIPTION "choose an integration test to build"
        POSSIBLEVALUES ${_arg_NAME_OF_TARGET} #AECoreTestEXE AEHal_Tests1
        CONSTRICTS_LATER_OPTIONS
)


if(${INTEGRATION_TESTS} STREQUAL "${_arg_NAME_OF_TARGET}")
message("building integration test for target ${_arg_NAME_OF_TARGET}. using specific test of name ${NAME_OF_TARGET}")

set(FULL_PATH_TO_TARGET ${_arg_LOCATION_OF_TARGET}/${_arg_NAME_OF_TARGET})

#get the fsrc files from the include and src directory of this location 
file(GLOB TARGET_SRCS
     "${FULL_PATH_TO_TARGET}/src/*.c"
     "${FULL_PATH_TO_TARGET}/src/*.cpp"
)
file(GLOB TARGET_HEADERS
     "${FULL_PATH_TO_TARGET}/include/*.h"
     "${FULL_PATH_TO_TARGET}/include/*.hpp"
)

if(${Build_System} STREQUAL "VSGDBCmake_Ninja" )

 add_bsp_based_executable(
	NAME ${_arg_NAME_OF_TARGET}
	SOURCES ${FULL_PATH_TO_TARGET}/main.cpp ${SRCS_TO_USER_CONFIG_FILES}
    ${TARGET_SRCS}
    ${TARGET_HEADERS}
	${FULL_PATH_TO_TARGET}/conf/UserBSPConfig.cpp
    ${FULL_PATH_TO_TARGET}/conf/AEConfig.h
	GENERATE_BIN
	GENERATE_MAP) 
	 
		#Always do this for BSP targets. I dont really understand why yet you need this
	target_include_directories(BSP PUBLIC "${FULL_PATH_TO_TARGET}/conf") 


else()

	 add_executable( ${_arg_NAME_OF_TARGET} 
		 main.cpp 
		${SRCS_TO_USER_CONFIG_FILES}
		) 


		target_include_directories(AECoreLib PUBLIC "${FULL_PATH_TO_TARGET}/conf")

endif()
	 

foreach(integtest  ${_arg_LIST_OF_TESTS})
	AEintegrationTest_create_test(
	TEST_NAME ${integtest} 
	FOR_USER_CONFIG_GROUP  Test_Group1)  

   AEintegrationTest_add_test(
   FOR_TARGET ${_arg_NAME_OF_TARGET}  
   All_TEST_NAMES  ${integtest} )
endforeach()

	#AEintegrationTest_create_test(
	#TEST_NAME defaultTest 
	#FOR_USER_CONFIG_GROUP  Test_Group1)  
   #AEintegrationTest_add_test(
   #FOR_TARGET AECoreTestEXE 
   #All_TEST_NAMES  defaultTest)


#target_link_libraries(${_arg_NAME_OF_TARGET}  PUBLIC  AECoreLib)    

#put all libraries this target links to 
foreach(tar ${_arg_LibrariesToLinkTo}) 
target_link_libraries(${_arg_NAME_OF_TARGET} PUBLIC  ${tar})  
endforeach() 

Set_Sources_in_SourceGroup(
NAMEOFGROUP target_sources
LISTOFSOURCES ${TARGET_SRCS})

    Set_Sources_in_SourceGroup(
NAMEOFGROUP target_headers
LISTOFSOURCES ${TARGET_HEADERS})
 


endif()

endmacro()
