#include <sstream>
#include "logging/log.h"
#include "runaction.h"

RunAction::RunAction(GameState& gameState)
	: BattleAction(gameState.getPlayer()),
	  gameState(gameState)
{

}

void RunAction::doAction()
{
	//postcondition: current mode is set to be exited.  Note that the monster
	//will still get a turn in when this action is chosen.

	gameState.requestExitCurrentMode();

	std::stringstream runMsg;
	runMsg<<gameState.getPlayer().ShowName()<<" ran from the battle!";
	log(runMsg.str());
}
