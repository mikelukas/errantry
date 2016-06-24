#ifndef SRC_EQUIPABLESCHOOSER_H_
#define SRC_EQUIPABLESCHOOSER_H_

#include <map>
#include "equipment.h"
#include "inventorychooser.h"
#include "player.h"

using std::map;

/* Used for choosing Weapons and Armor in player's inventory for equipping.
 * Displays stats relevant to these Equipment types, and lists only these types
 * from the player's inventory as choices.
 */
class EquipablesChooser: public InventoryChooser<EquipmentLine>
{
	protected:
		Player& player;
		int numWeapons;
		int numArmor;

		void displayRelevantStats() const;
		void displayInventoryChoices() const;
		void displayChoice(int, EquipmentLine*) const;

	public:
		EquipablesChooser(Player&, int, int);
		virtual ~EquipablesChooser() {};
};

#endif
