#include "statustemplate.h"

StatusTemplate::StatusTemplate(const string& name, EffectType type, int duration, const vector<const Context>* eligibleContexts)
	: name(name),
	  type(type),
	  durationTurns(duration),
	  eligibleContexts(eligibleContexts)
{

}

StatusTemplate::~StatusTemplate()
{
	//postcondition: deletes eligibleContexts vector.

	delete eligibleContexts;
}

const string& StatusTemplate::getName() const
{
	//postcondition: returns a displayable name for this status.

	return name;
}

const EffectType StatusTemplate::getType() const
{
	//postcondition: returns the type identifier of this Status.

	return type;
}

const int StatusTemplate::getDuration() const
{
	//postcondition: returns the remaining duration of this Status in number of turns.

	return durationTurns;
}

const vector<const Context>* StatusTemplate::getEligibleContexts() const
{
	//postcondition: returns the contexts in which this Status can be processed.

	return eligibleContexts;
}
