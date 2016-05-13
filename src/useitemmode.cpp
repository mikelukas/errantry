#include "gamestate.h"
#include "useitemmode.h"

UseItemMode::UseItemMode(GameData& gameData, GameState& gameState)
	: ApplyEquipmentMode(gameData, gameState)
{
	target = &(gameState.getPlayer());
}

EquipmentChooser* UseItemMode::createInventoryChooser()
{
	//postcondtion: allocates a UsableItemChooser

	return new UsableItemChooser(gameState.getPlayer());
}
