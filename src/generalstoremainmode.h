#ifndef SRC_GENERALSTOREMAINMODE_H_
#define SRC_GENERALSTOREMAINMODE_H_

#include "shopmainmode.h"

/* Top-level mode when entering an General Store from a town.  Just directs the player
 * to the Buy or Sell modes depending on their choice, initialized with the
 * proper item inventory from the town or player item inventory, respectively.
 */
class GeneralStoreMainMode: public ShopMainMode
{
	protected:

		void enterBuyMode();
		void enterSellMode();

	public:
		GeneralStoreMainMode(const Town&, GameData&, GameState&);
		~GeneralStoreMainMode() { };
};

#endif
