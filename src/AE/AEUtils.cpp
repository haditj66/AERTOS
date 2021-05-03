#include "AEUtils.h"

#include <stdarg.h>
#include "stdio.h"
 






void AEFormatMsg(char* formattedBuffer, uint32_t sizeOfFormatBuffer, const char* msgToFormat, ...)
{
	va_list lst;
	va_start(lst, msgToFormat); 
	vsnprintf(formattedBuffer, sizeOfFormatBuffer, msgToFormat, lst);
	va_end(lst);
	
}



	
void* NULLPeripheral::Instance = nullptr;

 


#if (PRINT_METHOD == PRINT_UART_NON_AE)
//this should be implemented in yourself 
extern void _AEPrint(char* msg);

#else
static  void _AEPrint(char* msg);

#endif


#ifdef  HARDWARE

#if (PRINT_METHOD == PRINT_SEMIHOSTING)
static void _AEPrint(char* msg)
{ 
	printf(msg);
}

#endif

#if (PRINT_METHOD == PRINT_UART_AE)

void _AEPrint(char* msg)
{
	//TODO: implement this
}

#endif





#if (PRINT_METHOD == PRINT_NONE)


void _AEPrint(char* msg)
{
	
}
#endif


#elif defined(SIMULATION)
void _AEPrint(char* msg)
{ 
	printf(msg);
    fflush(stdout);
}

#elif defined(USING_LINUX)

#include "iostream"
void _AEPrint(char* msg)
{
	std::cout << msg <<std::endl;
}

#endif //  







//void AEPrintWithCache(const char* msg) 
//{
//	
//#ifdef PRINT_USE_CACHE
//
//	
//	uint32_t sizeOfMsg = strlen(msg);
//	//append this to the char so far
//	memcpy(bufferForTransmittingStuff + indexOfCharsInBuffer, msg, sizeOfMsg);
//	
//	indexOfCharsInBuffer += sizeOfMsg;
//	numOfMsgsSentSoFar++;
//	if (numOfMsgsSentSoFar >= numOfMsgsUntilToSend)
//	{
//		_AEPrint(bufferForTransmittingStuff);
//		memset(bufferForTransmittingStuff, 0, 1000);
//		numOfMsgsSentSoFar = 0;
//		indexOfCharsInBuffer = 0;
//	}
//#else 
//	_AEPrint(msg);
//#endif
//}


static char msgFormatted[300];  
#ifdef PRINT_USE_CACHE
static char bufferForTransmittingStuff[1000];
static uint32_t indexOfCharsInBuffer = 0;
static uint16_t numOfMsgsUntilToSend = PRINT_CACHE_NUM;
static uint16_t numOfMsgsSentSoFar = 0; 
#endif

void AEPrint(const char* msg, ...)
{  
		va_list lst;
		va_start(lst, msg);
		vsnprintf(msgFormatted, sizeof(msgFormatted), msg, lst);
		va_end(lst);
	
//	//get size of char from the message
//	uint32_t sizeOfMsg = strlen(msg);
//	uint32_t sizeOfDigits = numDigits(num1);
//	//format the buffer to include the number 
//	snprintf(msgFormatted, sizeOfMsg + sizeOfDigits + 1, msg, num1);
	
	//AEPrintWithCache(msgFormatted);
	
	 
#ifdef PRINT_USE_CACHE
	
	uint32_t sizeOfMsg = strlen(msgFormatted);
	//append this to the char so far
	memcpy(bufferForTransmittingStuff + indexOfCharsInBuffer, msgFormatted, sizeOfMsg);
	
	indexOfCharsInBuffer += sizeOfMsg;
	numOfMsgsSentSoFar++;
	if (numOfMsgsSentSoFar >= numOfMsgsUntilToSend)
	{
		_AEPrint(bufferForTransmittingStuff);
		memset(bufferForTransmittingStuff, 0, 1000);
		numOfMsgsSentSoFar = 0;
		indexOfCharsInBuffer = 0;
	}
#else
	_AEPrint(msgFormatted);
#endif
	
}




 