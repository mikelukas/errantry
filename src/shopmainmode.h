#ifndef SRC_SHOPMAINMODE_H_
#define SRC_SHOPMAINMODE_H_

#include "gamemode.h"

/* Abstract base class for choices available when entering any kind of shop.
 */
class ShopMainMode : public GameMode
{
	protected:
		const Town& currentTown;

		virtual void updateDisplay();
		virtual bool processInput();

		virtual void enterBuyMode() = 0;
		virtual void enterSellMode() = 0;

	public:
		ShopMainMode(const Town&, GameData&, GameState&);
		~ShopMainMode() { };
};

#endif
