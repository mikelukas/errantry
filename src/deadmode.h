#ifndef SRC_DEADMODE_H_
#define SRC_DEADMODE_H_

#include "gamemode.h"

/* This mode is entered when the player dies.
 */
class DeadMode: public GameMode
{
	protected:
		virtual void updateDisplay(); //Displays message about player dying
		virtual bool processInput();

	public:
		DeadMode(GameData&, GameState&);
		~DeadMode() { };
};

#endif
