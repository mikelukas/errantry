#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "poisonstatus.h"

#include "../util/randutils.h"

PoisonStatus::PoisonStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{
	// TODO Auto-generated constructor stub

}

void PoisonStatus::onAdd()
{
	std::stringstream added;
	added<<applier.ShowName()<<" poisoned "<<target.ShowName()<<"!";
	log(added.str());
}

void PoisonStatus::onRemove()
{
	std::stringstream removed;
	removed<<target.ShowName()<<" recovered from "<<getName()<<".";
	log(removed.str());
}

void PoisonStatus::runTurnEffect()
{
	int basePoisonDamage = getRandIntBetween(1, POISON_DAMAGE);

	int poisonDamage = target.getHP()-basePoisonDamage > 0 ? basePoisonDamage : target.getHP()-1; //target can't die from poison
	if(poisonDamage == 0)
	{
		return;
	}

	target.ChangeHP(-1*poisonDamage);

	std::stringstream dmgMsg;
	dmgMsg<<target.ShowName()<<" took "<<poisonDamage<<" from "<<getName()<<"!";
	log(dmgMsg.str());
}
