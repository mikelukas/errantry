#ifndef SRC_STATUSES_POISONSTATUS_H_
#define SRC_STATUSES_POISONSTATUS_H_

#include "statuseffect.h"

const int POISON_DAMAGE = 10;

class PoisonStatus: public StatusEffect
{
	protected:

		virtual void runTurnEffect();

	public:
		PoisonStatus(const StatusTemplate&, const EffectParams&);
		virtual ~PoisonStatus() {}

		virtual void onAdd();
		virtual void onRemove();
};

#endif
