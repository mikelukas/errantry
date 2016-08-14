#ifndef SRC_STATUSES_DOOMEDSTATUS_H_
#define SRC_STATUSES_DOOMEDSTATUS_H_

#include "statuseffect.h"

/* This status reduces the target's HP to 0 when it expires */
class DoomedStatus: public StatusEffect
{
	public:
		DoomedStatus(const StatusTemplate&, const EffectParams&);
		virtual ~DoomedStatus() {}

		virtual void onAdd();
		virtual void onRemove();

		virtual const string getName() const;
};

#endif
