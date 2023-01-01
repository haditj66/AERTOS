//generated file: AEObjects.h
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.

#pragma once
#include "AEUtils.h"


//

#include "AE.h" 

//#include "AllPeripheralsHeaders.h"


//macro for being able to check if a macro is empty --------------------------------------
#define DO_EXPAND(VAL)  VAL ## 1
#define EXPAND(VAL)     DO_EXPAND(VAL)

//macro for static pointers ------------------------------------------------------------
#define S_CONC(A, B) S_CONC_(A, B)
#define S_CONC_(A, B) A * B ; 
#define SS_CONC(A, B) SS_CONC_(A, B)
//AECHANGED: used to be #define SS_CONC_(A, B) static A * B ; 
#define SS_CONC_(A, B) A * B ; 
//AECHANGEDDONE:

#define H_CONC(A) H_CONC_(A)
#define H_CONC_(A) A.h

//macro for static pointers ------------------------------------------------------------
#define A_CONC(A, B) A_CONC(A, B)
#define A_CONC_(A, B) A B 

#define Q(x) #x
#define QUOTE(x) Q(x)

class UIHolterMonitorFSM;
extern UIHolterMonitorFSM* FSMHolterUI;




//#include "AE_TDUAsService.h"
//#include "AETDUAsPossession.h"

//#include "VarSaver_AR.h"

//#include "stmFlashConf0\stmFlashConf0_FlashPeriph.h"

//#include "VarConfigurationCG.h"


//#include "VarSaverObjects.h"
//#include "SaveVariable.h"
//#include "VarConfigurationCG.h"
//#include "FreeRTOS.h"
//#include "VarSaver_AR.h"
//#include "SaveVariableBase.h" 
//#include "SaveVarTypeEnum.h" 

 

//other needed includes used by the AOs 
#if (defined(AnyOtherNeededIncludes1) && (EXPAND(AnyOtherNeededIncludes1) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes1))
#endif

#if (defined(AnyOtherNeededIncludes2) && (EXPAND(AnyOtherNeededIncludes2) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes2))
#endif

#if (defined(AnyOtherNeededIncludes3) && (EXPAND(AnyOtherNeededIncludes3) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes3))
#endif
 
#if (defined(AnyOtherNeededIncludes4) && (EXPAND(AnyOtherNeededIncludes4) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes4))
#endif

#if (defined(AnyOtherNeededIncludes5) && (EXPAND(AnyOtherNeededIncludes5) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes5))
#endif

#if (defined(AnyOtherNeededIncludes6) && (EXPAND(AnyOtherNeededIncludes6) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes6))
#endif

#if (defined(AnyOtherNeededIncludes7) && (EXPAND(AnyOtherNeededIncludes7) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes7))
#endif

#if (defined(AnyOtherNeededIncludes8) && (EXPAND(AnyOtherNeededIncludes8) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes8))
#endif

#if (defined(AnyOtherNeededIncludes9) && (EXPAND(AnyOtherNeededIncludes9) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes9))
#endif

#if (defined(AnyOtherNeededIncludes10) && (EXPAND(AnyOtherNeededIncludes10) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes10))
#endif


class AEObservorSensor;
TEMPLATEFORNoDefaults_AEClock
class AEClock;


#if (defined(AELoopObject1) && (EXPAND(AELoopObject1) == 0))  
#include QUOTE(H_CONC_(AnyOtherNeededIncludes1))
#endif



//for clocks ----------------

#define GlobalPtrToClock_1  

#define GlobalPtrToClock_2  

#define GlobalPtrToClock_3  

#define GlobalPtrToClock_4  

#define GlobalPtrToClock_5  

#define GlobalPtrToClock_6  

#define GlobalPtrToClock_7  

#define GlobalPtrToClock_8  

#define GlobalPtrToClock_9  

#define GlobalPtrToClock_10  


#if defined(ClockName1) && (EXPAND(ClockName1) == 0) 
extern ClockType1 * ClockName1;
#define GlobalPtrToClock_1 SS_CONC_(ClockType1, ClockName1)
#endif 

#if defined(ClockName2) && (EXPAND(ClockName2) == 0) 
extern ClockType2 * ClockName2;
#define GlobalPtrToClock_2 SS_CONC_(ClockType2, ClockName2)
#endif 

#if defined(ClockName3) && (EXPAND(ClockName3) == 0) 
extern ClockType3 * ClockName3;
#define GlobalPtrToClock_3 SS_CONC_(ClockType3, ClockName3)
#endif 

#if defined(ClockName4) && (EXPAND(ClockName4) == 0) 
extern ClockType4 * ClockName4;
#define GlobalPtrToClock_4 SS_CONC_(ClockType4, ClockName4)
#endif 

#if defined(ClockName5) && (EXPAND(ClockName5) == 0) 
extern ClockType5 * ClockName5;
#define GlobalPtrToClock_5 SS_CONC_(ClockType5, ClockName5)
#endif 

#if defined(ClockName6) && (EXPAND(ClockName6) == 0) 
extern ClockType6 * ClockName6;
#define GlobalPtrToClock_6 SS_CONC_(ClockType6, ClockName6)
#endif 

#if defined(ClockName7) && (EXPAND(ClockName7) == 0) 
extern ClockType7 * ClockName7;
#define GlobalPtrToClock_7 SS_CONC_(ClockType7, ClockName7)
#endif 

#if defined(ClockName8) && (EXPAND(ClockName8) == 0) 
extern ClockType8 * ClockName8;
#define GlobalPtrToClock_8 SS_CONC_(ClockType8, ClockName8)
#endif 

#if defined(ClockName9) && (EXPAND(ClockName9) == 0) 
extern ClockType9 * ClockName9;
#define GlobalPtrToClock_9 SS_CONC_(ClockType9, ClockName9)
#endif 

#if defined(ClockName10) && (EXPAND(ClockName10) == 0) 
extern ClockType10 * ClockName10;
#define GlobalPtrToClock_10 SS_CONC_(ClockType10, ClockName10)
#endif 


//for sensors -------------------------

#define GlobalPtrToSensor_1  

#define GlobalPtrToSensor_2  

#define GlobalPtrToSensor_3  

#define GlobalPtrToSensor_4  

#define GlobalPtrToSensor_5  

#define GlobalPtrToSensor_6  

#define GlobalPtrToSensor_7  

#define GlobalPtrToSensor_8  

#define GlobalPtrToSensor_9  

#define GlobalPtrToSensor_10  

#define GlobalPtrToSensor_11  

#define GlobalPtrToSensor_12  

#define GlobalPtrToSensor_13  

#define GlobalPtrToSensor_14  

#define GlobalPtrToSensor_15  

#define GlobalPtrToSensor_16  

#define GlobalPtrToSensor_17  

#define GlobalPtrToSensor_18  

#define GlobalPtrToSensor_19  

#define GlobalPtrToSensor_20  


#if defined(SensorName1) && (EXPAND(SensorName1) == 0) 
extern AEObservorSensor * SensorName1;
#define GlobalPtrToSensor_1  AEObservorSensor * SensorName1;
#endif

#if defined(SensorName2) && (EXPAND(SensorName2) == 0) 
extern AEObservorSensor * SensorName2;
#define GlobalPtrToSensor_2  AEObservorSensor * SensorName2;
#endif

#if defined(SensorName3) && (EXPAND(SensorName3) == 0) 
extern AEObservorSensor * SensorName3;
#define GlobalPtrToSensor_3  AEObservorSensor * SensorName3;
#endif

#if defined(SensorName4) && (EXPAND(SensorName4) == 0) 
extern AEObservorSensor * SensorName4;
#define GlobalPtrToSensor_4  AEObservorSensor * SensorName4;
#endif

#if defined(SensorName5) && (EXPAND(SensorName5) == 0) 
extern AEObservorSensor * SensorName5;
#define GlobalPtrToSensor_5  AEObservorSensor * SensorName5;
#endif

#if defined(SensorName6) && (EXPAND(SensorName6) == 0) 
extern AEObservorSensor * SensorName6;
#define GlobalPtrToSensor_6  AEObservorSensor * SensorName6;
#endif

#if defined(SensorName7) && (EXPAND(SensorName7) == 0) 
extern AEObservorSensor * SensorName7;
#define GlobalPtrToSensor_7  AEObservorSensor * SensorName7;
#endif

#if defined(SensorName8) && (EXPAND(SensorName8) == 0) 
extern AEObservorSensor * SensorName8;
#define GlobalPtrToSensor_8  AEObservorSensor * SensorName8;
#endif

#if defined(SensorName9) && (EXPAND(SensorName9) == 0) 
extern AEObservorSensor * SensorName9;
#define GlobalPtrToSensor_9  AEObservorSensor * SensorName9;
#endif

#if defined(SensorName10) && (EXPAND(SensorName10) == 0) 
extern AEObservorSensor * SensorName10;
#define GlobalPtrToSensor_10  AEObservorSensor * SensorName10;
#endif

#if defined(SensorName11) && (EXPAND(SensorName11) == 0) 
extern AEObservorSensor * SensorName11;
#define GlobalPtrToSensor_11  AEObservorSensor * SensorName11;
#endif

#if defined(SensorName12) && (EXPAND(SensorName12) == 0) 
extern AEObservorSensor * SensorName12;
#define GlobalPtrToSensor_12  AEObservorSensor * SensorName12;
#endif

#if defined(SensorName13) && (EXPAND(SensorName13) == 0) 
extern AEObservorSensor * SensorName13;
#define GlobalPtrToSensor_13  AEObservorSensor * SensorName13;
#endif

#if defined(SensorName14) && (EXPAND(SensorName14) == 0) 
extern AEObservorSensor * SensorName14;
#define GlobalPtrToSensor_14  AEObservorSensor * SensorName14;
#endif

