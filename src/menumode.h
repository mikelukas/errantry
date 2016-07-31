#ifndef SRC_MENUMODE_H_
#define SRC_MENUMODE_H_

#include <iostream>
#include "gamemode.h"

using std::cin;
using std::cout;
using std::endl;

/* Base class for all modes that display a menu of choices to player, then
 * process that choice.
 */
class MenuMode : public GameMode
{
	protected:
		virtual int displayMenu() = 0;
		virtual void testChoice(int) = 0;

		bool validateChoice(int, int) const;

	public:
		MenuMode(GameData&, GameState&, bool);
		~MenuMode() { };

		virtual void run(); //Calls displayMenu, followed by testChoice with player's choice from menu
};

#endif
