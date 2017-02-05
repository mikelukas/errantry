#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "hasoppositestatuseffect.h"

HasOppositeStatusEffect::HasOppositeStatusEffect(const EffectType oppositeStatus, const StatusTemplate& statusTemplate, const EffectParams& effectParams)
	: StatusEffect(statusTemplate, effectParams),
	  oppositeStatus(oppositeStatus)
{

}

void HasOppositeStatusEffect::apply()
{
	//postcondition: this StatusEffect is added to the target, UNLESS the target
	//has the opposite of this StatusEffect, in which case the opposite is
	//removed and this status is NOT added and set as expired.

	if(target.hasStatus(oppositeStatus))
	{
		target.removeStatus(oppositeStatus);
		setExpired();
		return;
	}

	StatusEffect::apply();
}

void HasOppositeStatusEffect::onAdd()
{
	//postcondition: a message is displayed that the status has been added to the target

	std::stringstream addedMsg;
	addedMsg<<target.ShowName()<<" feels "<<getAdjectiveFor(getType())<<"!";
	log(addedMsg.str());
}

void HasOppositeStatusEffect::onRemove()
{
	//postcondition: a message is displayed that the status has been removed from the target

	if(target.getHP() > 0)
	{
		std::stringstream removedMsg;
		removedMsg<<target.ShowName()<<" feels "<<getAdjectiveFor(oppositeStatus)<<".";
		log(removedMsg.str());
	}
}
