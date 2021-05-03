#pragma once


#include "cstdint"







//macro for action requests -------------------------



//actionrequests TDus ------------------------------------------------------------
//1
#define TemplateForActionArgTDU1 \
	class ARG1, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU = AENull

#define TemplateForActionArgTDU_NoDefaults1 \
	class ARG1, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU

#define TemplateForActionArgTDU_Args1 \
	ARG1, \
	RETURNARG, \
	POOLSIZE, \
	ForwardDeclaredTDU


//2
#define TemplateForActionArgTDU2 \
	class ARG1, \
	class ARG2, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU = AENull

#define TemplateForActionArgTDU_NoDefaults2 \
	class ARG1, \
	class ARG2, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU

#define TemplateForActionArgTDU_Args2 \
	ARG1, \
	ARG2, \
	RETURNARG, \
	POOLSIZE, \
	ForwardDeclaredTDU

//3
#define TemplateForActionArgTDU3 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU = AENull

#define TemplateForActionArgTDU_NoDefaults3 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU

#define TemplateForActionArgTDU_Args3 \
	ARG1, \
	ARG2, \
	ARG3, \
	RETURNARG, \
	POOLSIZE, \
	ForwardDeclaredTDU

//4
#define TemplateForActionArgTDU4 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class ARG4, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU = AENull

#define TemplateForActionArgTDU_NoDefaults4 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class ARG4, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU

#define TemplateForActionArgTDU_Args4 \
	 ARG1, \
	ARG2, \
	ARG3, \
	ARG4, \
	RETURNARG, \
	POOLSIZE, \
	ForwardDeclaredTDU

//5
#define TemplateForActionArgTDU5 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class ARG4, \
	class ARG5, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU = AENull

#define TemplateForActionArgTDU_NoDefaults5 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class ARG4, \
	class ARG5, \
	class RETURNARG, \
	uint8_t POOLSIZE, \
	class ForwardDeclaredTDU

#define TemplateForActionArgTDU_Args5 \
	ARG1, \
	ARG2, \
	ARG3, \
	ARG4, \
	ARG5, \
	RETURNARG, \
	POOLSIZE, \
	ForwardDeclaredTDU




#define Friend_ToALL_ActionRequestObjects_TDU 	\
template<TemplateForActionArgTDU_NoDefaults1>\
friend class ActionRequestObjectArgTDU1;\
template<TemplateForActionArgTDU_NoDefaults2>\
friend class ActionRequestObjectArgTDU2;\
template<TemplateForActionArgTDU_NoDefaults3>\
friend class ActionRequestObjectArgTDU3;\
template<TemplateForActionArgTDU_NoDefaults4>\
friend class ActionRequestObjectArgTDU4;\
template<TemplateForActionArgTDU_NoDefaults5>\
friend class ActionRequestObjectArgTDU5;




//actionrequests ------------------------------------------------------------


//1
#define TemplateForActionArg1 \
	class ARG1, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility = AENull

#define TemplateForActionArg_NoDefaults1 \
	class ARG1, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility

#define TemplateForActionArg_Args1 \
	ARG1, \
	RETURNARG, \
	__POOLSIZE, \
	ForwardDeclaredUtility


//2
#define TemplateForActionArg2 \
	class ARG1, \
	class ARG2, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility = AENull

#define TemplateForActionArg_NoDefaults2 \
	class ARG1, \
	class ARG2, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility

#define TemplateForActionArg_Args2 \
	ARG1, \
	ARG2, \
	RETURNARG, \
	__POOLSIZE, \
	ForwardDeclaredUtility

//3
#define TemplateForActionArg3 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility = AENull

#define TemplateForActionArg_NoDefaults3 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility

#define TemplateForActionArg_Args3 \
	ARG1, \
	ARG2, \
	ARG3, \
	RETURNARG, \
	__POOLSIZE, \
	ForwardDeclaredUtility

//4
#define TemplateForActionArg4 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class ARG4, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility = AENull

#define TemplateForActionArg_NoDefaults4 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class ARG4, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility

#define TemplateForActionArg_Args4 \
	 ARG1, \
	ARG2, \
	ARG3, \
	ARG4, \
	RETURNARG, \
	__POOLSIZE, \
	ForwardDeclaredUtility

//5
#define TemplateForActionArg5 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class ARG4, \
	class ARG5, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility = AENull

