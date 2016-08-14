#ifndef SRC_EFFECTS_CURESTATUSESEFFECT_H_
#define SRC_EFFECTS_CURESTATUSESEFFECT_H_

#include <vector>
#include "../effecttype.h"
#include "effect.h"

using std::vector;

/*Base class for effects that remove statuses from their target.*/
class CureStatusesEffect: public Effect
{
	protected:
		vector<EffectType>* typesToCure;

		virtual void runTurnEffect();

	public:
		CureStatusesEffect(EffectType, const EffectParams&);
		CureStatusesEffect(vector<EffectType>*, const EffectParams&);
		virtual ~CureStatusesEffect();
};

#endif
