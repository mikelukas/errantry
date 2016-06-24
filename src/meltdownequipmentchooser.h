#ifndef SRC_MELTDOWNEQUIPMENTCHOOSER_H_
#define SRC_MELTDOWNEQUIPMENTCHOOSER_H_

#include "armamentchooser.h"

/* Displays player's weapons and armor, and how much damage each would do if
 * melted down (see Meltdown effect).
 */
class MeltdownEquipmentChooser : public ArmamentChooser
{
	protected:
		void displayRelevantStats() const;
		void displayChoice(int, EquipmentLine*) const;

	public:
		MeltdownEquipmentChooser(Character&);
		virtual ~MeltdownEquipmentChooser() {}
};

#endif
