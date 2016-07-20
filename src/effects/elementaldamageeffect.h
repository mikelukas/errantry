#ifndef SRC_EFFECTS_ELEMENTALDAMAGEEFFECT_H_
#define SRC_EFFECTS_ELEMENTALDAMAGEEFFECT_H_

#include "effect.h"

const int BASE_ELEMENTAL_DAMAGE = 20;

/* Deals BASE_LEMENTAL_DAMAGE magical damage to the target, with the EFfect's
 * element.
 */
class ElementalDamageEffect: public Effect
{
	public:
		ElementalDamageEffect(const EffectParams&);
		virtual ~ElementalDamageEffect() {}

		virtual void apply();
};

#endif
