#include "applyequipmentmode.h"
#include "gamestate.h"

ApplyEquipmentMode::ApplyEquipmentMode(GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState),
	  invEquipment(NULL), //should be actually populated in updateEquipmentChoices()
	  target(NULL)
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

	//initializes or refreshes equipment choices vector
	cleanupEquipmentChoices();
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
	//postcondition: If player chose equipment, that equipment is used on them
	//via a call to useEquipment() on the player with the player as the target,
	//and the inventory list is updated.  Otherwise, if the player chose exit, the mode is exited.

	switch(choice)
	{
	case EXIT_CHOICE:
		gameState.exitCurrentMode();
		break;
	default:
		if(target != NULL) {
			gameState.getPlayer().useEquipment((*invEquipment)[choice-1]->pEquipment, *target);
		}
		break;
	}
}

void ApplyEquipmentMode::cleanupEquipmentChoices()
{
	if(invEquipment == NULL)
	{
		return;
	}

	delete invEquipment;
}
