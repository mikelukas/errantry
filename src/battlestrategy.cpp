#include "battlestrategy.h"
#include "fightaction.h"
#include "monstercastspellaction.h"

vector<BattleAction*>* BattleStrategy::getEligibleActions(Monster& monster, Character& target) const
{
	//postcondition: allocates new actions that are eligible for the monster to
	//choose from for battle.  These are put in a newly-allocated vector. It is
	//up to the caller to properly dispose of these objects.

	vector<BattleAction*>* eligibleActions = new vector<BattleAction*>();

	if(!monster.hasStatus(BLIND))
	{
		eligibleActions->push_back(new FightAction(monster, target));
	}

	if(!monster.hasStatus(MUTE) && monster.hasSpells())
	{
		eligibleActions->push_back(new MonsterCastSpellAction(monster, target));
	}

	return eligibleActions;
}
