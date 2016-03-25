#ifndef SRC_SHOPBUYMODE_H_
#define SRC_SHOPBUYMODE_H_

#include "shoptransactionmode.h"

/* Shop mode allowing player providing logic to display equipment for purchase,
 * validate purchase choice (i.e. does player have enough money), and add purchase
 * to inventory.
 */
class ShopBuyMode: public ShopTransactionMode
{
	protected:
		void displayShopChoice(const Equipment*) const;
		bool validateShopChoice(const Equipment*, int quantity) const;
		void processTransaction();

	public:
		ShopBuyMode(const vector<Equipment*>*, GameData&, GameState&);
		~ShopBuyMode() { };
};

#endif
