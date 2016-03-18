#ifndef SRC_BATTLEMODE_H_
#define SRC_BATTLEMODE_H_

#include "menumode.h"

/* This mode handles battle choices when a player encounters a monster randomly
 * while moving on the overworld.  It is also the base class for boss battles,
 * which are slightly special and occur when the user moves onto a cave.
 */
class BattleMode : public MenuMode
{
	protected:
		Monster& currMonster; //Monster we're fighting in this mode

		int displayMenu();
		void testChoice(int);

		void fight();
		virtual void runFromBattle();

		virtual void onBattleWon();

	public:
		BattleMode(Monster&, GameData&, GameState&);
		~BattleMode() { };
};

#endif
