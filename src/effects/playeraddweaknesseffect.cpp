#include "../elementchooser.h"
#include "playeraddweaknesseffect.h"

PlayerAddWeaknessEffect::PlayerAddWeaknessEffect(const EffectParams& effectParams)
	: AddWeaknessEffect(effectParams)
{

}

Element PlayerAddWeaknessEffect::chooseWeakness()
{
	//postcondition: player is prompted to choose an Element, and target is made
	//weak to that element.

	cout<<"Choose a weakness to add to "<<target.ShowName()<<":"<<endl;
	ElementChooser elementChooser;
	elementChooser.run();
	if(elementChooser.canceled())
	{
		return none;
	}

	return *(elementChooser.getChoice());
}
