#include <iostream>
#include "fightaction.h"
#include "monstercastspellaction.h"
#include "randombattlestrategy.h"

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

BattleAction* RandomBattleStrategy::makeBattleAction(GameData& gameData, const GameState& gameState, Monster& monster, Character& target)
{
	//postcondition: returns either a MonsterCastSpellAction or a FightAction,
	//chosen at random.
	//Will never return a MonsterCastSpellAction if the monster doesn't have spells

	int actionType = 0; //defaults to build fight action

	//If the monster has spells, randomly decide if they will fight or cast a spell
	if(!(monster.getSpellIds().empty()))
	{
		//Otherwise randomly choose between fighting and casting a spell
		actionType = gameState.getRandIntBetween(0,1);
	}

	BattleAction* chosenAction = NULL;
	switch(actionType)
	{
	case 1:
		chosenAction = new MonsterCastSpellAction(gameData, monster, target);
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
