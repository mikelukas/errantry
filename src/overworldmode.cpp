#include "bossbattlemode.h"
#include "gamestate.h"
#include "overworldmode.h"
#include "townmode.h"

OverworldMode::OverworldMode(GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState)
{

}

int OverworldMode::displayMenu()
{
	int choice = 0;
	vector<string>& map = gameData.getMap();

	cout<<"0    5   10   15   20   25  29"<<endl;
	for(int row=0; row<map.size(); row++)
		{
			cout<<map[row]
				<<" "<<row<<endl;
		}
	cout<<"*****Choices*****"<<endl;
	cout<<"*1)Move         *"<<endl;
	cout<<"*2)Status       *"<<endl;
	cout<<"*3)Quit Game    *"<<endl;
	cout<<"*****************"<<endl;
	cout<<"**********************MESSAGES**********************"<<endl;
	do
	{
		cout<<"Please choose an option:  "<<endl;
		cin>>choice;
	}while(!validateChoice(choice, 3));

	return choice;
}

void OverworldMode::testChoice(int choice)
{
	switch(choice)
		{
			case 1:
				move();
				break;
			case 2:
				printStatus();
				break;
			case 3:
				gameState.exitCurrentMode();
				break;
		}
}

void OverworldMode::move()
{
	//postcondition:  The player's position on the map will be moved
	//to the coordinates he/she specifies, if they are on the map.
	//If they are not, he/she will be prompted to re-enter them.
	//This function also handles whether or not a player encounters
	//an enemy or moves to a cave (marked with 'C') while he/she is moving

	int x, y;

	vector<string>& Map = gameData.getMap();
	int mapWidth = Map[0].size();
	int mapHeight = Map.size();

	Player& player = gameState.getPlayer();

	do
	 {
		cout<<"Please choose a valid x coordinate:  ";
		cin>>x;
	 }while(!validateChoice(x+1, mapWidth));
	do
	 {
		cout<<"Please choose a valid y coordinate:  ";
		cin>>y;
	 }while(!validateChoice(y+1, mapHeight));
		cout<<endl;

	 //error trap for valid coordinates

	Point Coords = player.GetCoords();
	Map[Coords.y][Coords.x] = gameState.getCurrentLandscape();

	player.SetCoords(x,y);
	gameState.setCurrentLandscape(Map[y][x]);

	switch(gameState.getCurrentLandscape())
		{
			case 'C': {
				Monster boss = gameData.getBosses()[gameState.getCurrentBoss()];
				GameMode* bossBattle = new BossBattleMode(boss, gameData, gameState);
				gameState.enterMode(bossBattle);
				break;
			}
			case TOWN_SYMBOL: {
				const Town& town = gameData.getTown(player.GetCoords());
				GameMode* townMode = new TownMode(town, gameData, gameState);
				gameState.enterMode(townMode);
				break;
			}
			default:
				getEnemy();
				break;
		}
	Map[y][x] = 'X';
}
void OverworldMode::getEnemy()
{   //postcondition:  a random monster is set into the game state from the monster
	//list to be fought in battle.  Depending on the region of
	//the map the player is in, the monsters may be more difficult.
	//Occasionally, the player will not encounter a monster when
	//he/she moves.

	int randMons;  //holds value to be used as index of monster
				   //in 'monsterList' if it is less than a certain
				   //number.
	const vector<Monster>& monsterList = gameData.getMonsters();
	int x = gameState.getPlayer().GetCoords().x;
	Region area = easy;

	if(x < 30)
		{
			if(x < 20)
				{
					if(x < 10)
						area = hard;
					else
						area = medium;
				}
			else
				area = easy;
		}

	randMons = rand() % 5 + 1;

	switch(area)
		{
			case easy:
				if(randMons < 3)
					{
						Monster monster = monsterList[randMons];
						GameMode* battle = new BattleMode(monster, gameData, gameState);
						gameState.enterMode(battle);
					}
				break;
			case medium:
				if(randMons < 4)
					{
						Monster monster = monsterList[randMons + 3];
						GameMode* battle = new BattleMode(monster, gameData, gameState);
						gameState.enterMode(battle);
					}
				break;
			case hard:
				if(randMons < 3)
					{
						Monster monster = monsterList[randMons + 7];
						GameMode* battle = new BattleMode(monster, gameData, gameState);
						gameState.enterMode(battle);
					}
				break;
		}

}
void OverworldMode::printStatus() const
{
	//postcondition:  prints out the status of a player;
	//their name, level, attributes, current experience, and
	//the amount of experience needed for the next level.
	//It lets the player view his/her status until she presses
	//x and enter when he/she is finished, and returns to the
	//map menu

	const Player& player = gameState.getPlayer();

	char junkCh;

	cout<<"********************************************************"<<endl;
	cout<<"*Name:  "<<player.ShowName()<<setw(16)<<"Level: "<<player.Level()<<endl;
	cout<<"*HP:  "<<player.Health()<<"   --health"<<endl;
	cout<<"*AP:  "<<player.Damage()<<"   --attack power"<<endl;
	cout<<"*DP:  "<<player.Defense()<<"   --defense percentage"<<endl;
	cout<<"*SP:  "<<player.Speed()<<"   --speed points"<<endl<<endl;
	cout<<"*Current experience points:     "<<player.NumExpPts()<<endl;
	cout<<"*Number needed for next level:  "<<player.NumToNext()<<endl<<endl;
	cout<<"**********************MESSAGES**********************"<<endl;
	cout<<"Press X and enter when done:  ";
	cin>>junkCh;
	cout<<endl<<endl;
}
