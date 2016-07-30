#include "effect.h"

EffectParams::EffectParams(Element element, Character& applier, Character& target)
	: element(element),
	  applier(applier),
	  target(target)
{

}

Effect::Effect(const EffectParams& effectParams)
	: element(effectParams.element),
	  applier(effectParams.applier),
	  target(effectParams.target),
	  used(false)
{


}

bool Effect::isExpired() const
{
	//postcondition: returns true if Effect has been used and is eligible to be
	//deallocated, false otherwise.

	return used;
}

void Effect::apply()
{
	//postcondition: calls runTurnEffect() to run Effect subclasses specific actions
	//then sets used to true so callers can know they can delete this Effect.

	runTurnEffect();
	used = true;
}
