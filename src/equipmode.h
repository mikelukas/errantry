#ifndef SRC_EQUIPMODE_H_
#define SRC_EQUIPMODE_H_

#include "applyequipmentmode.h"
#include "equipableschooser.h"

/* Mode allowing player to choose weapons and armor from their inventory to
 * equip on themselves.
 */
class EquipMode : public ApplyEquipmentMode
{
	protected:
		Chooser<EquipmentLine>* createInventoryChooser();

	public:
		EquipMode(GameData&, GameState&);
		~EquipMode() { };
};

#endif
