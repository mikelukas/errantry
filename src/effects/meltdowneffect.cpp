#include <iostream>
#include "../character.h"
#include "meltdowneffect.h"

using std::cout;
using std::endl;

MeltdownEffect::MeltdownEffect(const EffectParams& effectParams)
	: Effect(effectParams),
	  meltdownChoice(NULL)
{

}

MeltdownEffect::~MeltdownEffect()
{
	//postcondition: meltdownChoice freed if it was not NULL
	if(meltdownChoice != NULL)
	{
		delete meltdownChoice;
	}
}

bool MeltdownEffect::setup()
{
	//postcondition: meltdownChoice is set with equipment choice based on subclass's
	//implementation for how to get it, or is set to NULL if no equipment chosen,
	//signaling an abort.
	//returns true if meltdown is not NULL, false otherwise.

	meltdownChoice = chooseEquipment();

	return (meltdownChoice != NULL);
}

void MeltdownEffect::runTurnEffect()
{
	//postcondition: removes meltdownChoice from applier's inventory, converts it
	//raw magical damage of this effect's element, applies it to the target,
	//and displays a message indicating how much damage was dealt.

	if(meltdownChoice == NULL)
	{
		return; //caller should've not called this method if they ran setup(); shouldn't hit this code
	}

	//Remove chosen quantity of chosen equipment
	applier.RemoveEquipment(meltdownChoice);

	//Convert equipment stats to damage and deal it to the target
	int rawMeltdownDamage = meltdownChoice->quantity * (meltdownChoice->pEquipment->getStatMod().getMeltdownDamage());
	int netDamage = target.applyMagicalDamage(rawMeltdownDamage, element);

	cout<<applier.ShowName()<<" melted down "<<meltdownChoice->quantity<<" "<<meltdownChoice->pEquipment->getName()<<" into "<<netDamage<<" "<<getDisplayNameFor(element)<<" damage to "<<target.ShowName()<<"!"<<endl;
}
