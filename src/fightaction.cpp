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

void FightAction::doAction()
{
	//postcondition:  this function apply's physical damage from the attacker
	//to the defender.  Raw damage from the attacker is based on their AP

    int netDamage = defender.applyPhysicalDamage(attacker.getEffectiveAP());

    cout<<attacker.ShowName()<<" did "<<netDamage<<" damage to "<<defender.ShowName()<<"!"<<endl;
}
