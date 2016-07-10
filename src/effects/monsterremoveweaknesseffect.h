#ifndef SRC_EFFECTS_MONSTERREMOVEWEAKNESSEFFECT_H_
#define SRC_EFFECTS_MONSTERREMOVEWEAKNESSEFFECT_H_

#include "removeweaknesseffect.h"

/* One of the applier's weaknesses is randomly removed, or the effect is aborted
 * if the applier is not weak to anything.
 */
class MonsterRemoveWeaknessEffect : public RemoveWeaknessEffect
{
	protected:
		Element chooseWeakness();

	public:
		MonsterRemoveWeaknessEffect(Element, Character&, Character&);
		virtual ~MonsterRemoveWeaknessEffect() {}
};

#endif