#if defined(SensorName15) && (EXPAND(SensorName15) == 0) 
extern AEObservorSensor * SensorName15;
#define GlobalPtrToSensor_15  AEObservorSensor * SensorName15;
#endif

#if defined(SensorName16) && (EXPAND(SensorName16) == 0) 
extern AEObservorSensor * SensorName16;
#define GlobalPtrToSensor_16  AEObservorSensor * SensorName16;
#endif

#if defined(SensorName17) && (EXPAND(SensorName17) == 0) 
extern AEObservorSensor * SensorName17;
#define GlobalPtrToSensor_17  AEObservorSensor * SensorName17;
#endif

#if defined(SensorName18) && (EXPAND(SensorName18) == 0) 
extern AEObservorSensor * SensorName18;
#define GlobalPtrToSensor_18  AEObservorSensor * SensorName18;
#endif

#if defined(SensorName19) && (EXPAND(SensorName19) == 0) 
extern AEObservorSensor * SensorName19;
#define GlobalPtrToSensor_19  AEObservorSensor * SensorName19;
#endif

#if defined(SensorName20) && (EXPAND(SensorName20) == 0) 
extern AEObservorSensor * SensorName20;
#define GlobalPtrToSensor_20  AEObservorSensor * SensorName20;
#endif




//for AOs ----------------------------------------------

#define GlobalPtrToAO1_1 //define it here first so that the default value is empty
#define GlobalPtrToAO1_2
#define GlobalPtrToAO1_3
#define GlobalPtrToAO1_4
#define GlobalPtrToAO1_5 

#if (defined(AOInclude1) && (EXPAND(AOInclude1) == 0)) 

#include QUOTE(H_CONC_(AOInclude1))
#if  (defined(NameSpaceToAO1) && (EXPAND(NameSpaceToAO1) == 0))
#define NamespaceToSet1 A_CONC_(NameSpaceToAO1, ::)
#else
#define NamespaceToSet1
#endif


#if defined(InstanceNameOfAO1_1) && (EXPAND(InstanceNameOfAO1_1) == 0)
#define GlobalPtrToAO1_1 S_CONC_(A_CONC_(NamespaceToSet1,TypeOfAO1_1), InstanceNameOfAO1_1) //TypeOfAO1_1 * TypeOfAO1_1::InstanceNameOfAO1_1;
extern A_CONC_(NamespaceToSet1, TypeOfAO1_1)  * InstanceNameOfAO1_1;
#endif
#if defined(InstanceNameOfAO1_2) && (EXPAND(InstanceNameOfAO1_2) == 0)
#define GlobalPtrToAO1_2 S_CONC_(A_CONC_(NamespaceToSet1,TypeOfAO1_2), InstanceNameOfAO1_2) //TypeOfAO1_2 * TypeOfAO1_2::InstanceNameOfAO1_2;
extern A_CONC_(NamespaceToSet1, TypeOfAO1_2)  * InstanceNameOfAO1_2;
#endif
#if defined(InstanceNameOfAO1_3) && (EXPAND(InstanceNameOfAO1_3) == 0)
#define GlobalPtrToAO1_3 S_CONC_(A_CONC_(NamespaceToSet1,TypeOfAO1_3), InstanceNameOfAO1_3) //TypeOfAO1_3 * TypeOfAO1_3::InstanceNameOfAO1_3;
extern A_CONC_(NamespaceToSet1, TypeOfAO1_3)  * InstanceNameOfAO1_3;
#endif
#if defined(InstanceNameOfAO1_4) && (EXPAND(InstanceNameOfAO1_4) == 0)
#define GlobalPtrToAO1_4 S_CONC_(A_CONC_(NamespaceToSet1,TypeOfAO1_4), InstanceNameOfAO1_4) //TypeOfAO1_4 * TypeOfAO1_4::InstanceNameOfAO1_4;
extern A_CONC_(NamespaceToSet1, TypeOfAO1_4)  * InstanceNameOfAO1_4;
#endif
#if defined(InstanceNameOfAO1_5) && (EXPAND(InstanceNameOfAO1_5) == 0)
#define GlobalPtrToAO1_5 S_CONC_(A_CONC_(NamespaceToSet1,TypeOfAO1_5), InstanceNameOfAO1_5) //TypeOfAO1_5 * TypeOfAO1_5::InstanceNameOfAO1_5;
extern A_CONC_(NamespaceToSet1, TypeOfAO1_5)  * InstanceNameOfAO1_5;
#endif

#endif


#define GlobalPtrToAO2_1 //define it here first so that the default value is empty
#define GlobalPtrToAO2_2
#define GlobalPtrToAO2_3
#define GlobalPtrToAO2_4
#define GlobalPtrToAO2_5 

#if (defined(AOInclude2) && (EXPAND(AOInclude2) == 0)) 

#include QUOTE(H_CONC_(AOInclude2))

#if  (defined(NameSpaceToAO2) && (EXPAND(NameSpaceToAO2) == 0))
#define NamespaceToSet2 A_CONC_(NameSpaceToAO2, ::)
#else
#define NamespaceToSet2
#endif


#if defined(InstanceNameOfAO2_1) && (EXPAND(InstanceNameOfAO2_1) == 0)
#define GlobalPtrToAO2_1 S_CONC_(A_CONC_(NamespaceToSet2,TypeOfAO2_1), InstanceNameOfAO2_1) //TypeOfAO2_1 * TypeOfAO2_1::InstanceNameOfAO2_1;
extern A_CONC_(NamespaceToSet2, TypeOfAO2_1)  * InstanceNameOfAO2_1;
#endif
#if defined(InstanceNameOfAO2_2) && (EXPAND(InstanceNameOfAO2_2) == 0)
#define GlobalPtrToAO2_2 S_CONC_(A_CONC_(NamespaceToSet2,TypeOfAO2_2), InstanceNameOfAO2_2) //TypeOfAO2_2 * TypeOfAO2_2::InstanceNameOfAO2_2;
extern A_CONC_(NamespaceToSet2, TypeOfAO2_2)  * InstanceNameOfAO2_2;
#endif
#if defined(InstanceNameOfAO2_3) && (EXPAND(InstanceNameOfAO2_3) == 0)
#define GlobalPtrToAO2_3 S_CONC_(A_CONC_(NamespaceToSet2,TypeOfAO2_3), InstanceNameOfAO2_3) //TypeOfAO2_3 * TypeOfAO2_3::InstanceNameOfAO2_3;
extern A_CONC_(NamespaceToSet2, TypeOfAO2_3)  * InstanceNameOfAO2_3;
#endif
#if defined(InstanceNameOfAO2_4) && (EXPAND(InstanceNameOfAO2_4) == 0)
#define GlobalPtrToAO2_4 S_CONC_(A_CONC_(NamespaceToSet2,TypeOfAO2_4), InstanceNameOfAO2_4) //TypeOfAO2_4 * TypeOfAO2_4::InstanceNameOfAO2_4;
extern A_CONC_(NamespaceToSet2, TypeOfAO2_4)  * InstanceNameOfAO2_4;
#endif
#if defined(InstanceNameOfAO2_5) && (EXPAND(InstanceNameOfAO2_5) == 0)
#define GlobalPtrToAO2_5 S_CONC_(A_CONC_(NamespaceToSet2,TypeOfAO2_5), InstanceNameOfAO2_5) //TypeOfAO2_5 * TypeOfAO2_5::InstanceNameOfAO2_5;
extern A_CONC_(NamespaceToSet2, TypeOfAO2_5)  * InstanceNameOfAO2_5;
#endif

#endif


#define GlobalPtrToAO3_1 //define it here first so that the default value is empty
#define GlobalPtrToAO3_2
#define GlobalPtrToAO3_3
#define GlobalPtrToAO3_4
#define GlobalPtrToAO3_5 

#if (defined(AOInclude3) && (EXPAND(AOInclude3) == 0)) 

#include QUOTE(H_CONC_(AOInclude3))
#if  (defined(NameSpaceToAO3) && (EXPAND(NameSpaceToAO3) == 0))
#define NamespaceToSet3 A_CONC_(NameSpaceToAO3, ::)
#else
#define NamespaceToSet3
#endif


#if defined(InstanceNameOfAO3_1) && (EXPAND(InstanceNameOfAO3_1) == 0)
#define GlobalPtrToAO3_1 S_CONC_(A_CONC_(NamespaceToSet3,TypeOfAO3_1), InstanceNameOfAO3_1) //TypeOfAO3_1 * TypeOfAO3_1::InstanceNameOfAO3_1;
extern A_CONC_(NamespaceToSet3, TypeOfAO3_1)  * InstanceNameOfAO3_1;
#endif
#if defined(InstanceNameOfAO3_2) && (EXPAND(InstanceNameOfAO3_2) == 0)
#define GlobalPtrToAO3_2 S_CONC_(A_CONC_(NamespaceToSet3,TypeOfAO3_2), InstanceNameOfAO3_2) //TypeOfAO3_2 * TypeOfAO3_2::InstanceNameOfAO3_2;
extern A_CONC_(NamespaceToSet3, TypeOfAO3_2)  * InstanceNameOfAO3_2;
#endif
#if defined(InstanceNameOfAO3_3) && (EXPAND(InstanceNameOfAO3_3) == 0)
#define GlobalPtrToAO3_3 S_CONC_(A_CONC_(NamespaceToSet3,TypeOfAO3_3), InstanceNameOfAO3_3) //TypeOfAO3_3 * TypeOfAO3_3::InstanceNameOfAO3_3;
extern A_CONC_(NamespaceToSet3, TypeOfAO3_3)  * InstanceNameOfAO3_3;
#endif
#if defined(InstanceNameOfAO3_4) && (EXPAND(InstanceNameOfAO3_4) == 0)
#define GlobalPtrToAO3_4 S_CONC_(A_CONC_(NamespaceToSet3,TypeOfAO3_4), InstanceNameOfAO3_4) //TypeOfAO3_4 * TypeOfAO3_4::InstanceNameOfAO3_4;
extern A_CONC_(NamespaceToSet3, TypeOfAO3_4)  * InstanceNameOfAO3_4;
#endif
#if defined(InstanceNameOfAO3_5) && (EXPAND(InstanceNameOfAO3_5) == 0)
#define GlobalPtrToAO3_5 S_CONC_(A_CONC_(NamespaceToSet3,TypeOfAO3_5), InstanceNameOfAO3_5) //TypeOfAO3_5 * TypeOfAO3_5::InstanceNameOfAO3_5;
extern A_CONC_(NamespaceToSet3, TypeOfAO3_5)  * InstanceNameOfAO3_5;
#endif

