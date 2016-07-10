#ifndef SRC_EFFECTS_MONSTERADDWEAKNESSEFFECT_H_
#define SRC_EFFECTS_MONSTERADDWEAKNESSEFFECT_H_

#include "addweaknesseffect.h"

/* A weakness is automatically chosen for the target based on what the most
 * common element is that the applier has in their spells, and what weaknesses
 * the target already has.
 */
class MonsterAddWeaknessEffect: public AddWeaknessEffect
{
	protected:

		Element chooseWeakness();

	public:
		MonsterAddWeaknessEffect(Element, Character&, Character&);
		virtual ~MonsterAddWeaknessEffect() {}
};

#endif
