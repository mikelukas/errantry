#ifndef SRC_GAMESTATE_H_
#define SRC_GAMESTATE_H_

#include <set>
#include <stack>
#include "monster.h"
#include "player.h"
#include "town.h"

using std::set;
using std::stack;

class GameMode; //Forward declaration since GameState and GameMode are interdependent

const int INIT_LANDSCAPE = ' ';
const int INIT_NEXT_BOSS = 0;

/* This class tracks persistent state in the game, which will change as the
 * player progresses through choices and modes
 */
class GameState
{
	private:
		Player player;

		char landscape; //current type of landscape the player is standing on
		stack<GameMode*> activeModes; //top of stack is current game mode, items under it are modes that we got to it from

		int currBoss; //index of the next boss to be fought in 'Bosses'

	public:
		GameState();
		~GameState() { };

		Player& getPlayer();

		char getCurrentLandscape();
		void setCurrentLandscape(const char);

		GameMode* getCurrentMode() const;
		void enterMode(GameMode*);
		void exitCurrentMode();

		int getCurrentBoss();
		void advanceToNextBoss();

		void setGameOver();
		const bool isGameOver() const;
};

#endif
