#ifndef SRC_MENUMODE_H_
#define SRC_MENUMODE_H_

#include "gamemode.h"

/* Base class for all modes that display a menu of choices to player, then
 * process that choice.
 */
class MenuMode : public GameMode
{
	protected:
		virtual int displayMenu() = 0;
		virtual void testChoice(int) = 0;

	public:
		MenuMode(GameData&, GameState& gameState);
		~MenuMode() { };

		void run(); //Calls displayMenu, followed by testChoice with player's choice from menu


};

#endif
