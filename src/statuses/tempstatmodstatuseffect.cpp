#include "../character.h"
#include "tempstatmodstatuseffect.h"


TempStatModStatusEffect::TempStatModStatusEffect(const StatMod& modToApply, const EffectType oppositeStatus, const StatusTemplate& statTemplate, const EffectParams& effectParams)
	: HasOppositeStatusEffect(oppositeStatus, statTemplate, effectParams),
	  modToApply(modToApply)
{

}

void TempStatModStatusEffect::onAdd()
{
	//postcondition: modToApply is added to the target

	target.AddStats(modToApply);
	HasOppositeStatusEffect::onAdd();
}

void TempStatModStatusEffect::onRemove()
{
	//postcondition: modToApply is subtracted from the target.

	target.SubStats(modToApply);
	HasOppositeStatusEffect::onRemove();
}
