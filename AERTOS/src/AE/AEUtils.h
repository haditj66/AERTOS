/** \file AEUtils.h
 * A collection of utility functions for AE
 * A more elaborated file description.
 */

#pragma once

#ifdef SWIL_HWIL_DRIVEN__SWIL
#include <cstdint>				  
#endif  
 





#include "AE.h"
#include <string.h>
#include "AEPerformanceTimer.h"

#include "AEDefines.h"
 
#ifdef RTOS_USED__FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#endif



#define PoolManager AEPoolManager<Event1, Event1Size, Event2, Event2Size, Event3, Event3Size, Event4, Event4Size, Event5, Event5Size>::getInstance()
#define PublishSubscribeManager AEPublishSubscribeManager::getInstance()












 







enum AEPriorities
{
	LowestPriority  = AOPRIORITYLOWEST,
	MediumPriority  = AOPRIORITYMEDIUM,
	HighestPriority = AOPRIORITYHIGHEST - 1 // -1 so to leave room to the actual highest priority that the AE uses
};





class AENullFSMUtility
{
public:
	template<class TBla>
		void SetExclusivePossessor(TBla*) {}
	;
	uint16_t GetAO_ID() { return 0; }
	;
};


class NULLPeripheral
{
public:
	static void* Instance;
	static void* getInstance() { return nullptr; }
	;
	void initializePeripheral() {}
	;

};

class AENullClass {
public:float operator()(float a) { return 0; }
	;
	float FilterOutputValue;
	void Initialize(float a) {}
	;
	float GetObservation() { return 1; }
	;
	float* GetOutputDataAddress() const { return nullptr; }
	;
};

class AENULLEvent
{
public:
	bool EvtId;
	bool EvtIdStatic;
#pragma warning( disable : 26495)
	AENULLEvent() {}
	;
	void init(uint16_t evtId) {}
	;
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
		static void AEMemcpyIMPL1(void* dest, TTypeToCopyFrom source, uint32_t size) { memcpy(dest, (void*)source, size); }
		;
		static void AEMemcpyIMPL2(void* dest, TTypeToCopyFrom source, uint32_t size) { memcpy(dest, (void*)&source, size); }
		;
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
	inline void ArrayCheckToMemCopy<int32_t>::AEMemcpy(void* dest, int32_t source, uint32_t size)
	{
		memcpy(dest, &source, size);
	}
template<>
	inline void ArrayCheckToMemCopy<int16_t>::AEMemcpy(void* dest, int16_t source, uint32_t size)
	{
		memcpy(dest, &source, size);
	}
template<>
	inline void ArrayCheckToMemCopy<int8_t>::AEMemcpy(void* dest, int8_t source, uint32_t size)
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
//template<>
//	inline void ArrayCheckToMemCopy<int>::AEMemcpy(void* dest, int source, uint32_t size)
//	{
//		memcpy(dest, &source, size);
//	}



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






#include <cmath>

template< int64_t WholeNum, uint8_t MoveDecimalToLeftThisMany>
	class FloatInTemplateWorkAround
	{
	public:
		FloatInTemplateWorkAround() {}
		; 
	
		float GetValue()
		{
			float TenToThe = pow(10, MoveDecimalToLeftThisMany);
			return (float)((float)WholeNum / (float)TenToThe);
		}

	private:
	
	};






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
}
;

enum AEFSMActiveTypeEnum {
	PAUSE_TO_ACTIVATE,
	RESET_TO_ACTIVATE
};




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
	// look at file AESPBObservor.cpp at funciton _RefreshCheckStyle() for where this implementation makes a difference. 
	EachSPBTask,  //each spb has its own task that it will use to execute its refresh
	ChainOfSPBsTask, // there is one "chain task" that will run all refreshs
	//there are no tasks involved and so everything is run within the interrupt(although doesnt need to be an interrupt, can also just be from a normal tick() of a clock).
	//Currently this doesnt look to be any different than the 
	//ChainOfSPBsTask so maybe use this for now intead of that one. Remeber that if you do infact use this in an interrupt, it should be a VERY quick spb
	ChainOfSPBsFromInterrupt 

}
;








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
//SPB helpers
//############################### 










//############################### 
//Writing to file 
//############################### 
 
