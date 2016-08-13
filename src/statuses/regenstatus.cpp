#include <iostream>
#include "../character.h"
#include "regenstatus.h"
#include "../util/randutils.h"

using std::cout;
using std::endl;

RegenStatus::RegenStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{
}

void RegenStatus::onAdd()
{
	cout<<target.ShowName()<<" is regenerating!"<<endl;
}

void RegenStatus::onRemove()
{
	cout<<target.ShowName()<<" stopped regenerating."<<endl;
}

void RegenStatus::runTurnEffect()
{
	//postcondition: target regains a random amount of HP from 1 to MAX_REGEN_HP

	int regenHP = getRandIntBetween(1, MAX_REGEN_HP);
	target.ChangeHP(regenHP);

	cout<<target.ShowName()<<" regenerated "<<regenHP<<" HP!"<<endl;
}
