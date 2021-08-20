#pragma once
//#include "string.h"
//#include <string>
//#include "AEUtils.h"
#include "AEUtils.h"

#include "iostream"
//

#define gROUPNAME_STRING(s) #s
#define GROUPNAME_STRING(s) gROUPNAME_STRING(s)

static char const * const TestGroupName = GROUPNAME_STRING(INTEGRATION_TESTS);
	
#define _AEITEST(testName, thingToAssert, AssertionMessage) AEITEST_Func(testName, thingToAssert,  AssertionMessage,  __LINE__, __FILE__);

#define AEITEST(testName, thingToAssert, AssertionMessage) _AEITEST(testName, thingToAssert, AssertionMessage) 

inline void AEITEST_Func(char const * const testName, bool thingToAssert, std::string AssertionMessage, unsigned long ulLine, const char * const pcFileName)
{
//		std::string PathtoFile = CMAKE_CURRENT_SOURCE_DIR; //"C:\\visualgdb_projects\\AERTOS\\TestResources\\";
//		PathtoFile.append("\\IntegrationTestResults\\IntegrationResults.txt");
	
	std::string testLogMsg = "TESTGROUPNAME: ";
	testLogMsg.append(TestGroupName);
	testLogMsg.append("\n"); 
	
	testLogMsg.append("TESTNAME: ");
	testLogMsg.append(testName);
	testLogMsg.append("\n"); 
	
	testLogMsg.append("STATUS: ");
	if (thingToAssert == false)
	{testLogMsg.append("FAILED\n");	}
	else	
	{testLogMsg.append("PASSED\n"); }
	
	testLogMsg.append("FILE: ");
	testLogMsg.append(pcFileName);
	testLogMsg.append("\n"); 
	
	char msgFormatted[50];
	snprintf(msgFormatted, sizeof("LINE: %d\n"), "LINE: %d\n", ulLine);
	testLogMsg.append(msgFormatted); 
	
	testLogMsg.append("MESSAGE: "); 
	testLogMsg.append(AssertionMessage); 
	testLogMsg.append("\n"); 
	
	testLogMsg.append("OPTIONS: ");
	testLogMsg.append(CGEN_ALLOPTIONS);
	testLogMsg.append("\n\n");  
//	__LINE__, __FILE__
//	
//	over here. have cgen create a add_compile_definitions(CGEN_ALLOPTIONS="") for all the options with 
//		their respective value selected in the format OPTION::PV
	
	std::string PathtoFile = "IntegrationTestResults\\IntegrationResults.txt";
	
	
	AEWriteToEndOfFile(PathtoFile.c_str(), testLogMsg.c_str(), testLogMsg.length());
	
	
}
//if(thingToAssert == false){\
//AEPrint(AssertionMessage);\
//TheAssertToUse(thingToAssert); }