#include "gamestate.h"
#include "winmode.h"

WinMode::WinMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState)
{

}

void WinMode::run()
{
	cout<<"Congratulations, you have defeated the evil monsters of the land,"
		<<endl<<"saved the people, and allowed peace to flourish!"<<endl
		<<"You win!"<<endl;
	gameState.setGameOver();
}
