#include "AEObservorBase.h"
//#include "AELinkSignalFlow.h"
#include "AELinkDeterministic.h"


/*
TObservationType AEObservorBase::GetObservation()
{
	//first check if all linked observors have had their values canged
	for (uint16_t i = 0; i < numOfDeterministicLinks; i++)
	{
		//MyDeterministicLinks[i]->GetTheObservorImLinkedTo()->GetObservation();
	}
}*/


/*
void AEObservorBase::AddLink(AELinkBase* theLink)
{
	if (theLink->GetTheLinkType() == LinkType::Deterministic)
	{
		MyDeterministicLinksIPoint[numOfDeterministicLinksIPoint + 1] = (AELinkDeterministic*)theLink;
		numOfDeterministicLinksIPoint++;
	}
}*/


AEObservorBase* AEObservorBase::ObservorPool[MAXNUMOFOBSERVORS];
uint16_t AEObservorBase::CurrentId = 0;


void AEObservorBase::AddObserverOfInfluence(uint16_t observorID)
{ 
	

	 
	ObservorsOfInfluence[numOfObservorsOfInfluence] = observorID;


	//also add that observor's NeedARefeshValues 
	ObservorsOfInfluenceNeedARefeshValues[numOfObservorsOfInfluence] = 
		//&((AEObservorInterpretorBase*)(ObservorPool[observorID]))->DoINeedARefresh;
		&((static_cast<AEObservorInterpretorBase*>(ObservorPool[observorID]))->DoINeedARefresh);

	numOfObservorsOfInfluence++;
	 
}

AEObservorBase::AEObservorBase()
{
	Prescaler = 1;
	numOfObservorsOfInfluence = 0;

	isObservorOn = true;

	numOfDeterministicObservorsPointToMe = 0;

	FrequencyHasBeenConfigured = false;

	//set ID
	ObservorId = CurrentId;
	ObservorPool[CurrentId] = this;
	CurrentId++;
	 

	numOfDeterministicLinksIPointThatAreInterpretors = 0;
	HasThereBeenARefreshOAnyDeterministicObservors = false;
	SetToClock = false;
        
        NumOfSPBObservorsIPointTo = 0;
}



bool AEObservorBase::CheckIfObservorIsEndChain(AEObservorBase* theObservorToCheck)
{
	//go through all deterministic links pointing to this observor and check if ANY interpretors are the ones linking
	bool isEndChain = false;
	for (size_t j = 0; j < theObservorToCheck->numOfDeterministicLinksPointToMe; j++)
	{
		if (AELinkDeterministic::Links[theObservorToCheck->MyDeterministicLinksPointingToMe[j]].GetTheObservorIPointFrom()->GetMyObservorType() & ObservorType::Interpretors)
		{
			isEndChain = true;
			break;
		}
	}

	return isEndChain;
	
}



void AEObservorBase::GetAllSPBRecursivelyThisObservorPointsToandCheckIfTheyAreEndChains(AEObservorBase * theObservorToGetSPBs)
{
	//get all SPBs that that  observor points to
	for (int i = 0; i < theObservorToGetSPBs->NumOfSPBObservorsIPointTo; i++)
	{
		AEObservorBase* SPBPointsTo = theObservorToGetSPBs->SPBObservorsIPointTo[i];//AELinkSignalFlow::Links[theObservorToGetSPBs->MySPBLinksIPointing[i]].GetTheObservorIPointTo();
		//and check if it is an end chain.
		SPBPointsTo->IsEndChain = CheckIfObservorIsEndChain(SPBPointsTo);
		//check all SPBs of that one recursively
		GetAllSPBRecursivelyThisObservorPointsToandCheckIfTheyAreEndChains(SPBPointsTo);
	}

}

void AEObservorBase::InitializeEndChainObservors()
{
	//go through each observor so far and check for the ones that are SPB and sensor observors 
	//(as these are the only ones capable of being End_Chain)
	//first start with the sensors. if the sensor links to a SPB, check if that has an interpretor on it.
	//Then check if that SPB links to another SPB and check that one as well if an interpretor links to it.
	//continue this process until there are no other SPB that is linked to.
	//Any sensors or SPBs that had at least one interpretor linked to it, is an endchain.


	for (int i = 0; i < CurrentId; i++)
	{
		if (ObservorPool[i]->GetMyObservorType() & ObservorType::Sensor)
		{
			//check if this sensor is an endchain
			ObservorPool[i]->IsEndChain = CheckIfObservorIsEndChain(ObservorPool[i]);

			//get all observors that are SPBs that links to this sensor 
			GetAllSPBRecursivelyThisObservorPointsToandCheckIfTheyAreEndChains(ObservorPool[i]);
		}

	}


	//now that all endchain observors have been identified, Go through each endchain observor and
	//get their "chain of influence" (all observors that the endchain effects to refresh when it refreshes.)
	//to get this, get all observors(interpretors ONLY as SPBs dont need to be signalled to refresh as they are refreshed via
	//a clock tick only) that link to an observor and recursively that link to an observor.

	for (int j = 0; j < CurrentId; j++)
	{
		if (ObservorPool[j]->IsEndChain)
		{
			//go through all links to SPBs and interpretors that link to this endchain.
			//links FROM Interpretors 
			for (int i = 0; i < ObservorPool[j]->numOfDeterministicLinksPointToMe; i++)
			{
				
				RecursivelySetInfluencedPointedToInterpretors((AEObservorBase*)AELinkDeterministic::Links[ObservorPool[j]->MyDeterministicLinksPointingToMe[i]].GetTheInterpretorObservorIPointFrom(), ObservorPool[j]);
				
			}

			// links TO SPBs
			for (int i = 0; i < ObservorPool[j]->NumOfSPBObservorsIPointTo; i++)
			{
				RecursivelySetInfluencedPointedToInterpretors(ObservorPool[j]->SPBObservorsIPointTo[i], ObservorPool[j]);// (AELinkSignalFlow::Links[ObservorPool[j]->MySPBLinksIPointing[i]].GetTheObservorIPointTo(), ObservorPool[j]);
			}
		}

	}

}



