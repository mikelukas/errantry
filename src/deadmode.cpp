#include <iostream>
#include "deadmode.h"
#include "gamestate.h"

using std::cout;
using std::endl;

DeadMode::DeadMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, false)
{

}

void DeadMode::updateDisplay()
{
	cout<<"You failed to complete your mission of the conquest of evil."<<endl
		<<"The monsters continue to ravish the land and devour civilization"
		<<endl<<"You lose!"<<endl;
}

bool DeadMode::processInput()
{
	gameState.setGameOver();
	return true;
}