#define TemplateForActionArg_NoDefaults5 \
	class ARG1, \
	class ARG2, \
	class ARG3, \
	class ARG4, \
	class ARG5, \
	class RETURNARG, \
	uint8_t __POOLSIZE, \
	class ForwardDeclaredUtility

#define TemplateForActionArg_Args5 \
	ARG1, \
	ARG2, \
	ARG3, \
	ARG4, \
	ARG5, \
	RETURNARG, \
	__POOLSIZE, \
	ForwardDeclaredUtility


#define Friend_ToALL_ActionRequestObjects 	\
template<TemplateForActionArg_NoDefaults1>\
friend	class ActionRequestObjectArg1;\
template<TemplateForActionArg_NoDefaults2>\
friend	class ActionRequestObjectArg2;\
template<TemplateForActionArg_NoDefaults3>\
friend	class ActionRequestObjectArg3;\
template<TemplateForActionArg_NoDefaults4>\
friend	class ActionRequestObjectArg4;\
template<TemplateForActionArg_NoDefaults5>\
friend	class ActionRequestObjectArg5;


//macro for AESimpleFSM -------------------------------
#define TemplateFor_SimpleFSM \
	class TDerivedType,\
	class TSubMachine1 = AENullFSMUtility,\
	class TSubMachine2 = AENullFSMUtility,\
	class TSubMachine3 = AENullFSMUtility

#define TemplateFor_SimpleFSM_NoDefaults \
	class TDerivedType,\
	class TSubMachine1,\
	class TSubMachine2,\
	class TSubMachine3

#define TemplateFor_SimpleFSM_Args \
	TDerivedType,\
	TSubMachine1,\
	TSubMachine2,\
	TSubMachine3




//macro for AEAOResourceAsAPossession ------------------------


#define TemplateFor_RAsAPossession uint16_t POOLSIZE = 1, \
class ActionRequest1 = AENullActionRequest,\
class ActionRequest2 = AENullActionRequest,\
class ActionRequest3 = AENullActionRequest

#define TemplateFor_RAsAPossession_NoDefaults uint16_t POOLSIZE, \
class ActionRequest1,\
class ActionRequest2,\
class ActionRequest3

#define TemplateFor_RAsAPossession_NoDefaults_friend uint16_t _POOLSIZE, \
class ActionRequest1,\
class ActionRequest2,\
class ActionRequest3

#define TemplateARGSFor_RAsAPossession POOLSIZE, \
ActionRequest1,\
ActionRequest2,\
ActionRequest3



//macro for AEAOUpdateableAAP
#define TemplateFor_AEAOUpdateableAAP uint16_t InputChannelSize = 0, TemplateFor_RAsAPossession

#define TemplateFor_AEAOUpdateableAAP_NoDefaults uint16_t InputChannelSize, TemplateFor_RAsAPossession_NoDefaults

#define TemplateFor_AEAOUpdateableAAP_NoDefaults_friend uint16_t InputChannelSize, TemplateFor_RAsAPossession_NoDefaults_friend

#define TemplateARGSFor_AEAOUpdateableAAP InputChannelSize, TemplateARGSFor_RAsAPossession



//macro for AEAOResourceAsAService
#define TemplateFor_RAsAService uint16_t POOLSIZE = 1, \
class ActionRequest1 = AENullActionRequest,\
class ActionRequest2 = AENullActionRequest,\
class ActionRequest3 = AENullActionRequest

#define TemplateFor_RAsAService_NoDefaults uint16_t POOLSIZE, \
class ActionRequest1,\
class ActionRequest2,\
class ActionRequest3

#define TemplateFor_RAsAService_NoDefaults_friend uint16_t _POOLSIZE, \
class ActionRequest1,\
class ActionRequest2,\
class ActionRequest3

#define TemplateARGSFor_RAsAService  POOLSIZE, \
ActionRequest1,\
ActionRequest2,\
ActionRequest3


//macro for AEAOUpdateableAAS
#define TemplateFor_AEAOUpdateableAAS	 TemplateFor_RAsAService

#define TemplateFor_AEAOUpdateableAAS_NoDefaults	 TemplateFor_RAsAService_NoDefaults

#define TemplateFor_AEAOUpdateableAAS_NoDefaults_friend		 TemplateFor_RAsAService_NoDefaults_friend

#define TemplateARGSFor_AEAOUpdateableAAS	 TemplateARGSFor_RAsAService




