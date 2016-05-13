#ifndef SRC_APPLYEQUIPMENTMODE_H_
#define SRC_APPLYEQUIPMENTMODE_H_

#include <iomanip>
#include "equipmentchooser.h"
#include "menumode.h"

using std::setw;

/* Base classes for modes which let you choose equipment from your inventory
 * to apply on a target.
 */
class ApplyEquipmentMode : public MenuMode
{
	protected:
		const Equipment* equipmentChoice;
		Character* target;

		virtual int displayMenu();
		virtual void testChoice(int);

		virtual EquipmentChooser* createInventoryChooser() = 0;

	public:
		ApplyEquipmentMode(GameData&, GameState&);
		~ApplyEquipmentMode();
};

#endif
