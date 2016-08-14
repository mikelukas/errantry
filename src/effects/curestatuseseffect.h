#ifndef SRC_EFFECTS_CURESTATUSESEFFECT_H_
#define SRC_EFFECTS_CURESTATUSESEFFECT_H_

#include "../effecttype.h"
#include "effect.h"

/*Base class for effects that remove statuses from their target." */
class CureStatusesEffect: public Effect
{
	protected:
		EffectType typeToCure;

		virtual void runTurnEffect();

	public:
		CureStatusesEffect(EffectType, const EffectParams&);
		virtual ~CureStatusesEffect() {}
};

#endif
