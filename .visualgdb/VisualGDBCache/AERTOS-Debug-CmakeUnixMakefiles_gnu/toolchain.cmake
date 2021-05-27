SET(CMAKE_SYSTEM_NAME Linux)
SET(VISUALGDB_TOOLCHAIN_TYPE Linux)
SET(VISUALGDB_TOOLCHAIN_SUBTYPE GCC)
SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")
SET(CMAKE_ASM_COMPILER "/usr/bin/g++")

if(EXISTS "$ENV{TOOLCHAIN_ROOT}/Qt/v5-CMake/Qt5Cross.cmake")
	include("$ENV{TOOLCHAIN_ROOT}/Qt/v5-CMake/Qt5Cross.cmake")
endif()

function (visualgdb_toolchain_load_default_configuration)
endfunction() #visualgdb_toolchain_load_default_configuration

function (visualgdb_toolchain_compute_flags)
endfunction() #visualgdb_toolchain_compute_flags



set (VISUALGDB_COMPONENT_LISTS_DIR "C:/Users/Hadi/AppData/Local/VisualGDB")
include ("C:/Program Files (x86)/Sysprogs/VisualGDB/CMake/embedded/root.cmake")