#endif


#define GlobalPtrToAO4_1 //define it here first so that the default value is empty
#define GlobalPtrToAO4_2
#define GlobalPtrToAO4_3
#define GlobalPtrToAO4_4
#define GlobalPtrToAO4_5 

#if (defined(AOInclude4) && (EXPAND(AOInclude4) == 0)) 

#include QUOTE(H_CONC_(AOInclude4))
#if  (defined(NameSpaceToAO4) && (EXPAND(NameSpaceToAO4) == 0))
#define NamespaceToSet4 A_CONC_(NameSpaceToAO4, ::)
#else
#define NamespaceToSet4
#endif

//class w25DriverTDU;

#if defined(InstanceNameOfAO4_1) && (EXPAND(InstanceNameOfAO4_1) == 0)
#define GlobalPtrToAO4_1 S_CONC_(A_CONC_(NamespaceToSet4,TypeOfAO4_1), InstanceNameOfAO4_1) //TypeOfAO4_1 * TypeOfAO4_1::InstanceNameOfAO4_1;
extern A_CONC_(NamespaceToSet4, TypeOfAO4_1)  * InstanceNameOfAO4_1;
#endif
#if defined(InstanceNameOfAO4_2) && (EXPAND(InstanceNameOfAO4_2) == 0)
#define GlobalPtrToAO4_2 S_CONC_(A_CONC_(NamespaceToSet4,TypeOfAO4_2), InstanceNameOfAO4_2) //TypeOfAO4_2 * TypeOfAO4_2::InstanceNameOfAO4_2;
extern A_CONC_(NamespaceToSet4, TypeOfAO4_2)  * InstanceNameOfAO4_2;
#endif
#if defined(InstanceNameOfAO4_3) && (EXPAND(InstanceNameOfAO4_3) == 0)
#define GlobalPtrToAO4_3 S_CONC_(A_CONC_(NamespaceToSet4,TypeOfAO4_3), InstanceNameOfAO4_3) //TypeOfAO4_3 * TypeOfAO4_3::InstanceNameOfAO4_3;
extern A_CONC_(NamespaceToSet4, TypeOfAO4_3)  * InstanceNameOfAO4_3;
#endif
#if defined(InstanceNameOfAO4_4) && (EXPAND(InstanceNameOfAO4_4) == 0)
#define GlobalPtrToAO4_4 S_CONC_(A_CONC_(NamespaceToSet4,TypeOfAO4_4), InstanceNameOfAO4_4) //TypeOfAO4_4 * TypeOfAO4_4::InstanceNameOfAO4_4;
extern A_CONC_(NamespaceToSet4, TypeOfAO4_4)  * InstanceNameOfAO4_4;
#endif
#if defined(InstanceNameOfAO4_5) && (EXPAND(InstanceNameOfAO4_5) == 0)
#define GlobalPtrToAO4_5 S_CONC_(A_CONC_(NamespaceToSet4,TypeOfAO4_5), InstanceNameOfAO4_5) //TypeOfAO4_5 * TypeOfAO4_5::InstanceNameOfAO4_5;
extern A_CONC_(NamespaceToSet4, TypeOfAO4_5)  * InstanceNameOfAO4_5;
#endif

#endif


#define GlobalPtrToAO5_1 //define it here first so that the default value is empty
#define GlobalPtrToAO5_2
#define GlobalPtrToAO5_3
#define GlobalPtrToAO5_4
#define GlobalPtrToAO5_5 

#if (defined(AOInclude5) && (EXPAND(AOInclude5) == 0)) 

#include QUOTE(H_CONC_(AOInclude5))
#if  (defined(NameSpaceToAO5) && (EXPAND(NameSpaceToAO5) == 0))
#define NamespaceToSet5 A_CONC_(NameSpaceToAO5, ::)
#else
#define NamespaceToSet5
#endif


#if defined(InstanceNameOfAO5_1) && (EXPAND(InstanceNameOfAO5_1) == 0)
#define GlobalPtrToAO5_1 S_CONC_(A_CONC_(NamespaceToSet5,TypeOfAO5_1), InstanceNameOfAO5_1) //TypeOfAO5_1 * TypeOfAO5_1::InstanceNameOfAO5_1;
extern A_CONC_(NamespaceToSet5, TypeOfAO5_1)  * InstanceNameOfAO5_1;
#endif
#if defined(InstanceNameOfAO5_2) && (EXPAND(InstanceNameOfAO5_2) == 0)
#define GlobalPtrToAO5_2 S_CONC_(A_CONC_(NamespaceToSet5,TypeOfAO5_2), InstanceNameOfAO5_2) //TypeOfAO5_2 * TypeOfAO5_2::InstanceNameOfAO5_2;
extern A_CONC_(NamespaceToSet5, TypeOfAO5_2)  * InstanceNameOfAO5_2;
#endif
#if defined(InstanceNameOfAO5_3) && (EXPAND(InstanceNameOfAO5_3) == 0)
#define GlobalPtrToAO5_3 S_CONC_(A_CONC_(NamespaceToSet5,TypeOfAO5_3), InstanceNameOfAO5_3) //TypeOfAO5_3 * TypeOfAO5_3::InstanceNameOfAO5_3;
extern A_CONC_(NamespaceToSet5, TypeOfAO5_3)  * InstanceNameOfAO5_3;
#endif
#if defined(InstanceNameOfAO5_4) && (EXPAND(InstanceNameOfAO5_4) == 0)
#define GlobalPtrToAO5_4 S_CONC_(A_CONC_(NamespaceToSet5,TypeOfAO5_4), InstanceNameOfAO5_4) //TypeOfAO5_4 * TypeOfAO5_4::InstanceNameOfAO5_4;
extern A_CONC_(NamespaceToSet5, TypeOfAO5_4)  * InstanceNameOfAO5_4;
#endif
#if defined(InstanceNameOfAO5_5) && (EXPAND(InstanceNameOfAO5_5) == 0)
#define GlobalPtrToAO5_5 S_CONC_(A_CONC_(NamespaceToSet5,TypeOfAO5_5), InstanceNameOfAO5_5) //TypeOfAO5_5 * TypeOfAO5_5::InstanceNameOfAO5_5;
extern A_CONC_(NamespaceToSet5, TypeOfAO5_5)  * InstanceNameOfAO5_5;
#endif

#endif


#define GlobalPtrToAO6_1 //define it here first so that the default value is empty
#define GlobalPtrToAO6_2
#define GlobalPtrToAO6_3
#define GlobalPtrToAO6_4
#define GlobalPtrToAO6_5 

#if (defined(AOInclude6) && (EXPAND(AOInclude6) == 0)) 

#include QUOTE(H_CONC_(AOInclude6))
#if  (defined(NameSpaceToAO6) && (EXPAND(NameSpaceToAO6) == 0))
#define NamespaceToSet6 A_CONC_(NameSpaceToAO6, ::)
#else
#define NamespaceToSet6
#endif


#if defined(InstanceNameOfAO6_1) && (EXPAND(InstanceNameOfAO6_1) == 0)
#define GlobalPtrToAO6_1 S_CONC_(A_CONC_(NamespaceToSet6,TypeOfAO6_1), InstanceNameOfAO6_1) //TypeOfAO6_1 * TypeOfAO6_1::InstanceNameOfAO6_1;
extern A_CONC_(NamespaceToSet6, TypeOfAO6_1)  * InstanceNameOfAO6_1;
#endif
#if defined(InstanceNameOfAO6_2) && (EXPAND(InstanceNameOfAO6_2) == 0)
#define GlobalPtrToAO6_2 S_CONC_(A_CONC_(NamespaceToSet6,TypeOfAO6_2), InstanceNameOfAO6_2) //TypeOfAO6_2 * TypeOfAO6_2::InstanceNameOfAO6_2;
extern A_CONC_(NamespaceToSet6, TypeOfAO6_2)  * InstanceNameOfAO6_2;
#endif
#if defined(InstanceNameOfAO6_3) && (EXPAND(InstanceNameOfAO6_3) == 0)
#define GlobalPtrToAO6_3 S_CONC_(A_CONC_(NamespaceToSet6,TypeOfAO6_3), InstanceNameOfAO6_3) //TypeOfAO6_3 * TypeOfAO6_3::InstanceNameOfAO6_3;
extern A_CONC_(NamespaceToSet6, TypeOfAO6_3)  * InstanceNameOfAO6_3;
#endif
#if defined(InstanceNameOfAO6_4) && (EXPAND(InstanceNameOfAO6_4) == 0)
#define GlobalPtrToAO6_4 S_CONC_(A_CONC_(NamespaceToSet6,TypeOfAO6_4), InstanceNameOfAO6_4) //TypeOfAO6_4 * TypeOfAO6_4::InstanceNameOfAO6_4;
extern A_CONC_(NamespaceToSet6, TypeOfAO6_4)  * InstanceNameOfAO6_4;
#endif
#if defined(InstanceNameOfAO6_5) && (EXPAND(InstanceNameOfAO6_5) == 0)
#define GlobalPtrToAO6_5 S_CONC_(A_CONC_(NamespaceToSet6,TypeOfAO6_5), InstanceNameOfAO6_5) //TypeOfAO6_5 * TypeOfAO6_5::InstanceNameOfAO6_5;
extern A_CONC_(NamespaceToSet6, TypeOfAO6_5)  * InstanceNameOfAO6_5;
#endif

