#ifndef SRC_WINMODE_H_
#define SRC_WINMODE_H_

#include "gamemode.h"

/* This mode is entered when the player has won the game.
 */
class WinMode: public GameMode
{
	public:
		WinMode(GameData&, GameState&);
		~WinMode() { };

		void run(); //Displays win message
};

#endif
