
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
        message("${_src_dir}/${_src}")
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
#Add a test to Target you choose. The test will be placed 
#in directory ${TestsForTarget}_Tests with file names ${NameOfTestTarget}.cpp
#TestsForTarget: the target that these tests are meant for. for example AECoreLib
#########################
function(create_tests_for_target) 
set(options)
set(oneValueArgs TestsForTarget NameOfTestTarget ForUserConfigNum )
set(multiValueArgs LISTOF_EXTRA_SOURCES) 
cmake_parse_arguments(_arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

if(${TestGroups} STREQUAL  "Test_Group${_arg_ForUserConfigNum}")	 

set(PathToConf  "${CMAKE_SOURCE_DIR}/test/conf_group${_arg_ForUserConfigNum}")
 set(SRCsForTestsUserConf  	
  "${PathToConf}/AEConfig.h"
  "${PathToConf}/UserBSPConfig.cpp")
 #"${CMAKE_CURRENT_SOURCE_DIR}/${_arg_TestsForTarget}_Tests/conf/AEConfig.h"
		#"${CMAKE_CURRENT_SOURCE_DIR}/${_arg_TestsForTarget}_Tests/conf/UserBSPConfig.cpp")
          
 add_bsp_based_executable(NAME ${_arg_NameOfTestTarget}
	SOURCES
         ${_arg_LISTOF_EXTRA_SOURCES}
		 ${SRCsForTestsUserConf}
		"${CMAKE_CURRENT_SOURCE_DIR}/${_arg_TestsForTarget}_Tests/${_arg_NameOfTestTarget}.cpp"  
		"${CMAKE_SOURCE_DIR}/test/mainUnitTest.cpp"
	GENERATE_BIN
	GENERATE_MAP
	BUILD_UNIT_TESTS)
#target_include_directories(BSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${_arg_TestsForTarget}_Tests/conf")
target_include_directories(BSP PUBLIC "${PathToConf}")
target_include_directories(${_arg_NameOfTestTarget}  PUBLIC "${PathToConf}")

target_include_directories(${_arg_NameOfTestTarget}  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

Set_Sources_in_SourceGroup(NAMEOFGROUP "UserAEConf" LISTOFSOURCES  ${SRCsForTestsUserConf})

target_link_libraries(${_arg_NameOfTestTarget} PUBLIC  BSP)   
target_link_libraries(${_arg_NameOfTestTarget} PUBLIC  ${_arg_TestsForTarget})    
target_compile_definitions(${_arg_NameOfTestTarget} PRIVATE GOOGLE_TESTING)

endif()

endfunction()