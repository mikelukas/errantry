#ifndef SRC_TOWNMODE_H_
#define SRC_TOWNMODE_H_

#include "gamemode.h"

const string ARMORY_CLOSED_MSG = "The Armory is closed for business in ";
const string GENSTORE_CLOSED_MSG = "The General Store is closed for business in ";
const string MAGICSHOP_CLOSED_MSG = "The Magic Shop is closed for business in ";

/* The player enters this mode when moving into a Town on the overworld.
 * State and actions specific to being in a Town is tracked by this class.
 */
class TownMode : public GameMode
{
	protected:
		const Town& currentTown;

		virtual void updateDisplay();
		virtual bool processInput();

		void talk() const;
		void enterArmory();
		void enterGenStore();
		void enterMagicShop();

	public:
		TownMode(const Town& town, GameData&, GameState&);
		~TownMode() { };
};

#endif
