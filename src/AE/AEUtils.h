#pragma once

#ifdef SIMULATION
#include <cstdint>				  
#endif // SIMULATION
 


#include "AE.h"
#include <string.h>
#include "AEPerformanceTimer.h"

#include "AEDefines.h"
 

#define PoolManager AEPoolManager<Event1, Event1Size, Event2, Event2Size, Event3, Event3Size, Event4, Event4Size, Event5, Event5Size>::getInstance()
#define PublishSubscribeManager AEPublishSubscribeManager::getInstance()












 







enum AEPriorities
{
	LowestPriority = AOPRIORITYLOWEST,
	MediumPriority = AOPRIORITYMEDIUM,
	HighestPriority = AOPRIORITYHIGHEST - 1 // -1 so to leave room to the actual highest priority that the AE uses
};





class AENullFSMUtility
{
public:
	template<class TBla>
	void SetExclusivePossessor(TBla*) {};
	uint16_t GetAO_ID() { return 0; };
};


class NULLPeripheral
{
public:
	static void* Instance;
	static void* getInstance() { return nullptr; };
	void initializePeripheral() {};

};

class AENullClass {
public:float operator()(float a) { return 0; };
	   void Initialize(float a) {};
	   float GetObservation() { return 1; };
	   float* GetOutputDataAddress() { return nullptr; };
};

class AENULLEvent
{
public:
	bool EvtId;
	bool EvtIdStatic;
#pragma warning( disable : 26495)
	AENULLEvent() {};
	void init(uint16_t evtId) {};
};

typedef	bool AENull;

//forward declaration
class AENullActionRequest;


template<typename TypeOfArgToCheck>
struct IsArrayChecker
{
	static const bool IsArgumentArray(TypeOfArgToCheck argToCheck);
};

template<typename TypeOfArgToCheck>
inline const bool IsArrayChecker< TypeOfArgToCheck>::IsArgumentArray(TypeOfArgToCheck argToCheck)
{
	return sizeof(TypeOfArgToCheck) != sizeof(argToCheck);
}

template<class TTypeToCopyFrom>
class ArrayCheckToMemCopy
{
public:
	static void AEMemcpy(void* dest, TTypeToCopyFrom source, uint32_t size);
private:
	static void AEMemcpyIMPL1(void* dest, TTypeToCopyFrom source, uint32_t size) { memcpy(dest, (void*)source, size); };
	static void AEMemcpyIMPL2(void* dest, TTypeToCopyFrom source, uint32_t size) { memcpy(dest, (void*)&source, size); };
};

/*
template<class TTypeToCopyFrom, uint32_t N>
class ArrayCheckToMemCopy<TTypeToCopyFrom[N]>
{
public:
	static void AEMemcpy(void* dest, TTypeToCopyFrom source, uint32_t size) { memcpy(dest, source, size); };
private:
	static void AEMemcpyIMPL1(void* dest, TTypeToCopyFrom source, uint32_t size) { memcpy(dest, (void*)source, size); };
	static void AEMemcpyIMPL2(void* dest, TTypeToCopyFrom source, uint32_t size) { memcpy(dest, (void*)&source, size); };
};
*/


template<class TTypeToCopyFrom>
inline void ArrayCheckToMemCopy<TTypeToCopyFrom>::AEMemcpy(void* dest, TTypeToCopyFrom source, uint32_t size) {

	memcpy(dest, source, size);
}

template<>
inline void ArrayCheckToMemCopy<const char*>::AEMemcpy(void* dest, const char * source, uint32_t size)
{
	memcpy(dest, &source, size);
}

template<>
inline void ArrayCheckToMemCopy<char*>::AEMemcpy(void* dest, char* source, uint32_t size)
{
	memcpy(dest, &source, size);
}
template<>
inline void ArrayCheckToMemCopy<uint8_t*>::AEMemcpy(void* dest, uint8_t* source, uint32_t size)
{
	memcpy(dest, &source, size);
}

template<>
inline void ArrayCheckToMemCopy<char>::AEMemcpy(void* dest, char source, uint32_t size)
{
	memcpy(dest, &source, size);
}



