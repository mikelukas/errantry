#ifndef SRC_EFFECTS_ADDWEAKNESSEFFECT_H_
#define SRC_EFFECTS_ADDWEAKNESSEFFECT_H_

#include "effect.h"

/* Abstract base class for Effects that add a weakness to their target.
 * Subclasses must implement chooseWeakness() to return a weakness to set,
 * or none if they want setup() to cancel.
 */
class AddWeaknessEffect: public Effect
{
	protected:
		Element weaknessToAdd;

		virtual Element chooseWeakness() = 0;

		virtual void runTurnEffect();

	public:
		AddWeaknessEffect(const EffectParams&);
		virtual ~AddWeaknessEffect() {}

		virtual bool setup();
};

#endif
