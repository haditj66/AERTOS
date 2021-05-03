//Board specific defines
#if (MCU_ARM_ARCHITECTURE == M4) || (MCU_ARM_ARCHITECTURE == M3)

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
#define configPRIO_BITS       		4        /* 15 priority levels */
#endif


#endif