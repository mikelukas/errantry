#include <iostream>
#include "../character.h"
#include "hasoppositestatuseffect.h"

using std::cout;
using std::endl;

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

	cout<<target.ShowName()<<" feels "<<getAdjectiveFor(getType())<<"!"<<endl;
}

void HasOppositeStatusEffect::onRemove()
{
	//postcondition: a message is displayed that the status has been removed from the target

	if(target.getHP() > 0)
	{
		cout<<target.ShowName()<<" feels "<<getAdjectiveFor(oppositeStatus)<<"."<<endl;
	}
}
