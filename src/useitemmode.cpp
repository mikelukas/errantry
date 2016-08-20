#include "gamestate.h"
#include "useitemmode.h"

UseItemMode::UseItemMode(GameData& gameData, GameState& gameState)
	: ApplyEquipmentMode(gameData, gameState)
{
	target = &(gameState.getPlayer());
}

Chooser<EquipmentLine>* UseItemMode::createInventoryChooser()
{
	//postcondtion: allocates a UsableItemChooser

	return new UsableItemChooser(gameState.getPlayer());
}

void UseItemMode::useEquipment()
{
	//postcondition:: chosen item is used on the target by the player via a
	//call to useItem().

	gameState.getPlayer().useItem(equipmentChoice, *target);
}
