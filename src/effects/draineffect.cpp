#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "draineffect.h"

DrainEffect::DrainEffect(const EffectParams& effectParams)
	: Effect(effectParams)
{

}

void DrainEffect::runTurnEffect()
{
	//postcondition: BASE
	int netDamage = target.applyMagicalDamage(BASE_DRAIN_HP, element);
	applier.ChangeHP(netDamage); //add to applier's HP amount done in magical damage

	std::stringstream drainDmgStr;
	drainDmgStr<<applier.ShowName()<<" drained "<<netDamage<<" HP from "<<target.ShowName()<<"!";
	log(drainDmgStr.str());
}
