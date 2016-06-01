#ifndef SRC_USEITEMMODE_H_
#define SRC_USEITEMMODE_H_

#include "applyequipmentmode.h"
#include "usableitemchooser.h"

/* Mode allowing player to choose items from their inventory to use on himself/herself.
 */
class UseItemMode: public ApplyEquipmentMode
{
	protected:
		Chooser<EquipmentLine>* createInventoryChooser();

	public:
		UseItemMode(GameData&, GameState&);
		~UseItemMode() { };
};

#endif
