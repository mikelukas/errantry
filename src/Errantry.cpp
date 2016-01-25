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
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <math.h>
#include "apstring.h"
#include "apvector.h"
#include "chtypes1.h"

using std::ifstream;
using std::setw;

using std::cout;
using std::cin;
using std::endl;

const int MAXMONSTERS = 10;
const int MAXBOSSES = 8;
const int MAXSIZE = 50;
const Point STARTPOS = {29, 8};
 
enum State {overworld, bossBattle, battle};

void Intro();
bool GetMap(apvector<apstring>& Map);
bool GetMonsters(apvector<Monster>& monsters);
bool MainGame(Player& player, apvector<apstring>& Map,
              apvector<Monster>& monsters, Point& startPos);
void DisplayMenu(apvector<apstring>& Map, char& choice, 
                 State& location);
void mapChoices(apvector<apstring>& Map, int& choice);
void battleChoices(int& choice);
bool TestChoice(apvector<apstring>& Map, Player& player, 
                apvector<Monster>& monsterList, 
                apvector<Monster>& Bosses, Monster& monster,
                int choice, State& location, bool win, char& landscape,
                int& nextBoss);
void Move(apvector<apstring>& Map, Player& player, 
          apvector<Monster>& monsterList, apvector<Monster>& Bosses,
          State& location, Monster& monster, char& landscape,
          int nextBoss);
void Fight(Player& player, Monster& monster);
void PrintMap(const apvector<apstring> &Map);
void PrintStatus(Player& player);
void GameOver(bool win);

