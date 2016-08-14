#ifndef SRC_STATUSES_MUTESTATUS_H_
#define SRC_STATUSES_MUTESTATUS_H_

#include "statuseffect.h"

/* Having this status prevents the character from casting spells */
class MuteStatus: public StatusEffect
{
	public:
		MuteStatus(const StatusTemplate&, const EffectParams&);
		virtual ~MuteStatus() {}

		virtual void onAdd();
		virtual void onRemove();
};

#endif