/*
template<>
inline void ArrayCheckToMemCopy<char>::AEMemcpy(void* dest, char source, uint32_t size)
{
	memcpy(dest, &source, size);
}*/
template<>
inline void ArrayCheckToMemCopy<float>::AEMemcpy(void* dest, float source, uint32_t size)
{
	memcpy(dest, &source, size);
}
template<>
inline void ArrayCheckToMemCopy<uint32_t>::AEMemcpy(void* dest, uint32_t source, uint32_t size)
{
	memcpy(dest, &source, size);
}
template<>
inline void ArrayCheckToMemCopy<uint16_t>::AEMemcpy(void* dest, uint16_t source, uint32_t size)
{
	memcpy(dest, &source, size);
}
template<>
inline void ArrayCheckToMemCopy<uint8_t>::AEMemcpy(void* dest, uint8_t source, uint32_t size)
{
	memcpy(dest, &source, size);
}
template<>
inline void ArrayCheckToMemCopy<bool>::AEMemcpy(void* dest, bool source, uint32_t size)
{
	memcpy(dest, &source, size);
}
template<>
inline void ArrayCheckToMemCopy<double>::AEMemcpy(void* dest, double source, uint32_t size)
{
	memcpy(dest, &source, size);
}
template<>
inline void ArrayCheckToMemCopy<int>::AEMemcpy(void* dest, int source, uint32_t size)
{
	memcpy(dest, &source, size);
}



template<typename TTypeToCheck1, typename TTypeToCheck2 >
struct TypeChecker_isSame
{

	static const bool value = false;
};

template<typename TTypeToCheck1>
struct TypeChecker_isSame<TTypeToCheck1, TTypeToCheck1>
{
	static const bool value = true;
};

struct TypeChecker
{
	template<class TTypeToCheck>
	static bool IsAENullActionRequest();
	template<class TTypeToCheck>
	static bool IsAENullFSMUtility();
	template<class TTypetoCheck>
	static bool IsAENull();
	template<class TTypetoCheck>
	static bool Isuint32_tPtr();
	template<class TTypetoCheck>
	static bool IsfloatPtr();
	template<class TTypetoCheck>
	static bool IsAEEventNullClass();
	template<class TTypetoCheck>
	static bool IsNULLPeripheral();
};

//specialization function to check if a template parameter passed was an AENull in order to not use __FUNCTION__ or RTTI

template<>
inline bool TypeChecker::IsAENullActionRequest<AENullActionRequest>()
{
	return true;
}
//if any other type 
template<class TTypetoCheck>
inline bool TypeChecker::IsAENullActionRequest()
{
	return false;
}

template<>
inline bool TypeChecker::IsAENullFSMUtility<AENullFSMUtility>()
{
	return true;
}
//if any other type 
template<class TTypetoCheck>
inline bool TypeChecker::IsAENullFSMUtility()
{
	return false;
}

template<>
inline bool TypeChecker::IsAEEventNullClass<AENULLEvent>()
{
	return true;
}
//if any other type 
template<class TTypetoCheck>
inline bool TypeChecker::IsAEEventNullClass()
{
	return false;
}

template<>
inline bool TypeChecker::IsAENull<AENull>()
{
	return true;
}
//if any other type 
template<class TTypetoCheck>
inline bool TypeChecker::IsAENull()
{
	return false;
}

template<>
inline bool TypeChecker::Isuint32_tPtr<uint32_t>()
{
	return true;
}
//if any other type 
template<class TTypetoCheck>
inline bool TypeChecker::Isuint32_tPtr()
{
	return false;
}

template<>
inline bool TypeChecker::IsfloatPtr<float>()
{
	return true;
}
//if any other type 
template<class TTypetoCheck>
inline bool TypeChecker::IsfloatPtr()
{
	return false;
}

template<>
inline bool TypeChecker::IsNULLPeripheral<NULLPeripheral>()
{
	return true;
}
//if any other type 
template<class TTypetoCheck>
inline bool TypeChecker::IsNULLPeripheral()
{
	return false;
}



template <class T>
	int numDigits(T number)
	{
		int digits = 0;
		if (number < 0) digits = 1;
		while (number) {
			number /= 10;
			digits++;
		}
		return digits;
	}






//AEPrint ------------------------------------------------


















#include <stdio.h>


void AEPrint(const char *pFormat, ...);

void AEFormatMsg(char* formattedBuffer, uint32_t sizeOfFormat, const char* msgToFormat, ...);
















#ifndef  IARBuild

/*
extern "C" {
void vAssertCalled(unsigned long ulLine, const char * const pcFileName)
{
AEPrint((char*)pcFileName, ulLine);
}
}
*/