int main()
    {
        bool mapFound, monsFound, win;
        Player player;
        Point startPos;
        apvector<Monster> monsters(MAXMONSTERS);
        apvector<Monster> Bosses(MAXBOSSES);
        apvector<apstring> Map(MAXSIZE);
        
        mapFound = GetMap(Map);
        
        if(mapFound != false)
            {
                GetMonsters(monsters);
                GetMonsters(Bosses);
                if(monsFound != false)
                    {
                        cout<<"Monsters found!";
                        win = MainGame(player, Map, monsters, STARTPOS);
                        GameOver(win);
                    }
                else
                    cout<<"ERROR:  '../dat/Monster.dat' not found!"<<endl;
            }
        else
            cout<<"ERROR:  '../dat/Map1.dat' not found!"<<endl;
                
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
bool GetMap(apvector<apstring>& Map)
    {
        //Postcondition:  the world map for the game is retrieved from
        //a file for use in the program.
        int pos = 0;
        bool found = false;
        
        ifstream inFile("../dat/Map1.dat");
        
        if(inFile)
            {   
                while(pos<MAXSIZE && getline(inFile, Map[pos]))
                    {
                        pos++;
                    }
                Map.resize(pos);
                found = true;
                cout<<":  Map found."<<endl;                
            }
        return found;       
    }
bool GetMonsters(apvector<Monster>& monsters)
    {
        //Postcondition:  the attributes of each monster are retrieved
        //from a file for use in the program
        
        int pos = 0, hp, ap, dp, mdp, sp, gold, expPts;
        bool found = false;
        elemType weak;
        apstring name;
                
        ifstream inFile("../dat/Monster.dat");
        
        if(inFile)
            {
                while(pos<MAXMONSTERS && getline(inFile, name) &&
                      inFile>>hp>>ap>>dp>>mdp>>sp>>gold>>expPts
                            >>weak)
                    {
                        monsters[pos](hp, mp, ap, dp, mdp, sp, gold,
                                      expPts, weak);
                        pos++;
                    }
                monsters.resize(pos);
                found = true;
                cout<<":  Monsters found."<<endl;
            }
        return found;
    }
bool MainGame(Player& player, apvector<apstring>& Map, 
              apvector<Monster>& monsters, apvector<Monster>& Bosses,
              Point& StartPos)
    {
        //This function controls the main game.  It displays the
        //appropriate menus for the game's state(battle or map (overworld))
        //and also indirectly carries out all of the actions a user may
        //perform by calling the functions that perform those actions.
        
        int choice, nextBoss = 0;
            //nextboss holds the index of the next boss to be fought in
            //'Bosses'
        char landscape; //holds the current type of landscape the
                        //the player is standing on
        bool win = false, leave = false;
        State location = overworld;  //holds the state of the game
        player.SetCoords(StartPos.x, StartPos.y);
        Monster monster;     //will hold the monster to be fought if the 
                             //user encounters one while moving
        
        while(leave == false && win == false);
            {
                DisplayMenu(Map, choice, location);
                leave = TestChoice(Map, player, monsters, monster, 
                                   Bosses, choice, location, win,
                                   landscape, nextBoss);
            }
        return win;
    }
    
void DisplayMenu(apvector<apstring>& Map, int& choice, 
                 State& location)
    {   
        //postcondition:  The menu for the current state ofthe game 
        //(battle or map(overworld) ) is displayed, and the user may
        //choose an action from one of the options
        
        cout<<"0    1     2     3     4     5    6"<<endl;
        cout<<"**********************MESSAGES**********************"
            <<endl<<endl<<endl<<endl;
        switch(location)
            {
                case overworld:
                    mapChoices(Map, choice);
                    break;
                case bossBattle:
                case battle:
                    battleChoices(choice);
                    break;
            };
        
    }

void mapChoices(apvector<apstring>& Map, int& choice)
    {
        PrintMap(Map);
        cout<<"*****Choices*****";
        cout<<"*1)Move         *";
        cout<<"*3)Status       *";
        cout<<"*7)Quit Game    *";
        cout<<"*****************";
        do
         {
            cout<<"Please choose an option:  "<<endl;
            cin>>choice;
         }while(choice, 3);
        
    }

void battleChoices(int& choice)
    {
        cout<<"*****Choices*****";
        cout<<"*1)Fight        *";
        cout<<"*4)Run          *";
        cout<<"*****************";
        do
         {
            cout<<"Please choose an option:  "<<endl;
            cin>>choice;
         }while(Validate(choice, 2));
    }
bool TestChoice(apvector<apstring>& Map, Player& player, 
                apvector<Monster>& monsterList, 
                apvector<Monster>& Bosses, Monster& monster,
                int choice, State& location, bool win, char& landscape,
                int& nextBoss)
    {
        //postcondition:  the user-chosen action chose at the current
        //menu the player is at is carried out.  For instance, if the
        //user chooses move from the map menu, that action is
        //performed.  
        bool leave = false;  //holds whether or not the user chose quit
        
        switch(location)
            {
                case map:  //map menu
                    switch(choice)
                        {
                            case 1:
                                Move(Map, player, monsterList, Bosses,
                                     location, monster, landscape,
                                     nextBoss);
                                break;
                            case 2:
                                PrintStatus(player);
                                break;
                            case 3:
                                leave = true;
                                break;
                        }
                    break;
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
                    if(monster.Health() == 0)  //if boss is dead
                        {                      //find the next on the list
                                               //add exp. pts. from the 
                                               //boss.
                            if(nextBoss == 8)
                                win = true;
                            player.AddExp(monster.Experience());
                            location = map; 
                            nextBoss++;
                        }
                    break;              
                case battle:   //battle menu
                    switch(choice)
                        {
                            case 1:
                                Fight(player, monster);
                                break;
                            case 2:
                                location = map;
                                break;
                        }
                    BattleStatus(player, monster);
                    if(monster.Health() <= 0)
                        {
                            player.AddExp(monster.Experience());
                            location = map;
                        }
                    break;
            }
        if(player.Health() <= 0)  //if player dies, leave game
            leave == true;
        return leave;
    }
void Move(apvector<apstring>& Map, Player& player, 
          apvector<Monster>& monsterList, apvector<Monster>& Bosses,
          State& location, Monster& monster, char& landscape,
          int nextBoss)
    {
        //postcondition:  The player's position on the map will be moved
        //to the coordinates he/she specifies, if they are on the map.
        //If they are not, he/she will be prompted to re-enter them.
        //This function also handles whether or not a player encounters
        //an enemy or moves to a cave (marked with 'C') while he/she is moving
        
        int x, y, randMons;
        Point Coords;
        
        cout<<"Please choose an x coordinate on the map using"<<endl;
        cout<<"method described in the instructions:  ";
        cin>>x;
        cout<<"                                              ";
        cout<<"                                              ";
        cout<<"Now, please choose a y coordinate normally:  ";
        cin>>y;
        
        player.SetCoords(x,y);
        Coords = player.GetCoords();
        landscape = Map[Coords.x][Coords.y];
        Map[Coords.x][Coords.y] = 'X';
        
        if(Map[Coords.x][Coords.y] == 'C')
            {
                location = bossBattle;
                monster = Bosses[nextBoss];
            }
        else
            {
                numRandMons = random(20);
                if(randMons < 10)
                    {
                        monster = monsterList[randMons];
                        location = battle;
                    }
                
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
        
        int pDamage, pDefense, mDamage, mDefense;
        
        if(player.Defense() > 10)
            pDefense = (player.Defense()/10) * monster.Damage();
        else
            pDefense = player.Defense() * monster.Damage();
        
        if(monster.Defense() > 10)
            mDefense = (monster.Defense()/10) * player.Damage();
        else
            mDefense = monster.Defense() * monster.Damage();
            
        pDamage = player.Damage() - mDefense;
        mDamage = monster.Damage() - pDefense;
        if(player.Speed() >= monster.Speed())
            {
                monster.ChangeHP(-1 * pDamage);
                if(monster.Health() <= 0)
                    {
                        monster.ChangeHP(-1 * (0-monster.Health()));
                        return;
                    }
                player.ChangeHP(-1 * mDamage);
            }
        else
            {
                player.ChangeHP(-1 * mDamage);
                if(player.Health() <= 0)
                    {
                        player.ChangeHP(-1 * (0-player.Health()));
                        return;
                    }
                monster.ChangeHP(-1 * pDamage); 
            }
    }           
void PrintMap(const apvector<apstring>& Map)
    {
        int row, col, numrows, numcols;

        numrows=Map.length();
        numcols=Map[0].length();

        for(row=0; row<numrows; row++)
            {
                cout<<row;
                for(col=0; col<numcols; col++)
                    {
                        cout<<Map[row][col];
                    }
                cout<<endl;
            }
        cout<<endl<<endl;
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
    
