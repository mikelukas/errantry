/*
 * gamestate.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: mlukas
 */

#include "gamestate.h"

GameState::GameState()
	: player(),
	  landscape(INIT_LANDSCAPE),
	  currBoss(INIT_NEXT_BOSS)
{
	//monster and town not initialized because you don't start in a town

	initGameOverModes();
	activeModes.push(quit); //Quit is at the bottom of the stack, so  exiting all modes results in ending the game
	activeModes.push(INIT_MODE);
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
GameModeType GameState::getCurrentMode() const
{
	return activeModes.top();
}
void GameState::enterMode(const GameModeType mode)
{
	activeModes.push(mode);
}
void GameState::exitCurrentMode()
{
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
	if(currBoss > 7)
		enterMode(win);
	currBoss++;
	setCurrentLandscape('M');
}

void GameState::initGameOverModes()
{
	gameOverModes.insert(quit);
	gameOverModes.insert(dead);
	gameOverModes.insert(win);
}

const bool GameState::isGameOver() const
{
	//postcondition: returns true if the current mode is in one of the ones in the gameOverModes set
	return (gameOverModes.find(getCurrentMode()) != gameOverModes.end());
}

const bool GameState::isWon() const
{
	return (activeModes.top() == win);
}