#endif


#define GlobalPtrToAO7_1 //define it here first so that the default value is empty
#define GlobalPtrToAO7_2
#define GlobalPtrToAO7_3
#define GlobalPtrToAO7_4
#define GlobalPtrToAO7_5 

#if (defined(AOInclude7) && (EXPAND(AOInclude7) == 0)) 

#include QUOTE(H_CONC_(AOInclude7))
#if  (defined(NameSpaceToAO7) && (EXPAND(NameSpaceToAO7) == 0))
#define NamespaceToSet7 A_CONC_(NameSpaceToAO7, ::)
#else
#define NamespaceToSet7
#endif


#if defined(InstanceNameOfAO7_1) && (EXPAND(InstanceNameOfAO7_1) == 0)
#define GlobalPtrToAO7_1 S_CONC_(A_CONC_(NamespaceToSet7,TypeOfAO7_1), InstanceNameOfAO7_1) //TypeOfAO7_1 * TypeOfAO7_1::InstanceNameOfAO7_1;
extern A_CONC_(NamespaceToSet7, TypeOfAO7_1)  * InstanceNameOfAO7_1;
#endif
#if defined(InstanceNameOfAO7_2) && (EXPAND(InstanceNameOfAO7_2) == 0)
#define GlobalPtrToAO7_2 S_CONC_(A_CONC_(NamespaceToSet7,TypeOfAO7_2), InstanceNameOfAO7_2) //TypeOfAO7_2 * TypeOfAO7_2::InstanceNameOfAO7_2;
extern A_CONC_(NamespaceToSet7, TypeOfAO7_2)  * InstanceNameOfAO7_2;
#endif
#if defined(InstanceNameOfAO7_3) && (EXPAND(InstanceNameOfAO7_3) == 0)
#define GlobalPtrToAO7_3 S_CONC_(A_CONC_(NamespaceToSet7,TypeOfAO7_3), InstanceNameOfAO7_3) //TypeOfAO7_3 * TypeOfAO7_3::InstanceNameOfAO7_3;
extern A_CONC_(NamespaceToSet7, TypeOfAO7_3)  * InstanceNameOfAO7_3;
#endif
#if defined(InstanceNameOfAO7_4) && (EXPAND(InstanceNameOfAO7_4) == 0)
#define GlobalPtrToAO7_4 S_CONC_(A_CONC_(NamespaceToSet7,TypeOfAO7_4), InstanceNameOfAO7_4) //TypeOfAO7_4 * TypeOfAO7_4::InstanceNameOfAO7_4;
extern A_CONC_(NamespaceToSet7, TypeOfAO7_4)  * InstanceNameOfAO7_4;
#endif
#if defined(InstanceNameOfAO7_5) && (EXPAND(InstanceNameOfAO7_5) == 0)
#define GlobalPtrToAO7_5 S_CONC_(A_CONC_(NamespaceToSet7,TypeOfAO7_5), InstanceNameOfAO7_5) //TypeOfAO7_5 * TypeOfAO7_5::InstanceNameOfAO7_5;
extern A_CONC_(NamespaceToSet7, TypeOfAO7_5)  * InstanceNameOfAO7_5;
#endif

#endif


#define GlobalPtrToAO8_1 //define it here first so that the default value is empty
#define GlobalPtrToAO8_2
#define GlobalPtrToAO8_3
#define GlobalPtrToAO8_4
#define GlobalPtrToAO8_5 

#if (defined(AOInclude8) && (EXPAND(AOInclude8) == 0)) 

#include QUOTE(H_CONC_(AOInclude8))
#if  (defined(NameSpaceToAO8) && (EXPAND(NameSpaceToAO8) == 0))
#define NamespaceToSet8 A_CONC_(NameSpaceToAO8, ::)
#else
#define NamespaceToSet8
#endif


#if defined(InstanceNameOfAO8_1) && (EXPAND(InstanceNameOfAO8_1) == 0)
#define GlobalPtrToAO8_1 S_CONC_(A_CONC_(NamespaceToSet8,TypeOfAO8_1), InstanceNameOfAO8_1) //TypeOfAO8_1 * TypeOfAO8_1::InstanceNameOfAO8_1;
extern A_CONC_(NamespaceToSet8, TypeOfAO8_1)  * InstanceNameOfAO8_1;
#endif
#if defined(InstanceNameOfAO8_2) && (EXPAND(InstanceNameOfAO8_2) == 0)
#define GlobalPtrToAO8_2 S_CONC_(A_CONC_(NamespaceToSet8,TypeOfAO8_2), InstanceNameOfAO8_2) //TypeOfAO8_2 * TypeOfAO8_2::InstanceNameOfAO8_2;
extern A_CONC_(NamespaceToSet8, TypeOfAO8_2)  * InstanceNameOfAO8_2;
#endif
#if defined(InstanceNameOfAO8_3) && (EXPAND(InstanceNameOfAO8_3) == 0)
#define GlobalPtrToAO8_3 S_CONC_(A_CONC_(NamespaceToSet8,TypeOfAO8_3), InstanceNameOfAO8_3) //TypeOfAO8_3 * TypeOfAO8_3::InstanceNameOfAO8_3;
extern A_CONC_(NamespaceToSet8, TypeOfAO8_3)  * InstanceNameOfAO8_3;
#endif
#if defined(InstanceNameOfAO8_4) && (EXPAND(InstanceNameOfAO8_4) == 0)
#define GlobalPtrToAO8_4 S_CONC_(A_CONC_(NamespaceToSet8,TypeOfAO8_4), InstanceNameOfAO8_4) //TypeOfAO8_4 * TypeOfAO8_4::InstanceNameOfAO8_4;
extern A_CONC_(NamespaceToSet8, TypeOfAO8_4)  * InstanceNameOfAO8_4;
#endif
#if defined(InstanceNameOfAO8_5) && (EXPAND(InstanceNameOfAO8_5) == 0)
#define GlobalPtrToAO8_5 S_CONC_(A_CONC_(NamespaceToSet8,TypeOfAO8_5), InstanceNameOfAO8_5) //TypeOfAO8_5 * TypeOfAO8_5::InstanceNameOfAO8_5;
extern A_CONC_(NamespaceToSet8, TypeOfAO8_5)  * InstanceNameOfAO8_5;
#endif

#endif


#define GlobalPtrToAO9_1 //define it here first so that the default value is empty
#define GlobalPtrToAO9_2
#define GlobalPtrToAO9_3
#define GlobalPtrToAO9_4
#define GlobalPtrToAO9_5 

#if (defined(AOInclude9) && (EXPAND(AOInclude9) == 0)) 

#include QUOTE(H_CONC_(AOInclude9))
#if  (defined(NameSpaceToAO9) && (EXPAND(NameSpaceToAO9) == 0))
#define NamespaceToSet9 A_CONC_(NameSpaceToAO9, ::)
#else
#define NamespaceToSet9
#endif


#if defined(InstanceNameOfAO9_1) && (EXPAND(InstanceNameOfAO9_1) == 0)
#define GlobalPtrToAO9_1 S_CONC_(A_CONC_(NamespaceToSet9,TypeOfAO9_1), InstanceNameOfAO9_1) //TypeOfAO9_1 * TypeOfAO9_1::InstanceNameOfAO9_1;
extern A_CONC_(NamespaceToSet9, TypeOfAO9_1)  * InstanceNameOfAO9_1;
#endif
#if defined(InstanceNameOfAO9_2) && (EXPAND(InstanceNameOfAO9_2) == 0)
#define GlobalPtrToAO9_2 S_CONC_(A_CONC_(NamespaceToSet9,TypeOfAO9_2), InstanceNameOfAO9_2) //TypeOfAO9_2 * TypeOfAO9_2::InstanceNameOfAO9_2;
extern A_CONC_(NamespaceToSet9, TypeOfAO9_2)  * InstanceNameOfAO9_2;
#endif
#if defined(InstanceNameOfAO9_3) && (EXPAND(InstanceNameOfAO9_3) == 0)
#define GlobalPtrToAO9_3 S_CONC_(A_CONC_(NamespaceToSet9,TypeOfAO9_3), InstanceNameOfAO9_3) //TypeOfAO9_3 * TypeOfAO9_3::InstanceNameOfAO9_3;
extern A_CONC_(NamespaceToSet9, TypeOfAO9_3)  * InstanceNameOfAO9_3;
#endif
#if defined(InstanceNameOfAO9_4) && (EXPAND(InstanceNameOfAO9_4) == 0)
#define GlobalPtrToAO9_4 S_CONC_(A_CONC_(NamespaceToSet9,TypeOfAO9_4), InstanceNameOfAO9_4) //TypeOfAO9_4 * TypeOfAO9_4::InstanceNameOfAO9_4;
extern A_CONC_(NamespaceToSet9, TypeOfAO9_4)  * InstanceNameOfAO9_4;
#endif
#if defined(InstanceNameOfAO9_5) && (EXPAND(InstanceNameOfAO9_5) == 0)
#define GlobalPtrToAO9_5 S_CONC_(A_CONC_(NamespaceToSet9,TypeOfAO9_5), InstanceNameOfAO9_5) //TypeOfAO9_5 * TypeOfAO9_5::InstanceNameOfAO9_5;
extern A_CONC_(NamespaceToSet9, TypeOfAO9_5)  * InstanceNameOfAO9_5;
#endif

#endif


#define GlobalPtrToAO10_1 //define it here first so that the default value is empty
#define GlobalPtrToAO10_2
#define GlobalPtrToAO10_3
#define GlobalPtrToAO10_4
#define GlobalPtrToAO10_5 

