#ifndef SRC_STATUSES_STUNSTATUSEFFECT_H_
#define SRC_STATUSES_STUNSTATUSEFFECT_H_

#include "statuseffect.h"

/* If a character has this status, a check in battle will cause their turn to be
 * skipped until the status expires.
 */
class StunStatusEffect : public StatusEffect
{
	public:
		StunStatusEffect(const StatusTemplate&, const EffectParams&);
		virtual ~StunStatusEffect() {}

		virtual void onAdd();
		virtual void runTurnEffect();
		virtual void onRemove();
};

#endif
