#include <iostream>
#include "gamestate.h"
#include "winmode.h"

using std::cout;
using std::endl;

WinMode::WinMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, false)
{

}

void WinMode::updateDisplay()
{
	cout<<"Congratulations, you have defeated the evil monsters of the land,"
		<<endl<<"saved the people, and allowed peace to flourish!"<<endl
		<<"You win!"<<endl;
}

bool WinMode::processInput()
{
	gameState.setGameOver();

	return true;
}
