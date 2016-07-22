#include "gamemode.h"
#include "gamestate.h"

GameMode::GameMode(GameData& gameData, GameState& gameState)
	: gameData(gameData),
	  gameState(gameState),
	  context(NO_CONTEXT)
{

}

GameMode::GameMode(GameData& gameData, GameState& gameState, const Context context)
	: gameData(gameData),
	  gameState(gameState),
	  context(context)
{

}

GameMode::~GameMode() {
	// TODO Auto-generated destructor stub
}

void GameMode::processStatusEffects()
{
	//postcondition: calls processStatusesFor on the player, with this mode's
	//context (for some contexts there may be nothing to process).

	gameState.getPlayer().processStatusesFor(context);
}
