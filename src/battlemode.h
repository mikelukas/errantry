#ifndef SRC_BATTLEMODE_H_
#define SRC_BATTLEMODE_H_

#include <queue>
#include "battleaction.h"
#include "menumode.h"

using std::queue;

const int SKIP_TURN_CHOICE = -1;
const int DROP_CHANCE_PERCENT = 40;

/* This mode handles battle choices when a player encounters a monster randomly
 * while moving on the overworld.  It is also the base class for boss battles,
 * which are slightly special and occur when the user moves onto a cave.
 */
class BattleMode : public MenuMode
{
	protected:
		Monster currMonster; //Monster we're fighting in this mode
		queue<BattleAction*> actionQueue;

		int displayMenu();
		void displayFightChoice();
		void displayCastSpellChoice();
		bool testChoice(int);
		BattleAction* makeMonsterAction();
		void executeActions();

		bool testEndConditions();
		virtual void onBattleWon();

		void addMonsterEquipment();
		void learnMonsterSpells();
		void onLevelUp();

	public:
		BattleMode(Monster, GameData&, GameState&);
		~BattleMode();

		virtual void processStatusEffects();
		virtual void run();
};

#endif
