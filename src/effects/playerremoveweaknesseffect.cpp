#include "../character.h"
#include "../elementchooser.h"
#include "playerremoveweaknesseffect.h"

PlayerRemoveWeaknessEffect::PlayerRemoveWeaknessEffect(Element element, Character& applier, Character& target)
	: RemoveWeaknessEffect(element, applier, target)
{

}

Element PlayerRemoveWeaknessEffect::chooseWeakness()
{
	//postcondition: player is prompted to choose an Element, and target is made
	//weak to that element.

	cout<<"Choose a weakness to remove from "<<target.ShowName()<<":"<<endl;
	ElementChooser elementChooser;
	elementChooser.run();
	if(elementChooser.canceled())
	{
		return none;
	}

	return *(elementChooser.getChoice());
}
