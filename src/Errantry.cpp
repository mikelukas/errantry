//Mike Lukas - p2prog03-      -Errantry2.cpp-
//This program is game called Errantry which is fantasy adventure game.
//In it, the user may travel around a map and fight monsters.  The goal
//is to defeat all 7 of the boss monsters which are found only in caves
//on the map.  While the user is moving, he/she may encounter and fight
//monsters.  If the player defeats the monster, he/she will gain 
//experience points, which when enough are earned, promote the player 
//by one level and increase his/her attributes.  It is to the player's
//advantage to move around a lot and gain experience, because by 
//increase his/her attributes, the player has a better chance of defeating
//the bosses which are stronger than the regular enemies.  The output from
//this program includes the map the user travels on and his/her position
//on it or a battle display with player and enemy information displayed,
//a menu of actions the user may take while on the map, a menu of actions
//the user may take while in battle, and other comments regarding 
//experienced being earned and levels being increased.  Also, it will
//display an ending message when the game is lost or won, as well as
//instructions in the beginning.  

#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include "gamestate.h"
#include "gamedata.h"
#include "player.h"

using std::map;
using std::vector;
using std::string;

using std::setw;

using std::cout;
using std::cin;
using std::endl;
 
void Intro();
bool MainGame(GameData& gameData, GameState& gameState);
void DisplayMenu(vector<string>& Map, int& choice, GameState& gameState);
void townChoices(int& choice);
bool TestChoice(GameData& gameData,
                int choice, bool& win,
                Region& area, GameState& gameState);
void Move(GameData& gameData,
          const vector<Monster>& monsterList, const vector<Monster>& Bosses,
          Region& area, GameState& gameState);
void GetEnemy(const vector<Monster>& monsterList, int x, Region& area, GameState& gameState);
void Fight(Player& player, Monster& monster);
void PrintStatus(Player& player);
void Talk(Town& town);
void GameOver(bool win);

int main()
    {
        bool win;

        GameData gameData;
        GameState gameState;

        if(!gameData.loadSuccessful())
        	{
        		cout<<"ERROR:  'Could not read one or more data files!"<<endl;
        		return 1;
        	}

        Intro();
		win = MainGame(gameData, gameState);
		GameOver(win);

        return 0;
    }
void Intro()
    {
        char answer, start;
        do
         {
            cout<<"#/////**/----/**/////**/\**\\\\\**\----\**\\\\\#"<<endl
                <<"|                                              |"<<endl
                <<"|                                              |"<<endl
                <<"|                  Errantry                    |"<<endl
                <<"|                by Mike Lukas                 |"<<endl
                <<"|                                              |"<<endl
                <<"|                                              |"<<endl
                <<"#\\\\\**\----\**\\\\\**\/**/////**/----/**/////#"<<endl
                <<"Would you like to view the instructions?(y/n) ";
            cin>>answer;
         }while(!Validate(answer));
        
        if(answer == 'Y' || answer == 'y')
            {
                cout<<"The world you have just set foot in has become one of chaos."<<endl
                    <<"Monsters ravish the land destroying all that once was beautiful"
              <<endl<<"to the people.  An errant warrior from another continent, it is"<<endl
                    <<"your job to defeat these monsters and their evil controllers"<<endl
                    <<"hiding in various caves around the continent.  Only after all"<<endl
                    <<"7 have been defeated, can the monsters be vanquished and peace"<<endl
                    <<"be restored."<<endl
                    <<"Your position on the continent is marked by an X on the map."<<endl
                    <<"You begin on the right side.  As you progress to the other"<<endl
                    <<"side of the continent, beware, for the monsters become stronger."<<endl
                    <<"The various C's along the map mark the entrances to caves."<<endl
                    <<"By moving to the caves, you can fight the evil controllers" <<endl
                    <<"of the monsters.  While you move around the map, you may encouner"<<endl
                    <<"monsters.  By defeating these monsters, you can increase your"<<endl
                    <<"experience points.  When you gain enough, you will advance 1"<<endl
                    <<"level.  Every level advance allows you to increase your attributes"<<endl
                    <<"and become stronger.  If you are defeated by a monster in battle,"<<endl
                    <<"you lose the game.  You may view your statistics at any time"<<endl
                    <<"by choosing that option on the map menu.  Build your levels"<<endl
                    <<"so that you are stronger and can fight monsters and controllers"<<endl
                    <<"better!  Good luck and enjoy Errantry!"<<endl;
            }
        cout<<"Type x and press enter to start the game:  ";
        cin>>start;
        cout<<"****************************************************"<<endl;
    }
bool MainGame(GameData& gameData, GameState& gameState)
    {
        //This function controls the main game.  It displays the
        //appropriate menus for the game's state(battle or map (overworld))
        //and also indirectly carries out all of the actions a user may
        //perform by calling the functions that perform those actions.
        
        int choice;
        bool win = false, leave = false;
        Region area = gameState.getCurrentRegion();
        
        while(leave == false && win == false)
            {
                DisplayMenu(gameData.getMap(), choice, gameState);
                leave = TestChoice(gameData,
								   choice, win,
                                   area, gameState);
            }
        return win;
    }
    
