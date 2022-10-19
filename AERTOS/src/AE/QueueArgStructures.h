#pragma once

#include <cstdint>
#include "FreeRTOS.h"
#include "AEEventBase.h"


class TwoIntArgStructure
{
public:
	int Arg1;
	int Arg2; 

	TwoIntArgStructure() : Arg1(0), Arg2(0) {}
	TwoIntArgStructure(int arg1, int arg2) :Arg1(arg1), Arg2(arg2) {}


	//copyConstructor
	TwoIntArgStructure(const TwoIntArgStructure &objToCopy) {
		Arg1 = objToCopy.Arg1;
		Arg2 = objToCopy.Arg2;
	}

};


class TwoIntAndBoolArgStructure
{
public:
	int Arg1;
	int Arg2;
	bool Arg3;

	TwoIntAndBoolArgStructure() : Arg1(0), Arg2(0) , Arg3(0){}
	TwoIntAndBoolArgStructure(int arg1, int arg2, bool arg3) :Arg1(arg1), Arg2(arg2), Arg3(arg3) {}

	//copyConstructor
	TwoIntAndBoolArgStructure(const TwoIntAndBoolArgStructure &objToCopy) {
		Arg1 = objToCopy.Arg1;
		Arg2 = objToCopy.Arg2;
		Arg3 = objToCopy.Arg3;
	}

};


class ThreeIntAndAEEvtBasePtr
{
public:

	static ThreeIntAndAEEvtBasePtr ObjectPool[NUMOFACTIVEOBJECTS];
	static uint16_t IndexForObjectPool;

	//factory method for getting ThreeIntAndAEEvtBasePtr from a pool.
	static ThreeIntAndAEEvtBasePtr* GetFromPool(uint16_t arg1, uint16_t arg2, uint16_t arg3, AEEventDiscriminator_t* arg4);
	   
	

	uint16_t Arg1;
	uint16_t Arg2;
	uint16_t Arg3; 
	AEEventDiscriminator_t* Arg4;
	 
	//copyConstructor
	ThreeIntAndAEEvtBasePtr(const ThreeIntAndAEEvtBasePtr &objToCopy) {
		Arg1 = objToCopy.Arg1;
		Arg2 = objToCopy.Arg2;
		Arg3 = objToCopy.Arg3;
		Arg4 = objToCopy.Arg4;
	}

protected:

	ThreeIntAndAEEvtBasePtr() : Arg1(0), Arg2(0), Arg3(0), Arg4(nullptr) {}
	ThreeIntAndAEEvtBasePtr(uint16_t arg1, uint16_t arg2, uint16_t arg3, AEEventDiscriminator_t* arg4) : Arg1(arg1), Arg2(arg2), Arg3(arg3), Arg4(arg4) {}
};

 