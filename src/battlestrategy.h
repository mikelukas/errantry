#ifndef BATTLESTRATEGY_H_
#define BATTLESTRATEGY_H_

#include "battleaction.h"
#include "gamestate.h"
#include "monster.h"

/* BattleStrategy objects build BattleActions for monsters in battle.
 * This is an abstract base class to define that interface.
 */
class BattleStrategy
{
	protected:

	public:
		BattleStrategy() {};
		virtual ~BattleStrategy() {}

		virtual BattleStrategy* clone() const = 0;

		virtual BattleAction* makeBattleAction(const GameState&, Monster&, Character&) = 0;
};

#endif
