#ifndef SRC_BATTLEUSEITEMMODE_H_
#define SRC_BATTLEUSEITEMMODE_H_

#include "useitemmode.h"

class BattleUseItemMode : public UseItemMode
{
	protected:
		Monster& monster;

		void setTarget(Character*);

		int displayMenu();
		void testChoice(int);

		void displayRelevantPlayerAttrs();

	public:
		BattleUseItemMode(GameData&, GameState&, Monster&);
		~BattleUseItemMode() {}
};

#endif
