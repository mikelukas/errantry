#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "stunstatuseffect.h"

StunStatusEffect::StunStatusEffect(const StatusTemplate& statusTemplate, const EffectParams& effectParams)
	: StatusEffect(statusTemplate, effectParams)
{

}

void StunStatusEffect::onAdd()
{
	//postcondition: displays a message that the target is stunned.

	std::stringstream added;
	added<<target.ShowName()<<" is "<<getAdjectiveFor(getType())<<"!";
	log(added.str());
}

void StunStatusEffect::runTurnEffect()
{
	//postcondition: displays a message that the target can't make a move.

	std::stringstream stunnedMsg;
	stunnedMsg<<target.ShowName()<<" can't move!";
	log(stunnedMsg.str());
}

void StunStatusEffect::onRemove()
{
	//postcondition: displays a message that the target is no longer stunned.

	std::stringstream removed;
	removed<<target.ShowName()<<" recovers.";
	log(removed.str());
}
