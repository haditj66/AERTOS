#pragma once

//this is the file that needs to have ALL events defined.

//#include "AEConfig.h"
  
//##############################################
//put all your events here!
//##############################################

#include "AEEventBase.h"
//#include "PeripheralImplementations.h"



class I2C_RXCpltEVT : public AEEventBase
{
public:
	//TODO: get rid of these unnecdessary statics evt Ids
	static EventPoolSize_t EvtIdStatic;

	uint8_t forI2C;

	I2C_RXCpltEVT() {}
	; 
	 
};

class I2C_TXCpltEVT : public AEEventBase
{
public:
	//TODO: get rid of these unnecdessary statics evt Ids
	static EventPoolSize_t EvtIdStatic;

	uint8_t forI2C;

	I2C_TXCpltEVT() {}
	; 

};

class Uart2RecieveEVT : public AEEventBase
{ 
public:
	//TODO: get rid of these unnecdessary statics evt Ids
	static EventPoolSize_t EvtIdStatic;

	Uart2RecieveEVT() {}
	;//readBuffer = UART2Peripheral::readBuffer; };

	char* readBuffer;

};

class PCConnecttionCheckEVT : public AEEventBase
{
public:
	//TODO: get rid of these unnecdessary statics evt Ids
	static EventPoolSize_t EvtIdStatic;

	bool isConnected; 

};



class SPBDecompressionDone : public AEEventBase
{
public:
	static EventPoolSize_t EvtIdStatic;

	char* ConcactenatedData;

};


class CommandRequested : public AEEventBase
{
public:
	static EventPoolSize_t EvtIdStatic;

	char CommandData[20];

};


class ButtonChanged : public AEEventBase
{
public:
	static EventPoolSize_t EvtIdStatic;

	uint8_t ForButton;

	bool isButtonWentDown;

};


class EventTest1 : public AEEventBase
{

public:
	//TODO: get rid of these unnecdessary statics evt Ids
	static EventPoolSize_t EvtIdStatic;

	EventTest1()
		: AEEventBase() {}
	;

	int someParam;
private:


};



class EventTest2 : public  AEEventBase
{
public:

	static EventPoolSize_t EvtIdStatic;

	EventTest2()
		: AEEventBase() {}
	;

	uint16_t someParam2;
private:


};



