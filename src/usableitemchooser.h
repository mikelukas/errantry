#ifndef SRC_USABLEITEMCHOOSER_H_
#define SRC_USABLEITEMCHOOSER_H_

#include "inventorychooser.h"
#include "player.h"

/* Used for choosing Items in player's inventory for use on a target later.
 * Displays stats relevant to Item use, and lists only Items from player inventory.
 */
class UsableItemChooser: public InventoryChooser<EquipmentLine>
{
	protected:
		const Player& player;

		virtual void displayRelevantStats() const;
		virtual void displayInventoryChoices() const;

		virtual void displayChoice(int, EquipmentLine*) const;

	public:
		UsableItemChooser(Player&);
		~UsableItemChooser() {};
};

#endif
