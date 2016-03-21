#ifndef SRC_ARMORYMAINMODE_H_
#define SRC_ARMORYMAINMODE_H_

#include "shopmainmode.h"

/* Top-level mode when entering an Armory from a town.  Just directs the player
 * to the ArmoryBuy or ArmorySell modes depending on their choice, initialized
 * with the proper inventory from the town.
 */
class ArmoryMainMode : public ShopMainMode
{
	protected:

		void enterBuyMode();
		void enterSellMode();

	public:
		ArmoryMainMode(const Town&, GameData&, GameState&);
		~ArmoryMainMode() { };
};

#endif
