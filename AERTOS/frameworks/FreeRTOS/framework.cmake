if(TRUE)
    if(NOT DEFINED BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap)
        set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap "heap_4")
        set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap "${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap}" PARENT_SCOPE)
    endif()

    if(NOT DEFINED BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore)
        set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore "CM3")
        set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore "${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" PARENT_SCOPE)
    endif()

    if(NOT DEFINED BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.cmsis)
        set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.cmsis "CMSIS_RTOS")
        set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.cmsis "${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.cmsis}" PARENT_SCOPE)
    endif()

    set(BSP_CONFIGURATION_com.sysprogs.rtos_type "com.sysprogs.freertos")
    set(BSP_CONFIGURATION_com.sysprogs.rtos_type "${BSP_CONFIGURATION_com.sysprogs.rtos_type}" PARENT_SCOPE)
    set(_sources
        "${FRAMEWORK_ROOT}/croutine.c"
        "${FRAMEWORK_ROOT}/event_groups.c"
        "${FRAMEWORK_ROOT}/History.txt"
        "${FRAMEWORK_ROOT}/list.c"
        "${FRAMEWORK_ROOT}/queue.c"
        "${FRAMEWORK_ROOT}/readme.txt"
        "${FRAMEWORK_ROOT}/stream_buffer.c"
        "${FRAMEWORK_ROOT}/st_readme.txt"
        "${FRAMEWORK_ROOT}/tasks.c"
        "${FRAMEWORK_ROOT}/timers.c"
        "${FRAMEWORK_ROOT}/include/atomic.h"
        "${FRAMEWORK_ROOT}/include/croutine.h"
        "${FRAMEWORK_ROOT}/include/deprecated_definitions.h"
        "${FRAMEWORK_ROOT}/include/event_groups.h"
        "${FRAMEWORK_ROOT}/include/FreeRTOS.h"
        "${FRAMEWORK_ROOT}/include/list.h"
        "${FRAMEWORK_ROOT}/include/message_buffer.h"
        "${FRAMEWORK_ROOT}/include/mpu_prototypes.h"
        "${FRAMEWORK_ROOT}/include/mpu_wrappers.h"
        "${FRAMEWORK_ROOT}/include/portable.h"
        "${FRAMEWORK_ROOT}/include/projdefs.h"
        "${FRAMEWORK_ROOT}/include/queue.h"
        "${FRAMEWORK_ROOT}/include/semphr.h"
        "${FRAMEWORK_ROOT}/include/StackMacros.h"
        "${FRAMEWORK_ROOT}/include/stack_macros.h"
        "${FRAMEWORK_ROOT}/include/stream_buffer.h"
        "${FRAMEWORK_ROOT}/include/task.h"
        "${FRAMEWORK_ROOT}/include/timers.h")
    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.cmsis}" STREQUAL "CMSIS_RTOS")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/CMSIS_RTOS/cmsis_os.c" "${FRAMEWORK_ROOT}/CMSIS_RTOS/cmsis_os.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.cmsis}" STREQUAL "CMSIS_RTOS_V2")
        set(_sources ${_sources}
            "${FRAMEWORK_ROOT}/CMSIS_RTOS_V2/cmsis_os2.c"
            "${FRAMEWORK_ROOT}/CMSIS_RTOS_V2/cmsis_os.h"
            "${FRAMEWORK_ROOT}/CMSIS_RTOS_V2/cmsis_os2.h"
            "${FRAMEWORK_ROOT}/CMSIS_RTOS_V2/freertos_mpool.h"
            "${FRAMEWORK_ROOT}/CMSIS_RTOS_V2/freertos_os2.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM0")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM0/port.c" "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM0/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM23/non_secure")
        set(_sources ${_sources}
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/non_secure/port.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/non_secure/portasm.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/non_secure/portasm.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/non_secure/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM23/secure")
        set(_sources ${_sources}
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/secure/secure_context.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/secure/secure_context_port.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/secure/secure_heap.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/secure/secure_init.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/secure/secure_context.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/secure/secure_heap.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/secure/secure_init.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23/secure/secure_port_macros.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM23_NTZ/non_secure")
        set(_sources ${_sources}
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23_NTZ/non_secure/port.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23_NTZ/non_secure/portasm.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23_NTZ/non_secure/portasm.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM23_NTZ/non_secure/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM3")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM3/port.c" "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM3/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM33/non_secure")
        set(_sources ${_sources}
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/non_secure/port.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/non_secure/portasm.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/non_secure/portasm.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/non_secure/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM33/secure")
        set(_sources ${_sources}
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/secure/secure_context.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/secure/secure_context_port.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/secure/secure_heap.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/secure/secure_init.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/secure/secure_context.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/secure/secure_heap.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/secure/secure_init.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33/secure/secure_port_macros.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM33_NTZ/non_secure")
        set(_sources ${_sources}
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33_NTZ/non_secure/port.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.h"
            "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM33_NTZ/non_secure/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM3_MPU")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM3_MPU/port.c" "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM3_MPU/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM4F")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM4F/port.c" "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM4F/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM4_MPU")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM4_MPU/port.c" "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM4_MPU/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM7/r0p1")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM7/ReadMe.txt" "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM7/r0p1/port.c" "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM7/r0p1/portmacro.h")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "CM7_MPU/r0p1")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM7_MPU/ReadMe.txt" "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM7_MPU/r0p1/port.c" "${FRAMEWORK_ROOT}/portable/GCC/ARM_CM7_MPU/r0p1/portmacro.h")
    endif()

    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "MSVC")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/MSVC-MingW/port.c" "${FRAMEWORK_ROOT}/portable/MSVC-MingW/portmacro.h" )
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap}" STREQUAL "heap_1")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/MemMang/heap_1.c")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap}" STREQUAL "heap_2")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/MemMang/heap_2.c")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap}" STREQUAL "heap_3")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/MemMang/heap_3.c")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap}" STREQUAL "heap_4")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/MemMang/heap_4.c")
    endif()


    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.heap}" STREQUAL "heap_5")
        set(_sources ${_sources} "${FRAMEWORK_ROOT}/portable/MemMang/heap_5.c")
    endif()


    set(_includes
        "${FRAMEWORK_ROOT}/${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.cmsis}"
        "${FRAMEWORK_ROOT}/include"
        "${FRAMEWORK_ROOT}"
        "${FRAMEWORK_ROOT}/portable/GCC/ARM_${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}")

    if("${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.freertos.portcore}" STREQUAL "MSVC")
       set(_includes ${_includes} "${FRAMEWORK_ROOT}/portable/MSVC-MingW")
    endif()

    set(_defines "USE_FREERTOS")
    set(_forced_includes)
    set(_prebuilt_libraries)
    create_bsp_framework_library_from_vars(StandaloneEFP "com.sysprogs.arm.stm32.freertos" StandaloneEFP_freertos "FreeRTOS" "FreeRTOS")
    set(_framework_libraries ${_framework_libraries} "${_created_library}")
endif()

set(_core_includes "${_core_includes}" PARENT_SCOPE)
set(_core_defines "${_core_defines}" PARENT_SCOPE)
set(_core_forced_includes "${_core_forced_includes}" PARENT_SCOPE)
set(_framework_libraries "${_framework_libraries}" PARENT_SCOPE)
