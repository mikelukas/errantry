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

bool MenuMode::validateChoice(int answer, int numChoices)
{
	//postcondition:  determines if response entered by user is
	//a valid response number and returns true if so, false
	//if not.
	if(answer >0 && answer<=numChoices)
		return true;
	else
		cout<<"Invalid Response"<<endl;
	return false;
}
