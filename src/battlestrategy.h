#ifndef BATTLESTRATEGY_H_
#define BATTLESTRATEGY_H_

#include <vector>
#include "battleaction.h"
#include "monster.h"

/* BattleStrategy objects build BattleActions for monsters in battle.
 * This is an abstract base class to define that interface.
 */
class BattleStrategy
{
	public:
		BattleStrategy() {};
		virtual ~BattleStrategy() {}

		virtual BattleStrategy* clone() const = 0;

		virtual vector<BattleAction*>* getEligibleActions(Monster&, Character&) const;
		virtual BattleAction* makeBattleAction(Monster&, Character&) = 0;
};

#endif
