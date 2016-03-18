#ifndef SRC_DEADMODE_H_
#define SRC_DEADMODE_H_

#include "gamemode.h"

/* This mode is entered when the player dies.
 */
class DeadMode: public GameMode
{
	public:
		DeadMode(GameData&, GameState&);
		~DeadMode() { };

		void run(); //Displays message about player dying
};

#endif
