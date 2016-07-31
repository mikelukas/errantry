#include "menumode.h"

MenuMode::MenuMode(GameData& gameData, GameState& gameState, bool processesStatuses)
	: GameMode(gameData, gameState, processesStatuses)
{

}

void MenuMode::run()
{
	int choice = displayMenu();
	testChoice(choice);
}

bool MenuMode::validateChoice(int answer, int numChoices) const
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
