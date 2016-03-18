#ifndef SRC_QUITMODE_H_
#define SRC_QUITMODE_H_

#include "gamemode.h"

/* This mode is entered when the player chooses to quit the game.
 */
class QuitMode : public GameMode
{
	public:
		QuitMode(GameData&, GameState&);
		~QuitMode() { };

		void run(); //Displays quit message
};

#endif