#endif //   






//Converts milliseconds to the RTOS's tick
#define AE_Tick_To_Milli(millis)\
( TickType_t )(millis / (1000/AEconfigTICK_RATE_HZ));\
configASSERT((millis / (1000/AEconfigTICK_RATE_HZ)) > 0);




//#pragma warning( disable : WarningCode)
//// code with warning
//#pragma warning( pop ) 
////suppress warnigns
//#define AESUPRESS_WARNING_START(WarningCode) #pragma warning( push )
//#define AESUPRESS_WARNING_STOP(WarningCode)





//state typedefs   --------------------------------------

enum AETransitionType {
	TRANSITION = 0,
	UNHANDLED,
	DEACTIVE,
	ACTIVATE
};

enum AEFSMActiveTypeEnum {
	PAUSE_TO_ACTIVATE,
	RESET_TO_ACTIVATE
};


#if NUMOFEVENTS > (256-2) //the minus 2 is to account for the two enter and exit events

#define ENTEREVENT_Id	0xffff
#define EXITEVENT_Id	0xffff - 1
#else  
#define ENTEREVENT_Id	0xff
#define EXITEVENT_Id	0xff - 1
#endif

//macro to return a state transition

#define CastToStateFuncPtr(stateToTransitionTo) reinterpret_cast<TypeOfThisFSM::StateFuncPtr>(stateToTransitionTo);

#define TRANSITION_TOSTATE(stateToTransitionTo) \
thisFSM->StateToTransitionTo = CastToStateFuncPtr(stateToTransitionTo)\
transitionType = TRANSITION;

#define AE_EXIT() transitionType = DEACTIVE;

#define AE_CastEvent(TypeToCastTo) ((TypeToCastTo)evt->evt)






//macros -------------------------------------- 

 /*
//macro for template
#if MAXNUMBEROF_FILTERS == 1
#define TEMPLATEFOR_AESPBOUTPUT \
template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS, uint8_t NUMOFFILTERS, class TFilter1, uint32_t TheParameterNOTone1, bool isParameterNOToneInputSize1, uint32_t TheParameterNOTone2, bool isParameterNOToneInputSize2, uint32_t TheParameterNOTone3, bool isParameterNOToneInputSize3>
#define TEMPLATEFOR_AESPBOUTPARAMS OUTPUTSIZE, NUMOFINPUTSIGNALS, NUMOFFILTERS, TFilter1, TheParameterNOTone1, isParameterNOToneInputSize1, TheParameterNOTone2, isParameterNOToneInputSize2, TheParameterNOTone3, isParameterNOToneInputSize3
#endif
#if MAXNUMBEROF_FILTERS == 2
#define TEMPLATEFOR_AESPBOUTPUT \
template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS, uint8_t NUMOFFILTERS, class TFilter1,class TFilter2, uint32_t TheParameterNOTone1, bool isParameterNOToneInputSize1, uint32_t TheParameterNOTone2, bool isParameterNOToneInputSize2, uint32_t TheParameterNOTone3, bool isParameterNOToneInputSize3>
#define TEMPLATEFOR_AESPBOUTPARAMS OUTPUTSIZE, NUMOFINPUTSIGNALS, NUMOFFILTERS, TFilter1, TFilter2, TheParameterNOTone1, isParameterNOToneInputSize1, TheParameterNOTone2, isParameterNOToneInputSize2, TheParameterNOTone3, isParameterNOToneInputSize3
#endif
#if MAXNUMBEROF_FILTERS == 3
#define TEMPLATEFOR_AESPBOUTPUT \
template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS, uint8_t NUMOFFILTERS, class TFilter1,class TFilter2,class TFilter3, uint32_t TheParameterNOTone1, bool isParameterNOToneInputSize1, uint32_t TheParameterNOTone2, bool isParameterNOToneInputSize2, uint32_t TheParameterNOTone3, bool isParameterNOToneInputSize3>
#define TEMPLATEFOR_AESPBOUTPARAMS OUTPUTSIZE, NUMOFINPUTSIGNALS, NUMOFFILTERS, TFilter1, TFilter2, TFilter3, TheParameterNOTone1, isParameterNOToneInputSize1, TheParameterNOTone2, isParameterNOToneInputSize2, TheParameterNOTone3, isParameterNOToneInputSize3
#endif
#if MAXNUMBEROF_FILTERS == 4
#define TEMPLATEFOR_AESPBOUTPUT \
template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS, uint8_t NUMOFFILTERS, class TFilter1,class TFilter2,class TFilter3,class TFilter4, uint32_t TheParameterNOTone1, bool isParameterNOToneInputSize1, uint32_t TheParameterNOTone2, bool isParameterNOToneInputSize2, uint32_t TheParameterNOTone3, bool isParameterNOToneInputSize3>
#define TEMPLATEFOR_AESPBOUTPARAMS OUTPUTSIZE, NUMOFINPUTSIGNALS, NUMOFFILTERS, TFilter1, TFilter2, TFilter3, TFilter4, TheParameterNOTone1, isParameterNOToneInputSize1, TheParameterNOTone2, isParameterNOToneInputSize2, TheParameterNOTone3, isParameterNOToneInputSize3
#endif
#if MAXNUMBEROF_FILTERS == 5  */






