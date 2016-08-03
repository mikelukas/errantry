//Mike Lukas - p2prog03-      -monster.cpp-
//Member function definitions for the monster class.  Function
//explanations also included

#include <limits>
#include "monster.h"
#include "randombattlestrategy.h"

using std::numeric_limits;
using std::streamsize;

//Constructors-------------------------------------------------------//

Monster::Monster(string& name, int hp, int mp, int ap, int dp, int mdp, int sp, int gold, int expPoints)
    : Character(hp, mp, ap, dp, mdp, sp, gold, expPoints)
    {
		this->name = name;
        battleStrategy = new RandomBattleStrategy();
    }

Monster::Monster(const Monster& monster)
	: Character(monster),
	  battleStrategy(monster.battleStrategy->clone()),
	  droppableSpells(monster.getDroppableSpells())
	{
		//postcondition: performs a deep copy of monster; BattleStrategy* is cloned.

	}

Monster::~Monster()
	{
		delete battleStrategy;
	}

BattleStrategy* Monster::getBattleStrategy() const
{
	return battleStrategy;
}
const set<const SpellTemplate*>& Monster::getDroppableSpells() const
{
	return droppableSpells;
}

void Monster::AddDroppableSpell(const SpellTemplate* droppableSpell)
{
	droppableSpells.insert(droppableSpell);
}

void Monster::apply(const Equipment* eq)
	{
		//postcondition: The incoming Equipment is "applied" to the monster, which
		//adds the stat changes from the Equipment to the monster's stats.
		//Currently only items can be applied to monsters.

		switch(eq->getType())
		{
		case ITEM:
			AddStats(eq->getStatMod());
			break;
		default:
			return;
		}
	}
