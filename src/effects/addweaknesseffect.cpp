#include <sstream>
#include "addweaknesseffect.h"
#include "../character.h"
#include "../logging/log.h"

AddWeaknessEffect::AddWeaknessEffect(const EffectParams& effectParams)
	: Effect(effectParams),
	  weaknessToAdd(none)
{

}

bool AddWeaknessEffect::setup()
{
	//postcondition: returns true if weaknessToAdd is set with the chosen
	//weakness (from subclass)
	//returns false if weakness choosing was aborted

	weaknessToAdd = chooseWeakness();

	return (weaknessToAdd != none); //if none is the weakness, then must not have been able to choose one.
}

void AddWeaknessEffect::runTurnEffect()
{
	//postcondition: weaknessToAdd is added to the target, with a message
	//displayed as to what weakness was added.

	target.addWeakness(weaknessToAdd);

	std::stringstream weakenedMsg;
	weakenedMsg<<target.ShowName()<<" is now weak to "<<getDisplayNameFor(weaknessToAdd)<<".";
	log(weakenedMsg.str());
}