//macro for being able to check if a macro is empty --------------------------------------
#define DO_EXPAND(VAL)  VAL ## 1
#define EXPAND(VAL)     DO_EXPAND(VAL)

//macro for static pointers ------------------------------------------------------------
#define S_CONC(A, B) S_CONC_(A, B)
#define S_CONC_(A, B) static A * B ; 

//macro for static pointers ------------------------------------------------------------
#define A_CONC(A, B) S_CONC_(A, B)
#define A_CONC_(A, B) A B 




//make singleton put this in the header for public:  ------------------------------
#define MAKE_SINGLETON(className) public: \
static className* getInstance(); \
className(className const&) = delete; \
void operator=(className const&) = delete; \
private: \
static className* instance; \
className(); \
public: 
// for singleton
// Don't forget to declare the two in private. You want to make sure they
// are unacceptable otherwise you may accidentally get copies of
// your singleton appearing.
//make singleton put this in the header for public:  
#define MAKE_SINGLETON_PUT_IN_CPP(className) \
className* className::instance = 0; \
className* className::getInstance() \
{ \
	if (instance == 0) \
	{ \
		static className soleInstance; \
		instance = &soleInstance; \
	} \
	return instance; \
}




//macro for properties 
#define PropertyGet(type, var) \
private: \
    type _##var; \
public: \
    type Get##var() const{ return _##var; }

#define PropertySet(type, var) \
private: \
    type _##var; \
public: \
    void Set##var(type val) { _##var = val; }

#define PropertyGetSet(type, var) \
private: \
    type _##var; \
public: \
    type Get##var() const{ return _##var; }\
    void Set##var(type val) { _##var = val; }

#define PropertyGetProtectedSet(type, var) \
protected: \
    type _##var; \
void Set##var(type val) { _##var = val; } \
public: \
    type Get##var() const{ return _##var; }







enum StyleOfSPB {
	EachSPBTask, //each spb has its own task that it will use to execute its refresh
	ChainOfSPBsTask,// there is one "chain task" that will run all refreshs
	ChainOfSPBsFromInterrupt //there are no tasks involved and so everything is run within the interrupt. 

};








#define CREATE_AND_SET_CHANNEL(CHANNEL_ID, INPUTSIZE, COUNTBUFFER)\
if (INPUTSIZE == 1) \
{ \
	static float signalBuffer##CHANNEL_ID[COUNTBUFFER]; \
	static InputChannel  InCh##CHANNEL_ID(CHANNEL_ID, INPUTSIZE, COUNTBUFFER, signalBuffer##CHANNEL_ID); \
	ChannelsToSet[CHANNEL_ID - 1] = &InCh##CHANNEL_ID; \
}\
else if (COUNTBUFFER == 1) \
{ \
	static float signalBuffer##CHANNEL_ID[INPUTSIZE]; \
	static InputChannel  InCh##CHANNEL_ID(CHANNEL_ID, INPUTSIZE, COUNTBUFFER, signalBuffer##CHANNEL_ID); \
	ChannelsToSet[CHANNEL_ID - 1] = &InCh##CHANNEL_ID; \
} \
else \
{ \
	static float signalBuffer##CHANNEL_ID[COUNTBUFFER][INPUTSIZE]; \
	static InputChannel  InCh##CHANNEL_ID(CHANNEL_ID, INPUTSIZE, COUNTBUFFER, (float**)signalBuffer##CHANNEL_ID); \
	ChannelsToSet[CHANNEL_ID - 1] = &InCh##CHANNEL_ID; \
} 



































