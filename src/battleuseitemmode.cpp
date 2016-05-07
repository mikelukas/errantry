#include "battleuseitemmode.h"
#include "gamestate.h"
#include "statsdisplayer.h"

BattleUseItemMode::BattleUseItemMode(GameData& gameData, GameState& gameState, Monster& monster)
	: UseItemMode(gameData, gameState),
	  monster(monster)
{
	target = NULL;
}

void BattleUseItemMode::setTarget(Character* newTarget)
{
	target = newTarget;
}

void BattleUseItemMode::displayRelevantPlayerAttrs()
{
	Player& player = gameState.getPlayer();

	cout<<player.ShowName()<<endl;
	StatsDisplayer::battleDisplayFor(player);
	cout<<endl;
	cout<<monster.ShowName()<<endl;
	StatsDisplayer::battleDisplayFor(monster);
}

int BattleUseItemMode::displayMenu()
{
	int itemChoice = 0;
	do {
		itemChoice = UseItemMode::displayMenu();
		if(itemChoice == EXIT_CHOICE)
		{
			return itemChoice;
		}

		//Prompt player to choice a target for their item choice
		int targetChoice = 0;

		cout<<"**********************MESSAGES**********************"<<endl;
		cout<<"1)Player"<<endl
			<<"2)Monster"<<endl
			<<"0)Back"<<endl
			<<endl;
		cout<<"Choose a target:"<<endl;
		cin>>targetChoice;

		//Set mode target based on player choice, choice should only be able to be valid at this point
		switch(targetChoice)
		{
		case 1:
			setTarget(&(gameState.getPlayer()));
			break;
		case 2:
			setTarget(&(monster));
			break;
		case EXIT_CHOICE:
			continue;
		default:
			cout<<"Invalid response"<<endl;
			break;
		}
	} while(target == NULL);

	return itemChoice;
}

void BattleUseItemMode::testChoice(int itemChoice)
{
	//postcondition: calls testChoice with the item the player chose, but also
	//automatically exits the mode if the user didn't already choose to exit,
	//since the player can only use 1 item per turn in battle.

	UseItemMode::testChoice(itemChoice);
	if(itemChoice != EXIT_CHOICE)
	{
		gameState.exitCurrentMode();
	}
}
