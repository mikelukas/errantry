#ifndef SRC_EFFECTS_CUREPOISONEFFECT_H_
#define SRC_EFFECTS_CUREPOISONEFFECT_H_

#include "curestatuseffect.h"

/* Removes poison from the target. */
class CurePoisonEffect: public CureStatusEffect
{
	public:
		CurePoisonEffect(const EffectParams& effectParams) : CureStatusEffect(POISON, effectParams) {}
		virtual ~CurePoisonEffect() {}
};

#endif
