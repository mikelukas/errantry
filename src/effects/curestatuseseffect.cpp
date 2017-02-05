#include "../character.h"
#include "curestatuseseffect.h"

CureStatusesEffect::CureStatusesEffect(EffectType typeToCure, const EffectParams& effectParams)
	: Effect(effectParams)
{
	typesToCure = new vector<EffectType>();
	typesToCure->push_back(typeToCure);
}

CureStatusesEffect::CureStatusesEffect(vector<EffectType>* typesToCure, const EffectParams& effectParams)
	: Effect(effectParams),
	  typesToCure(typesToCure)
{
	//postcondition: typesToCure is assigned to this instances typesToCure
	//field, and will be deleted when this effect is cleaned up.

}

CureStatusesEffect::~CureStatusesEffect()
{
	//postcondition: deletes the vector of statuses to clear vector

	delete typesToCure;
}

void CureStatusesEffect::runTurnEffect()
{
	//postcondition: if the target has any of the statuse in typesToCure, they
	//are removed.

	for(vector<EffectType>::const_iterator it = typesToCure->begin(); it != typesToCure->end(); it++)
	{
		target.removeStatus((*it));
	}
}
