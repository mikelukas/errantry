#include "applyequipmentmode.h"
#include "gamestate.h"

ApplyEquipmentMode::ApplyEquipmentMode(GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState),
	  invEquipment(NULL) //should be actually populated in updateEquipmentChoices()
{

}

ApplyEquipmentMode::~ApplyEquipmentMode()
{
	cleanupEquipmentChoices();
}

void ApplyEquipmentMode::run()
{
	//postcondition: Updates the equipment choice list before displaying the menu,
	//since the player's inventory will be changed by whatever they choose.

	updateEquipmentChoices();
	MenuMode::run();
}

int ApplyEquipmentMode::displayMenu()
{
	//postcondition: the player's current attributes relative to the type of
	//equipment they can apply in this mode are displayed, followed by eligible
	//equipment choices they can apply to themselves in this mode.

	int choice;

	cout<<"****************************************************"<<endl;
	displayRelevantPlayerAttrs();
	cout<<"----------------------------------------------------"<<endl;
	displayEquipmentList();
	cout<<EXIT_CHOICE<<") Back"<<endl;
	cout<<"**********************MESSAGES**********************"<<endl;

	do
	{
		cout<<"Please choose an option:  "<<endl;
		cin>>choice;

		if(choice == EXIT_CHOICE)
		{
			return choice;
		}
	} while(!validateChoice(choice, invEquipment->size()));

	return choice;
}

void ApplyEquipmentMode::testChoice(int choice)
{
	//postcondition: If player chose equipment, that equipment is applied to them
	//via a call to apply() on the player, and the inventory list is updated.
	//Otherwise, if the player chose exit, the mode is exited.

	switch(choice)
	{
	case EXIT_CHOICE:
		gameState.exitCurrentMode();
		break;
	default:
		gameState.getPlayer().apply((*invEquipment)[choice-1]);
		cleanupEquipmentChoices();
		updateEquipmentChoices();
		break;
	}
}

void ApplyEquipmentMode::cleanupEquipmentChoices()
{
	if(invEquipment == NULL)
	{
		return;
	}

	//all EquipmentLine* in choices vector were also dynamically allocated prior to creating this mode
	while(!invEquipment->empty())
	{
		delete (invEquipment->back());
		invEquipment->pop_back();
	}
	delete invEquipment;
}