//############################### 
//Writing to file 
//############################### 
 
#ifdef HARDWARE
#include <TestResourceManager.h>	
inline void  AEWriteToEndOfFile(const char* FileNameToWriteTo, const void* ThingToWrite, uint32_t SizeOfThingToWrite) 
{
	auto hInputs = TRMCreateFile(FileNameToWriteTo, sfmCreateOrAppendWriteOnly);
	ssize_t done = TRMWriteFile(hInputs, ThingToWrite, SizeOfThingToWrite);
	TRMCloseFile(hInputs);
}

inline void  AEClearContentsOfFile(const char* FileNameToClear) 
{
	auto hInputs = TRMCreateFile(FileNameToClear, sfmCreateOrTruncateWriteOnly);
	ssize_t done = TRMWriteFile(hInputs, "", 1);
	TRMCloseFile(hInputs);
}
 
#else
#include <string>
#include <stdio.h>
inline void  AEWriteToEndOfFile(const char* FileNameToWriteTo, const void* ThingToWrite, uint32_t SizeOfThingToWrite) 
{
	std::string PathtoFile = "C:\\visualgdb_projects\\AERTOS\\TestResources\\";
	PathtoFile.append(FileNameToWriteTo);
	FILE* fp = fopen(PathtoFile.c_str(), "a");
	//if fp=0 then file must not exist
	if(fp != 0)
	{fprintf(fp, "%s", ThingToWrite); 
	fclose(fp);
	}
}

inline void  AEClearContentsOfFile(const char* FileNameToClear) 
{
	std::string PathtoFile = "C:\\visualgdb_projects\\AERTOS\\TestResources\\";
	PathtoFile.append(FileNameToClear);
	FILE* fp = fopen(PathtoFile.c_str(), "w");
	fprintf(fp, "%s", ""); 
	fclose(fp);
}
#endif

//###############################
//unit testing friend classes
//###############################

#ifdef GOOGLE_TESTING
#include <gtest/gtest.h>
#define AEFRIEND_TEST(groupName, testName) FRIEND_TEST(groupName, testName)
#else
#define AEFRIEND_TEST(groupName, testName)
#endif

//###############################
//Assert
//###############################

//get the type of assert to use
#if GOOGLE_TESTING 

class AssertTestCheck
{
  public:
	AssertTestCheck(std::string assertName, bool isToCheckPass)
		: AssertName(assertName), IsToCheckPass(isToCheckPass){}
	std::string AssertName; 
	bool IsToCheckPass;
};

#include <vector>
static std::vector<AssertTestCheck*> UniqueIdsOfTestingAsserts;
//use the GoogleTest assert
#define TheAssertToUse(predicate) EXPECT_TRUE(predicate)

#define AE_Expect_Assert_To_Fail(AssertionMessage) UniqueIdsOfTestingAsserts.push_back(new AssertTestCheck(AssertionMessage, false));
#define AE_Expect_Assert_To_Pass(AssertionMessage) UniqueIdsOfTestingAsserts.push_back(new AssertTestCheck(AssertionMessage, true));
#define AE_Clear_Expectations_Of_Asserts UniqueIdsOfTestingAsserts.clear();

#else
//use the freeRTOS assert

#define TheAssertToUse(predicate) configASSERT(predicate)
#endif



#define AEAssertRuntime(thingToAssert, AssertionMessage)\
if(thingToAssert == false){\
AEPrint(AssertionMessage);\
TheAssertToUse(thingToAssert); }
	 

#define AEAssertRuntimeNoMsg(thingToAssert) AEAssertRuntime(thingToAssert, "")

#if GOOGLE_TESTING
//use this for testing when you want to later test that this assert failed
#define AEAssertRuntimeWithAssertCodeToTest(thingToAssert, uniqueNameOfAssert, AssertionMessage) \
for (size_t i = 0; i < UniqueIdsOfTestingAsserts.size(); i++)\
{\
	if (UniqueIdsOfTestingAsserts[i]->AssertName == uniqueNameOfAssert)\
	{\
		EXPECT_TRUE(UniqueIdsOfTestingAsserts[i]->IsToCheckPass == thingToAssert);\
		break;\
	}\
	AEAssertRuntime(false, "assert name not found.")\
}

//if(thingToAssert == false){UniqueIdsOfTestingAsserts.push_back(uniqueNameOfAssert); }

