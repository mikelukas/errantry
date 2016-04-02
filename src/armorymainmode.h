#ifndef SRC_ARMORYMAINMODE_H_
#define SRC_ARMORYMAINMODE_H_

#include "shopmainmode.h"

/* Top-level mode when entering an Armory from a town.  Just directs the player
 * to the ShopBuy or ShopSell modes depending on their choice, initialized
 * with the proper inventory from the town or player weapon and armor inventory, respectively.
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
