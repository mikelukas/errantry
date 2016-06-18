#include <iostream>
#include "fightaction.h"

using std::cout;
using std::endl;

FightAction::FightAction(Character& attacker, Character& defender)
	: attacker(attacker),
	  defender(defender)
{

}

void FightAction::execute()
{
	//postcondition:  this function apply's physical damage from the attacker
	//to the defender.  Raw damage from the attacker is based on their AP

    int netDamage = defender.applyPhysicalDamage(attacker.Damage());

    cout<<attacker.ShowName()<<" did "<<netDamage<<" damage to "<<defender.ShowName()<<"!"<<endl;
}
