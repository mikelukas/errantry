#include "fightaction.h"

FightAction::FightAction(Character& attacker, Character& defender)
	: attacker(attacker),
	  defender(defender)
{

}

void FightAction::execute()
{
	//postcondition:  this function deals damage to the defender from the attacker.
	//It deducts that damage from the defender's HP.
	//A certain defense number is subtracted for the DP value of the defender,
	//so that the attacker does not do all of their damage(AP) to the defender.

    int pDamage = attacker.Damage() - defender.Defense();
    if(pDamage < 0)
        pDamage = 0;

    defender.ChangeHP(-1 * pDamage);
}
