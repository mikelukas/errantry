#include <iostream>
#include "../character.h"
#include "stunstatuseffect.h"

using std::cout;
using std::endl;

StunStatusEffect::StunStatusEffect(const StatusTemplate& statusTemplate, const EffectParams& effectParams)
	: StatusEffect(statusTemplate, effectParams)
{

}

void StunStatusEffect::onAdd()
{
	//postcondition: displays a message that the target is stunned.

	cout<<target.ShowName()<<" is "<<getAdjectiveFor(getType())<<"!"<<endl;
}

void StunStatusEffect::onTurn()
{
	//postcondition: displays a message that the target can't make a move.

	cout<<target.ShowName()<<" can't move!"<<endl;
}

void StunStatusEffect::onRemove()
{
	//postcondition: displays a message that the target is no longer stunned.

	cout<<target.ShowName()<<" can move again."<<endl;
}