//inline static bool AEHasAssertFailed(std::string uniqueNameOfAssert)
//{ 
//	for (size_t i = 0; i < UniqueIdsOfTestingAsserts.size(); i++)
//	{
//		if (UniqueIdsOfTestingAsserts[i] == uniqueNameOfAssert){return true;}
//	}
//	return false; 
//}

//inline static void AEResetAssertCodes() { UniqueIdsOfTestingAsserts.clear();}

#else 
#define AEAssertRuntimeWithAssertCodeToTest(thingToAssert, uniqueNameOfAssert, AssertionMessage) AEAssertRuntime(thingToAssert, AssertionMessage)
#endif

//TODO: get static asserts
#define AEAssertStatic

 


//############################### 
//performance timers
//############################### 

extern AEPerformanceTimer* AEPerfTimer1;
extern AEPerformanceTimer* AEPerfTimer2;
extern AEPerformanceTimer* AEPerfTimer3; 
	 

#define PRIV_AEStartTimer(forTimer) \
AEPerfTimer##forTimer->AEStart_Timer();

#define PRIV_AEStopTimer(forTimer) \
AEPerfTimer##forTimer->AEStop_Timer();







#define AEStartTimer(forTimer)\
AEAssertRuntime(AEPerfTimer##forTimer->_TimerRunningFromStart == false ,"you already ran AEStartTimer and then tried to run it again for timer ##forTimer")\
AEAssertRuntime(AEPerfTimer##forTimer->_TimerRunningFromReEnter == false, "you cant mix calling AETimerForEnteringAndReEntering and AEStartTimer for timer ##forTimer")\
AEPerfTimer##forTimer->_TimerRunningFromStart = true; \
PRIV_AEStartTimer(forTimer)

#define AEStopTimer(forTimer)\
AEAssertRuntime(AEPerfTimer##forTimer->_TimerRunningFromStart == true ,"you never ran AEStartTimer and then tried to run AEStopTimer for timer ##forTimer")\
AEAssertRuntime(AEPerfTimer##forTimer->_TimerRunningFromReEnter == false ,"you cant mix calling AETimerForEnteringAndReEntering and AEStopTimer for timer ##forTimer")\
AEPerfTimer##forTimer->_TimerRunningFromStart = false;\
PRIV_AEStopTimer(forTimer)


#define AEPrintTimerDuration(forTimer)\
AEPrint("timer %d took: %d \n", forTimer, AEPerfTimer##forTimer->GetElapsedTimeInNanoSeconds()); //(uint32_t)(1000000000f*

#define AEGetTimerDuration(forTimer)\
AEPerfTimer##forTimer->GetElapsedTimeInNanoSeconds()

#define AEPrintAllTimerDuration \
AEPrintTimerDuration(1)\
AEPrintTimerDuration(2)\
AEPrintTimerDuration(3)


#define AETimerForEnteringAndReEntering_AndPrint(forTimer)\
AEAssertRuntime(AEPerfTimer##forTimer->_TimerRunningFromStart == false,"you already ran AEStartTimer and then tried to call AETimerForEnteringAndReEntering. You should only use this macro for reentering starting and stopping the timer")\
if(AEPerfTimer##forTimer->_TimerRunningFromReEnter == false){ AEPerfTimer##forTimer->_TimerRunningFromReEnter = true; PRIV_AEStartTimer(forTimer); }\
else{PRIV_AEStopTimer(forTimer); AEPerfTimer##forTimer->_TimerRunningFromReEnter = false;\
AEPrintTimerDuration(forTimer)\
} 


 
//############################### 
//logging times
//############################### 


#include <string>

inline void _AELogTimer(PerfElapsed_t duration, const char* FileNameToWriteTo) 
{
	
#ifdef HARDWARE
	std::string PathtoFile = "PerformanceTimes\\Hardware\\%s\\%s.txt";
	char PathtoFile1[250]; 
	AEFormatMsg(PathtoFile1, sizeof(PathtoFile1), PathtoFile.c_str(), FileNameToWriteTo, FileNameToWriteTo);
	PathtoFile = PathtoFile1;
#else 
	std::string PathtoFile = "PerformanceTimes\\Simulation\\%s\\%s.txt";
	char PathtoFile1[250]; 
	AEFormatMsg(PathtoFile1, sizeof(PathtoFile1), PathtoFile.c_str(), FileNameToWriteTo, FileNameToWriteTo);
	PathtoFile = PathtoFile1;
#endif
	std::string PathtoFileMain = "PerformanceTimes\\MostRecentTimes.txt";
	
	char formatedMsg[100];
	char formatedMsg2[150]; 
	AEFormatMsg(formatedMsg, sizeof(formatedMsg), "\n%d", duration);
	AEFormatMsg(formatedMsg2, sizeof(formatedMsg2), "\n%s :: %d ", FileNameToWriteTo, duration);
	//	std::filesystem::create_directory
	std::string formatedmsgStr = formatedMsg;
	std::string formatedmsgStr2 = formatedMsg2;
	
	AEWriteToEndOfFile(PathtoFile.c_str(), formatedmsgStr.c_str(), formatedmsgStr.length());
	AEWriteToEndOfFile(PathtoFileMain.c_str(), formatedmsgStr2.c_str(), formatedmsgStr2.length());
	
	
}

#define AELogTimer(forTimer, FileNameToWriteTo ) _AELogTimer(AEGetTimerDuration(forTimer), FileNameToWriteTo)







//############################### 
//helper functions 
//############################### 

 
//example AE_GET_LAST_BITS of a variable with bits 00101101 AE_GET_LAST_BITS(var, 4)  will give 00001101
#define AE_GET_LAST_BITS(VarToGetBits, ThisManyBitsFromLast) ((VarToGetBits) & ((1<<(ThisManyBitsFromLast))-1))
#define AE_GET_MID_BITS(VarToGetBits,FromBit,ToBit) AE_GET_LAST_BITS((VarToGetBits)>>(FromBit),((ToBit)-(FromBit)))




static float AE_Map(float valueToMap, float lowerBoundOfMapFROM, float UpperBoundOfMapFROM, float lowerBoundOfMapTO, float UpperBoundOfMapTO)
{
	if (valueToMap < lowerBoundOfMapFROM)
	{
		return lowerBoundOfMapTO;
	}

	if (valueToMap > UpperBoundOfMapFROM)
	{
		return UpperBoundOfMapTO;
	}

	float mappedValue = (((UpperBoundOfMapTO - lowerBoundOfMapTO) / (UpperBoundOfMapFROM - lowerBoundOfMapFROM))
		* (valueToMap - lowerBoundOfMapFROM)) + lowerBoundOfMapTO;

	return mappedValue;
}



//#include "AEmemcpy.h"
/*

static void AEmemcpyManyFromBottomUp1(void* dst, void* src, uint32_t size)
{
	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst;
		char *srcp = (char *)src;

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
			memcpy(destp + (i * 10), srcp + (i * 10), 10);
		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder);

	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i* 10)
		{
			if (size <= i)
			{ 
				char *destp = (char *)dst;
				char *srcp = (char *)src; 

				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby)+ 100), (srcp + (i * incrmentby)+ 100), incrmentby);
				}

				memcpy(destp + ((timesToCopy * incrmentby)+ 100), srcp + ((timesToCopy * incrmentby)+ 100), remainder);

				break;
			}
		}
	}


}





static void AEmemcpyManyFromBottomUp2(void* dst, void* src
	, void* dst2, void* src2, uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst;
		char *srcp = (char *)src;
		char *destp2 = (char *)dst2;
		char *srcp2 = (char *)src2;

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
			memcpy(destp + (i * 10), srcp + (i * 10), 10);
			memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder);
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder);

	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
				char *destp = (char *)dst;
				char *srcp = (char *)src;
				char *destp2 = (char *)dst2;
				char *srcp2 = (char *)src2;

				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby);
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby);
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);

				break;
			}
		}
	}


}





static void AEmemcpyManyFromBottomUp3(void* dst, void* src
	, void* dst2, void* src2
	, void* dst3, void* src3, uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst;
		char *srcp = (char *)src;
		char *destp2 = (char *)dst2;
		char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3;
		char *srcp3 = (char *)src3;

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
			memcpy(destp + (i * 10), srcp + (i * 10), 10);
			memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
			memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder);
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder);
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder);

	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
				char *destp = (char *)dst;
				char *srcp = (char *)src;
				char *destp2 = (char *)dst2;
				char *srcp2 = (char *)src2;
				char *destp3 = (char *)dst3;
				char *srcp3 = (char *)src3;

				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby);
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby);
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby);
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);

				break;
			}
		}
	}


}*/