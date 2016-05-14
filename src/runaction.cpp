#include "runaction.h"

RunAction::RunAction(GameState& gameState)
	: gameState(gameState)
{

}

void RunAction::execute()
{
	//postcondition: current mode is set to be exited.  Note that the monster
	//will still get a turn in when this action is chosen.

	gameState.requestExitCurrentMode();
}
