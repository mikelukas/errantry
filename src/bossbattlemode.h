#ifndef SRC_BOSSBATTLEMODE_H_
#define SRC_BOSSBATTLEMODE_H_

#include "battlemode.h"

/* Entered when player moves onto a cave from the overworld.  Boss battles are
 * mostly the same as regular battles, but the player can't run, the remaining
 * bosses in the game needs advanced, and the player can win the game if they
 * win the boss battle and it is the last boss.
 */
class BossBattleMode : public BattleMode
{
	protected:

		void runFromBattle();
		void onBattleWon();

	public:
		BossBattleMode(Monster, GameData&, GameState&);
		~BossBattleMode() { };
};

#endif
