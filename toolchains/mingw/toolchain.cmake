SET(CMAKE_SYSTEM_NAME Windows)
SET(VISUALGDB_TOOLCHAIN_TYPE Windows)
SET(VISUALGDB_TOOLCHAIN_SUBTYPE GCC)
SET(CMAKE_C_COMPILER "${TOOLCHAIN_ROOT}/bin/gcc.exe")
SET(CMAKE_CXX_COMPILER "${TOOLCHAIN_ROOT}/bin/g++.exe")
SET(CMAKE_ASM_COMPILER "${TOOLCHAIN_ROOT}/bin/g++.exe")

if(EXISTS "$ENV{TOOLCHAIN_ROOT}/Qt/v5-CMake/Qt5Cross.cmake")
	include("$ENV{TOOLCHAIN_ROOT}/Qt/v5-CMake/Qt5Cross.cmake")
endif()

function (visualgdb_toolchain_load_default_configuration)
endfunction() #visualgdb_toolchain_load_default_configuration

function (visualgdb_toolchain_compute_flags)
endfunction() #visualgdb_toolchain_compute_flags

set(SYSPROG_PATH "C:/VisualGDBAllFiles/Sysprogs") #"C:/Program Files (x86)/Sysprogs")

set (VISUALGDB_COMPONENT_LISTS_DIR "C:/VisualGDBAllFiles/VisualGDB")#"C:/Users/Hadi/AppData/Local/VisualGDB")
include ("${SYSPROG_PATH}/VisualGDB/CMake/embedded/root.cmake")
