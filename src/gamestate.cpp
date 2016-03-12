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
	  region(INIT_REGION),
	  nextBoss(INIT_NEXT_BOSS),
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
GameMode GameState::getCurrentMode()
{
	return mode;
}
Region GameState::getCurrentRegion()
{
	return region;
}
Town& GameState::getCurrentTown()
{
	return town;
}
Monster& GameState::getMonster()
{
	return monster;
}
int GameState::getNextBoss()
{
	return nextBoss;
}
bool GameState::isWon()
{
	return win;
}
