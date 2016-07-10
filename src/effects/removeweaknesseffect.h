#ifndef SRC_EFFECTS_REMOVEWEAKNESSEFFECT_H_
#define SRC_EFFECTS_REMOVEWEAKNESSEFFECT_H_

#include <iostream>
#include "effect.h"

using std::cout;
using std::endl;

/* Abstract base class for Effects that remove a weakness from their target.
 * Subclasses must implement chooseWeakness() to return a weakness to remove,
 * or none if they want setup() to cancel.
 */
class RemoveWeaknessEffect : public Effect
{
	protected:
		Element weaknessToRemove;

		virtual Element chooseWeakness() = 0;

	public:
		RemoveWeaknessEffect(Element, Character&, Character&);
		virtual ~RemoveWeaknessEffect() {}

		virtual bool setup();
		virtual void run();
};

#endif
