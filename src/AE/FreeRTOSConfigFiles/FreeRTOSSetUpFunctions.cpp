
#include  "FreeRTOSSetUpFunctions.h"
#include "FreeRTOS.h"
#include <stdio.h>
#include <task.h>
 

#include "AEUtils.h"



#ifdef SWIL_HWIL_DRIVEN__SWIL
	
#define mainREGION_1_SIZE	8201
#define mainREGION_2_SIZE	29905
#define mainREGION_3_SIZE	7607
	
void  prvInitialiseHeap(void)
{
	/* The Windows demo could create one large heap region, in which case it would
	be appropriate to use heap_4.  However, purely for demonstration purposes,
	heap_5 is used instead, so start by defining some heap regions.  No
	initialisation is required when any other heap implementation is used.  See
	http://www.freertos.org/a00111.html for more information.

	The xHeapRegions structure requires the regions to be defined in start address
	order, so this just creates one big array, then populates the structure with
	offsets into the array - with gaps in between and messy alignment just for test
	purposes. */
	static uint8_t ucHeap[configTOTAL_HEAP_SIZE];
	volatile uint32_t ulAdditionalOffset = 19; /* Just to prevent 'condition is always true' warnings in configASSERT(). */
	const HeapRegion_t xHeapRegions[] =
	{
		/* Start address with dummy offsets						Size */
		{ ucHeap + 1, mainREGION_1_SIZE },
		{ ucHeap + 15 + mainREGION_1_SIZE, mainREGION_2_SIZE },
		{ ucHeap + 19 + mainREGION_1_SIZE + mainREGION_2_SIZE, mainREGION_3_SIZE },
		{ NULL, 0 }
	};

	/* Sanity check that the sizes and offsets defined actually fit into the
	array. */
	configASSERT((ulAdditionalOffset + mainREGION_1_SIZE + mainREGION_2_SIZE + mainREGION_3_SIZE) < configTOTAL_HEAP_SIZE);

	/* Prevent compiler warnings when configASSERT() is not defined. */
	(void)ulAdditionalOffset;

	vPortDefineHeapRegions(xHeapRegions);
}
	
	
#endif 
 
/*
#if SWIL_HWIL_DRIVEN == SWIL
extern void RTOSInit()
{ prvInitialiseHeap();}
#else
extern void RTOSInit()
{}
#endif 
*/
 	   

//extern void AEPrint(char* msg);
 


