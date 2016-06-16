#ifndef RANDOMBATTLESTRATEGY_H_
#define RANDOMBATTLESTRATEGY_H_

#include "battlestrategy.h"

/* Constructs a battle action at random for the monster */
class RandomBattleStrategy : public BattleStrategy
{
	public:
		RandomBattleStrategy();
		virtual ~RandomBattleStrategy() {}

		BattleStrategy* clone() const;

		BattleAction* makeBattleAction(GameData&, const GameState&, Monster&, Character&);
};

#endif
