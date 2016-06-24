#ifndef SRC_ARMAMENTCHOOSER_H_
#define SRC_ARMAMENTCHOOSER_H_

#include "character.h"
#include "equipment.h"
#include "inventorychooser.h"

/* Abstract class for listing weapon and armor choices from a Character's inventory. */
class ArmamentChooser : public InventoryChooser<EquipmentLine>
{
	protected:
		int numWeapons;
		int numArmor;

		virtual void displayInventoryChoices() const;

	public:
		ArmamentChooser(Character&);
		virtual ~ArmamentChooser() {}
};

#endif
