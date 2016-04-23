#include "bossbattlemode.h"
#include "equipmode.h"
#include "gamestate.h"
#include "overworldmode.h"
#include "statsdisplayer.h"
#include "townmode.h"
#include "quitmode.h"
#include "useitemmode.h"

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
	cout<<"*3)Equip        *"<<endl;
	cout<<"*4)Use Item     *"<<endl;
	cout<<"*5)Quit Game    *"<<endl;
	cout<<"*****************"<<endl;
	cout<<"**********************MESSAGES**********************"<<endl;
	do
	{
		cout<<"Please choose an option:  "<<endl;
		cin>>choice;
	}while(!validateChoice(choice, 5));

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
				equip();
				break;
			case 4:
				useItem();
				break;
			case 5:
				GameMode* quit = new QuitMode(gameData, gameState);
				gameState.enterMode(quit);
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
				int currBoss = gameState.getCurrentBoss();
				GameMode* bossBattle = new BossBattleMode(gameData.getBosses()[currBoss], gameData, gameState);
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
						GameMode* battle = new BattleMode(monsterList[randMons], gameData, gameState);
						gameState.enterMode(battle);
					}
				break;
			case medium:
				if(randMons < 4)
					{
						GameMode* battle = new BattleMode(monsterList[randMons + 3], gameData, gameState);
						gameState.enterMode(battle);
					}
				break;
			case hard:
				if(randMons < 3)
					{
						GameMode* battle = new BattleMode(monsterList[randMons + 7], gameData, gameState);
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
	cout<<"Name:  "<<player.ShowName()<<endl
		<<endl;
	StatsDisplayer::fullDisplayFor(player);
	cout<<"**********************MESSAGES**********************"<<endl;
	cout<<"Press X and enter when done:  ";
	cin>>junkCh;
	cout<<endl<<endl;
}

void OverworldMode::equip()
{
	GameMode* equipMode = new EquipMode(gameData, gameState);
	gameState.enterMode(equipMode);
}

void OverworldMode::useItem()
{
	GameMode* useItemMode = new UseItemMode(gameData, gameState);
	gameState.enterMode(useItemMode);
}
