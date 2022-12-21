




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
set(oneValueArgs NAME_OF_TARGET LOCATION_OF_TARGET)
set(multiValueArgs LibrariesToLinkTo LIST_OF_TESTS) 
cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN}) 


#if(NOT DEFINED _arg_ONLY_CREATE_LIBRARY)
    #set(_arg_ONLY_CREATE_LIBRARY "FALSE")
#endif()




if(${INTEGRATION_TESTS} STREQUAL "${_arg_NAME_OF_TARGET}")
message("building integration test for target ${_arg_NAME_OF_TARGET}. using specific test of name ${NAME_OF_TARGET}")

set(FULL_PATH_TO_TARGET ${_arg_LOCATION_OF_TARGET})


#run the cgen macro for utilities
#Generate_Macro2_Using_Cgen(
#WORKINGDIRECTORY ${FULL_PATH_TO_TARGET}
#MACRO2_COMMAND AEServiceMacro)


#get the fsrc files from the include and src directory of this location 
file(GLOB TARGET_SRCS
     "${FULL_PATH_TO_TARGET}/src/*.c"
     "${FULL_PATH_TO_TARGET}/src/*.cpp"
)
file(GLOB TARGET_HEADERS
     "${FULL_PATH_TO_TARGET}/include/*.h"
     "${FULL_PATH_TO_TARGET}/include/*.hpp"
)

set(ALL_SOURCES_HEADERS  ${TARGET_SRCS}   ${TARGET_HEADERS}  ) 

_CREATE_AEOBJECTS_FILE()


if(${Build_System} STREQUAL "VSGDBCmake_Ninja" )

set(EXE_USER_CONFIG_FILES 	
    ${FULL_PATH_TO_TARGET}/conf/UserBSPConfig.cpp
    ${FULL_PATH_TO_TARGET}/conf/AEConfig.h 
    ${FULL_PATH_TO_TARGET}/conf/EventsForProject.h 
    ) 

     
    
     add_bsp_based_library(
	NAME ${_arg_NAME_OF_TARGET}_lib
	SOURCES  
                #${EXE_USER_CONFIG_FILES}
    #${FULL_PATH_TO_TARGET}/AEObjects.h 
    ${TARGET_SRCS}
    ${TARGET_HEADERS} 
    ) 

    #write to  AEBUILD_INFO_DIR the directory 
    file(APPEND "${AEBUILD_INFO_DIR}" "BuildTarget==${_arg_NAME_OF_TARGET}_lib\n") 
    

    if(((${_arg_ONLY_CREATE_LIBRARY} STREQUAL 0  )))#  or NOT DEFINED  ONLY_CREATE_LIBRARY


         #add_bsp_based_library(
	#NAME ${_arg_NAME_OF_TARGET}_conf 
	#SOURCES         
    #) 


         add_bsp_based_executable(
	        NAME ${_arg_NAME_OF_TARGET}
	        SOURCES ${FULL_PATH_TO_TARGET}/main.cpp ${SRCS_TO_USER_CONFIG_FILES}  
                            ${EXE_USER_CONFIG_FILES}
    ${FULL_PATH_TO_TARGET}/AEObjects.h 
    #${FULL_PATH_TO_TARGET}/include/LoopObjeect1Test.h 
	        GENERATE_BIN
	        GENERATE_MAP) 


    file(APPEND "${AEBUILD_INFO_DIR}" "BuildTarget==${_arg_NAME_OF_TARGET}\n") 

                if(${INCLUDE_HAL} STREQUAL "TRUE")
    target_link_libraries(${_arg_NAME_OF_TARGET}  PUBLIC  AEHalLib  )  
    target_include_directories(AEHalLib PUBLIC "${FULL_PATH_TO_TARGET}/conf")
    endif()
    
            #target_link_libraries(${_arg_NAME_OF_TARGET}_lib PUBLIC  ${_arg_NAME_OF_TARGET}_conf)  
            target_link_libraries(${_arg_NAME_OF_TARGET} PUBLIC  ${_arg_NAME_OF_TARGET}_lib)  
            target_include_directories(${_arg_NAME_OF_TARGET} PUBLIC "${FULL_PATH_TO_TARGET}/include")
            target_include_directories(${_arg_NAME_OF_TARGET} PUBLIC "${FULL_PATH_TO_TARGET}/conf")
            target_include_directories(${_arg_NAME_OF_TARGET}_lib  PUBLIC "${FULL_PATH_TO_TARGET}/include")
            target_include_directories(${_arg_NAME_OF_TARGET}_lib  PUBLIC "${FULL_PATH_TO_TARGET}")
            target_include_directories(${_arg_NAME_OF_TARGET}_lib PUBLIC "${FULL_PATH_TO_TARGET}/conf")


            foreach(integtest  ${_arg_LIST_OF_TESTS})
	            AEintegrationTest_create_test(
	            TEST_NAME ${integtest} 
	            FOR_USER_CONFIG_GROUP  Test_Group1)  

               AEintegrationTest_add_test(
               FOR_TARGET ${_arg_NAME_OF_TARGET}  
               All_TEST_NAMES  ${_arg_LIST_OF_TESTS} )
             endforeach()    

	 endif()      
     foreach(tar ${_arg_LibrariesToLinkTo}) 
                 target_link_libraries(${_arg_NAME_OF_TARGET}_lib PUBLIC  ${tar})  
            endforeach() 

    #if the hal is included, add this library
    if(${INCLUDE_HAL} STREQUAL "TRUE")
    target_link_libraries(${_arg_NAME_OF_TARGET}_lib PUBLIC  AEHalLib  )  
    endif()

		#Always do this for BSP targets. I dont really understand why yet you need this
	target_include_directories(BSP PUBLIC "${FULL_PATH_TO_TARGET}/conf") 


