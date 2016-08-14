#ifndef SRC_STATUSES_STATUSTEMPLATE_H_
#define SRC_STATUSES_STATUSTEMPLATE_H_

#include <string>
#include <vector>
#include "../context.h"
#include "../effecttype.h"

using std::string;
using std::vector;

const int UNLIMITED_DURATION = -1;

/* Base class for StatusEffects, meant to contain initial field values. */
class StatusTemplate
{
	protected:
		const string name;
		const EffectType type;
		int durationTurns;
		const Context eligibleContext;

	public:
		StatusTemplate(const string&, EffectType, int, const Context);
		virtual ~StatusTemplate() {};

		virtual const string getName() const;
		const EffectType getType() const;
		const int getDuration() const;
		const Context getEligibleContext() const;
};

#endif
