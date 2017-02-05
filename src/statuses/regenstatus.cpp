#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "regenstatus.h"
#include "../util/randutils.h"

RegenStatus::RegenStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{
}

void RegenStatus::onAdd()
{
	std::stringstream added;
	added<<target.ShowName()<<" is regenerating!";
	log(added.str());
}

void RegenStatus::onRemove()
{
	std::stringstream removed;
	removed<<target.ShowName()<<" stopped regenerating.";
	log(removed.str());
}

void RegenStatus::runTurnEffect()
{
	//postcondition: target regains a random amount of HP from 1 to MAX_REGEN_HP

	int regenHP = getRandIntBetween(1, MAX_REGEN_HP);
	target.ChangeHP(regenHP);

	std::stringstream regenMsg;
	regenMsg<<target.ShowName()<<" regenerated "<<regenHP<<" HP!";
	log(regenMsg.str());
}
