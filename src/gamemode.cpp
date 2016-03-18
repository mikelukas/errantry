/*
 * GameMode.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: mlukas
 */

#include "gamemode.h"

GameMode::GameMode(GameData& gameData, GameState& gameState)
	: gameData(gameData),
	  gameState(gameState)
{

}

GameMode::~GameMode() {
	// TODO Auto-generated destructor stub
}

