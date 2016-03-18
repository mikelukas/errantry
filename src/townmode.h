#ifndef SRC_TOWNMODE_H_
#define SRC_TOWNMODE_H_

#include "menumode.h"

/* The player enters this mode when moving into a Town on the overworld.
 * State and actions specific to being in a Town is tracked by this class.
 */
class TownMode : public MenuMode
{
	protected:
		const Town& currentTown;

		int displayMenu();
		void testChoice(int);

		void talk() const;

	public:
		TownMode(const Town& town, GameData&, GameState&);
		~TownMode() { };
};

#endif
