#pragma once





//prv intialize -----------------------------------------
#ifndef HARDWARE
//void  prvInitialiseHeap(void);
#endif
 
//extern void AEPrint(char* msg);


#ifdef HARDWARE



#ifdef __cplusplus
extern "C" {
#endif
	
	//void _Error_Handler(char *, int);

//#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif






#ifdef __cplusplus
extern "C" {
#endif 

	/*
	* Only the comprehensive demo uses application hook (callback) functions.  See
	* http://www.freertos.org/a00016.html for more information.
	*/
//	void vFullDemoTickHookFunction(void);
//	void vFullDemoIdleFunction(void);


	
	/*
	* This demo uses heap_5.c, so start by defining some heap regions.  It is not
	* necessary for this demo to use heap_5, as it could define one large heap
	* region.  Heap_5 is only used for test and example purposes.  See
	* http://www.freertos.org/a00111.html for an explanation.
	*/
	//static void  prvInitialiseHeap( void );

	/*
	* Prototypes for the standard FreeRTOS application hook (callback) functions
	* implemented within this file.  See http://www.freertos.org/a00016.html .
	*/
	//void vApplicationMallocFailedHook(void);
//	void vApplicationIdleHook(void); 
//	void vApplicationTickHook(void);
//	void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);
//	void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize);

	//void AssertCalled(unsigned long ulLine, const char * const pcFileName);
    //void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
#ifdef __cplusplus
}
#endif 