//macro for AEPeripherals
#define TemplateFor_AEPeripherals \
class DerivedType, uint16_t NumOfGpioPinsNeeded, class PeripheralHandleTypeDef \
	, Portenum PORT1 = Portenum::PortsMaxNum, PinEnum PIN1 = PinEnum::PINMaxNum\
	, Portenum PORT2 = Portenum::PortsMaxNum, PinEnum PIN2 = PinEnum::PINMaxNum\
	, Portenum PORT3 = Portenum::PortsMaxNum, PinEnum PIN3 = PinEnum::PINMaxNum\
	, Portenum PORT4 = Portenum::PortsMaxNum, PinEnum PIN4 = PinEnum::PINMaxNum\
	, Portenum PORT5 = Portenum::PortsMaxNum, PinEnum PIN5 = PinEnum::PINMaxNum\

#define TemplateFor_AEPeripherals_NoDefaults \
class DerivedType, uint16_t NumOfGpioPinsNeeded, class PeripheralHandleTypeDef \
	, Portenum PORT1  , PinEnum PIN1 \
	, Portenum PORT2  , PinEnum PIN2  \
	, Portenum PORT3  , PinEnum PIN3  \
	, Portenum PORT4 , PinEnum PIN4  \
	, Portenum PORT5  , PinEnum PIN5  \

#define TemplateArgs_AEPeripherals \
DerivedType, NumOfGpioPinsNeeded, PeripheralHandleTypeDef \
	, PORT1  , PIN1 \
	, PORT2  , PIN2  \
	, PORT3  , PIN3  \
	, PORT4 , PIN4  \
	, PORT5  , PIN5  \




//macro for AEAOResource -----------------------------------------

#define DeclareActionRequestTemplateArgs \
typedef typename ActionRequest1::ARGTYPE1 Action1_ARGTYPE1_t;\
typedef typename ActionRequest2::ARGTYPE1 Action2_ARGTYPE1_t;\
typedef typename ActionRequest3::ARGTYPE1 Action3_ARGTYPE1_t;\
typedef typename ActionRequest1::ARGTYPE2 Action1_ARGTYPE2_t;\
typedef typename ActionRequest2::ARGTYPE2 Action2_ARGTYPE2_t;\
typedef typename ActionRequest3::ARGTYPE2 Action3_ARGTYPE2_t;\
typedef typename ActionRequest1::ARGTYPE3 Action1_ARGTYPE3_t;\
typedef typename ActionRequest2::ARGTYPE3 Action2_ARGTYPE3_t;\
typedef typename ActionRequest3::ARGTYPE3 Action3_ARGTYPE3_t;\
typedef typename ActionRequest1::ARGTYPE4 Action1_ARGTYPE4_t;\
typedef typename ActionRequest2::ARGTYPE4 Action2_ARGTYPE4_t;\
typedef typename ActionRequest3::ARGTYPE4 Action3_ARGTYPE4_t;\
typedef typename ActionRequest1::ARGTYPE5 Action1_ARGTYPE5_t;\
typedef typename ActionRequest2::ARGTYPE5 Action2_ARGTYPE5_t;\
typedef typename ActionRequest3::ARGTYPE5 Action3_ARGTYPE5_t;\
\
typedef typename ActionRequest1::RETURNTYPE Action1_RETURNTYPE_t;\
typedef typename ActionRequest2::RETURNTYPE Action2_RETURNTYPE_t;\
typedef typename ActionRequest3::RETURNTYPE Action3_RETURNTYPE_t;\
\
typedef typename ActionRequest1::CLASSTOPASS Action1_CLASSTOPASS_t;\
typedef typename ActionRequest2::CLASSTOPASS Action2_CLASSTOPASS_t;\
typedef typename ActionRequest3::CLASSTOPASS Action3_CLASSTOPASS_t;

//template<class TActionRequestToRun>\

