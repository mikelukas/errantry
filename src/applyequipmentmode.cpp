#include "applyequipmentmode.h"
#include "gamestate.h"

ApplyEquipmentMode::ApplyEquipmentMode(GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState),
	  equipmentChoice(NULL),
	  target(NULL)
{

}

ApplyEquipmentMode::~ApplyEquipmentMode()
{

}

int ApplyEquipmentMode::displayMenu()
{
	//postcondition: invokes display on the InventoryChooser subclasses create,
	//and gets player choice from that.

	int choice;

	EquipmentChooser* invChooser = createInventoryChooser();
	invChooser->display();

	choice = invChooser->getChoice();
	equipmentChoice = invChooser->getChosenEquipment();

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
	case EXIT_CHOICE:
		gameState.exitCurrentMode();
		break;
	default:
		if(equipmentChoice != NULL && target != NULL) {
			gameState.getPlayer().useEquipment(equipmentChoice, *target);
		}
		break;
	}
}
