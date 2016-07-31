#include "gamemode.h"
#include "gamestate.h"

GameMode::GameMode(GameData& gameData, GameState& gameState, bool processesStatuses)
	: gameData(gameData),
	  gameState(gameState),
	  processesStatuses(processesStatuses)
{

}

void GameMode::processStatusEffects()
{
	//postcondition: if processesStatuses is set for the mode, calls processStatusesFor
	//on the player.  Some modes may be considered to not "pass time", i.e. shops,
	//so will set processStatuses to false.

	if(!processesStatuses)
	{
		return;
	}

	gameState.getPlayer().processStatusEffects();
}