else()

	 add_executable( ${_arg_NAME_OF_TARGET} 
		 main.cpp 
		${SRCS_TO_USER_CONFIG_FILES}
		) 


		target_include_directories(AECoreLib PUBLIC "${FULL_PATH_TO_TARGET}/conf")

endif()


#target_include_directories(${_arg_NAME_OF_TARGET}_lib PUBLIC "${FULL_PATH_TO_TARGET}/include")
#target_include_directories(${_arg_NAME_OF_TARGET}_lib PUBLIC "${FULL_PATH_TO_TARGET}/src")
	 



	#AEintegrationTest_create_test(
	#TEST_NAME defaultTest 
	#FOR_USER_CONFIG_GROUP  Test_Group1)  
   #AEintegrationTest_add_test(
   #FOR_TARGET AECoreTestEXE 
   #All_TEST_NAMES  defaultTest)


#target_link_libraries(${_arg_NAME_OF_TARGET}  PUBLIC  AECoreLib)    

#put all libraries this target links to 



Set_Sources_in_SourceGroup(
NAMEOFGROUP user_config_files
LISTOFSOURCES ${EXE_USER_CONFIG_FILES})

Set_Sources_in_SourceGroup(
NAMEOFGROUP target_sources
LISTOFSOURCES ${TARGET_SRCS})
#
    Set_Sources_in_SourceGroup(
NAMEOFGROUP target_headers
LISTOFSOURCES ${TARGET_HEADERS})
 


endif()

endmacro()





macro(_CREATE_AEOBJECTS_FILE) 
Generate_File_Using_Cgen_IN(
INPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/GeneratedFiles
OUTPUT_DIRECTORY ${FULL_PATH_TO_TARGET}
INPUT_FILE_NAME AEObjects
OUTPUT_FILE_NAME AEObjects
OUTPUT_FILE_EXTENSION .h
    )
endmacro()









#########################
#generate cgen macro2 command in the directory specified
#MACRO2_COMMAND: the macro2 command you want to use.
#WORKINGDIRECTORY the directory to put the generated file

######################### 
function(Generate_Macro2_Using_Cgen )
    set(options)
    set(oneValueArgs WORKINGDIRECTORY MACRO2_COMMAND)
    set(multiValueArgs)
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

        
    #run cgen macro in this directory to generate the cmake generated file
    execute_process(COMMAND  cgen macro2 ${_arg_MACRO2_COMMAND}
            WORKING_DIRECTORY ${_arg_WORKINGDIRECTORY}
            OUTPUT_VARIABLE outVar 
            ERROR_VARIABLE errorVar)
              
    message("Ran macro2  ${_arg_MACRO2_COMMAND}  in directory ${_arg_WORKINGDIRECTORY}")         
    message("outVar: ${outVar}")         
    message("errorVar: ${errorVar}")         

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
# generate the build file that will build all targets in proper order
#########################
macro(Generate_AEBuildFile)
execute_process(COMMAND cgen aebuild
            WORKING_DIRECTORY ${CODEGENGUI_PATH}
            OUTPUT_VARIABLE outVar 
            ERROR_VARIABLE errorVar)
			
			message("outVar: ${outVar}")
			message("errorVar: ${errorVar}")
endmacro()







