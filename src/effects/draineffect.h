#ifndef SRC_EFFECTS_DRAINEFFECT_H_
#define SRC_EFFECTS_DRAINEFFECT_H_

#include "effect.h"

const int BASE_DRAIN_HP = 15;

/* target is dealt BASE_DRAIN_HP magic damage, and net damage HP is added to
 * applier's HP.
 */
class DrainEffect: public Effect
{
	public:
		DrainEffect(const EffectParams&);
		virtual ~DrainEffect() {}

		virtual void apply();
};

#endif
