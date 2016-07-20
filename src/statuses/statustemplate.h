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
		const string& name;
		const EffectType type;
		int durationTurns;
		const vector<const Context>* eligibleContexts; //freed in destructor

	public:
		StatusTemplate(const string&, EffectType, int, const vector<const Context>*);
		virtual ~StatusTemplate();

		const string& getName() const;
		const EffectType getType() const;
		const int getDuration() const;
		const vector<const Context>* getEligibleContexts() const;
};

#endif
