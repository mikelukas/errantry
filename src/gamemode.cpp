#include "logging/log.h"
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

void GameMode::run()
{
	//postcondition: calls updateDisplay() to prompt user with choices and gather
	//input, then calls processInput() to process the input choice.  processInput()
	//returns a boolean that indicates if the turn is finished, which will end
	//the run call and allow the main game loop to iterate through other steps of
	//a turn. Otherwise the player is taken back to the menu to gather a different
	//choice.

	bool finishTurn = false;
	do
	{
		updateDisplay();
		finishTurn = processInput();
	} while(!finishTurn);
}

bool GameMode::validateChoice(int answer, int numChoices) const
{
	//postcondition:  determines if response entered by user is
	//a valid response number and returns true if so, false
	//if not.
	if(answer >0 && answer<=numChoices)
		return true;
	else
		log("Invalid Response");
	return false;
}