#ifdef SWIL_HWIL_DRIVEN__HWIL
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
	std::string PathtoFile = CGEN_CMAKE_CURRENT_SOURCE_DIR;
	//	std::string PathtoFile = "C:\\visualgdb_projects\\AERTOS\\TestResources\\";
		PathtoFile.append("\\TestResources\\");
	PathtoFile.append(FileNameToWriteTo);
	FILE* fp = fopen(PathtoFile.c_str(), "a");
	//if fp=0 then file must not exist
	if(fp != 0)
	{
		fprintf(fp, "%s", ThingToWrite); 
		fclose(fp);
	}
}

inline void  AEClearContentsOfFile(const char* FileNameToClear) 
{
	std::string PathtoFile = CGEN_CMAKE_CURRENT_SOURCE_DIR;
	//	std::string PathtoFile = "C:\\visualgdb_projects\\AERTOS\\TestResources\\";
		PathtoFile.append("\\TestResources\\");
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
		: AssertName(assertName)
		, IsToCheckPass(isToCheckPass) {}
	std::string AssertName; 
	bool IsToCheckPass;
}
;

#include <vector>
static std::vector<AssertTestCheck*> UniqueIdsOfTestingAsserts;
//use the GoogleTest assert
 
 

#define TheAssertToUse(predicate) EXPECT_TRUE(predicate)

#define AE_Expect_Assert_To_Fail(AssertionMessage) UniqueIdsOfTestingAsserts.push_back(new AssertTestCheck(AssertionMessage, false));
#define AE_Expect_Assert_To_Pass(AssertionMessage) UniqueIdsOfTestingAsserts.push_back(new AssertTestCheck(AssertionMessage, true));
#define AE_Clear_Expectations_Of_Asserts UniqueIdsOfTestingAsserts.clear();
 

#else

//use the freeRTOS assert






//
//#define _AEweaks(ret, funcName) ret funcName##r
//
//#if  AEPLATFORM == VSGDBCmakeNinja_armnoneabiid
//#define _AEweak(ret, funcName) __weak ret funcName
//
//#elif AEPLATFORM == VSGDBCmakeNinja_mingw
//#define _AEweak(ret, funcName) ret funcName
//
//#endif
//
//typedef void (*RuntimeAssertfnc_t)(void);
//static RuntimeAssertfnc_t fncr = NULL;
//void RuntimeAssertr()
//{
//	if (fncr != nullptr)
//	{
//		fncr();
//	}
//}

  

 
//_AEweaks(void, RuntimeAssert)()
//{
//}
//
//void RuntimeAssert()
//{
//	//implementation
//}



#if NUMOFEVENTS > (256-2) //the minus 2 is to account for the two enter and exit events

#define ENTEREVENT_Id	0xffff
#define EXITEVENT_Id	0xffff - 1
#else  
#define ENTEREVENT_Id	0xff
#define EXITEVENT_Id	0xff - 1
#endif


/// \def assert the the predicate. test code: sdve46ydv
#define TheAssertToUse(predicate) configASSERT(predicate)
#endif


///  this will assert the predicate. if fails, will print assert command. test code: asvasf343
#define AEAssertRuntime(thingToAssert, AssertionMessage)\
if(thingToAssert == false){\
AEPrint(AssertionMessage);\
TheAssertToUse(thingToAssert); }
	 

#define AEAssertRuntimeNoMsg(thingToAssert) AEAssertRuntime(thingToAssert, "")

#if GOOGLE_TESTING

///####
///Use this for testing when you want to later test that this assert passed or failed with a unit test.
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
///Use this for testing when you want to later test that this assert passed or failed with a unit test.
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
#include <vector>

extern std::vector<std::string> logFilesToLogSoFar;
extern std::vector<std::string> logpathToFile;
extern std::vector<std::string> logthingToWrite;
extern std::vector<uint32_t> logthingToWriteSize;

