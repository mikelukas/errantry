#ifndef SRC_GAMEMODE_H_
#define SRC_GAMEMODE_H_

#include "context.h"
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

		bool processesStatuses;

		virtual int updateDisplay() = 0;
		virtual bool processInput(int) = 0; //return indicates if this choice finishes the current turn.

		bool validateChoice(int, int) const;

	public:
		GameMode(GameData&, GameState&, bool);
		virtual ~GameMode() {};

		virtual void processStatusEffects();

		virtual void run();  //Calls displayMenu, followed by testChoice with player's choice from menu

};

#endif
