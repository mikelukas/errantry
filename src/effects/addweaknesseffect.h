#ifndef SRC_EFFECTS_ADDWEAKNESSEFFECT_H_
#define SRC_EFFECTS_ADDWEAKNESSEFFECT_H_

#include <iostream>
#include "effect.h"

using std::cout;
using std::endl;

/* Abstract base class for Effects that add a weakness to their target.
 * Subclasses must implement chooseWeakness() to return a weakness to set,
 * or none if they want setup() to cancel.
 */
class AddWeaknessEffect: public Effect
{
	protected:
		Element weaknessToAdd;

		virtual Element chooseWeakness() = 0;

	public:
		AddWeaknessEffect(const EffectParams&);
		virtual ~AddWeaknessEffect() {}

		virtual bool setup();
		virtual void run();
};

#endif
