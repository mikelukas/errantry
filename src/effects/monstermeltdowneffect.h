#ifndef SRC_EFFECTS_MONSTERMELTDOWNEFFECT_H_
#define SRC_EFFECTS_MONSTERMELTDOWNEFFECT_H_

#include "meltdowneffect.h"

/* A random piece of equipment and quantity of that equipment is chosen from
 * the monster's inventory, and melted down in to raw magical damage.
 * setup() aborts if monster has no equipment.
 */
class MonsterMeltdownEffect: public MeltdownEffect
{
	protected:
		EquipmentLine* chooseEquipment() const;

	public:
		MonsterMeltdownEffect(Element, Character&, Character&);
		virtual ~MonsterMeltdownEffect() {}
};

#endif
