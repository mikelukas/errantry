#include "../character.h"
#include "removeweaknesseffect.h"

RemoveWeaknessEffect::RemoveWeaknessEffect(Element element, Character& applier, Character& target)
	: Effect(element, applier, target),
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

void RemoveWeaknessEffect::run()
{
	//postcondition: weaknessToRemove is removed from the target, with a message
	//displayed as to what weakness was removed.

	target.removeWeakness(weaknessToRemove);

	cout<<target.ShowName()<<" no longer is weak to "<<getDisplayNameFor(weaknessToRemove)<<"."<<endl;
}