inline void _AELogTimer(PerfElapsed_t duration, const char* FileNameToWriteTo) 
{
	//first if you are not google testing, I need to check if the file i am writing to has already beed processed
#ifndef GOOGLE_TESTING
	for (std::string  fi : logFilesToLogSoFar)
	{
		if (fi == FileNameToWriteTo)
		{
			//do nothing as already processed file.
			return; 
		}
	}
	logFilesToLogSoFar.push_back(FileNameToWriteTo);
	
#endif
	

	
#ifdef SWIL_HWIL_DRIVEN__HWIL
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
	
	

	
	//only write if unit testing, otherwise log to the file happens after integration testing ends. 
#ifdef GOOGLE_TESTING
	AEWriteToEndOfFile(PathtoFile.c_str(), formatedmsgStr.c_str(), formatedmsgStr.length());
	AEWriteToEndOfFile(PathtoFileMain.c_str(), formatedmsgStr2.c_str(), formatedmsgStr2.length()); #else	logpathToFile.push_back(PathtoFile);
	logthingToWrite.push_back(formatedmsgStr);
	logthingToWriteSize.push_back(formatedmsgStr.length());  
#endif
	
}

#define AELogTimer(forTimer, FileNameToWriteTo ) _AELogTimer(AEGetTimerDuration(forTimer), FileNameToWriteTo)







//############################### 
//helper functions 
//############################### 

 
//example AE_GET_LAST_BITS of a variable with bits 00101101 AE_GET_LAST_BITS(var, 4)  will give 00001101
#define AE_GET_LAST_BITS(VarToGetBits, ThisManyBitsFromLast) ((VarToGetBits) & ((1<<(ThisManyBitsFromLast))-1))
#define AE_GET_MID_BITS(VarToGetBits,FromBit,ToBit) AE_GET_LAST_BITS((VarToGetBits)>>(FromBit),((ToBit)-(FromBit)))

	
static std::string AE_convertToString(char* a, int size)
{
	int i;
	std::string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}
	
static std::string AE_convertToString(const char* a, int size)
{
	int i;
	std::string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}


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





 //------------------ comparisons
#include <math.h>
static bool AE_FloatApproximatelyEqual(float a, float b, float epsilon)
{
	return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}




//this will end the program based on which device it is running on.
static void AEEndProgram()
{
#if AERTOS_ENVIRONMENT__RTOS_PC
	AEPrint("Application END");
	for (;;) {};
#else
	exit(EXIT_SUCCESS); 
#endif
}

 




