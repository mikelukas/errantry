#ifndef SRC_STATUSES_TEMPSTATMODSTATUSEFFECT_H_
#define SRC_STATUSES_TEMPSTATMODSTATUSEFFECT_H_

#include <string>
#include "../effecttype.h"
#include "../statmod.h"
#include "hasoppositestatuseffect.h"

using std::string;

/* Base class for StatusEffects that apply a temporary modification to one or
 * more of the target's attributes.
 */
class TempStatModStatusEffect: public HasOppositeStatusEffect
{
	protected:
		const StatMod modToApply;

	public:
		TempStatModStatusEffect(const StatMod&, const EffectType, const StatusTemplate&, const EffectParams&);
		virtual ~TempStatModStatusEffect() {}

		virtual void onAdd();
		virtual void onRemove();
};

#endif