#if (defined(AOInclude10) && (EXPAND(AOInclude10) == 0)) 

#include QUOTE(H_CONC_(AOInclude10))
#if  (defined(NameSpaceToAO10) && (EXPAND(NameSpaceToAO10) == 0))
#define NamespaceToSet10 A_CONC_(NameSpaceToAO10, ::)
#else
#define NamespaceToSet10
#endif


#if defined(InstanceNameOfAO10_1) && (EXPAND(InstanceNameOfAO10_1) == 0)
#define GlobalPtrToAO10_1 S_CONC_(A_CONC_(NamespaceToSet10,TypeOfAO10_1), InstanceNameOfAO10_1) //TypeOfAO10_1 * TypeOfAO10_1::InstanceNameOfAO10_1;
extern A_CONC_(NamespaceToSet10, TypeOfAO10_1)  * InstanceNameOfAO10_1;
#endif
#if defined(InstanceNameOfAO10_2) && (EXPAND(InstanceNameOfAO10_2) == 0)
#define GlobalPtrToAO10_2 S_CONC_(A_CONC_(NamespaceToSet10,TypeOfAO10_2), InstanceNameOfAO10_2) //TypeOfAO10_2 * TypeOfAO10_2::InstanceNameOfAO10_2;
extern A_CONC_(NamespaceToSet10, TypeOfAO10_2)  * InstanceNameOfAO10_2;
#endif
#if defined(InstanceNameOfAO10_3) && (EXPAND(InstanceNameOfAO10_3) == 0)
#define GlobalPtrToAO10_3 S_CONC_(A_CONC_(NamespaceToSet10,TypeOfAO10_3), InstanceNameOfAO10_3) //TypeOfAO10_3 * TypeOfAO10_3::InstanceNameOfAO10_3;
extern A_CONC_(NamespaceToSet10, TypeOfAO10_3)  * InstanceNameOfAO10_3;
#endif
#if defined(InstanceNameOfAO10_4) && (EXPAND(InstanceNameOfAO10_4) == 0)
#define GlobalPtrToAO10_4 S_CONC_(A_CONC_(NamespaceToSet10,TypeOfAO10_4), InstanceNameOfAO10_4) //TypeOfAO10_4 * TypeOfAO10_4::InstanceNameOfAO10_4;
extern A_CONC_(NamespaceToSet10, TypeOfAO10_4)  * InstanceNameOfAO10_4;
#endif
#if defined(InstanceNameOfAO10_5) && (EXPAND(InstanceNameOfAO10_5) == 0)
#define GlobalPtrToAO10_5 S_CONC_(A_CONC_(NamespaceToSet10,TypeOfAO10_5), InstanceNameOfAO10_5) //TypeOfAO10_5 * TypeOfAO10_5::InstanceNameOfAO10_5;
extern A_CONC_(NamespaceToSet10, TypeOfAO10_5)  * InstanceNameOfAO10_5;
#endif

#endif


#define GlobalPtrToAO11_1 //define it here first so that the default value is empty
#define GlobalPtrToAO11_2
#define GlobalPtrToAO11_3
#define GlobalPtrToAO11_4
#define GlobalPtrToAO11_5 

#if (defined(AOInclude11) && (EXPAND(AOInclude11) == 0)) 

#include QUOTE(H_CONC_(AOInclude11))
#if  (defined(NameSpaceToAO11) && (EXPAND(NameSpaceToAO11) == 0))
#define NamespaceToSet11 A_CONC_(NameSpaceToAO11, ::)
#else
#define NamespaceToSet11
#endif


#if defined(InstanceNameOfAO11_1) && (EXPAND(InstanceNameOfAO11_1) == 0)
#define GlobalPtrToAO11_1 S_CONC_(A_CONC_(NamespaceToSet11,TypeOfAO11_1), InstanceNameOfAO11_1) //TypeOfAO11_1 * TypeOfAO11_1::InstanceNameOfAO11_1;
extern A_CONC_(NamespaceToSet11, TypeOfAO11_1)  * InstanceNameOfAO11_1;
#endif
#if defined(InstanceNameOfAO11_2) && (EXPAND(InstanceNameOfAO11_2) == 0)
#define GlobalPtrToAO11_2 S_CONC_(A_CONC_(NamespaceToSet11,TypeOfAO11_2), InstanceNameOfAO11_2) //TypeOfAO11_2 * TypeOfAO11_2::InstanceNameOfAO11_2;
extern A_CONC_(NamespaceToSet11, TypeOfAO11_2)  * InstanceNameOfAO11_2;
#endif
#if defined(InstanceNameOfAO11_3) && (EXPAND(InstanceNameOfAO11_3) == 0)
#define GlobalPtrToAO11_3 S_CONC_(A_CONC_(NamespaceToSet11,TypeOfAO11_3), InstanceNameOfAO11_3) //TypeOfAO11_3 * TypeOfAO11_3::InstanceNameOfAO11_3;
extern A_CONC_(NamespaceToSet11, TypeOfAO11_3)  * InstanceNameOfAO11_3;
#endif
#if defined(InstanceNameOfAO11_4) && (EXPAND(InstanceNameOfAO11_4) == 0)
#define GlobalPtrToAO11_4 S_CONC_(A_CONC_(NamespaceToSet11,TypeOfAO11_4), InstanceNameOfAO11_4) //TypeOfAO11_4 * TypeOfAO11_4::InstanceNameOfAO11_4;
extern A_CONC_(NamespaceToSet11, TypeOfAO11_4)  * InstanceNameOfAO11_4;
#endif
#if defined(InstanceNameOfAO11_5) && (EXPAND(InstanceNameOfAO11_5) == 0)
#define GlobalPtrToAO11_5 S_CONC_(A_CONC_(NamespaceToSet11,TypeOfAO11_5), InstanceNameOfAO11_5) //TypeOfAO11_5 * TypeOfAO11_5::InstanceNameOfAO11_5;
extern A_CONC_(NamespaceToSet11, TypeOfAO11_5)  * InstanceNameOfAO11_5;
#endif

#endif


#define GlobalPtrToAO12_1 //define it here first so that the default value is empty
#define GlobalPtrToAO12_2
#define GlobalPtrToAO12_3
#define GlobalPtrToAO12_4
#define GlobalPtrToAO12_5 

#if (defined(AOInclude12) && (EXPAND(AOInclude12) == 0)) 

#include QUOTE(H_CONC_(AOInclude12))
#if  (defined(NameSpaceToAO12) && (EXPAND(NameSpaceToAO12) == 0))
#define NamespaceToSet12 A_CONC_(NameSpaceToAO12, ::)
#else
#define NamespaceToSet12
#endif


#if defined(InstanceNameOfAO12_1) && (EXPAND(InstanceNameOfAO12_1) == 0)
#define GlobalPtrToAO12_1 S_CONC_(A_CONC_(NamespaceToSet12,TypeOfAO12_1), InstanceNameOfAO12_1) //TypeOfAO12_1 * TypeOfAO12_1::InstanceNameOfAO12_1;
extern A_CONC_(NamespaceToSet12, TypeOfAO12_1)  * InstanceNameOfAO12_1;
#endif
#if defined(InstanceNameOfAO12_2) && (EXPAND(InstanceNameOfAO12_2) == 0)
#define GlobalPtrToAO12_2 S_CONC_(A_CONC_(NamespaceToSet12,TypeOfAO12_2), InstanceNameOfAO12_2) //TypeOfAO12_2 * TypeOfAO12_2::InstanceNameOfAO12_2;
extern A_CONC_(NamespaceToSet12, TypeOfAO12_2)  * InstanceNameOfAO12_2;
#endif
#if defined(InstanceNameOfAO12_3) && (EXPAND(InstanceNameOfAO12_3) == 0)
#define GlobalPtrToAO12_3 S_CONC_(A_CONC_(NamespaceToSet12,TypeOfAO12_3), InstanceNameOfAO12_3) //TypeOfAO12_3 * TypeOfAO12_3::InstanceNameOfAO12_3;
extern A_CONC_(NamespaceToSet12, TypeOfAO12_3)  * InstanceNameOfAO12_3;
#endif
#if defined(InstanceNameOfAO12_4) && (EXPAND(InstanceNameOfAO12_4) == 0)
#define GlobalPtrToAO12_4 S_CONC_(A_CONC_(NamespaceToSet12,TypeOfAO12_4), InstanceNameOfAO12_4) //TypeOfAO12_4 * TypeOfAO12_4::InstanceNameOfAO12_4;
extern A_CONC_(NamespaceToSet12, TypeOfAO12_4)  * InstanceNameOfAO12_4;
#endif
#if defined(InstanceNameOfAO12_5) && (EXPAND(InstanceNameOfAO12_5) == 0)
#define GlobalPtrToAO12_5 S_CONC_(A_CONC_(NamespaceToSet12,TypeOfAO12_5), InstanceNameOfAO12_5) //TypeOfAO12_5 * TypeOfAO12_5::InstanceNameOfAO12_5;
extern A_CONC_(NamespaceToSet12, TypeOfAO12_5)  * InstanceNameOfAO12_5;
#endif

#endif


#define GlobalPtrToAO13_1 //define it here first so that the default value is empty
#define GlobalPtrToAO13_2
#define GlobalPtrToAO13_3
#define GlobalPtrToAO13_4
#define GlobalPtrToAO13_5 

#if (defined(AOInclude13) && (EXPAND(AOInclude13) == 0)) 

#include QUOTE(H_CONC_(AOInclude13))
#if  (defined(NameSpaceToAO13) && (EXPAND(NameSpaceToAO13) == 0))
#define NamespaceToSet13 A_CONC_(NameSpaceToAO13, ::)
#else
#define NamespaceToSet13
#endif


