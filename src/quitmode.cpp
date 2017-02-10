#include <iostream>
#include "gamestate.h"
#include "quitmode.h"

using std::cout;
using std::endl;

QuitMode::QuitMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, false)
{

}

void QuitMode::run()
{
	//TODO: Make different message for quitting, possibly request user confirmation before ending game
	cout<<"You failed to complete your mission of the conquest of evil."<<endl
		<<"The monsters continue to ravish the land and devour civilization"
		<<endl<<"You lose!"<<endl;
	gameState.setGameOver();
}
