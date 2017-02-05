#ifndef SRC_EFFECTS_REMOVEWEAKNESSEFFECT_H_
#define SRC_EFFECTS_REMOVEWEAKNESSEFFECT_H_

#include "effect.h"

/* Abstract base class for Effects that remove a weakness from their target.
 * Subclasses must implement chooseWeakness() to return a weakness to remove,
 * or none if they want setup() to cancel.
 */
class RemoveWeaknessEffect : public Effect
{
	protected:
		Element weaknessToRemove;

		virtual Element chooseWeakness() = 0;

		virtual void runTurnEffect();

	public:
		RemoveWeaknessEffect(const EffectParams&);
		virtual ~RemoveWeaknessEffect() {}

		virtual bool setup();
};

#endif