#if defined(InstanceNameOfAO13_1) && (EXPAND(InstanceNameOfAO13_1) == 0)
#define GlobalPtrToAO13_1 S_CONC_(A_CONC_(NamespaceToSet13,TypeOfAO13_1), InstanceNameOfAO13_1) //TypeOfAO13_1 * TypeOfAO13_1::InstanceNameOfAO13_1;
extern A_CONC_(NamespaceToSet13, TypeOfAO13_1)  * InstanceNameOfAO13_1;
#endif
#if defined(InstanceNameOfAO13_2) && (EXPAND(InstanceNameOfAO13_2) == 0)
#define GlobalPtrToAO13_2 S_CONC_(A_CONC_(NamespaceToSet13,TypeOfAO13_2), InstanceNameOfAO13_2) //TypeOfAO13_2 * TypeOfAO13_2::InstanceNameOfAO13_2;
extern A_CONC_(NamespaceToSet13, TypeOfAO13_2)  * InstanceNameOfAO13_2;
#endif
#if defined(InstanceNameOfAO13_3) && (EXPAND(InstanceNameOfAO13_3) == 0)
#define GlobalPtrToAO13_3 S_CONC_(A_CONC_(NamespaceToSet13,TypeOfAO13_3), InstanceNameOfAO13_3) //TypeOfAO13_3 * TypeOfAO13_3::InstanceNameOfAO13_3;
extern A_CONC_(NamespaceToSet13, TypeOfAO13_3)  * InstanceNameOfAO13_3;
#endif
#if defined(InstanceNameOfAO13_4) && (EXPAND(InstanceNameOfAO13_4) == 0)
#define GlobalPtrToAO13_4 S_CONC_(A_CONC_(NamespaceToSet13,TypeOfAO13_4), InstanceNameOfAO13_4) //TypeOfAO13_4 * TypeOfAO13_4::InstanceNameOfAO13_4;
extern A_CONC_(NamespaceToSet13, TypeOfAO13_4)  * InstanceNameOfAO13_4;
#endif
#if defined(InstanceNameOfAO13_5) && (EXPAND(InstanceNameOfAO13_5) == 0)
#define GlobalPtrToAO13_5 S_CONC_(A_CONC_(NamespaceToSet13,TypeOfAO13_5), InstanceNameOfAO13_5) //TypeOfAO13_5 * TypeOfAO13_5::InstanceNameOfAO13_5;
extern A_CONC_(NamespaceToSet13, TypeOfAO13_5)  * InstanceNameOfAO13_5;
#endif

#endif


#define GlobalPtrToAO14_1 //define it here first so that the default value is empty
#define GlobalPtrToAO14_2
#define GlobalPtrToAO14_3
#define GlobalPtrToAO14_4
#define GlobalPtrToAO14_5 

#if (defined(AOInclude14) && (EXPAND(AOInclude14) == 0)) 

#include QUOTE(H_CONC_(AOInclude14))
#if  (defined(NameSpaceToAO14) && (EXPAND(NameSpaceToAO14) == 0))
#define NamespaceToSet14 A_CONC_(NameSpaceToAO14, ::)
#else
#define NamespaceToSet14
#endif


#if defined(InstanceNameOfAO14_1) && (EXPAND(InstanceNameOfAO14_1) == 0)
#define GlobalPtrToAO14_1 S_CONC_(A_CONC_(NamespaceToSet14,TypeOfAO14_1), InstanceNameOfAO14_1) //TypeOfAO14_1 * TypeOfAO14_1::InstanceNameOfAO14_1;
extern A_CONC_(NamespaceToSet14, TypeOfAO14_1)  * InstanceNameOfAO14_1;
#endif
#if defined(InstanceNameOfAO14_2) && (EXPAND(InstanceNameOfAO14_2) == 0)
#define GlobalPtrToAO14_2 S_CONC_(A_CONC_(NamespaceToSet14,TypeOfAO14_2), InstanceNameOfAO14_2) //TypeOfAO14_2 * TypeOfAO14_2::InstanceNameOfAO14_2;
extern A_CONC_(NamespaceToSet14, TypeOfAO14_2)  * InstanceNameOfAO14_2;
#endif
#if defined(InstanceNameOfAO14_3) && (EXPAND(InstanceNameOfAO14_3) == 0)
#define GlobalPtrToAO14_3 S_CONC_(A_CONC_(NamespaceToSet14,TypeOfAO14_3), InstanceNameOfAO14_3) //TypeOfAO14_3 * TypeOfAO14_3::InstanceNameOfAO14_3;
extern A_CONC_(NamespaceToSet14, TypeOfAO14_3)  * InstanceNameOfAO14_3;
#endif
#if defined(InstanceNameOfAO14_4) && (EXPAND(InstanceNameOfAO14_4) == 0)
#define GlobalPtrToAO14_4 S_CONC_(A_CONC_(NamespaceToSet14,TypeOfAO14_4), InstanceNameOfAO14_4) //TypeOfAO14_4 * TypeOfAO14_4::InstanceNameOfAO14_4;
extern A_CONC_(NamespaceToSet14, TypeOfAO14_4)  * InstanceNameOfAO14_4;
#endif
#if defined(InstanceNameOfAO14_5) && (EXPAND(InstanceNameOfAO14_5) == 0)
#define GlobalPtrToAO14_5 S_CONC_(A_CONC_(NamespaceToSet14,TypeOfAO14_5), InstanceNameOfAO14_5) //TypeOfAO14_5 * TypeOfAO14_5::InstanceNameOfAO14_5;
extern A_CONC_(NamespaceToSet14, TypeOfAO14_5)  * InstanceNameOfAO14_5;
#endif

#endif


#define GlobalPtrToAO15_1 //define it here first so that the default value is empty
#define GlobalPtrToAO15_2
#define GlobalPtrToAO15_3
#define GlobalPtrToAO15_4
#define GlobalPtrToAO15_5 

#if (defined(AOInclude15) && (EXPAND(AOInclude15) == 0)) 

#include QUOTE(H_CONC_(AOInclude15))
#if  (defined(NameSpaceToAO15) && (EXPAND(NameSpaceToAO15) == 0))
#define NamespaceToSet15 A_CONC_(NameSpaceToAO15, ::)
#else
#define NamespaceToSet15
#endif


#if defined(InstanceNameOfAO15_1) && (EXPAND(InstanceNameOfAO15_1) == 0)
#define GlobalPtrToAO15_1 S_CONC_(A_CONC_(NamespaceToSet15,TypeOfAO15_1), InstanceNameOfAO15_1) //TypeOfAO15_1 * TypeOfAO15_1::InstanceNameOfAO15_1;
extern A_CONC_(NamespaceToSet15, TypeOfAO15_1)  * InstanceNameOfAO15_1;
#endif
#if defined(InstanceNameOfAO15_2) && (EXPAND(InstanceNameOfAO15_2) == 0)
#define GlobalPtrToAO15_2 S_CONC_(A_CONC_(NamespaceToSet15,TypeOfAO15_2), InstanceNameOfAO15_2) //TypeOfAO15_2 * TypeOfAO15_2::InstanceNameOfAO15_2;
extern A_CONC_(NamespaceToSet15, TypeOfAO15_2)  * InstanceNameOfAO15_2;
#endif
#if defined(InstanceNameOfAO15_3) && (EXPAND(InstanceNameOfAO15_3) == 0)
#define GlobalPtrToAO15_3 S_CONC_(A_CONC_(NamespaceToSet15,TypeOfAO15_3), InstanceNameOfAO15_3) //TypeOfAO15_3 * TypeOfAO15_3::InstanceNameOfAO15_3;
extern A_CONC_(NamespaceToSet15, TypeOfAO15_3)  * InstanceNameOfAO15_3;
#endif
#if defined(InstanceNameOfAO15_4) && (EXPAND(InstanceNameOfAO15_4) == 0)
#define GlobalPtrToAO15_4 S_CONC_(A_CONC_(NamespaceToSet15,TypeOfAO15_4), InstanceNameOfAO15_4) //TypeOfAO15_4 * TypeOfAO15_4::InstanceNameOfAO15_4;
extern A_CONC_(NamespaceToSet15, TypeOfAO15_4)  * InstanceNameOfAO15_4;
#endif
#if defined(InstanceNameOfAO15_5) && (EXPAND(InstanceNameOfAO15_5) == 0)
#define GlobalPtrToAO15_5 S_CONC_(A_CONC_(NamespaceToSet15,TypeOfAO15_5), InstanceNameOfAO15_5) //TypeOfAO15_5 * TypeOfAO15_5::InstanceNameOfAO15_5;
extern A_CONC_(NamespaceToSet15, TypeOfAO15_5)  * InstanceNameOfAO15_5;
#endif

#endif


#define GlobalPtrToAO16_1 //define it here first so that the default value is empty
#define GlobalPtrToAO16_2
#define GlobalPtrToAO16_3
#define GlobalPtrToAO16_4
#define GlobalPtrToAO16_5 

#if (defined(AOInclude16) && (EXPAND(AOInclude16) == 0)) 

#include QUOTE(H_CONC_(AOInclude16))
#if  (defined(NameSpaceToAO16) && (EXPAND(NameSpaceToAO16) == 0))
#define NamespaceToSet16 A_CONC_(NameSpaceToAO16, ::)
#else
#define NamespaceToSet16
#endif


