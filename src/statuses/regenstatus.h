#ifndef SRC_STATUSES_REGENSTATUS_H_
#define SRC_STATUSES_REGENSTATUS_H_

#include "statuseffect.h"

const int MAX_REGEN_HP = 10;

/* Target recovers a random amount of HP between 1 and 10 each turn */
class RegenStatus: public StatusEffect
{
	protected:

		virtual void runTurnEffect();

	public:
		RegenStatus(const StatusTemplate&, const EffectParams&);
		virtual ~RegenStatus() {}

		virtual void onAdd();
		virtual void onRemove();
};

#endif
