#ifndef SRC_EQUIPMENTCHOOSER_H_
#define SRC_EQUIPMENTCHOOSER_H_

#include "equipment.h"
#include "inventorychooser.h"

/* Abstract base class specifically for choosing Equipment in player's inventory.
 * Adds ability to get the Equipment* itself based on player's numerical choice.
 *
 * DE-ALLOCATES invChoices upon destruction.
 */
class EquipmentChooser : public InventoryChooser<EquipmentLine*>
{
	public:
		EquipmentChooser(vector<EquipmentLine*>*);
		virtual ~EquipmentChooser();

		const Equipment* getChosenEquipment() const;
};

#endif
