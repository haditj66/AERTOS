
		set(FREERTOSROOT "C:/Users/Hadi/AppData/Local/VisualGDB/EmbeddedBSPs/arm-eabi/com.sysprogs.arm.stm32")
		set(_framework_libraries "")
 
        set(_sources
            "${FREERTOSROOT}/FreeRTOS/License/license.txt"
            "${FREERTOSROOT}/FreeRTOS/Source/croutine.c"
            "${FREERTOSROOT}/FreeRTOS/Source/event_groups.c"
            "${FREERTOSROOT}/FreeRTOS/Source/list.c"
            "${FREERTOSROOT}/FreeRTOS/Source/queue.c"
            "${FREERTOSROOT}/FreeRTOS/Source/readme.txt"
            "${FREERTOSROOT}/FreeRTOS/Source/stream_buffer.c"
            "${FREERTOSROOT}/FreeRTOS/Source/st_readme.txt"
            "${FREERTOSROOT}/FreeRTOS/Source/tasks.c"
            "${FREERTOSROOT}/FreeRTOS/Source/timers.c"
            "${FREERTOSROOT}/FreeRTOS/Source/include/croutine.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/deprecated_definitions.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/event_groups.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/FreeRTOS.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/list.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/message_buffer.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/mpu_prototypes.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/mpu_wrappers.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/portable.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/projdefs.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/queue.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/semphr.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/StackMacros.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/stack_macros.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/stream_buffer.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/task.h"
            "${FREERTOSROOT}/FreeRTOS/Source/include/timers.h" 
            #${FREERTOS_EXTRA_SRCS}
			#"${CMAKE_SOURCE_DIR}/src/AE/FreeRTOSConfig.h"  "${CMAKE_SOURCE_DIR}/FreeRTOSConfigFiles/FreeRTOSSetUpFunctions.h" "${CMAKE_SOURCE_DIR}/FreeRTOSConfigFiles/FreeRTOSSetUpFunctions.cpp" "${CMAKE_SOURCE_DIR}/FreeRTOSConfigFiles/BoardSpecificFreeRTOSDefines.h"
            )
      


            set(_sources ${_sources} "${FREERTOSROOT}/FreeRTOS/Source/portable/MSVC-MingW/port.c" "${FREERTOSROOT}/FreeRTOS/Source/portable/MSVC-MingW/portmacro.h") 
            set(_sources ${_sources} "${FREERTOSROOT}/FreeRTOS/Source/portable/MemMang/heap_5.c")



        set(_includes
            "${FREERTOSROOT}/FreeRTOS/Source/CMSIS_RTOS"
            "${FREERTOSROOT}/FreeRTOS/Source/Include" 
			"${FREERTOSROOT}/FreeRTOS/Source/Portable/MSVC-MingW"
			${FREERTOS_EXTRA_INCLUDES}
            )
        set(_defines "USE_FREERTOS")
        set(_forced_includes)
        set(BSP_ALIAS BSP)
       create_bsp_framework_library_from_vars(BSP "com.sysprogs.arm.stm32.freertos" com.sysprogs.arm.stm32.freertos "FreeRTOS" "FreeRTOS")
        set(_framework_libraries ${_framework_libraries} "${_created_library}")
        set(_all_includes ${_sources} ${_includes})
       
	   set(FREERTOS_INCLUDES ${_includes})
	   set(FREERTOS_DEFINES ${_defines})

        message("FREERTOS_INCLUDES------------------- ${FREERTOS_INCLUDES}")
