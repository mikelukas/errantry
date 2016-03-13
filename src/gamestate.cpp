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
	  mode(INIT_MODE),
	  currBoss(INIT_NEXT_BOSS),
	  win(false)
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
GameMode GameState::getCurrentMode()
{
	return mode;
}
void GameState::setCurrentMode(const GameMode mode)
{
	this->mode = mode;
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
		win = true;
	currBoss++;
	setCurrentLandscape('M');
}

const bool GameState::isWon() const
{
	return win;
}
