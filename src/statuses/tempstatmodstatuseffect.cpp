#include <iostream>
#include "../character.h"
#include "tempstatmodstatuseffect.h"

using std::cout;
using std::endl;

TempStatModStatusEffect::TempStatModStatusEffect(const StatMod& modToApply, const EffectType oppositeStatus, const StatusTemplate& statTemplate, const EffectParams& effectParams)
	: StatusEffect(statTemplate, effectParams),
	  modToApply(modToApply),
	  oppositeStatus(oppositeStatus)
{

}

void TempStatModStatusEffect::apply()
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

void TempStatModStatusEffect::onAdd()
{
	//postcondition: modToApply is added to the target

	target.AddStats(modToApply);
	cout<<target.ShowName()<<" feels "<<getAdjectiveFor(getType())<<"!"<<endl;
}

void TempStatModStatusEffect::onRemove()
{
	//postcondition: modToApply is subtracted from the target.

	target.SubStats(modToApply);
	if(target.getHP() > 0)
	{
		cout<<target.ShowName()<<" feels "<<getAdjectiveFor(oppositeStatus)<<"."<<endl;
	}
}