template <class TTypeOfVars>
	inline uint32_t AEmemcpy_MultipleVariablesToArray(TTypeOfVars* varWriteTo,
		TTypeOfVars* varWriteFrom1,
		int varSize_NotInBytes1,
		TTypeOfVars* varWriteFrom2,
		int varSize_NotInBytes2 )
	{
	
		int totalSizeBytes = sizeof(TTypeOfVars)* (varSize_NotInBytes1 + varSize_NotInBytes2 );
		int ind = 0;
		memcpy(varWriteTo, varWriteFrom1, varSize_NotInBytes1 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes1;
		memcpy(&varWriteTo[ind], varWriteFrom2, varSize_NotInBytes2 * sizeof(TTypeOfVars)); 
	
		return totalSizeBytes;
	}

template <class TTypeOfVars>
	inline uint32_t AEmemcpy_MultipleVariablesToArray(TTypeOfVars* varWriteTo,
		TTypeOfVars* varWriteFrom1,
		int varSize_NotInBytes1,
		TTypeOfVars* varWriteFrom2,
		int varSize_NotInBytes2,
		TTypeOfVars* varWriteFrom3,
		int varSize_NotInBytes3 )
	{
	
		int totalSizeBytes = sizeof(TTypeOfVars)* (varSize_NotInBytes1 + varSize_NotInBytes2 + varSize_NotInBytes3  );
		int ind = 0;
		memcpy(varWriteTo, varWriteFrom1, varSize_NotInBytes1 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes1;
		memcpy(&varWriteTo[ind], varWriteFrom2, varSize_NotInBytes2 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes2;
		memcpy(&varWriteTo[ind], varWriteFrom3, varSize_NotInBytes3 * sizeof(TTypeOfVars));  
	
		return totalSizeBytes;
	}


template <class TTypeOfVars>
	inline uint32_t AEmemcpy_MultipleVariablesToArray(TTypeOfVars* varWriteTo,
		TTypeOfVars* varWriteFrom1,
		int varSize_NotInBytes1,
		TTypeOfVars* varWriteFrom2,
		int varSize_NotInBytes2,
		TTypeOfVars* varWriteFrom3,
		int varSize_NotInBytes3,
		TTypeOfVars* varWriteFrom4,
		int varSize_NotInBytes4 )
	{
	
		int totalSizeBytes = sizeof(TTypeOfVars)* (varSize_NotInBytes1 + varSize_NotInBytes2 + varSize_NotInBytes3 + varSize_NotInBytes4 );
		int ind = 0;
		memcpy(varWriteTo, varWriteFrom1, varSize_NotInBytes1 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes1;
		memcpy(&varWriteTo[ind], varWriteFrom2, varSize_NotInBytes2 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes2;
		memcpy(&varWriteTo[ind], varWriteFrom3, varSize_NotInBytes3 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes3;
		memcpy(&varWriteTo[ind], varWriteFrom4, varSize_NotInBytes4 * sizeof(TTypeOfVars)); 
	
		return totalSizeBytes;
	}

template <class TTypeOfVars>
	inline uint32_t AEmemcpy_MultipleVariablesToArray(TTypeOfVars* varWriteTo,
		TTypeOfVars* varWriteFrom1,
		int varSize_NotInBytes1,
		TTypeOfVars* varWriteFrom2,
		int varSize_NotInBytes2,
		TTypeOfVars* varWriteFrom3,
		int varSize_NotInBytes3,
		TTypeOfVars* varWriteFrom4,
		int varSize_NotInBytes4,
		TTypeOfVars* varWriteFrom5,
		int varSize_NotInBytes5 )
	{
	
		int totalSizeBytes = sizeof(TTypeOfVars)* (varSize_NotInBytes1 + varSize_NotInBytes2 + varSize_NotInBytes3 + varSize_NotInBytes4 + varSize_NotInBytes5   );
		int ind = 0;
		memcpy(varWriteTo, varWriteFrom1, varSize_NotInBytes1 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes1;
		memcpy(&varWriteTo[ind], varWriteFrom2, varSize_NotInBytes2 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes2;
		memcpy(&varWriteTo[ind], varWriteFrom3, varSize_NotInBytes3 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes3;
		memcpy(&varWriteTo[ind], varWriteFrom4, varSize_NotInBytes4 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes4;
		memcpy(&varWriteTo[ind], varWriteFrom5, varSize_NotInBytes5 * sizeof(TTypeOfVars)); 
	
		return totalSizeBytes;
	}

template <class TTypeOfVars>
	inline uint32_t AEmemcpy_MultipleVariablesToArray(TTypeOfVars* varWriteTo,
		TTypeOfVars* varWriteFrom1,
		int varSize_NotInBytes1,
		TTypeOfVars* varWriteFrom2,
		int varSize_NotInBytes2,
		TTypeOfVars* varWriteFrom3,
		int varSize_NotInBytes3,
		TTypeOfVars* varWriteFrom4,
		int varSize_NotInBytes4,
		TTypeOfVars* varWriteFrom5,
		int varSize_NotInBytes5,
		TTypeOfVars* varWriteFrom6,
		int varSize_NotInBytes6)
	{
	
		int totalSizeBytes = sizeof(TTypeOfVars)* (varSize_NotInBytes1 + varSize_NotInBytes2 + varSize_NotInBytes3 + varSize_NotInBytes4 + varSize_NotInBytes5 + varSize_NotInBytes6  );
		int ind = 0;
		memcpy(varWriteTo, varWriteFrom1, varSize_NotInBytes1 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes1;
		memcpy(&varWriteTo[ind], varWriteFrom2, varSize_NotInBytes2 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes2;
		memcpy(&varWriteTo[ind], varWriteFrom3, varSize_NotInBytes3 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes3;
		memcpy(&varWriteTo[ind], varWriteFrom4, varSize_NotInBytes4 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes4;
		memcpy(&varWriteTo[ind], varWriteFrom5, varSize_NotInBytes5 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes5;
		memcpy(&varWriteTo[ind], varWriteFrom6, varSize_NotInBytes6 * sizeof(TTypeOfVars)); 
	
		return totalSizeBytes;
	}

template <class TTypeOfVars>
	inline uint32_t AEmemcpy_MultipleVariablesToArray(TTypeOfVars* varWriteTo,
		TTypeOfVars* varWriteFrom1,
		int varSize_NotInBytes1,
		TTypeOfVars* varWriteFrom2,
		int varSize_NotInBytes2,
		TTypeOfVars* varWriteFrom3,
		int varSize_NotInBytes3,
		TTypeOfVars* varWriteFrom4,
		int varSize_NotInBytes4,
		TTypeOfVars* varWriteFrom5,
		int varSize_NotInBytes5,
		TTypeOfVars* varWriteFrom6,
		int varSize_NotInBytes6,
		TTypeOfVars* varWriteFrom7,
		int varSize_NotInBytes7 
	)
	{
	
		int totalSizeBytes = sizeof(TTypeOfVars)* (varSize_NotInBytes1 + varSize_NotInBytes2 + varSize_NotInBytes3 + varSize_NotInBytes4 + varSize_NotInBytes5 + varSize_NotInBytes6 + varSize_NotInBytes7   );
		int ind = 0;
		memcpy(varWriteTo, varWriteFrom1, varSize_NotInBytes1 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes1;
		memcpy(&varWriteTo[ind], varWriteFrom2, varSize_NotInBytes2 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes2;
		memcpy(&varWriteTo[ind], varWriteFrom3, varSize_NotInBytes3 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes3;
		memcpy(&varWriteTo[ind], varWriteFrom4, varSize_NotInBytes4 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes4;
		memcpy(&varWriteTo[ind], varWriteFrom5, varSize_NotInBytes5 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes5;
		memcpy(&varWriteTo[ind], varWriteFrom6, varSize_NotInBytes6 * sizeof(TTypeOfVars));
		ind += varSize_NotInBytes6;
		memcpy(&varWriteTo[ind], varWriteFrom7, varSize_NotInBytes7 * sizeof(TTypeOfVars)); 
	
		return totalSizeBytes;
	}


template <class TTypeOfVars>
	inline uint32_t AEmemcpy_MultipleVariablesToArray(TTypeOfVars* varWriteTo,
	TTypeOfVars* varWriteFrom1, int varSize_NotInBytes1,
		TTypeOfVars* varWriteFrom2, int varSize_NotInBytes2,
		TTypeOfVars* varWriteFrom3, int varSize_NotInBytes3,
		TTypeOfVars* varWriteFrom4, int varSize_NotInBytes4,
		TTypeOfVars* varWriteFrom5, int varSize_NotInBytes5,
		TTypeOfVars* varWriteFrom6, int varSize_NotInBytes6,
		TTypeOfVars* varWriteFrom7, int varSize_NotInBytes7,
		TTypeOfVars* varWriteFrom8, int varSize_NotInBytes8
	)
{
	
	int totalSizeBytes = sizeof(TTypeOfVars)* (varSize_NotInBytes1 + varSize_NotInBytes2 + varSize_NotInBytes3 + varSize_NotInBytes4 + varSize_NotInBytes5 + varSize_NotInBytes6 + varSize_NotInBytes7 + varSize_NotInBytes8);
	int ind = 0;
	memcpy(varWriteTo, varWriteFrom1, varSize_NotInBytes1 * sizeof(TTypeOfVars));
	ind += varSize_NotInBytes1;
	memcpy(&varWriteTo[ind], varWriteFrom2, varSize_NotInBytes2 * sizeof(TTypeOfVars));
	ind += varSize_NotInBytes2;
	memcpy(&varWriteTo[ind], varWriteFrom3, varSize_NotInBytes3 * sizeof(TTypeOfVars));
	ind += varSize_NotInBytes3;
	memcpy(&varWriteTo[ind], varWriteFrom4, varSize_NotInBytes4 * sizeof(TTypeOfVars));
	ind += varSize_NotInBytes4;
	memcpy(&varWriteTo[ind], varWriteFrom5, varSize_NotInBytes5 * sizeof(TTypeOfVars));
	ind += varSize_NotInBytes5;
	memcpy(&varWriteTo[ind], varWriteFrom6, varSize_NotInBytes6 * sizeof(TTypeOfVars));
	ind += varSize_NotInBytes6;
	memcpy(&varWriteTo[ind], varWriteFrom7, varSize_NotInBytes7 * sizeof(TTypeOfVars));
	ind += varSize_NotInBytes7;
	memcpy(&varWriteTo[ind], varWriteFrom8, varSize_NotInBytes8 * sizeof(TTypeOfVars));
	
	return totalSizeBytes;
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