void DisplayMenu(vector<string>& Map, int& choice, GameState& gameState)
    {   
        //postcondition:  The menu for the current state ofthe game 
        //(battle or map(overworld) ) is displayed, and the user may
        //choose an action from one of the options
        
        int row, numrows;
        numrows = Map.size();

        Player& player = gameState.getPlayer();
            
        switch(gameState.getCurrentMode())
          {
            case overworld:
                cout<<"0    5   10   15   20   25  29"<<endl;
                for(row=0; row<numrows; row++)
                    {
                        cout<<Map[row]
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
                 }while(!Validate(choice, 3));
                break;
            case town:
				townChoices(choice);
				break;
            case bossBattle:
            case battle:
            	Monster monster = gameState.getCurrentMonster();

                cout<<"*************ENEMY! You went to battle!*************"<<endl;
                cout<<player.ShowName()<<endl;
                cout<<"HP:  "<<player.Health()<<"/"<<player.MaxHealth()<<endl;
                cout<<"AP:  "<<player.Damage()<<endl;
                cout<<endl;
                cout<<endl;
                cout<<endl;
                cout<<monster.ShowName()<<endl;
                cout<<"HP:  "<<monster.mHealth()<<endl;
                cout<<"*****************"<<endl;
                cout<<"*1)Fight        *"<<endl;
                cout<<"*2)Run          *"<<endl;
                cout<<"*****************"<<endl;
                cout<<"**********************MESSAGES**********************"<<endl;
                do
                 {
                    cout<<"Please choose an option:  "<<endl;
                    cin>>choice;
                 }while(!Validate(choice,2));
                break;
        }
    }
void townChoices(int& choice)
    {
		//postcondition: Displays town menu options to user, and returns their choice.

        cout<<"*****Choices*****"<<endl;
        cout<<"*1)Talk         *"<<endl;
        cout<<"*2)Leave Town   *"<<endl;
        cout<<"*****************"<<endl;
        do
         {
            cout<<"Please choose an option:  ";
            cin>>choice;
         }while(!Validate(choice, 2));
    }
bool TestChoice(GameData& gameData,
                int choice, bool& win,
                Region& area, GameState& gameState)
    {
        //postcondition:  the user-chosen action chose at the current
        //menu the player is at is carried out.  For instance, if the
        //user chooses move from the map menu, that action is
        //performed.  
        char cont;          //holds character user types at the 'press x and enter
                            //to continue' prompt
        bool leave = false;  //holds whether or not the user chose quit
        Player& player = gameState.getPlayer();
        Monster& monster = gameState.getCurrentMonster();
        
        switch(gameState.getCurrentMode())
            {
                case overworld:  //map menu
                    switch(choice)
                        {
                            case 1:
                                Move(gameData, gameData.getMonsters(), gameData.getBosses(),
                                     area, gameState);
                                break;
                            case 2:
                                PrintStatus(player);
                                break;
                            case 3:
                                leave = true;
                                break;
                        }
                    break;
				case town: {//braces necessary b/c of declaring variables inside of case; statement
					Town& town = gameState.getCurrentTown();
					switch(choice)
						{
							case 1:
								Talk(town);
								break;
							case 2: //Leave Town
								gameState.setCurrentMode(overworld);
								break;
						}
					break;
				}
                case bossBattle:  //battle menu
                    switch(choice)
                        {
                            case 1:
                                Fight(player, monster);
                                break;
                            case 2:
                                cout<<"Can't run from boss fight!"<<endl;
                                break;
                        }
                    if(monster.mHealth() <= 0)  //if boss is dead
                        {                      //find the next on the list
                                               //add exp. pts. from the 
                                               //boss.
                            if(gameState.getCurrentBoss() > 7)
                                win = true;
                            cout<<"You won the battle!  ";
                            cout<<"You gained "<<monster.Experience()<<" pts!";
                            cout<<endl;
                            cout<<"Press X and enter to continue:  ";
                            cin>>cont;
                            player.AddExp(monster.Experience());
                            if(player.NumExpPts() >= player.NumToNext())
                                player.LevelUp();
                            player.ChangeHP(player.MaxHealth() - player.Health());

                            gameState.advanceToNextBoss();
                            gameState.setCurrentMode(overworld);
                        }
                    break;              
                case battle:   //battle menu
                    switch(choice)
                        {
                            case 1:
                                Fight(player, monster);
                                break;
                            case 2:
                            	gameState.setCurrentMode(overworld);
                                break;
                        }
                    if(monster.mHealth() <= 0)
                        {
                            cout<<"You won the battle!  ";
                            cout<<"You gained "<<monster.Experience()<<" pts!";
                            cout<<endl;
                            cout<<"Press X and enter to continue:  ";
                            cin>>cont;
                            player.AddExp(monster.Experience());
                            if(player.NumExpPts() >= player.NumToNext())
                                player.LevelUp();
                            player.ChangeHP(player.MaxHealth() - player.Health());
                            gameState.setCurrentMode(overworld);
                        }
                    break;
            }
        if(player.Health() <= 0)  //if player dies, leave game
            leave = true;
        return leave;
    }
