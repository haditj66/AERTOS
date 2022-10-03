#pragma once

#include "FreeRTOS.h"
#include "semphr.h" 
#include "AEPublishSubscribeManager.h"
#include "AEEventBase.h"

//only events that are less than _MAX_NumOfAllEvents should be subscribed 
	//or unsubscribed to. events passed then are always considered to be subbed to.
#define CheckIfSubscribedEventIsValid configASSERT(Tevt::EvtIdStatic < MAX_NumOfAllEvents);
#define CheckIfSubscribedEventIsValid2 configASSERT(Tevt < MAX_NumOfAllEvents);
#define CheckIfSubscribedEventIsValid3 configASSERT(TEventToSubscribeTo::EvtIdStatic < MAX_NumOfAllEvents);
#define CheckIfSubscribedEventIsValid4 configASSERT(TEventToUnSubscribeTo::EvtIdStatic < MAX_NumOfAllEvents);


template <class Tevt>
inline void _InlineSubscribe(uint16_t AO_ID)
{
	ThreeIntAndAEEvtBasePtr* subscriberArgs = ThreeIntAndAEEvtBasePtr::GetFromPool(Tevt::EvtIdStatic, AO_ID, 0, nullptr);

	CheckIfSubscribedEventIsValid

	xQueueSendToBack(AEPublishSubscribeManager::getInstance()->queueForSubAndPub, &subscriberArgs, 0);
};

template <uint16_t Tevt>
inline void _InlineSubscribe(uint16_t AO_ID)
{
	ThreeIntAndAEEvtBasePtr* subscriberArgs = ThreeIntAndAEEvtBasePtr::GetFromPool(Tevt, AO_ID, 0, nullptr);

	CheckIfSubscribedEventIsValid2

	xQueueSendToBack(AEPublishSubscribeManager::getInstance()->queueForSubAndPub, &subscriberArgs, 0);
};


template <class Tevt>
inline void _InlineUnSubscribe(uint16_t AO_ID)
{
	ThreeIntAndAEEvtBasePtr* unsubscriberArgs = ThreeIntAndAEEvtBasePtr::GetFromPool(Tevt::EvtIdStatic, AO_ID, 1, nullptr);

	CheckIfSubscribedEventIsValid

	xQueueSendToBack(AEPublishSubscribeManager::getInstance()->queueForSubAndPub, &unsubscriberArgs, 0);
};

template <uint16_t Tevt>
inline void _InlineUnSubscribe(uint16_t AO_ID)
{
	ThreeIntAndAEEvtBasePtr* unsubscriberArgs = ThreeIntAndAEEvtBasePtr::GetFromPool(Tevt, AO_ID, 1, nullptr);

	CheckIfSubscribedEventIsValid2

	xQueueSendToBack(AEPublishSubscribeManager::getInstance()->queueForSubAndPub, &unsubscriberArgs, 0);
};


template<class TEventToSubscribeTo>
inline void _InlineSubscribeFROMISR(uint16_t AO_ID) {

	CheckIfSubscribedEventIsValid3

	AEPublishSubscribeManager::getInstance()->_SubscribeToEvt(TEventToSubscribeTo::EvtIdStatic, AO_ID);
};


template<class TEventToUnSubscribeTo>
inline void _InlineUnSubscribeFROMISR(uint16_t AO_ID) {
	CheckIfSubscribedEventIsValid4

	AEPublishSubscribeManager::getInstance()->_UnSubscribeToEvt(TEventToUnSubscribeTo::EvtIdStatic, AO_ID);
};

template <uint16_t Tevt>
inline void _InlineSubscribeFROMISR(uint16_t AO_ID) {
	CheckIfSubscribedEventIsValid2
	AEPublishSubscribeManager::getInstance()->_SubscribeToEvt(Tevt, AO_ID);
};


template <uint16_t Tevt>
inline void _InlineUnSubscribeFROMISR(uint16_t AO_ID) {
	CheckIfSubscribedEventIsValid2
	AEPublishSubscribeManager::getInstance()->_UnSubscribeToEvt(Tevt, AO_ID);
};