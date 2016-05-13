#include "equipmentchooser.h"

EquipmentChooser::EquipmentChooser(vector<EquipmentLine*>* invEquipment)
	: InventoryChooser(invEquipment)
{

}

EquipmentChooser::~EquipmentChooser()
{
	//postcondition: invChoices freed; assumes subclasses allocated it at creation

	if(invChoices == NULL)
	{
		return;
	}

	delete invChoices;
}

const Equipment* EquipmentChooser::getChosenEquipment() const
{
	//postcondition: returns equipment pointer at the index the player chose
	//in invChoices, or NULL if they chose to exit

	if(choice == EXIT_CHOICE) {
		return NULL;
	}

	return (*invChoices)[choice-1]->pEquipment;
}
