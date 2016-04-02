#include "gamestate.h"
#include "shopmainmode.h"

ShopMainMode::ShopMainMode(const Town& town, GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState),
	  currentTown(town)
{

}

int ShopMainMode::displayMenu()
{
	//postcondition: Displays shop menu options to user, and returns their choice.
	int choice;

	cout<<"*****Choices*****"<<endl;
	cout<<"*1)Buy          *"<<endl;
	cout<<"*2)Sell         *"<<endl;
	cout<<"*3)Leave        *"<<endl;
	cout<<"*****************"<<endl;
	do
	 {
		cout<<"Please choose an option:  ";
		cin>>choice;
	 }while(!validateChoice(choice, 3));

	return choice;
}

void ShopMainMode::testChoice(int choice)
{
	switch(choice)
	{
		case 1:
			enterBuyMode();
			break;
		case 2:
			enterSellMode();
			break;
		case 3:
			gameState.exitCurrentMode();
			break;
	}
}
