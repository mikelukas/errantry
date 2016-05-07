#ifndef SRC_USEITEMMODE_H_
#define SRC_USEITEMMODE_H_

#include "applyequipmentmode.h"

class UseItemMode: public ApplyEquipmentMode
{
	protected:

		void updateEquipmentChoices();

		virtual void displayRelevantPlayerAttrs();
		virtual void displayEquipmentList();

	public:
		UseItemMode(GameData&, GameState&);
		~UseItemMode() { };
};

#endif
