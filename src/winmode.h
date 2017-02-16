#ifndef SRC_WINMODE_H_
#define SRC_WINMODE_H_

#include "gamemode.h"

/* This mode is entered when the player has won the game.
 */
class WinMode: public GameMode
{
	protected:
		virtual int updateDisplay(); //Displays win message
		virtual bool processInput(int);

	public:
		WinMode(GameData&, GameState&);
		~WinMode() { };
};

#endif
