#ifndef SRC_EFFECTS_MPDAMAGEEFFECT_H_
#define SRC_EFFECTS_MPDAMAGEEFFECT_H_

#include "effect.h"

const int BASE_MP_DROP = 10;

/* Reduces target's MP by BASE_MP_DROP */
class MpDamageEffect: public Effect
{
	public:
		MpDamageEffect(Element, Character&, Character&);
		virtual ~MpDamageEffect() {}

		virtual void run();
};

#endif
