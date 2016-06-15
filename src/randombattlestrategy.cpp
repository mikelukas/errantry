#include <iostream>
#include "fightaction.h"
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

BattleAction* RandomBattleStrategy::makeBattleAction(const GameState& gameState, Monster& monster, Character& target)
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

	switch(actionType)
	{
	case 1:
		cout<<monster.ShowName()<<" chose to cast a spell."<<endl;
		return NULL;//todo: return new MonsterCastSpellAction(monster, target);
		break;
	default:
		return new FightAction(monster, target);
	}
}
