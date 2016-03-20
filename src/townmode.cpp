#include "gamestate.h"
#include "townmode.h"

TownMode::TownMode(const Town& town, GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState),
	  currentTown(town)
{

}

int TownMode::displayMenu()
{
	//postcondition: Displays town menu options to user, and returns their choice.
	int choice;

	cout<<"*****Choices*****"<<endl;
	cout<<"*1)Talk         *"<<endl;
	cout<<"*2)Leave Town   *"<<endl;
	cout<<"*****************"<<endl;
	do
	 {
		cout<<"Please choose an option:  ";
		cin>>choice;
	 }while(!validateChoice(choice, 2));

	return choice;
}

void TownMode::testChoice(int choice)
{
	switch(choice)
		{
			case 1:
				talk();
				break;
			case 2: //Leave Town
				gameState.exitCurrentMode();
				break;
		}
}

void TownMode::talk() const
{
	//postcondition: prints out what people are saying at the current town.

	char junkCh;

	cout<<"****************************************************"<<endl;
	cout<<currentTown.getConversation();
	cout<<"**********************MESSAGES**********************"<<endl;
	cout<<"Press X and enter when done:  ";
	cin>>junkCh;
	cout<<endl<<endl;
}
