#include <iostream>
#include "fightaction.h"
#include "monstercastspellaction.h"
#include "randombattlestrategy.h"
#include "randutils.h"

using std::cout;
using std::endl;

RandomBattleStrategy::RandomBattleStrategy()
{

}

BattleStrategy* RandomBattleStrategy::clone() const
{
	//postcondition: allocates of copy of this object and returns a pointer to it.

	return new RandomBattleStrategy(*this);
}

BattleAction* RandomBattleStrategy::makeBattleAction(Monster& monster, Character& target)
{
	//postcondition: returns either a MonsterCastSpellAction or a FightAction,
	//chosen at random.
	//Will never return a MonsterCastSpellAction if the monster doesn't have spells

	//If the monster has spells, randomly choose between fight or cast, otherwise just fight
	int actionType = monster.hasSpells() ? getRandIntBetween(0,1) : 0;

	BattleAction* chosenAction = NULL;
	switch(actionType)
	{
	case 1:
		chosenAction = new MonsterCastSpellAction(monster, target);
		break;
	default:
		chosenAction = new FightAction(monster, target);
	}

	chosenAction->setup();
	if(chosenAction->isAborted())
	{
		delete chosenAction;

		chosenAction = new FightAction(monster, target);
		chosenAction->setup();
	}

	return chosenAction;
}
