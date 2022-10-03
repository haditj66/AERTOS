if(TRUE)
    if(NOT DEFINED BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.ll_driver)
        set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.ll_driver "")
        set(BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.ll_driver "${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.ll_driver}" PARENT_SCOPE)
    endif()

    set(_sources
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_crc.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_dac.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_dma.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_dma2d.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_exti.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmpi2c.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_gpio.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_i2c.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_lptim.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_pwr.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rcc.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rng.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rtc.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_spi.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_tim.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usart.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_utils.c"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_bus.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_cortex.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_crc.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_dac.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_dma.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_dma2d.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_exti.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmc.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fmpi2c.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_fsmc.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_gpio.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_i2c.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_iwdg.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_lptim.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_pwr.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_rcc.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_rng.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_rtc.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_sdmmc.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_spi.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_system.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_tim.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usart.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_utils.h"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_wwdg.h")
    set(_includes
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc/Legacy"
        "${FRAMEWORK_ROOT}/STM32F4xx_HAL_Driver/Inc"
        "${FRAMEWORK_ROOT}/CMSIS_HAL/Device/ST/STM32F4xx/Include"
        "${FRAMEWORK_ROOT}/CMSIS_HAL/Core/Include"
        "${FRAMEWORK_ROOT}/CMSIS_HAL/Include")
    set(_defines "${BSP_CONFIGURATION_com.sysprogs.stm32.hal_device_family}" "${BSP_CONFIGURATION_com.sysprogs.bspoptions.stm32.ll_driver}")
    set(_forced_includes)
    set(_prebuilt_libraries)
    create_bsp_framework_library_from_vars(StandaloneEFP "com.sysprogs.arm.stm32.STM32F4_ll" StandaloneEFP_STM32F4_ll "STM32F4 Low-level Driver Library" "LL")
    set(_framework_libraries ${_framework_libraries} "${_created_library}")
endif()

set(_core_includes "${_core_includes}" PARENT_SCOPE)
set(_core_defines "${_core_defines}" PARENT_SCOPE)
set(_core_forced_includes "${_core_forced_includes}" PARENT_SCOPE)
set(_framework_libraries "${_framework_libraries}" PARENT_SCOPE)
