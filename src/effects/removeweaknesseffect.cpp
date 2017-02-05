#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "removeweaknesseffect.h"

RemoveWeaknessEffect::RemoveWeaknessEffect(const EffectParams& effectParams)
	: Effect(effectParams),
	  weaknessToRemove(none)
{

}

bool RemoveWeaknessEffect::setup()
{
	//postcondition: returns true if weaknessToRemove is set with the chosen
	//weakness (from subclass)
	//returns false if weakness choosing was aborted

	weaknessToRemove = chooseWeakness();

	return (weaknessToRemove != none); //if none is the weakness, then must not have been able to choose one.
}

void RemoveWeaknessEffect::runTurnEffect()
{
	//postcondition: weaknessToRemove is removed from the target, with a message
	//displayed as to what weakness was removed.

	target.removeWeakness(weaknessToRemove);

	std::stringstream removedWeaknessMsg;
	removedWeaknessMsg<<target.ShowName()<<" no longer is weak to "<<getDisplayNameFor(weaknessToRemove)<<".";
	log(removedWeaknessMsg.str());
}
