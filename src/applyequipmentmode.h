#ifndef SRC_APPLYEQUIPMENTMODE_H_
#define SRC_APPLYEQUIPMENTMODE_H_

#include <iomanip>
#include "inventorychooser.h"
#include "gamemode.h"

using std::setw;

/* Base classes for modes which let you choose equipment from your inventory
 * to apply on a target.
 */
class ApplyEquipmentMode : public GameMode
{
	protected:
		const Equipment* equipmentChoice;
		Character* target;

		virtual int updateDisplay();
		virtual bool processInput(int);
		virtual void useEquipment() = 0;

		virtual Chooser<EquipmentLine>* createInventoryChooser() = 0;

	public:
		ApplyEquipmentMode(GameData&, GameState&);
		~ApplyEquipmentMode();
};

#endif