#if defined(InstanceNameOfAO16_1) && (EXPAND(InstanceNameOfAO16_1) == 0)
#define GlobalPtrToAO16_1 S_CONC_(A_CONC_(NamespaceToSet16,TypeOfAO16_1), InstanceNameOfAO16_1) //TypeOfAO16_1 * TypeOfAO16_1::InstanceNameOfAO16_1;
extern A_CONC_(NamespaceToSet16, TypeOfAO16_1)  * InstanceNameOfAO16_1;
#endif
#if defined(InstanceNameOfAO16_2) && (EXPAND(InstanceNameOfAO16_2) == 0)
#define GlobalPtrToAO16_2 S_CONC_(A_CONC_(NamespaceToSet16,TypeOfAO16_2), InstanceNameOfAO16_2) //TypeOfAO16_2 * TypeOfAO16_2::InstanceNameOfAO16_2;
extern A_CONC_(NamespaceToSet16, TypeOfAO16_2)  * InstanceNameOfAO16_2;
#endif
#if defined(InstanceNameOfAO16_3) && (EXPAND(InstanceNameOfAO16_3) == 0)
#define GlobalPtrToAO16_3 S_CONC_(A_CONC_(NamespaceToSet16,TypeOfAO16_3), InstanceNameOfAO16_3) //TypeOfAO16_3 * TypeOfAO16_3::InstanceNameOfAO16_3;
extern A_CONC_(NamespaceToSet16, TypeOfAO16_3)  * InstanceNameOfAO16_3;
#endif
#if defined(InstanceNameOfAO16_4) && (EXPAND(InstanceNameOfAO16_4) == 0)
#define GlobalPtrToAO16_4 S_CONC_(A_CONC_(NamespaceToSet16,TypeOfAO16_4), InstanceNameOfAO16_4) //TypeOfAO16_4 * TypeOfAO16_4::InstanceNameOfAO16_4;
extern A_CONC_(NamespaceToSet16, TypeOfAO16_4)  * InstanceNameOfAO16_4;
#endif
#if defined(InstanceNameOfAO16_5) && (EXPAND(InstanceNameOfAO16_5) == 0)
#define GlobalPtrToAO16_5 S_CONC_(A_CONC_(NamespaceToSet16,TypeOfAO16_5), InstanceNameOfAO16_5) //TypeOfAO16_5 * TypeOfAO16_5::InstanceNameOfAO16_5;
extern A_CONC_(NamespaceToSet16, TypeOfAO16_5)  * InstanceNameOfAO16_5;
#endif

#endif


#define GlobalPtrToAO17_1 //define it here first so that the default value is empty
#define GlobalPtrToAO17_2
#define GlobalPtrToAO17_3
#define GlobalPtrToAO17_4
#define GlobalPtrToAO17_5 

#if (defined(AOInclude17) && (EXPAND(AOInclude17) == 0)) 

#include QUOTE(H_CONC_(AOInclude17))
#if  (defined(NameSpaceToAO17) && (EXPAND(NameSpaceToAO17) == 0))
#define NamespaceToSet17 A_CONC_(NameSpaceToAO17, ::)
#else
#define NamespaceToSet17
#endif


#if defined(InstanceNameOfAO17_1) && (EXPAND(InstanceNameOfAO17_1) == 0)
#define GlobalPtrToAO17_1 S_CONC_(A_CONC_(NamespaceToSet17,TypeOfAO17_1), InstanceNameOfAO17_1) //TypeOfAO17_1 * TypeOfAO17_1::InstanceNameOfAO17_1;
extern A_CONC_(NamespaceToSet17, TypeOfAO17_1)  * InstanceNameOfAO17_1;
#endif
#if defined(InstanceNameOfAO17_2) && (EXPAND(InstanceNameOfAO17_2) == 0)
#define GlobalPtrToAO17_2 S_CONC_(A_CONC_(NamespaceToSet17,TypeOfAO17_2), InstanceNameOfAO17_2) //TypeOfAO17_2 * TypeOfAO17_2::InstanceNameOfAO17_2;
extern A_CONC_(NamespaceToSet17, TypeOfAO17_2)  * InstanceNameOfAO17_2;
#endif
#if defined(InstanceNameOfAO17_3) && (EXPAND(InstanceNameOfAO17_3) == 0)
#define GlobalPtrToAO17_3 S_CONC_(A_CONC_(NamespaceToSet17,TypeOfAO17_3), InstanceNameOfAO17_3) //TypeOfAO17_3 * TypeOfAO17_3::InstanceNameOfAO17_3;
extern A_CONC_(NamespaceToSet17, TypeOfAO17_3)  * InstanceNameOfAO17_3;
#endif
#if defined(InstanceNameOfAO17_4) && (EXPAND(InstanceNameOfAO17_4) == 0)
#define GlobalPtrToAO17_4 S_CONC_(A_CONC_(NamespaceToSet17,TypeOfAO17_4), InstanceNameOfAO17_4) //TypeOfAO17_4 * TypeOfAO17_4::InstanceNameOfAO17_4;
extern A_CONC_(NamespaceToSet17, TypeOfAO17_4)  * InstanceNameOfAO17_4;
#endif
#if defined(InstanceNameOfAO17_5) && (EXPAND(InstanceNameOfAO17_5) == 0)
#define GlobalPtrToAO17_5 S_CONC_(A_CONC_(NamespaceToSet17,TypeOfAO17_5), InstanceNameOfAO17_5) //TypeOfAO17_5 * TypeOfAO17_5::InstanceNameOfAO17_5;
extern A_CONC_(NamespaceToSet17, TypeOfAO17_5)  * InstanceNameOfAO17_5;
#endif

#endif


#define GlobalPtrToAO18_1 //define it here first so that the default value is empty
#define GlobalPtrToAO18_2
#define GlobalPtrToAO18_3
#define GlobalPtrToAO18_4
#define GlobalPtrToAO18_5 

#if (defined(AOInclude18) && (EXPAND(AOInclude18) == 0)) 

#include QUOTE(H_CONC_(AOInclude18))
#if  (defined(NameSpaceToAO18) && (EXPAND(NameSpaceToAO18) == 0))
#define NamespaceToSet18 A_CONC_(NameSpaceToAO18, ::)
#else
#define NamespaceToSet18
#endif


#if defined(InstanceNameOfAO18_1) && (EXPAND(InstanceNameOfAO18_1) == 0)
#define GlobalPtrToAO18_1 S_CONC_(A_CONC_(NamespaceToSet18,TypeOfAO18_1), InstanceNameOfAO18_1) //TypeOfAO18_1 * TypeOfAO18_1::InstanceNameOfAO18_1;
extern A_CONC_(NamespaceToSet18, TypeOfAO18_1)  * InstanceNameOfAO18_1;
#endif
#if defined(InstanceNameOfAO18_2) && (EXPAND(InstanceNameOfAO18_2) == 0)
#define GlobalPtrToAO18_2 S_CONC_(A_CONC_(NamespaceToSet18,TypeOfAO18_2), InstanceNameOfAO18_2) //TypeOfAO18_2 * TypeOfAO18_2::InstanceNameOfAO18_2;
extern A_CONC_(NamespaceToSet18, TypeOfAO18_2)  * InstanceNameOfAO18_2;
#endif
#if defined(InstanceNameOfAO18_3) && (EXPAND(InstanceNameOfAO18_3) == 0)
#define GlobalPtrToAO18_3 S_CONC_(A_CONC_(NamespaceToSet18,TypeOfAO18_3), InstanceNameOfAO18_3) //TypeOfAO18_3 * TypeOfAO18_3::InstanceNameOfAO18_3;
extern A_CONC_(NamespaceToSet18, TypeOfAO18_3)  * InstanceNameOfAO18_3;
#endif
#if defined(InstanceNameOfAO18_4) && (EXPAND(InstanceNameOfAO18_4) == 0)
#define GlobalPtrToAO18_4 S_CONC_(A_CONC_(NamespaceToSet18,TypeOfAO18_4), InstanceNameOfAO18_4) //TypeOfAO18_4 * TypeOfAO18_4::InstanceNameOfAO18_4;
extern A_CONC_(NamespaceToSet18, TypeOfAO18_4)  * InstanceNameOfAO18_4;
#endif
#if defined(InstanceNameOfAO18_5) && (EXPAND(InstanceNameOfAO18_5) == 0)
#define GlobalPtrToAO18_5 S_CONC_(A_CONC_(NamespaceToSet18,TypeOfAO18_5), InstanceNameOfAO18_5) //TypeOfAO18_5 * TypeOfAO18_5::InstanceNameOfAO18_5;
extern A_CONC_(NamespaceToSet18, TypeOfAO18_5)  * InstanceNameOfAO18_5;
#endif

#endif


#define GlobalPtrToAO19_1 //define it here first so that the default value is empty
#define GlobalPtrToAO19_2
#define GlobalPtrToAO19_3
#define GlobalPtrToAO19_4
#define GlobalPtrToAO19_5 

#if (defined(AOInclude19) && (EXPAND(AOInclude19) == 0)) 

#include QUOTE(H_CONC_(AOInclude19))
#if  (defined(NameSpaceToAO19) && (EXPAND(NameSpaceToAO19) == 0))
#define NamespaceToSet19 A_CONC_(NameSpaceToAO19, ::)
#else
#define NamespaceToSet19
#endif


