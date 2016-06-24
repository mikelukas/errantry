#include "equipmode.h"
#include "gamestate.h"

EquipMode::EquipMode(GameData& gameData, GameState& gameState)
	: ApplyEquipmentMode(gameData, gameState)
{
	target = &(gameState.getPlayer());
}

Chooser<EquipmentLine>* EquipMode::createInventoryChooser()
{
	//postcondition: allocates an EquipablesChooser.

	Player & player = gameState.getPlayer();

	return new EquipablesChooser(player);
}
