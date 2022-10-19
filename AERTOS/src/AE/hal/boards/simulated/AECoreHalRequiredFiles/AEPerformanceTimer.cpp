#include "AEPerformanceTimer.h"




AEPerformanceTimer::AEPerformanceTimer()
{  
}

void AEPerformanceTimer::AEStart_Timer()
{  
	StartingPoint = std::chrono::steady_clock::now();
}

void AEPerformanceTimer::AEStop_Timer()
{ 
	
	EndingPoint = std::chrono::steady_clock::now(); 
	ElapsedCycles = std::chrono::duration_cast<std::chrono::nanoseconds>(EndingPoint - StartingPoint).count();
 
} 
	
 

PerfElapsed_t AEPerformanceTimer::GetElapsedTimeInNanoSeconds()
{
	return  ElapsedCycles;
}