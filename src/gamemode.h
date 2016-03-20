#ifndef SRC_GAMEMODE_H_
#define SRC_GAMEMODE_H_

#include "gamedata.h"

class GameState; //Forward declaration since GameState and GameMode are interdependent

/* Subclasses of GameMode encapsulate mode-specific processing, and mode-specific
 * state, to avoid having to create a growing number of conditionals in
 * Errantry.cpp, and have mode-specific state persist after the mode has been
 * exited (e.g. Monsters and Towns).
 */
class GameMode
{
	protected:
		GameData& gameData;
		GameState& gameState;

	public:
		GameMode(GameData& gameData, GameState& gameState);
		virtual ~GameMode();

		virtual void run() = 0;
};

#endif