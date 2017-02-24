#include <time.h> //time()
#include "gamemode.h"
#include "gamestate.h"

GameState::GameState()
	: player(),
	  landscape(INIT_LANDSCAPE),
	  nextMode(NULL),
	  exitCurrentModeRequested(false),
	  currBoss(INIT_NEXT_BOSS)

{
	srand(time(NULL));
	//monster and town not initialized because you don't start in a town
}

Player& GameState::getPlayer()
{
	return player;
}

char GameState::getCurrentLandscape()
{
	return landscape;
}
void GameState::setCurrentLandscape(const char landscape)
{
	this->landscape = landscape;
}
GameMode* GameState::getCurrentMode() const
{
	return activeModes.top();
}
void GameState::requestEnterMode(GameMode* mode)
{
	//postcondition: schedules the incoming mode to be changed to become the
	//current mode when the current mode finishes running.
	//If an exit request and an enter request are made by the same mode, the exit
	//request will always be handled first.
	//Use this method within modes to request changing to a new one.  It ensures
	//an exit request won't immediately drop you out of a mode you tried to enter
	//and ensures that multiple modes won't be set to be entered by the same mode.

	nextMode = mode;
}
void GameState::handleEnterModeRequest()
{
	//postcondition: if a nextMode was requested to be entered, it will be made
	//the active mode, and nextMode will be set back to NULL
	//onEnter() is called on the mode after it has been activated.

	if(nextMode != NULL)
	{
		enterMode(nextMode);
		nextMode = NULL;

		//Inform the newly-entered mode that it is now active
		activeModes.top()->onEnter();
	}
}
void GameState::enterMode(GameMode* mode)
{
	//postcondition: mode becomes the current active mode.  Mode will be deleted
	//when exitCurrentMode is called.

	activeModes.push(mode);
}
void GameState::requestExitCurrentMode()
{
	//postcondition: schedules the current mode to be popped and deleted after
	//the current mode finishes running.
	//If an exit request and an enter request are made by the same mode, the exit
	//request will always be handled first.
	//Use this method within modes to exit the current mode; it prevents the effect of
	//multiple calls to exitCurrentMode() while still running a mode, which would
	//result in unwanted exiting of extra modes, and also allows the current
	//mode to finish exiting before its destructor is called, which could cause
	//unwanted deletion of state.

	exitCurrentModeRequested = true;
}
void GameState::handleExitModeRequest()
{
	//postcondition: if exitCurrentModeRequested is set, calls exitCurrentMode()
	//and clears exitCurrentModeRequested.
	//onEnter() is then called on the mode that was previous running (unless
	//there were no previous modes running)

	if(exitCurrentModeRequested)
	{
		exitCurrentMode();
		exitCurrentModeRequested = false;

		//Inform the new current mode that it is now active
		if(!activeModes.empty())
		{
			activeModes.top()->onEnter();
		}
	}
}
void GameState::exitCurrentMode()
{
	//postcondition: deletes the current mode and makes the mode that the player
	//was previously in before they got to that mode the current mode
	//Method is private since exiting the current mode while it is running can
	//destroy state that mode needs to finish running, because its destructor
	//will immediately be called.
	//If the current mode should be exited, a request to do so should be made
	//instead of directly calling this method.
	//NOTE: onEnter() is not called on the mode here b/c in the event of a
	//GameOver, un-desired effects could happen at the end of the game as each
	//mode is popped and the one below it is entered

	delete activeModes.top();
	activeModes.pop();
}
int GameState::getCurrentBoss()
{
	return currBoss;
}
void GameState::advanceToNextBoss()
{
	currBoss++;
	setCurrentLandscape('M');
}

void GameState::setGameOver()
{
	//postcondition: all modes are exited (activeModes stack is emptied)
	while(!activeModes.empty())
	{
		exitCurrentMode();
	}
}

const bool GameState::isGameOver() const
{
	//postcondition: returns true if the activeModes is empty
	return activeModes.empty();
}
