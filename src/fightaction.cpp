#include <iostream>
#include "fightaction.h"

using std::cout;
using std::endl;

FightAction::FightAction(Character& attacker, Character& defender)
	: BattleAction(attacker),
	  attacker(attacker),
	  defender(defender)
{

}

bool FightAction::isAttackerBlind()
{
	//postcondition: returns true if the taccker has blind status and displays
	//a message that they can't fight.

	if(attacker.hasStatus(BLIND))
	{
		cout<<attacker.ShowName()<<" can't see to fight!"<<endl;
		return true;
	}

	return false;
}

void FightAction::setup()
{
	//postcondition: aborts if attacker is blind.

	if(isAttackerBlind())
	{
		setAborted(true);
	}
}

void FightAction::doAction()
{
	//postcondition:  this function apply's physical damage from the attacker
	//to the defender.  Raw damage from the attacker is based on their AP

	if(isAttackerBlind())
	{
		return;
	}

    int netDamage = defender.applyPhysicalDamage(attacker.getEffectiveAP());

    cout<<attacker.ShowName()<<" did "<<netDamage<<" damage to "<<defender.ShowName()<<"!"<<endl;
}
