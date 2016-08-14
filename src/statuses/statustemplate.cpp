#include "statustemplate.h"

StatusTemplate::StatusTemplate(const string& name, EffectType type, int duration, const Context eligibleContext)
	: name(name),
	  type(type),
	  durationTurns(duration),
	  eligibleContext(eligibleContext)
{

}

const string StatusTemplate::getName() const
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

const Context StatusTemplate::getEligibleContext() const
{
	//postcondition: returns the contexts in which this Status can be processed.

	return eligibleContext;
}
