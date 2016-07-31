#include "applyequipmentmode.h"
#include "gamestate.h"

ApplyEquipmentMode::ApplyEquipmentMode(GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState, true),
	  equipmentChoice(NULL),
	  target(NULL)
{

}

ApplyEquipmentMode::~ApplyEquipmentMode()
{

}

int ApplyEquipmentMode::displayMenu()
{
	//postcondition: runs the InventoryChooser that subclasses create, and gets
	//the player choice from it.

	int choice;

	Chooser<EquipmentLine>* invChooser = createInventoryChooser();
	invChooser->run();

	choice = invChooser->getChoiceNum();

	EquipmentLine* chosenEqLine = invChooser->getChoice();
	if(chosenEqLine != NULL)
	{
		equipmentChoice = chosenEqLine->pEquipment;
	}

	delete invChooser;

	return choice;
}

void ApplyEquipmentMode::testChoice(int choice)
{
	//postcondition: If player chose equipment, that equipment is used on them
	//via a call to useEquipment() on the player with the player as the target,
	//and the inventory list is updated.  Otherwise, if the player chose exit, the mode is exited.

	switch(choice)
	{
	case CANCELED_CHOICE:
		gameState.requestExitCurrentMode();
		break;
	default:
		if(equipmentChoice != NULL && target != NULL) {
			gameState.getPlayer().useEquipment(equipmentChoice, *target);
		}
		break;
	}
}