#define DeclareUtilityRequestFunctions \
template<class  TActionRequestToRun = bool>\
void RunRequest1(uint16_t AOID, Action1_ARGTYPE1_t arg1 = false, Action1_ARGTYPE2_t arg2 = false, Action1_ARGTYPE3_t arg3 = false, Action1_ARGTYPE4_t arg4 = false, Action1_ARGTYPE5_t arg5 = false);\
\
template<class TActionRequestToRun = bool>\
void RunRequest2(uint16_t AOID, Action2_ARGTYPE1_t arg1 = false, Action2_ARGTYPE2_t arg2 = false, Action2_ARGTYPE3_t arg3 = false, Action2_ARGTYPE4_t arg4 = false, Action2_ARGTYPE5_t arg5 = false);\
\
template<class TActionRequestToRun = bool>\
void RunRequest3(uint16_t AOID, Action3_ARGTYPE1_t arg1 = false, Action3_ARGTYPE2_t arg2 = false, Action3_ARGTYPE3_t arg3 = false, Action3_ARGTYPE4_t arg4 = false, Action3_ARGTYPE5_t arg5 = false);\
\
template<class TActionRequestToRun = bool>\
Token* RunRequestWithWait1(uint16_t AOID, Action1_ARGTYPE1_t arg1 = false, Action1_ARGTYPE2_t arg2 = false, Action1_ARGTYPE3_t arg3 = false, Action1_ARGTYPE4_t arg4 = false, Action1_ARGTYPE5_t arg5 = false);\
\
template<class TActionRequestToRun = bool>\
void DoneWithRequest1(Token* tokenOfRequest);\
\
template<class TActionRequestToRun = bool>\
Token* RunRequestWithWait2(uint16_t AOID, Action2_ARGTYPE1_t arg1 = false, Action2_ARGTYPE2_t arg2 = false, Action2_ARGTYPE3_t arg3 = false, Action2_ARGTYPE4_t arg4 = false, Action2_ARGTYPE5_t arg5 = false); \
\
template<class TActionRequestToRun = bool>\
void DoneWithRequest2(Token* tokenOfRequest);\
\
template<class TActionRequestToRun = bool>\
Token* RunRequestWithWait3(uint16_t AOID, Action3_ARGTYPE1_t arg1 = false, Action3_ARGTYPE2_t arg2 = false, Action3_ARGTYPE3_t arg3 = false, Action3_ARGTYPE4_t arg4 = false, Action3_ARGTYPE5_t arg5 = false); \
\
template<class TActionRequestToRun = bool>\
void DoneWithRequest3(Token* tokenOfRequest);

//macro for AEAOResource -----------------------------------------




#define TEMPLATEFOR_AESPBOUTPUT template<uint32_t OUTPUTSIZE, uint16_t NUMOFINPUTSIGNALS  ,bool IsOutputSubscribeAble, uint8_t NUMOFFILTERS, class TFilter1,class TFilter2,uint8_t Filter2LinksFrom,class TFilter3,uint8_t Filter3LinksFrom,class TFilter4,uint8_t Filter4LinksFrom,class TFilter5, uint8_t Filter5LinksFrom, \
uint32_t TheParameterNOTone1, bool isParameterNOToneInputSize1  ,\
uint32_t TheParameterNOTone2 , bool isParameterNOToneInputSize2  ,\
uint32_t TheParameterNOTone3 , bool isParameterNOToneInputSize3  ,\
uint32_t TheParameterNOTone4 , bool isParameterNOToneInputSize4  ,\
uint32_t TheParameterNOTone5, bool isParameterNOToneInputSize5  ,\
uint32_t TheParameterNOTone6, bool isParameterNOToneInputSize6  ,\
uint32_t TheParameterNOTone7, bool isParameterNOToneInputSize7  ,\
uint32_t TheParameterNOTone8, bool isParameterNOToneInputSize8  ,\
uint32_t TheParameterNOTone9, bool isParameterNOToneInputSize9  ,\
uint32_t TheParameterNOTone10, bool isParameterNOToneInputSize10 ,\
uint32_t TheParameterNOTone11, bool isParameterNOToneInputSize11  ,\
uint32_t TheParameterNOTone12, bool isParameterNOToneInputSize12 >
#define TEMPLATEFOR_AESPBOUTPARAMS OUTPUTSIZE, NUMOFINPUTSIGNALS,IsOutputSubscribeAble,NUMOFFILTERS,  TFilter1, TFilter2,Filter2LinksFrom, TFilter3,Filter3LinksFrom, TFilter4,Filter4LinksFrom, TFilter5,Filter5LinksFrom, \
TheParameterNOTone1, isParameterNOToneInputSize1, \
TheParameterNOTone2, isParameterNOToneInputSize2, \
TheParameterNOTone3, isParameterNOToneInputSize3, \
TheParameterNOTone4, isParameterNOToneInputSize4, \
TheParameterNOTone5, isParameterNOToneInputSize5, \
TheParameterNOTone6, isParameterNOToneInputSize6, \
TheParameterNOTone7, isParameterNOToneInputSize7, \
TheParameterNOTone8, isParameterNOToneInputSize8, \
TheParameterNOTone9, isParameterNOToneInputSize9, \
TheParameterNOTone10, isParameterNOToneInputSize10, \
TheParameterNOTone11, isParameterNOToneInputSize11, \
TheParameterNOTone12, isParameterNOToneInputSize12

