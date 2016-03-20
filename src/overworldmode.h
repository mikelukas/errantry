#ifndef SRC_OVERWORLDMODE_H_
#define SRC_OVERWORLDMODE_H_

#include <iomanip>
#include "menumode.h"

using std::setw;

enum Region {easy, medium, hard};

/* This mode is the main mode of the game, and is entered after the player views
 * the intro and instructions, and starts.
 * It displays the map and allows the player to move around and encounter enemies,
 * enter towns and caves, and show their current status.  The player can also
 * quit the game from this mode.
 */
class OverworldMode : public MenuMode
{
	protected:
		int displayMenu();
		void testChoice(int);

		void move();
		void getEnemy();

		void printStatus() const;

	public:
		OverworldMode(GameData&, GameState&);
		~OverworldMode() { };
};

#endif
