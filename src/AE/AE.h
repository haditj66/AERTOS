#pragma once



//DONT PUT #include AEUtils.H HERE. IT WONT WORK!

//! [Adding a resource]
 
#include "AEConfig.h" 

//! [Adding a resource]



//TODO: the bottom should not be configured and should maybe be moved to another lcoation?
//for concactenating the value of two macros
#define M_CONC(A, B) M_CONC_(A, B)
#define M_CONC_(A, B) A##B
//event names for enums
#define Event1_Evt M_CONC(Event1,_Evt) 
#define Event2_Evt M_CONC(Event2,_Evt) 
#define Event3_Evt M_CONC(Event3,_Evt) 
#define Event4_Evt M_CONC(Event4,_Evt) 
#define Event5_Evt M_CONC(Event5,_Evt) 
#define Event6_Evt M_CONC(Event6,_Evt) 


//define all signals events used in the project here. ----------------------------
enum ProjectEventSignals {

#if Event1Size > 0
	Event1_Evt = 0,
#endif
#if Event2Size > 0
	Event2_Evt,
#endif
#if Event3Size > 0
	Event3_Evt,
#endif
#if Event4Size > 0
	Event4_Evt,
#endif
#if Event5Size > 0
	Event5_Evt,
#endif
#if Event6Size > 0
	Event6_Evt,
#endif 
	MAX_NumOfEvents,

	//place your signals here.
#if Signal1 != 1000
	Signal1,
#endif 
#if Signal2 != 1000
	Signal2,
#endif 
#if Signal3 != 1000
	Signal3,
#endif 
#if Signal4 != 1000
	Signal4,
#endif 
#if Signal5 != 1000
	Signal5,
#endif 
#if Signal6 != 1000
	Signal6,
#endif 
#if Signal7 != 1000
	Signal7,
#endif 

	_MAX_NumOfAllEvents,
	//the following events are events used ONLY by fsms. they are not stored in the event subscribers buffer as they are always posted
	// directly to an AOfsm and never published. 
	Enter_Sig,
	Exit_Sig,
	Update_Sig,
	ActivateFSM_Sig,
	DeActivateFSM_Sig

};

#define NUMOFEVENTS MAX_NumOfEvents
#define MAX_NumOfAllEvents _MAX_NumOfAllEvents //-1 it should be minus one however that "MAX_NumOfEvents" in the enum adds one more place to the enum. this means that I will have one empty slot in the EventSubscribers[evtId][AOID]  array at the evtId = MAX_NumOfEvents.


#ifndef configAE_USE_TDUs_AsService
#define configAE_USE_TDUs_AsService 0
#endif

#ifndef configAE_USE_U_AsService
#define configAE_USE_U_AsService 0
#endif

#ifndef configAE_USE_DDSM_AsService
#define configAE_USE_DDSM_AsService 0
#endif

#ifndef AEconfigUSE_TRACE_FACILITY
#define AEconfigUSE_TRACE_FACILITY 0
#endif 

  
#ifndef AEINCLUDE_eTaskGetState
#define AEINCLUDE_eTaskGetState 1
#endif 

#ifndef MAXNUM_OF_SUBSCRIBERS_To_A_SPB
#define MAXNUM_OF_SUBSCRIBERS_To_A_SPB 2
#endif

#ifndef MAXNUM_OF_AE_SUBSCRIPTIONS_To_SPBs
#define MAXNUM_OF_AE_SUBSCRIPTIONS_To_SPBs 3
#endif

#ifndef MAXNUM_OF_TOTAL_SPB_SUBSCRIPTIONS
#define MAXNUM_OF_TOTAL_SPB_SUBSCRIPTIONS 5
#endif

#ifndef MaxNumOfAELoops
#define MaxNumOfAELoops 1
#endif 

#ifndef MAXSPB_CHAIN_POOLSIZE
#define MAXSPB_CHAIN_POOLSIZE 4
#endif

#ifndef MaxAELoopsPerClock 
#define MaxAELoopsPerClock 3
#endif


#ifndef MaxNumOfGPIOPinsToUse
#define MaxNumOfGPIOPinsToUse 25
#endif


#ifndef Event1
#define Event1 AENULLEvent
#define Event1Size 0
#endif
#ifndef Event2
#define Event2 AENULLEvent
#define Event2Size 0
#endif
#ifndef Event3
#define Event3 AENULLEvent
#define Event3Size 0
#endif
#ifndef Event4
#define Event4 AENULLEvent
#define Event4Size 0
#endif
#ifndef Event5
#define Event5 AENULLEvent
#define Event5Size 0
#endif


 