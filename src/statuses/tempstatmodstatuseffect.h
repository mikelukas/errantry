#ifndef SRC_STATUSES_TEMPSTATMODSTATUSEFFECT_H_
#define SRC_STATUSES_TEMPSTATMODSTATUSEFFECT_H_

#include <string>
#include "../effecttype.h"
#include "../statmod.h"
#include "statuseffect.h"

using std::string;

/* Base class for StatusEffects that apply a temporary modification to one or
 * more of the target's attributes.
 */
class TempStatModStatusEffect: public StatusEffect
{
	protected:
		const StatMod modToApply;
		const EffectType oppositeStatus;

	public:
		TempStatModStatusEffect(const StatMod&, const EffectType, const StatusTemplate&, const EffectParams&);
		virtual ~TempStatModStatusEffect() {}

		virtual void onAdd();
		virtual void onRemove();

		virtual void apply();
};

#endif
