#include "applyequipmentmode.h"
#include "gamestate.h"

ApplyEquipmentMode::ApplyEquipmentMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, true),
	  equipmentChoice(NULL),
	  target(NULL)
{

}

ApplyEquipmentMode::~ApplyEquipmentMode()
{

}

void ApplyEquipmentMode::updateDisplay()
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
	else
	{
		equipmentChoice = NULL;
	}

	delete invChooser;
}

bool ApplyEquipmentMode::processInput()
{
	//postcondition: If player chose equipment, that equipment is used on them
	//via a call to useEquipment() on the player with the player as the target,
	//and the inventory list is updated.  Otherwise, if the player chose exit, the mode is exited.
	//Always returns true to indicate turn should finish.

	if(equipmentChoice != NULL && target != NULL) {
		useEquipment();
	} else {
		gameState.requestExitCurrentMode();
	}

	return true;
}
