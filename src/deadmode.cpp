#include <iostream>
#include "deadmode.h"
#include "gamestate.h"

using std::cout;
using std::endl;

DeadMode::DeadMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, false)
{

}

int DeadMode::updateDisplay()
{
	cout<<"You failed to complete your mission of the conquest of evil."<<endl
		<<"The monsters continue to ravish the land and devour civilization"
		<<endl<<"You lose!"<<endl;

	return 1;
}

bool DeadMode::processInput(int choice)
{
	gameState.setGameOver();
	return true;
}