#ifdef __cplusplus 
extern "C" {
#endif 
	




	/*
	* Writes trace data to a disk file when the trace recording is stopped.
	* This function will simply overwrite any trace files that already exist.
	*/
	//static void prvSaveTraceFile( void );

	/*-----------------------------------------------------------*/

	/* When configSUPPORT_STATIC_ALLOCATION is set to 1 the application writer can
	use a callback function to optionally provide the memory required by the idle
	and timer tasks.  This is the stack that will be used by the timer task.  It is
	declared here, as a global, so it can be checked by a test that is implemented
	in a different file. */
	StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

	/* Notes if the trace is running or not. */
	static BaseType_t xTraceRunning = pdTRUE;








	void vApplicationMallocFailedHook(void)
	{
		/* vApplicationMallocFailedHook() will only be called if
		configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
		function that will get called if a call to pvPortMalloc() fails.
		pvPortMalloc() is called internally by the kernel whenever a task, queue,
		timer or semaphore is created.  It is also called by various parts of the
		demo application.  If heap_1.c, heap_2.c or heap_4.c is being used, then the
		size of the	heap available to pvPortMalloc() is defined by
		configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the xPortGetFreeHeapSize()
		API function can be used to query the size of free heap space that remains
		(although it does not provide information on how the remaining heap might be
		fragmented).  See http://www.freertos.org/a00111.html for more
		information. */
		vAssertCalled(__LINE__, __FILE__);
	}
	/*-----------------------------------------------------------*/

	void vApplicationIdleHook(void)
	{
		/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
		to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
		task.  It is essential that code added to this hook function never attempts
		to block in any way (for example, call xQueueReceive() with a block time
		specified, or call vTaskDelay()).  If application tasks make use of the
		vTaskDelete() API function to delete themselves then it is also important
		that vApplicationIdleHook() is permitted to return to its calling function,
		because it is the responsibility of the idle task to clean up memory
		allocated by the kernel to any task that has since deleted itself. */

		/* Uncomment the following code to allow the trace to be stopped with any
		key press.  The code is commented out by default as the kbhit() function
		interferes with the run time behaviour. */
		/*
		if( _kbhit() != pdFALSE )
		{
		if( xTraceRunning == pdTRUE )
		{
		vTraceStop();
		prvSaveTraceFile();
		xTraceRunning = pdFALSE;
		}
		}
		*/



	}

	
	  
void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName)
	{
		static char msgFormattedstackoverflow[70];
		snprintf(msgFormattedstackoverflow, 70, "\n\nEXCEPTION STACK OVERFLOW: occured for task %s", pcTaskName);
 
		//AEPrint(msgFormattedstackoverflow);
		
		configASSERT(false);
	}
	
	
	

	void vApplicationTickHook(void)
	{


	}
	/*-----------------------------------------------------------*/

	void vApplicationDaemonTaskStartupHook(void)
	{
		/* This function will be called once only, when the daemon task starts to
		execute	(sometimes called the timer task).  This is useful if the
		application includes initialisation code that would benefit from executing
		after the scheduler has been started. */
	}
	/*-----------------------------------------------------------*/

	
	void vAssertCalled(unsigned long ulLine, const char * const pcFileName)
	{
		static BaseType_t xPrinted = pdFALSE;
 		volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

		/* Called if an assertion passed to configASSERT() fails.  See
		http://www.freertos.org/a00110.html#configASSERT for more information. */

		/* Parameters are not used. */
		(void)ulLine;
		(void)pcFileName; 
		
		
#ifdef SWIL_HWIL_DRIVEN__SWIL
		printf("ASSERT! Line %ld, file %s, GetLastError() %ld\r\n", ulLine, pcFileName, GetLastError());
#else
		AEPrint((char*)"config assertion failed at line %d \n", ulLine); 
		printf("ASSERT! Line %ld, file %s, GetLastError() %ld\r\n", ulLine, pcFileName, 0);
#endif



		taskENTER_CRITICAL();
		{
			/* Stop the trace recording. */
			if (xPrinted == pdFALSE)
			{
				xPrinted = pdTRUE;
				if (xTraceRunning == pdTRUE)
				{
					//vTraceStop();
					//prvSaveTraceFile();
				}
			}

			/* You can step out of this function to debug the assertion by using
			the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
			value. */
			while (ulSetToNonZeroInDebuggerToContinue == 0)
			{
				//__asm { NOP };
				//__asm { NOP };
			}
		}
		taskEXIT_CRITICAL();
	}
	/*-----------------------------------------------------------*/
	/*
	static void prvSaveTraceFile( void )
	{
	FILE* pxOutputFile;

	fopen_s( &pxOutputFile, "Trace.dump", "wb");

	if( pxOutputFile != NULL )
	{
	fwrite( RecorderDataPtr, sizeof( RecorderDataType ), 1, pxOutputFile );
	fclose( pxOutputFile );
	printf( "\r\nTrace output saved to Trace.dump\r\n" );
	}
	else
	{
	printf( "\r\nFailed to create trace dump file\r\n" );
	}
	}*/
	/*-----------------------------------------------------------*/

 
	/*-----------------------------------------------------------*/

	/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
	implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
	used by the Idle task. */
	void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
	{
		/* If the buffers to be provided to the Idle task are declared inside this
		function then they must be declared static - otherwise they will be allocated on
		the stack and so not exists after this function exits. */
		static StaticTask_t xIdleTaskTCB;
		static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

		/* Pass out a pointer to the StaticTask_t structure in which the Idle task's
		state will be stored. */
		*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

		/* Pass out the array that will be used as the Idle task's stack. */
		*ppxIdleTaskStackBuffer = uxIdleTaskStack;

		/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
		Note that, as the array is necessarily of type StackType_t,
		configMINIMAL_STACK_SIZE is specified in words, not bytes. */
		*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	}
	/*-----------------------------------------------------------*/

	/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
	application must provide an implementation of vApplicationGetTimerTaskMemory()
	to provide the memory that is used by the Timer service task. */
	void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
	{
		/* If the buffers to be provided to the Timer task are declared inside this
		function then they must be declared static - otherwise they will be allocated on
		the stack and so not exists after this function exits. */


		static StaticTask_t xTimerTaskTCB;

		/* Pass out a pointer to the StaticTask_t structure in which the Timer
		task's state will be stored. */
		*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

		/* Pass out the array that will be used as the Timer task's stack. */
		*ppxTimerTaskStackBuffer = uxTimerTaskStack;

		/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
		Note that, as the array is necessarily of type StackType_t,
		configMINIMAL_STACK_SIZE is specified in words, not bytes. */
		*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
	}






#ifdef __cplusplus
}
#endif 

 