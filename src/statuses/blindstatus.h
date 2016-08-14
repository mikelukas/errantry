#ifndef SRC_STATUSES_BLINDSTATUS_H_
#define SRC_STATUSES_BLINDSTATUS_H_

#include "statuseffect.h"

/* Having this status causes the Character to not be able to attack.*/
class BlindStatus: public StatusEffect
{
	public:
		BlindStatus(const StatusTemplate&, const EffectParams&);
		virtual ~BlindStatus() {}

		virtual void onAdd();
		virtual void onRemove();
};

#endif
