#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "healeffect.h"

HealEffect::HealEffect(const EffectParams& effectParams)
	: Effect(effectParams)
{

}

void HealEffect::runTurnEffect()
{
	//postcondition: BASE_HEAL_HP is added to target's HP.

	target.ChangeHP(BASE_HEAL_HP);

	std::stringstream healStr;
	healStr<<target.ShowName()<<" healed "<<BASE_HEAL_HP<<" HP!";
	log(healStr.str());
}
