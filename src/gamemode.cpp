#include "gamemode.h"
#include "gamestate.h"

GameMode::GameMode(GameData& gameData, GameState& gameState)
	: gameData(gameData),
	  gameState(gameState)
{

}

void GameMode::processStatusEffects()
{
	//postcondition: calls processStatusesFor on the player, with this mode's
	//context (for some contexts there may be nothing to process).

	gameState.getPlayer().processStatusEffects();
}
