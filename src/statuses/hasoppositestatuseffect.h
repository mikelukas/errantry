#ifndef SRC_STATUSES_HASOPPOSITESTATUSEFFECT_H_
#define SRC_STATUSES_HASOPPOSITESTATUSEFFECT_H_

#include "statuseffect.h"

/* Base class for statuses with that have an opposite which should be removed
 * when the status is applied.
 */
class HasOppositeStatusEffect: public StatusEffect
{
	protected:
		const EffectType oppositeStatus;

	public:
		HasOppositeStatusEffect(const EffectType, const StatusTemplate&, const EffectParams&);
		virtual ~HasOppositeStatusEffect() {}

		virtual void onAdd();
		virtual void onRemove();

		virtual void apply();
};

#endif
