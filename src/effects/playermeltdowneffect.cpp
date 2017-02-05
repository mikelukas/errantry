#include <iostream>
#include <sstream>
#include "../logging/log.h"
#include "../character.h"
#include "../meltdownequipmentchooser.h"
#include "playermeltdowneffect.h"

using std::cout;
using std::cin;
using std::endl;

PlayerMeltdownEffect::PlayerMeltdownEffect(const EffectParams& effectParams)
	: MeltdownEffect(effectParams)
{

}

EquipmentLine* PlayerMeltdownEffect::chooseEquipment() const
{
	//postcondition: player is asked to choose a piece of equipment, and a
	//quantity of that equipment, and a new EquipmentLine is allocated for their
	//choice and returned.  It is up to the caller to free this eq line.  If the
	//player aborted choosing equipment, NULL is returned.

	EquipmentLine* chosenEqLine = NULL;
	do {
		MeltdownEquipmentChooser eqChooser(applier);
		eqChooser.run();
		if(eqChooser.canceled())
		{
			return NULL;
		}

		EquipmentLine* invEqLine = eqChooser.getChoice();

		//Can melt down more than 1 piece of the chosen equipment, so ask player for quantity
		int chosenQuantity = 0;
		do
		{
			cout<<"How many "<<invEqLine->pEquipment->getName()<<" (up to "<<invEqLine->quantity<<", or 0 to go back)? ";
			cin>>chosenQuantity;
		} while(!validateQuantityChoice(chosenQuantity, invEqLine->quantity));

		if(chosenQuantity == 0)
		{
			continue;
		}

		chosenEqLine = new EquipmentLine(invEqLine->pEquipment, chosenQuantity);  //We copy what they chose so we don't change the quantity of the actual original inventory equipment here.
	} while(chosenEqLine == NULL);

	return chosenEqLine;
}

bool PlayerMeltdownEffect::validateQuantityChoice(int chosenQuantity, int available) const
{
	//postcondition: returns true if player chose 0, or a positive number quantity
	//of equipment that does not exceed the amount they actually have, false otherwise.

	if(chosenQuantity < 0)
	{
		std::stringstream negMsg;
		negMsg<<"You can't melt down a negative amount of equipment.";
		log(negMsg.str());
		return false;
	}

	if(chosenQuantity > available)
	{
		std::stringstream tooMuchMsg;
		tooMuchMsg<<"You can't melt down more equipment than you have of that type ("<<available<<").";
		log(tooMuchMsg.str());
		return false;
	}

	return true;
}
