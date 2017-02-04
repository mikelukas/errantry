#include <algorithm> //random_shuffle
#include "fightaction.h"
#include "skipturnaction.h"
#include "monstercastspellaction.h"
#include "randombattlestrategy.h"

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
	//postcondition: returns a BattleAction for the monster, which has had
	//setup() called on it and is not aborted.
	//Randomly chooses this action from among initial eligible actions for the
	//monster as returned by getEligibleActions().
	//Returns a SkipTurnAction if the monster doesn't have any eligible actions
	//or all eligible actions abort during setup().

	BattleAction* chosenAction = NULL;

	//Randomly choose a valid action.
	vector<BattleAction*>* eligibleActions = getEligibleActions(monster, target);
	std::random_shuffle(eligibleActions->begin(), eligibleActions->end());
	while(!eligibleActions->empty())
	{
		chosenAction = eligibleActions->back();
		eligibleActions->pop_back();

		chosenAction->setup();
		if(!chosenAction->isAborted())
		{
			break;
		}

		delete chosenAction;
		chosenAction = NULL;
	}

	//If no valid actions were found, monster must lose its turn
	if(chosenAction == NULL)
	{
		chosenAction = new SkipTurnAction(monster);
		chosenAction->setup();
	}

	//de-allocate any remaining actions in queue, and then queue itself
	while(!eligibleActions->empty())
	{
		delete (eligibleActions->back());
		eligibleActions->pop_back();
	}
	delete eligibleActions;

	return chosenAction;
}
