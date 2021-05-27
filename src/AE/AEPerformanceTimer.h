#pragma once

#include "AE.h"
 
#include <cstdint>

#if (TOOLCHAIN_USED == arm_non_eabi_id )
typedef uint32_t PerfIntSize_t;
typedef uint32_t PerfElapsed_t;
#endif
#if (TOOLCHAIN_USED == mingw)
#include <sys\timeb.h> 
#include "sysinfoapi.h"
#include <chrono>
typedef std::chrono::time_point<std::chrono::steady_clock> PerfIntSize_t;
typedef long PerfElapsed_t;
#endif
#if (TOOLCHAIN_USED == gnu)
#include <chrono>
typedef std::chrono::time_point<std::chrono::steady_clock> PerfIntSize_t;
typedef long PerfElapsed_t;
#endif

class AEPerformanceTimer
{
	//only this function will create the instances of this class.
	friend void AE_Init(void);
	
public:
	 
	//this should not be accessed by the user as it will be used in a macro for entering and reentering
	bool _TimerRunningFromStart;
	bool _TimerRunningFromReEnter;

	PerfElapsed_t GetElapsedTimeInNanoSeconds();
	
#if SWIL_HWIL_DRIVEN == HWIL
	uint32_t GetElapsedTimeCPUCycles();
#endif
	

	
	void AEStart_Timer(); 

	void AEStop_Timer();

	
	
private:
	void _init() {_TimerRunningFromStart = false; _TimerRunningFromReEnter = false; }
	
#if SWIL_HWIL_DRIVEN == SWIL
	std::chrono::time_point<std::chrono::steady_clock>  start; 
	std::chrono::time_point<std::chrono::steady_clock>  end;
#endif
	
	
	PerfIntSize_t EndingPoint;
	PerfIntSize_t StartingPoint; 
	PerfElapsed_t ElapsedCycles; 
	uint32_t ClckFreq;
	
	AEPerformanceTimer();
	

};

