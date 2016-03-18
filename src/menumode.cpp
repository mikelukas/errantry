/*
 * menumode.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: mlukas
 */

#include "menumode.h"

MenuMode::MenuMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState)
{

}

void MenuMode::run()
{
	int choice = displayMenu();
	testChoice(choice);
}
