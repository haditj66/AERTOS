#pragma once

#include "AEUtils.h"

#include "iostream"

#include "vector"


#define gROUPNAME_STRING(s) #s
#define GROUPNAME_STRING(s) gROUPNAME_STRING(s)

static char const * const TestGroupName = GROUPNAME_STRING(INTEGRATION_TESTS);
	
#define _AEITEST(testName, thingToAssert, AssertionMessage) AEITEST_Func(testName, thingToAssert,  AssertionMessage,  __LINE__, __FILE__);
#define _AEITEST_EndTestsIfFalseAssertion(testName, thingToAssert, AssertionMessage) AEITEST_Func(testName, thingToAssert,  AssertionMessage,  __LINE__, __FILE__, true);

#define _AEITEST_EXPECT_TEST_TO_RUN(testName) AEITEST_EXPECT_TEST_TO_RUN_FUNC(testName) ;

#define _AEITEST_END_TestsAfterTimer(timeInMilliBeforeEnd) AEITEST_END_TestsAfterTimer_FUNC(timeInMilliBeforeEnd);
#define _AEITEST_END AEITEST_END_FUNC();

//#define AEITEST(testName, thingToAssert, AssertionMessage) _AEITEST(testName, thingToAssert, AssertionMessage) 


//#define PATH_TO_TESTMACRO_FILE "/CGensaveFiles/IntegrationTestMacros.h"
//#define FULLPATHTEST CGEN_CMAKE_CURRENT_BINARY_DIR 
//#define FULLPATHTEST2 GROUPNAME_STRING(FULLPATHTEST PATH_TO_TESTMACRO_FILE)
#include PATH_TO_TESTMACRO_FILE  
//"build/VSGDBCmakeNinja_armnoneabiid/Debug"


typedef void(*AEITestFunction_t)(char const * const testName, bool thingToAssert, std::string AssertionMessage, unsigned long ulLine, std::string pcFileName);

enum LogStatus
{
	PASSED,
	FAILED,
	FINISHED,
	EXCEPTION
};


class AEITestLogData
{
public:
	
	AEITestLogData()
	{
		ID = 0xffffffff;
		NumOfTimesFailed = 0;
		NumOfTimesPassed = 0;
	}
	
	uint32_t ID;
	uint32_t NumOfTimesFailed;
	uint32_t NumOfTimesPassed; 
	std::string testName;
	LogStatus status;
	std::string AssertionMessage;
	unsigned long ulLine;
	std::string pcFileName;
	
	
};

static std::vector<AEITestLogData*> TestLogsArgs;





inline void LogAEITest(AEITestLogData* testData)//(std::string testName, LogStatus status, std::string AssertionMessage, unsigned long ulLine, std::string pcFileName)
{
	std::string statusStr = "NA";
	if (testData->status == LogStatus::PASSED)
	{
		statusStr = "PASSED";
	}
	if (testData->status == LogStatus::FAILED)
	{
		statusStr = "FAILED";
	}
	if (testData->status == LogStatus::FINISHED)
	{
		statusStr = "FINISHED";
	}
	if (testData->status == LogStatus::EXCEPTION)
	{
		statusStr = "EXCEPTION";
	}
	
	std::string testLogMsg = "TESTGROUPNAME: ";
	testLogMsg.append(INTEGRATION_TEST_CHOSEN);
	testLogMsg.append("\n"); 
	
	testLogMsg.append("TESTSPECIFIC: ");
	testLogMsg.append(INTEGRATION_TEST_CHOSEN_SPECIFIC);
	testLogMsg.append("\n"); 
 
	testLogMsg.append("TESTNAME: ");
	testLogMsg.append(testData->testName);
	testLogMsg.append("\n"); 
	
	testLogMsg.append("STATUS: ");
	testLogMsg.append(statusStr);
	testLogMsg.append("\n"); 
	
	testLogMsg.append("FILE: ");
	testLogMsg.append(testData->pcFileName);
	testLogMsg.append("\n"); 
	
	char msgFormatted[50];
	snprintf(msgFormatted, sizeof("LINE: %d\n"), "LINE: %d\n", testData->ulLine);
	testLogMsg.append(msgFormatted); 
	
	testLogMsg.append("MESSAGE: "); 
	testLogMsg.append(testData->AssertionMessage); 
	testLogMsg.append("\n"); 
	
	testLogMsg.append("NumOfPasses: "); 
	testLogMsg.append(std::to_string(testData->NumOfTimesPassed)); 
	testLogMsg.append("\n"); 
	
	testLogMsg.append("NumOfFails: "); 
	testLogMsg.append(std::to_string(testData->NumOfTimesFailed)); 
	testLogMsg.append("\n"); 
	
	testLogMsg.append("OPTIONS: ");
	testLogMsg.append(CGEN_ALLOPTIONS);
	testLogMsg.append("\n\n");  
	
			  
	std::string PathtoFile = "IntegrationTestResults\\IntegrationResults.txt";
	
	
	AEWriteToEndOfFile(PathtoFile.c_str(), testLogMsg.c_str(), testLogMsg.length());
}
 