#if defined(InstanceNameOfAO19_1) && (EXPAND(InstanceNameOfAO19_1) == 0)
#define GlobalPtrToAO19_1 S_CONC_(A_CONC_(NamespaceToSet19,TypeOfAO19_1), InstanceNameOfAO19_1) //TypeOfAO19_1 * TypeOfAO19_1::InstanceNameOfAO19_1;
extern A_CONC_(NamespaceToSet19, TypeOfAO19_1)  * InstanceNameOfAO19_1;
#endif
#if defined(InstanceNameOfAO19_2) && (EXPAND(InstanceNameOfAO19_2) == 0)
#define GlobalPtrToAO19_2 S_CONC_(A_CONC_(NamespaceToSet19,TypeOfAO19_2), InstanceNameOfAO19_2) //TypeOfAO19_2 * TypeOfAO19_2::InstanceNameOfAO19_2;
extern A_CONC_(NamespaceToSet19, TypeOfAO19_2)  * InstanceNameOfAO19_2;
#endif
#if defined(InstanceNameOfAO19_3) && (EXPAND(InstanceNameOfAO19_3) == 0)
#define GlobalPtrToAO19_3 S_CONC_(A_CONC_(NamespaceToSet19,TypeOfAO19_3), InstanceNameOfAO19_3) //TypeOfAO19_3 * TypeOfAO19_3::InstanceNameOfAO19_3;
extern A_CONC_(NamespaceToSet19, TypeOfAO19_3)  * InstanceNameOfAO19_3;
#endif
#if defined(InstanceNameOfAO19_4) && (EXPAND(InstanceNameOfAO19_4) == 0)
#define GlobalPtrToAO19_4 S_CONC_(A_CONC_(NamespaceToSet19,TypeOfAO19_4), InstanceNameOfAO19_4) //TypeOfAO19_4 * TypeOfAO19_4::InstanceNameOfAO19_4;
extern A_CONC_(NamespaceToSet19, TypeOfAO19_4)  * InstanceNameOfAO19_4;
#endif
#if defined(InstanceNameOfAO19_5) && (EXPAND(InstanceNameOfAO19_5) == 0)
#define GlobalPtrToAO19_5 S_CONC_(A_CONC_(NamespaceToSet19,TypeOfAO19_5), InstanceNameOfAO19_5) //TypeOfAO19_5 * TypeOfAO19_5::InstanceNameOfAO19_5;
extern A_CONC_(NamespaceToSet19, TypeOfAO19_5)  * InstanceNameOfAO19_5;
#endif

#endif


#define GlobalPtrToAO20_1 //define it here first so that the default value is empty
#define GlobalPtrToAO20_2
#define GlobalPtrToAO20_3
#define GlobalPtrToAO20_4
#define GlobalPtrToAO20_5 

#if (defined(AOInclude20) && (EXPAND(AOInclude20) == 0)) 

#include QUOTE(H_CONC_(AOInclude20))
#if  (defined(NameSpaceToAO20) && (EXPAND(NameSpaceToAO20) == 0))
#define NamespaceToSet20 A_CONC_(NameSpaceToAO20, ::)
#else
#define NamespaceToSet20
#endif


#if defined(InstanceNameOfAO20_1) && (EXPAND(InstanceNameOfAO20_1) == 0)
#define GlobalPtrToAO20_1 S_CONC_(A_CONC_(NamespaceToSet20,TypeOfAO20_1), InstanceNameOfAO20_1) //TypeOfAO20_1 * TypeOfAO20_1::InstanceNameOfAO20_1;
extern A_CONC_(NamespaceToSet20, TypeOfAO20_1)  * InstanceNameOfAO20_1;
#endif
#if defined(InstanceNameOfAO20_2) && (EXPAND(InstanceNameOfAO20_2) == 0)
#define GlobalPtrToAO20_2 S_CONC_(A_CONC_(NamespaceToSet20,TypeOfAO20_2), InstanceNameOfAO20_2) //TypeOfAO20_2 * TypeOfAO20_2::InstanceNameOfAO20_2;
extern A_CONC_(NamespaceToSet20, TypeOfAO20_2)  * InstanceNameOfAO20_2;
#endif
#if defined(InstanceNameOfAO20_3) && (EXPAND(InstanceNameOfAO20_3) == 0)
#define GlobalPtrToAO20_3 S_CONC_(A_CONC_(NamespaceToSet20,TypeOfAO20_3), InstanceNameOfAO20_3) //TypeOfAO20_3 * TypeOfAO20_3::InstanceNameOfAO20_3;
extern A_CONC_(NamespaceToSet20, TypeOfAO20_3)  * InstanceNameOfAO20_3;
#endif
#if defined(InstanceNameOfAO20_4) && (EXPAND(InstanceNameOfAO20_4) == 0)
#define GlobalPtrToAO20_4 S_CONC_(A_CONC_(NamespaceToSet20,TypeOfAO20_4), InstanceNameOfAO20_4) //TypeOfAO20_4 * TypeOfAO20_4::InstanceNameOfAO20_4;
extern A_CONC_(NamespaceToSet20, TypeOfAO20_4)  * InstanceNameOfAO20_4;
#endif
#if defined(InstanceNameOfAO20_5) && (EXPAND(InstanceNameOfAO20_5) == 0)
#define GlobalPtrToAO20_5 S_CONC_(A_CONC_(NamespaceToSet20,TypeOfAO20_5), InstanceNameOfAO20_5) //TypeOfAO20_5 * TypeOfAO20_5::InstanceNameOfAO20_5;
extern A_CONC_(NamespaceToSet20, TypeOfAO20_5)  * InstanceNameOfAO20_5;
#endif

#endif





#define DECLARE_ALL_AO_PTR \
GlobalPtrToAO1_1 \
GlobalPtrToAO1_2 \
GlobalPtrToAO1_3 \
GlobalPtrToAO1_4 \
GlobalPtrToAO1_5 \
GlobalPtrToAO2_1 \
GlobalPtrToAO2_2 \
GlobalPtrToAO2_3 \
GlobalPtrToAO2_4 \
GlobalPtrToAO2_5 \
GlobalPtrToAO3_1 \
GlobalPtrToAO3_2 \
GlobalPtrToAO3_3 \
GlobalPtrToAO3_4 \
GlobalPtrToAO3_5 \
GlobalPtrToAO4_1 \
GlobalPtrToAO4_2 \
GlobalPtrToAO4_3 \
GlobalPtrToAO4_4 \
GlobalPtrToAO4_5 \
GlobalPtrToAO5_1 \
GlobalPtrToAO5_2 \
GlobalPtrToAO5_3 \
GlobalPtrToAO5_4 \
GlobalPtrToAO5_5 \
GlobalPtrToAO6_1 \
GlobalPtrToAO6_2 \
GlobalPtrToAO6_3 \
GlobalPtrToAO6_4 \
GlobalPtrToAO6_5 \
GlobalPtrToAO7_1 \
GlobalPtrToAO7_2 \
GlobalPtrToAO7_3 \
GlobalPtrToAO7_4 \
GlobalPtrToAO7_5 \
GlobalPtrToAO8_1 \
GlobalPtrToAO8_2 \
GlobalPtrToAO8_3 \
GlobalPtrToAO8_4 \
GlobalPtrToAO8_5 \
GlobalPtrToAO9_1 \
GlobalPtrToAO9_2 \
GlobalPtrToAO9_3 \
GlobalPtrToAO9_4 \
GlobalPtrToAO9_5 \
GlobalPtrToAO10_1 \
GlobalPtrToAO10_2 \
GlobalPtrToAO10_3 \
GlobalPtrToAO10_4 \
GlobalPtrToAO10_5 \
GlobalPtrToAO11_1 \
GlobalPtrToAO11_2 \
GlobalPtrToAO11_3 \
GlobalPtrToAO11_4 \
GlobalPtrToAO11_5 \
GlobalPtrToAO12_1 \
GlobalPtrToAO12_2 \
GlobalPtrToAO12_3 \
GlobalPtrToAO12_4 \
GlobalPtrToAO12_5 \
GlobalPtrToAO13_1 \
GlobalPtrToAO13_2 \
GlobalPtrToAO13_3 \
GlobalPtrToAO13_4 \
GlobalPtrToAO13_5 \
GlobalPtrToAO14_1 \
GlobalPtrToAO14_2 \
GlobalPtrToAO14_3 \
GlobalPtrToAO14_4 \
GlobalPtrToAO14_5 \
GlobalPtrToAO15_1 \
GlobalPtrToAO15_2 \
GlobalPtrToAO15_3 \
GlobalPtrToAO15_4 \
GlobalPtrToAO15_5 \
GlobalPtrToAO16_1 \
GlobalPtrToAO16_2 \
GlobalPtrToAO16_3 \
GlobalPtrToAO16_4 \
GlobalPtrToAO16_5 \
GlobalPtrToAO17_1 \
GlobalPtrToAO17_2 \
GlobalPtrToAO17_3 \
GlobalPtrToAO17_4 \
GlobalPtrToAO17_5 \
GlobalPtrToAO18_1 \
GlobalPtrToAO18_2 \
GlobalPtrToAO18_3 \
GlobalPtrToAO18_4 \
GlobalPtrToAO18_5 \
GlobalPtrToAO19_1 \
GlobalPtrToAO19_2 \
GlobalPtrToAO19_3 \
GlobalPtrToAO19_4 \
GlobalPtrToAO19_5 \
GlobalPtrToAO20_1 \
GlobalPtrToAO20_2 \
GlobalPtrToAO20_3 \
GlobalPtrToAO20_4 \
GlobalPtrToAO20_5 \
GlobalPtrToClock_1 \
GlobalPtrToClock_2 \
GlobalPtrToClock_3 \
GlobalPtrToClock_4 \
GlobalPtrToClock_5 \
GlobalPtrToClock_6 \
GlobalPtrToClock_7 \
GlobalPtrToClock_8 \
GlobalPtrToClock_9 \
GlobalPtrToClock_10 \
GlobalPtrToSensor_1 \
GlobalPtrToSensor_2 \
GlobalPtrToSensor_3 \
GlobalPtrToSensor_4 \
GlobalPtrToSensor_5 \
GlobalPtrToSensor_6 \
GlobalPtrToSensor_7 \
GlobalPtrToSensor_8 \
GlobalPtrToSensor_9 \
GlobalPtrToSensor_10 \
GlobalPtrToSensor_11 \
GlobalPtrToSensor_12 \
GlobalPtrToSensor_13 \
GlobalPtrToSensor_14 \
GlobalPtrToSensor_15 \
GlobalPtrToSensor_16 \
GlobalPtrToSensor_17 \
GlobalPtrToSensor_18 \
GlobalPtrToSensor_19 \
GlobalPtrToSensor_20 












