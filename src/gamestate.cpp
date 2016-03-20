/*
 * gamestate.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: mlukas
 */

#include "gamemode.h"
#include "gamestate.h"

GameState::GameState()
	: player(),
	  landscape(INIT_LANDSCAPE),
	  currBoss(INIT_NEXT_BOSS)
{
	//monster and town not initialized because you don't start in a town
}

GameState::~GameState() {
	// TODO Auto-generated destructor stub
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
void GameState::enterMode(GameMode* mode)
{
	//postcondition: mode becomes the current active mode.  Mode will be deleted
	//when exitCurrentMode is called
	activeModes.push(mode);
}
void GameState::exitCurrentMode()
{
	//postcondition: deletes the current mode and makes the mode that the player
	//was previously in before they got to that mode the current mode
	delete activeModes.top();
	activeModes.pop();
}
Town& GameState::getCurrentTown()
{
	return town;
}
void GameState::setCurrentTown(const Town& town)
{
	this->town = town;
}
Monster& GameState::getCurrentMonster()
{
	return monster;
}
void GameState::setCurrentMonster(Monster monster)
{
	this->monster = monster;
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
