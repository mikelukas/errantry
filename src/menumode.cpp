#include "menumode.h"

MenuMode::MenuMode(GameData& gameData, GameState& gameState, bool processesStatuses)
	: GameMode(gameData, gameState, processesStatuses)
{

}

void MenuMode::run()
{
	//postcondition: calls displayMenu() to prompt user with choices and gather
	//input, then calls testChoice() to process the input choice.  testChoice()
	//returns a boolean that indicates if the turn is finished, which will end
	//the run call and allow the main game loop to iterate through other steps of
	//a turn. Otherwise the player is taken back to the menu to gather a different
	//choice.

	bool finishTurn = false;
	do
	{
		int choice = displayMenu();
		finishTurn = testChoice(choice);
	} while(!finishTurn);
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