void Move(GameData& gameData,
          const vector<Monster>& monsterList, const vector<Monster>& Bosses,
          Region& area, GameState& gameState)
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
         }while(!Validate(x+1, mapWidth));
        do
         {
            cout<<"Please choose a valid y coordinate:  ";
            cin>>y;
         }while(!Validate(y+1, mapHeight));
            cout<<endl;
         
         //error trap for valid coordinates
        
        Point Coords = player.GetCoords();
        Map[Coords.y][Coords.x] = gameState.getCurrentLandscape();
        
        player.SetCoords(x,y);  
        gameState.setCurrentLandscape(Map[y][x]);
        
        switch(gameState.getCurrentLandscape())
			{
				case 'C':
					gameState.setCurrentMode(bossBattle);
					gameState.setCurrentMonster(Bosses[gameState.getCurrentBoss()]);
					break;
				case TOWN_SYMBOL:
					gameState.setCurrentMode(town);
					gameState.setCurrentTown(gameData.getTown(player.GetCoords()));
					break;
				default:
					GetEnemy(monsterList, x, area, gameState);
					break;
			}
        Map[y][x] = 'X';
    }
void GetEnemy(const vector<Monster>& monsterList, int x, Region& area, GameState& gameState)
    {   //postcondition:  a random monster is set into the game state from the monster
        //list to be fought in battle.  Depending on the region of
        //the map the player is in, the monsters may be more difficult.
        //Occasionally, the player will not encounter a monster when
        //he/she moves.
        
        int randMons;  //holds value to be used as index of monster
                       //in 'monsterList' if it is less than a certain
                       //number.
        //variable x is the x coordinate of the player on the map.
        
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
                            gameState.setCurrentMonster(monsterList[randMons]);
                            gameState.setCurrentMode(battle);
                        }
                    break;
                case medium:
                    if(randMons < 4)
                        {
                    		gameState.setCurrentMonster(monsterList[randMons + 3]);
                    		gameState.setCurrentMode(battle);
                        }
                    break;
                case hard:
                    if(randMons < 3)
                        {
                    		gameState.setCurrentMonster(monsterList[randMons + 7]);
                    		gameState.setCurrentMode(battle);
                        }
                    break;
            }
        
    }
            
void Fight(Player& player, Monster& monster)
    {
        //postcondition:  this function deals damage to the monster
        //from the player and damage from to the player by the monster.
        //It deducts that damage from the player's and monster's HP.
        //A certain defense number is subtracted for the DP value of the
        //player and monster, so that the player and monster do not
        //do all of their damage(AP) to the other. 
        
        int pDamage, mDamage;
        
        pDamage = player.Damage() - monster.Defense();
        
        if(pDamage < 0)
            pDamage = 0;
        mDamage = monster.Damage() - monster.Defense();
        
        if(mDamage < 0)
            mDamage = 0;
        
        if(player.Speed() >= monster.Speed())
            {
                monster.ChangeHP(-1 * pDamage);
                player.ChangeHP(-1 * mDamage);
            }
        else
            {
                player.ChangeHP(-1 * mDamage);
                monster.ChangeHP(-1 * pDamage); 
            }
    }

void PrintStatus(Player& player)
    {
        //postcondition:  prints out the status of a player;
        //their name, level, attributes, current experience, and
        //the amount of experience needed for the next level.
        //It lets the player view his/her status until she presses
        //x and enter when he/she is finished, and returns to the
        //map menu
        
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
void Talk(Town& town)
	{
		//postcondition: prints out what people are saying at the current town.

		char junkCh;

		cout<<"****************************************************"<<endl;
		cout<<town.getConversation();
		cout<<"**********************MESSAGES**********************"<<endl;
		cout<<"Press X and enter when done:  ";
		cin>>junkCh;
		cout<<endl<<endl;
	}
void GameOver(bool win)
    {
        //postcondition:  This function displays an ending message when the game
        //has ended, depending on whether the user has ended the game by winning,
        //or whether he/she has ended it by losing.
        
        if(win)
            {
                cout<<"Congratulations, you have defeated the evil monsters of the land,"
                    <<endl<<"saved the people, and allowed peace to flourish!"<<endl
                    <<"You win!"<<endl;
            }
        else
            {
                cout<<"You failed to complete your mission of the conquest of evil."<<endl
                    <<"The monsters continue to ravish the land and devour civilization"
                    <<endl<<"You lose!"<<endl;
            }
    }
    
