#include "battlemode.h"
#include "deadmode.h"
#include "gamestate.h"

BattleMode::BattleMode(Monster monster, GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState),
	  currMonster(monster)
{

}

int BattleMode::displayMenu()
{
	int choice;
	Player& player = gameState.getPlayer();

	cout<<"*************ENEMY! You went to battle!*************"<<endl;
	cout<<player.ShowName()<<endl;
	cout<<"HP:  "<<player.Health()<<"/"<<player.MaxHealth()<<endl;
	cout<<"AP:  "<<player.Damage()<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<currMonster.ShowName()<<endl;
	cout<<"HP:  "<<currMonster.mHealth()<<endl;
	cout<<"*****************"<<endl;
	cout<<"*1)Fight        *"<<endl;
	cout<<"*2)Run          *"<<endl;
	cout<<"*****************"<<endl;
	cout<<"**********************MESSAGES**********************"<<endl;
	do
	{
		cout<<"Please choose an option:  "<<endl;
		cin>>choice;
	}while(!validateChoice(choice,2));

	return choice;
}

void BattleMode::testChoice(int choice)
{
	switch(choice)
		{
			case 1:
				fight();
				break;
			case 2:
				runFromBattle();
				break;
		}
}

void BattleMode::fight()
{
    //postcondition:  this function deals damage to the monster
    //from the player and damage from to the player by the monster.
    //It deducts that damage from the player's and monster's HP.
    //A certain defense number is subtracted for the DP value of the
    //player and monster, so that the player and monster do not
    //do all of their damage(AP) to the other.

	Player& player = gameState.getPlayer();

    int pDamage, mDamage;

    pDamage = player.Damage() - currMonster.Defense();

    if(pDamage < 0)
        pDamage = 0;
    mDamage = currMonster.Damage() - currMonster.Defense();

    if(mDamage < 0)
        mDamage = 0;

    if(player.Speed() >= currMonster.Speed())
        {
    		currMonster.ChangeHP(-1 * pDamage);
            player.ChangeHP(-1 * mDamage);
        }
    else
        {
            player.ChangeHP(-1 * mDamage);
            currMonster.ChangeHP(-1 * pDamage);
        }

    if(currMonster.mHealth() <= 0)
		{
    		onBattleWon();
		}

    if(player.Health() <= 0)
		{
			//if player dies, leave game
			GameMode* dead = new DeadMode(gameData, gameState);
			gameState.enterMode(dead);
		}
}

void BattleMode::runFromBattle()
{
	gameState.exitCurrentMode();
}

void BattleMode::onBattleWon()
{
	Player& player = gameState.getPlayer();

	char cont;
	cout<<"You won the battle!  ";
	cout<<"You gained "<<currMonster.Experience()<<" pts!";
	cout<<endl;
	cout<<"Press X and enter to continue:  ";
	cin>>cont;
	player.AddExp(currMonster.Experience());
	if(player.NumExpPts() >= player.NumToNext())
		player.LevelUp();
	player.ChangeHP(player.MaxHealth() - player.Health());
	gameState.exitCurrentMode();
}