//#endif 



#define TEMPLATESPB_Filters uint8_t NumOfFilters= 0, class TFilter1 = AENullClass, class TFilter2 = AENullClass, uint8_t Filter2LinksFrom = 0, class TFilter3 = AENullClass, uint8_t Filter3LinksFrom = 0, class TFilter4 = AENullClass, uint8_t Filter4LinksFrom = 0, class TFilter5 = AENullClass , uint8_t Filter5LinksFrom = 0
#define TEMPLATESPB_FiltersFunctionParams uint8_t NumOfFilters, class TFilter1, class TFilter2, uint8_t Filter2LinksFrom, class TFilter3, uint8_t Filter3LinksFrom, class TFilter4, uint8_t Filter4LinksFrom, class TFilter5, uint8_t Filter5LinksFrom 
#define TEMPLATESPB_FilterParams NumOfFilters, TFilter1, TFilter2,Filter2LinksFrom, TFilter3, Filter3LinksFrom,TFilter4, Filter4LinksFrom, TFilter5, Filter5LinksFrom


#define AEPOOLMANAGERTEMPLATE template<class TEvent1 , uint16_t sizeOfEvent1Pool,class TEvent2 , uint16_t sizeOfEvent2Pool,class TEvent3 , uint16_t sizeOfEvent3Pool,class TEvent4 , uint16_t sizeOfEvent4Pool, class TEvent5 , uint16_t sizeOfEvent5Pool>
#define AEPOOLMANAGERTEMPLATE_ARGS TEvent1, sizeOfEvent1Pool, TEvent2, sizeOfEvent2Pool, TEvent3, sizeOfEvent3Pool, TEvent4 , sizeOfEvent4Pool, TEvent5 , sizeOfEvent5Pool



//template for clock
#define TEMPLATEFOR_AEClock template<uint16_t NumOfSensorsIWillBeSetTo_Prescale1 = 0, \
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale1 = 0,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale1 = 0,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale2 = 0,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale2 = 0,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale2 = 0,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale4 = 0,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale4 = 0,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale4 = 0,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale8 = 0,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale8 = 0,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale8 = 0,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale16 = 0,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale16 = 0,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale16 = 0,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale32 = 0,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale32 = 0,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale32 = 0,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale64 = 0,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale64 = 0,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale64 = 0>

#define TEMPLATEFORNoDefaults_AEClock template<uint16_t NumOfSensorsIWillBeSetTo_Prescale1, \
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale1,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale1,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale2,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale2,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale2,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale4,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale4,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale4,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale8,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale8,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale8,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale16,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale16,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale16,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale32,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale32,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale32,\
uint16_t NumOfSensorsIWillBeSetTo_Prescale64,\
uint16_t NumOfInterpretorsIWillBeSetTo_Prescale64,\
uint16_t NumOfTDUsIWillBeSetTo_Prescale64>

#define TEMPLATEFORParams_AEClock NumOfSensorsIWillBeSetTo_Prescale1, \
 NumOfInterpretorsIWillBeSetTo_Prescale1,\
 NumOfTDUsIWillBeSetTo_Prescale1,\
 NumOfSensorsIWillBeSetTo_Prescale2,\
 NumOfInterpretorsIWillBeSetTo_Prescale2,\
 NumOfTDUsIWillBeSetTo_Prescale2,\
 NumOfSensorsIWillBeSetTo_Prescale4,\
 NumOfInterpretorsIWillBeSetTo_Prescale4,\
 NumOfTDUsIWillBeSetTo_Prescale4,\
 NumOfSensorsIWillBeSetTo_Prescale8,\
 NumOfInterpretorsIWillBeSetTo_Prescale8,\
 NumOfTDUsIWillBeSetTo_Prescale8,\
 NumOfSensorsIWillBeSetTo_Prescale16,\
 NumOfInterpretorsIWillBeSetTo_Prescale16,\
 NumOfTDUsIWillBeSetTo_Prescale16,\
 NumOfSensorsIWillBeSetTo_Prescale32,\
 NumOfInterpretorsIWillBeSetTo_Prescale32,\
 NumOfTDUsIWillBeSetTo_Prescale32,\
 NumOfSensorsIWillBeSetTo_Prescale64,\
 NumOfInterpretorsIWillBeSetTo_Prescale64,\
 NumOfTDUsIWillBeSetTo_Prescale64







