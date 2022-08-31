#include "QueueArgStructures.h"

ThreeIntAndAEEvtBasePtr ThreeIntAndAEEvtBasePtr::ObjectPool[NUMOFACTIVEOBJECTS];
uint16_t ThreeIntAndAEEvtBasePtr::IndexForObjectPool = 0;


ThreeIntAndAEEvtBasePtr * ThreeIntAndAEEvtBasePtr::GetFromPool(uint16_t arg1, uint16_t arg2, uint16_t arg3, AEEventDiscriminator_t * arg4)
{ 
	//modulos for setting it back to 0 when NUMOFACTIVEOBJECTS is hit
	IndexForObjectPool = (IndexForObjectPool + 1) % NUMOFACTIVEOBJECTS;

	ThreeIntAndAEEvtBasePtr::ObjectPool[IndexForObjectPool].Arg1 = arg1;
	ThreeIntAndAEEvtBasePtr::ObjectPool[IndexForObjectPool].Arg2 = arg2;
	ThreeIntAndAEEvtBasePtr::ObjectPool[IndexForObjectPool].Arg3 = arg3;
	ThreeIntAndAEEvtBasePtr::ObjectPool[IndexForObjectPool].Arg4 = arg4;

	return &ThreeIntAndAEEvtBasePtr::ObjectPool[IndexForObjectPool];
}