#########################
#generate a cgen macro file given a .in file located in the GeneratedFiles folder
#INPUT_FILE_NAME: the .in file name in the GeneratedFiles folder that will be used to generate the file
#OUTPUT_FILE_NAME: the name of the file outputted. (just name without extension not including path )
#OUTPUT_FILE_EXTENSION: extension of output file
#OUTPUT_DIRECTORY the directory to put the generated file 
#INPUT_DIRECTORY the directory that your inpur cgen file is in. make sure that the file is of extension .cgenM.in
function(Generate_File_Using_Cgen_IN)
    set(options)
    set(oneValueArgs INPUT_DIRECTORY OUTPUT_DIRECTORY INPUT_FILE_NAME OUTPUT_FILE_NAME OUTPUT_FILE_EXTENSION
        Macro1 Macro2 Macro3 Macro4 Macro5 Macro6 Macro7 Macro8 Macro9 Macro10
        Macro11 Macro12 Macro13 Macro14 Macro15 Macro16 Macro17 Macro18 Macro19 Macro20
        Macro21 Macro22 Macro23 Macro24 Macro25 Macro26 Macro27 Macro28 Macro29 Macro30
        Macro31 Macro32 Macro33 Macro34 Macro35 Macro36 Macro37 Macro38 Macro39 Macro40
        Macro41 Macro42 Macro43 Macro44 Macro45 Macro46 Macro47 Macro48 Macro49 Macro50
        LoopIncrement1 LoopIncrement2 LoopIncrement3 LoopIncrement4 LoopIncrement5
        LoopIncrement6 LoopIncrement7 LoopIncrement8 LoopIncrement9 LoopIncrement10
        )
    set(multiValueArgs)
    cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

     
    #if generated file does not exist yet, create it
    #if(NOT EXISTS "${_arg_WORKINGDIRECTORY}/${_arg_OUTPUT_FILE_NAME}.${OUTPUT_FILE_EXTENSION}")
        #file(WRITE "${_arg_WORKINGDIRECTORY}/${_arg_OUTPUT_FILE_NAME}.${OUTPUT_FILE_EXTENSION}" "newfile")
        #ctest_sleep(5)
    #endif()
    message("_arg_OUTPUT_FILE_EXTENSION    ${_arg_OUTPUT_FILE_EXTENSION}")
     

    if(${_arg_OUTPUT_FILE_EXTENSION} STREQUAL "xml")
        set(COMMENT_CGEN "<!--")
        set(COMMENT_CGEN_END "-->")
    elseif(${_arg_OUTPUT_FILE_EXTENSION} STREQUAL "cmake")
        set(COMMENT_CGEN "#")
        set(COMMENT_CGEN_END "")
    else()
        set(COMMENT_CGEN "//")
        set(COMMENT_CGEN_END "")
    endif()

    #first make sure the input file even exists. if not, dont do anything
    if (NOT EXISTS ${_arg_INPUT_DIRECTORY}/${_arg_INPUT_FILE_NAME}.in)
        message(WARNING "HADI: the input file ${_arg_INPUT_DIRECTORY}/${_arg_INPUT_FILE_NAME}.in  did not exist when
                attempting to cgen generate macro.")
        return()
    endif ()

    #take the file and append the required header stuff for cgen. You'll then need to generate an intermediary file
    # so to not disturb the original configure .in file.
    File(READ ${_arg_INPUT_DIRECTORY}/${_arg_INPUT_FILE_NAME}.in CONTENTS_OF_FILE)
    set(CONTENTS_OF_FILE1
"##Macro1 @_arg_Macro1@
##Macro2 @_arg_Macro2@
##Macro3 @_arg_Macro3@
##Macro4 @_arg_Macro4@
##Macro5 @_arg_Macro5@
##Macro6 @_arg_Macro6@
##Macro7 @_arg_Macro7@
##Macro8 @_arg_Macro8@
##Macro9 @_arg_Macro9@
##Macro10 @_arg_Macro10@
##Macro11 @_arg_Macro11@
##Macro12 @_arg_Macro12@
##Macro13 @_arg_Macro13@
##Macro14 @_arg_Macro14@
##Macro15 @_arg_Macro15@
##Macro16 @_arg_Macro16@
##Macro17 @_arg_Macro17@
##Macro18 @_arg_Macro18@
##Macro19 @_arg_Macro19@
##Macro20 @_arg_Macro20@
##Macro21 @_arg_Macro21@
##Macro22 @_arg_Macro22@
##Macro23 @_arg_Macro23@
##Macro24 @_arg_Macro24@
##Macro25 @_arg_Macro25@
##Macro26 @_arg_Macro26@
##Macro27 @_arg_Macro27@
##Macro28 @_arg_Macro28@
##Macro29 @_arg_Macro29@
##Macro30 @_arg_Macro30@
##Macro31 @_arg_Macro31@
##Macro32 @_arg_Macro32@
##Macro33 @_arg_Macro33@
##Macro34 @_arg_Macro34@
##Macro35 @_arg_Macro35@
##Macro36 @_arg_Macro36@
##Macro37 @_arg_Macro37@
##Macro38 @_arg_Macro38@
##Macro39 @_arg_Macro39@
##Macro40 @_arg_Macro40@
##Macro41 @_arg_Macro41@
##Macro42 @_arg_Macro42@
##Macro43 @_arg_Macro43@
##Macro44 @_arg_Macro44@
##Macro45 @_arg_Macro45@
##Macro46 @_arg_Macro46@
##Macro47 @_arg_Macro47@
##Macro48 @_arg_Macro48@
##Macro49 @_arg_Macro49@
##Macro50 @_arg_Macro50@
##LoopIncrement1 @_arg_LoopIncrement1@
##LoopIncrement2 @_arg_LoopIncrement2@
##LoopIncrement3 @_arg_LoopIncrement3@
##LoopIncrement4 @_arg_LoopIncrement4@
##LoopIncrement5 @_arg_LoopIncrement5@
##LoopIncrement6 @_arg_LoopIncrement6@
##LoopIncrement7 @_arg_LoopIncrement7@
##LoopIncrement8 @_arg_LoopIncrement8@
##LoopIncrement9 @_arg_LoopIncrement9@
##LoopIncrement10 @_arg_LoopIncrement10@
##ToFile @_arg_OUTPUT_FILE_NAME@@_arg_OUTPUT_FILE_EXTENSION@")
set(CONTENTS_OF_FILE "${CONTENTS_OF_FILE1}\n${CONTENTS_OF_FILE}")


    File(WRITE ${_arg_INPUT_DIRECTORY}/${_arg_INPUT_FILE_NAME}.cgenM.in "${CONTENTS_OF_FILE}")

    #generate the file
    configure_file(${_arg_INPUT_DIRECTORY}/${_arg_INPUT_FILE_NAME}.cgenM.in
            ${_arg_OUTPUT_DIRECTORY}/${_arg_OUTPUT_FILE_NAME}.cgenM @ONLY)



set(USERNAME $ENV{USER})
set(errorVar)
    message("running cgen macro at directory ${_arg_OUTPUT_DIRECTORY}")

	if (WIN32)
	    execute_process(COMMAND cgen macro
            WORKING_DIRECTORY ${_arg_OUTPUT_DIRECTORY}
            OUTPUT_VARIABLE outVar 
            ERROR_VARIABLE errorVar)
			
			message("outVar: ${outVar}")
			message("errorVar: ${errorVar}")
	else()
		    execute_process(COMMAND  cgen macro
            WORKING_DIRECTORY ${_arg_OUTPUT_DIRECTORY}
            OUTPUT_VARIABLE outVar 
            ERROR_VARIABLE errorVar)
			
			message("outVar: ${outVar}")
			message("errorVar: ${errorVar}") 
	endif()

    #run cgen macro in this directory to generate the cmake generated file

             
if(NOT EXISTS "${_arg_OUTPUT_DIRECTORY}/${_arg_OUTPUT_FILE_NAME}.${_arg_OUTPUT_FILE_EXTENSION}")

	 if (WIN32)
	     execute_process(COMMAND  cgen macro
             WORKING_DIRECTORY ${_arg_OUTPUT_DIRECTORY}
             OUTPUT_VARIABLE outVar 
             ERROR_VARIABLE errorVar)
			
			 message("outVar: ${outVar}")
			 message("errorVar: ${errorVar}")
	 else()
		     execute_process(COMMAND  cgen macro
             WORKING_DIRECTORY ${_arg_OUTPUT_DIRECTORY}
             OUTPUT_VARIABLE outVar 
             ERROR_VARIABLE errorVar)
			
			 message("outVar: ${outVar}")
			 message("errorVar: ${errorVar}") 
	 endif()

endif()


  if(errorVar STREQUAL "")
   else()
   message(FATAL_ERROR "HADI: cgen gave an error!: it is for file ${_arg_OUTPUT_DIRECTORY}/${_arg_OUTPUT_FILE_NAME} \n of error message ${errorVar}")
   endif()

    #remove that cgen file so that it does not get called again with every execution of cgen in that directory
    file(REMOVE  ${_arg_OUTPUT_DIRECTORY}/${_arg_OUTPUT_FILE_NAME}.cgenM)


endfunction() 


