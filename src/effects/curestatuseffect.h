#ifndef SRC_EFFECTS_CURESTATUSEFFECT_H_
#define SRC_EFFECTS_CURESTATUSEFFECT_H_

#include "../effecttype.h"
#include "effect.h"

/*Base class for effects that remove statuses from their target." */
class CureStatusEffect: public Effect
{
	protected:
		EffectType typeToCure;

		virtual void runTurnEffect();

	public:
		CureStatusEffect(EffectType, const EffectParams&);
		virtual ~CureStatusEffect() {}
};

#endif
