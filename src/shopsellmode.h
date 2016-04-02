#ifndef SRC_SHOPSELLMODE_H_
#define SRC_SHOPSELLMODE_H_

#include "shoptransactionmode.h"

/* Shop mode providing logic to display player's inventory for sale,
 * validate the sale choice (i.e. did the player choose more to sell than they have),
 * and subtract the sold amount from their inventory, and add the appropriate gold
 * amount.
 */
class ShopSellMode: public ShopTransactionMode
{
	protected:
		void displayShopChoice(const EquipmentLine*) const;
		bool validateShopChoice(const Equipment*, int quantity) const;
		void processTransaction();
		void updateChoices(int);

	public:
		ShopSellMode(vector<EquipmentLine*>*, GameData&, GameState&);
		~ShopSellMode() { };
};

#endif
