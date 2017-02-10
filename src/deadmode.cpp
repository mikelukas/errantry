#include <iostream>
#include "deadmode.h"
#include "gamestate.h"

using std::cout;
using std::endl;

DeadMode::DeadMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, false)
{
	// TODO Auto-generated constructor stub
}

void DeadMode::run()
{
	cout<<"You failed to complete your mission of the conquest of evil."<<endl
		<<"The monsters continue to ravish the land and devour civilization"
		<<endl<<"You lose!"<<endl;
	gameState.setGameOver();
}
