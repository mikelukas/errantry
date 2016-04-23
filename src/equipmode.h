#ifndef SRC_EQUIPMODE_H_
#define SRC_EQUIPMODE_H_

#include "applyequipmentmode.h"

class EquipMode : public ApplyEquipmentMode
{
	protected:

		void updateEquipmentChoices();

		void displayRelevantPlayerAttrs();
		void displayEquipmentList();

	public:
		EquipMode(GameData&, GameState&);
		~EquipMode() { };
};

#endif
