#include <iostream>
#include "gamestate.h"
#include "shopmainmode.h"

using std::cout;
using std::cin;
using std::endl;

ShopMainMode::ShopMainMode(const Town& town, GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, false),
	  currentTown(town)
{

}

void ShopMainMode::updateDisplay()
{
	//postcondition: Displays shop menu options to user, and returns their choice.

	cout<<"*****Choices*****"<<endl;
	cout<<"*1)Buy          *"<<endl;
	cout<<"*2)Sell         *"<<endl;
	cout<<"*3)Leave        *"<<endl;
	cout<<"*****************"<<endl;
}

bool ShopMainMode::processInput()
{
	int choice = 0;
	do
	{
		cout<<"Please choose an option:  ";
		cin>>choice;
	}while(!validateChoice(choice, 3));

	switch(choice)
	{
		case 1:
			enterBuyMode();
			break;
		case 2:
			enterSellMode();
			break;
		case 3:
			gameState.requestExitCurrentMode();
			break;
	}

	return true;
}
