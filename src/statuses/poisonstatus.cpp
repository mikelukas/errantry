#include <iostream>
#include "../character.h"
#include "poisonstatus.h"
#include "../randutils.h"

using std::cout;
using std::endl;

PoisonStatus::PoisonStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{
	// TODO Auto-generated constructor stub

}

void PoisonStatus::onAdd()
{
	cout<<applier.ShowName()<<" poisoned "<<target.ShowName()<<"!"<<endl;
}

void PoisonStatus::onRemove()
{
	cout<<target.ShowName()<<" recovered from "<<getName()<<"."<<endl;
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
	cout<<target.ShowName()<<" took "<<poisonDamage<<" from "<<getName()<<"!"<<endl;
}