void AEObservorBase::RecursivelySetInfluencedPointedToInterpretors(AEObservorBase * ObservorToChackSet, AEObservorBase * forEndChain)
{
	//first check if it is a interpretor or a SPB. SPBs should not be added to the array while interpretors should.
	if (ObservorToChackSet->GetMyObservorType() & ObservorType::SPB)
	{
		// if its a SPB then it can only have signalFlowLinks Or interpretors that link TO it

	}
	else if (ObservorToChackSet->GetMyObservorType() & ObservorType::Interpretors)
	{
		forEndChain->AddObserverOfInfluence(ObservorToChackSet->ObservorId);

		//if its an interpretor than same as before. I want interpretors that links FROM it and SBPS that it links TO
		/*AEObservorInterpretorBase* interpretor = static_cast<AEObservorInterpretorBase*>(ObservorToChackSet);
		for (int i = 0; i < interpretor->numOfDeterministicLinksIPoint; i++)
		{
			RecursivelySetInfluencedPointedToInterpretors(AELinkDeterministic::Links[interpretor->MyDeterministicLinksIPoint[i]].GetTheObservorIPointTo(), forEndChain);
		}*/

	}

	//SPBs that this links TO
	for (int i = 0; i < ObservorToChackSet->NumOfSPBObservorsIPointTo; i++)
	{
		RecursivelySetInfluencedPointedToInterpretors(ObservorToChackSet->SPBObservorsIPointTo[i], forEndChain);//(AELinkSignalFlow::Links[ObservorToChackSet->MySPBLinksIPointing[i]].GetTheObservorIPointTo(), forEndChain);
	}
	//links FROM Interpretors 
	for (int i = 0; i < ObservorToChackSet->numOfDeterministicLinksPointToMe; i++)
	{ 
		RecursivelySetInfluencedPointedToInterpretors((AEObservorBase*)(AELinkDeterministic::Links[ObservorToChackSet->MyDeterministicLinksPointingToMe[i]].GetTheInterpretorObservorIPointFrom()), forEndChain);
		
	}

}



uint16_t AEObservorBase::GetnumOfObservorsOfInfluence()
{
	return numOfObservorsOfInfluence;
}

bool** AEObservorBase::GetObservorsOfInfluenceNeedARefeshValues()
{
	return ObservorsOfInfluenceNeedARefeshValues;
}

float AEObservorBase::GetFrequencyIRefreshAt()
{
	return FrequencyIRefreshAt;
}

void AEObservorBase::AddSignalFlowLink(AESPBObservor * toObservor, uint16_t ToChannel, uint8_t toOutPutFilter )
{
	//start moving away from links as objects. They dont serve a real purpose. any information that an observor needs about a linked 
	//observor can simply be embedded in the observor itself rather then needing to misdirectly call a link for that information.
	// of course the only thing is that by having links you have a nice data structure for data that should be grouped and variable can
	//be associated with another variable. However, even though this is neater and easier to read, the extra time taken calling a links address
	// to get to the data may not be worth it. Either way the data taken will be the same as the data will either be stored on the observor or the link.
	/*	uint8_t linkId = AELinkSignalFlow::InitializeLinkFromPool(this, toObservor);
	this->MySPBLinksIPointing[this->numOfSPBLinksIPoint] = linkId;


	toObservor->MySPBLinksPointingToMe[toObservor->numOfSignalLinksPointToMe] = linkId;

	this->numOfSPBLinksIPoint++;
	toObservor->numOfSignalLinksPointToMe++;
	*/

	//SetObservorIPointTo(toObservor); 
	OutputFilterThatSignalGoesFrom[NumOfSPBObservorsIPointTo] = toOutPutFilter-1;
	SPBObservorsIPointTo[NumOfSPBObservorsIPointTo] = toObservor;
	ChannelIdsIConnectTo[NumOfSPBObservorsIPointTo] = ToChannel;
	NumOfSPBObservorsIPointTo++;
}

uint16_t AEObservorBase::GetClockIdImSourcedTo()
{
	return ClockIdImSourcedTo;
}

uint8_t AEObservorBase::GetMyObservorType()
{
	return MyObservorType;
}

void AEObservorBase::SetMyObservorType(ObservorType myObservorType)
{
	MyObservorType |= myObservorType;

}


