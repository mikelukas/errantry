#ifndef SRC_APPLYEQUIPMENTMODE_H_
#define SRC_APPLYEQUIPMENTMODE_H_

#include <iomanip>
#include "menumode.h"

using std::setw;

const int EXIT_CHOICE = 0;

class ApplyEquipmentMode : public MenuMode
{
	protected:

		vector<EquipmentLine*>* invEquipment; //populate in updateEquipmentChoices()

		int displayMenu();
		void testChoice(int);

		virtual void updateEquipmentChoices() = 0;
		void cleanupEquipmentChoices();

		virtual void displayRelevantPlayerAttrs() = 0;
		virtual void displayEquipmentList() = 0;

	public:
		ApplyEquipmentMode(GameData&, GameState&);
		~ApplyEquipmentMode();

		void run();
};

#endif
