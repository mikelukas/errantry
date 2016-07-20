#ifndef SRC_EFFECTS_HEALEFFECT_H_
#define SRC_EFFECTS_HEALEFFECT_H_

#include "effect.h"

const int BASE_HEAL_HP = 25;

/* Heals target's HP by BASE_HEAL_HP amount. */
class HealEffect: public Effect
{
	public:
		HealEffect(const EffectParams&);
		virtual ~HealEffect() {}

		virtual void apply();
};

#endif
