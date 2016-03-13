#ifndef SRC_GAMESTATE_H_
#define SRC_GAMESTATE_H_

#include "monster.h"
#include "player.h"
#include "town.h"

enum GameMode {overworld, town, bossBattle, battle};
enum Region {easy, medium, hard};

const int INIT_LANDSCAPE = ' ';
const GameMode INIT_MODE = overworld;
const int INIT_NEXT_BOSS = 0;

/* This class tracks persistent state in the game, which will change as the
 * player progresses through choices and modes
 */
class GameState
{
	private:
		Player player;

		char landscape; //current type of landscape the player is standing on
		GameMode mode; //current mode of the game
		Town town; //current town the player is in, if they have moved onto a town in the map

		Monster monster; //will hold the monster to be fought if the user encounters one while moving
		int currBoss; //index of the next boss to be fought in 'Bosses'

		bool win;

	public:
		GameState();
		~GameState();

		Player& getPlayer();

		char getCurrentLandscape();
		void setCurrentLandscape(const char);

		GameMode getCurrentMode();
		void setCurrentMode(const GameMode);

		Town& getCurrentTown();
		void setCurrentTown(const Town&);

		Monster& getCurrentMonster();
		void setCurrentMonster(Monster);

		int getCurrentBoss();
		void advanceToNextBoss();

		const bool isWon() const;
};

#endif
