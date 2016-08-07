#include <iostream>
#include "runaction.h"

using std::cout;
using std::endl;

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
	cout<<gameState.getPlayer().ShowName()<<" ran from the battle!"<<endl;
}