inline void LogAEITest(std::string testName, LogStatus status, std::string AssertionMessage, unsigned long ulLine, std::string pcFileName)
{
	AEITestLogData testLogData;
	testLogData.AssertionMessage = AssertionMessage;
	testLogData.pcFileName = pcFileName;
	testLogData.status = status;
	testLogData.testName = testName;
	testLogData.ulLine = ulLine;
	LogAEITest(&testLogData);
}



#include <stdlib.h>

inline void _AEITEST_END_FUNC()
{ 
	
	//iterate through all saved logs and write them to the file
	for(AEITestLogData* ele : TestLogsArgs)
	{ 
		LogAEITest(ele);
	}
	 
  
	//vTaskEndScheduler();
	exit(EXIT_SUCCESS); 
}


inline void AEITEST_END_FUNC()
{
  
	//log timer tests that need logging. only done for integration testing.
#ifndef GOOGLE_TESTING 
	for (uint32_t i = 0; i < logpathToFile.size(); i++)
	{
		AEWriteToEndOfFile(logpathToFile[i].c_str(), logthingToWrite[i].c_str(), logthingToWriteSize[i]);
	}  
#endif
	
	
	
	LogAEITest("FINISH_TEST_GROUP", LogStatus::FINISHED, "done test group", 0, "None");
	
	_AEITEST_END_FUNC();
}



static char const * const hardfaultmsg = 
	"TESTGROUPNAME: " INTEGRATION_TEST_CHOSEN "\nTESTSPECIFIC: " INTEGRATION_TEST_CHOSEN_SPECIFIC "\nSTATUS: EXCEPTION\nFILE: None\nLINE: 0\nMESSAGE: hardfault has occured\nNumOfPasses: 0\nNumOfFails: 0\nOPTIONS: " CGEN_ALLOPTIONS "\n\n";
//end integration tests as a hardfault has happened
inline void AEITEST_END_HARDFAULT_FUNC()
{
	//std::string PathtoFile = "IntegrationTestResults\\IntegrationResults.txt";
	
	
	AEWriteToEndOfFile("IntegrationTestResults\\IntegrationResults.txt", hardfaultmsg, strlen(hardfaultmsg));    //, "HARDFAULT:" CGEN_ALLOPTIONS "\n", strlen(CGEN_ALLOPTIONS)+11);
	//LogAEITest("FINISH_TEST_GROUP", LogStatus::EXCEPTION, "a hard fault occured during this test group", 0, "None");
	
	_AEITEST_END_FUNC();
}





void AEITEST_END_TestsAfterTimer_FUNC(uint32_t timeInMilliBeforeEnd);


inline void AEITEST_EXPECT_TEST_TO_RUN_FUNC(std::string testName) 
{ 
	
	int ID = std::hash<std::string> {}(testName);
	AEITestLogData* testLogData;   // = new AEITestLogData();
	
	
	//check if this test has been executed already
	bool testFound = false;
	for (AEITestLogData* ele : TestLogsArgs)
	{ 
		if (ele->ID == ID)
		{ 
			testLogData = ele;
			testFound = true;
			return;
		}
	}
	if (testFound == false)
	{ 
		testLogData = new AEITestLogData();
		
		testLogData->AssertionMessage = "This test never ran.";
		testLogData->pcFileName = ""; 
		testLogData->testName = testName;
		testLogData->ulLine = 0;
		testLogData->status = LogStatus::FAILED;
		testLogData->ID = ID;
	
	
		TestLogsArgs.push_back(testLogData);
	}
}


/**

 … test function that runs or somethign.…

*/
inline void AEITEST_Func(std::string testName, bool thingToAssert, std::string AssertionMessage, unsigned long ulLine, std::string pcFileName, bool endTestIfFailed = false)
{ 
	
	int ID = std::hash<std::string> { }(testName);
	AEITestLogData* testLogData;// = new AEITestLogData();
	
	
	//check if this test has been executed already
	bool testFound = false;
	for(AEITestLogData* ele : TestLogsArgs)
	{ 
		if (ele->ID == ID)
		{ 
			testLogData = ele;
			testFound = true;
		}
	}
	if (testFound == false)
	{ 
		testLogData = new AEITestLogData();
		
		testLogData->AssertionMessage = AssertionMessage;
		testLogData->pcFileName = pcFileName; 
		testLogData->testName = testName;
		testLogData->ulLine = ulLine;
		testLogData->ID = ID;
	
	
		TestLogsArgs.push_back(testLogData);
	
	}
	
	//save the args to log it later so to not have to write to the file too often and to avoid race conditions of writing to the file. 
	if(thingToAssert == false)
	{testLogData->NumOfTimesFailed += 1;}
	else	
	{testLogData->NumOfTimesPassed += 1; }
	LogStatus status;
	testLogData->status = testLogData->NumOfTimesFailed > 0 ? LogStatus::FAILED : LogStatus::PASSED;
	 
	
	

	if (endTestIfFailed == true)
	{
		if (testLogData->NumOfTimesFailed > 0)
		{
			AEITEST_END_FUNC();
		}
	}
	
  
	
	 
}




inline void AEITEST_LogOnlyIfFalse_Func(std::string testName, bool thingToAssert, std::string AssertionMessage, unsigned long ulLine, std::string pcFileName, bool endTestIfFailed = false)
{
	if (thingToAssert == false)
	{
		AEITEST_Func(testName, thingToAssert, AssertionMessage, ulLine, pcFileName, endTestIfFailed);
	}
		
}

 

