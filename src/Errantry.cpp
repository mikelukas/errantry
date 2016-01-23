//Mike Lukas - p2prog03-      -Errantry.cpp-

#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include "apstring.h"
#include "apvector.h"
#include "chtypes.h"

const int MAXMONSTERS = 20;
const int MAXBOSSES = 8;
const int MAXSIZE = 50;
const Point STARTPOS = {29, 8};
 
enum State {overworld, town, battle};

bool GetMap(apvector<apstring>& Map);
bool GetMonsters(apvector<Monster>& monsters);
bool MainGame(Player& player, apvector<apstring>& Map,
              apvector<Monster>& monsters, Point& startPos);
void DisplayMenu(apvector<apstring>& Map, char& choice, 
                 State& location);
void mapChoices(apvector<apstring>& Map, int& choice);
void townChoices(int& choice)
void battleChoices(int& choice);
bool TestChoice(apvector<apstring>& Map, Player& player,
				apvector<Monster>& monsterList, 
				apvector<Monster>& Bosses, Monster& monster, 
				char choice, State& location, bool win, char& landscape,
				int& nextBoss,
				int& townNum)
void Move(apvector<apstring>& Map, Player& player, 
          apvector<Monster>& monsterList, apvector<Monster>& Bosses,
          State& location, Monster& monster, char& landscape,
          int nextBoss);
void Fight(Player& player, Monster& monster);                
void PrintMap(const apvector<apstring> &Map);
void GameOver(bool win);

int main()
    {
        bool mapFound, monsFound, win;
        Player player;
        Point startPos;
        apvector<Monster> monsters(MAXMONSTERS);
        apvector<Monster> Bosses(MAXBOSSES)
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
bool GetMap(apvector<apstring>& Map)
    {
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
        int choice, nextBoss = 0, townNum = 0;
        char landscape;
        bool win = false, dead = false, leave = false;
        State location = overworld;
        Monster monster;
        
        while(dead == false && leave == false && win == false);
            {
                DisplayMenu(Map, choice, location);
                leave = TestChoice(Map, player, monsters, monster,
                				   Bosses, choice, location, win
                                   landscape, nextBoss, townNum);
                __clrscr();
            }
        return win;
    }
    
void DisplayMenu(apvector<apstring>& Map, int& choice, 
                 State& location)
    {
        cout<<"0    1     2     3     4     5    6"<<endl;
        gotoxy(0,22);
        cout<<"**********************MESSAGES**********************"
            <<endl<<endl<<endl<<endl;
        switch(location)
            {
                case overworld:
                    mapChoices(Map, choice);
                    break;
                case town:
                    townChoices(choice);
                    break;
                case bossBattle:
                case battle:
                    battleChoices(choice);
                    break;
            };
        
    }

void mapChoices(apvector<apstring>& Map, int& choice)
    {
        
        __gotoxy(0,1);
        PrintMap(Map);
        __gotoxy(30,0);
        cout<<"*****Choices*****";
        __gotoxy(30,1);
        cout<<"*1)Move         *";
        __gotoxy(30,2);
        cout<<"*2)Inventory    *";
        __gotoxy(30,3);
        cout<<"*3)Status       *";
        __gotoxy(30,4);
        cout<<"*4)Equip Weapons*";
        __gotoxy(30,5);
        cout<<"*5)Equip Armor  *";
        __gotoxy(30,6);
        cout<<"*6)Use Items    *";
        __gotoxy(30,7);
        cout<<"*7)Quit Game    *";
        __gotoxy(30,8);
        cout<<"*****************";
        do
         {
            __gotoxy(0,23);
            cout<<"Please choose an option:  "<<endl;
            cin>>choice;
         }while(choice, 7);
        
    }
void townChoices(int& choice)
    {
        __gotoxy(30,0);
        cout<<"*****Choices*****";
        __gotoxy(30,1);
        cout<<"*1)Goto a Shop  *";
        __gotoxy(30,2);
        cout<<"*2)Magic Lessons*";
        __gotoxy(30,3);
        cout<<"*3)Talk         *";
        __gotoxy(30,4);
        cout<<"*4)Leave Town   *";
        __gotoxy(30,5);
        cout<<"*****************";
        do
         {
            __gotoxy(0,23);
            cout<<"Please choose an option:  ";
            cin>>choice;
         }while(choice, 4);
    }
void battleChoices(int& choice)
    {
        __gotoxy(30,0);
        cout<<"*****Choices*****";
        __gotoxy(30,1);
        cout<<"*1)Fight        *";
        __gotoxy(30,2);
        cout<<"*2)Cast Spell   *";
        __gotoxy(30,3);
        cout<<"*3)Use Item     *";
        __gotoxy(30,4);
        cout<<"*4)Run          *";
        __gotoxy(30,5);
        cout<<"*****************";
        do
         {
            __gotoxy(0,23);
            cout<<"Please choose an option:  "<<endl;
            cin>>choice;
         }while(Validate(choice, 4);
    }
bool TestChoice(apvector<apstring>& Map, Player& player, 
                apvector<Monster>& monsterList, 
                apvector<Monster>& Bosses, Monster& monster,
                int choice, State& location, bool win, char& landscape,
                int& nextBoss, int& townNum)
    {
        bool leave = false;
        
        switch(location)
            {
                case map:
                    switch(choice)
                        {
                            case 1:
                                Move(Map, player, monsterList, Bosses,
                                     location, monster, landscape,
                                     nextBoss);
                                break;
                            case 2:
                                PrintInventory(player);
                                break;
                            case 3:
                                PrintStatus(player);
                                break;
                            case 4:
                                EquipWeapons(player);
                                break;
                            case 5:
                                EquipArmor(player);
                                break;
                            case 6:
                                UseItem(player);
                                break;
                            case 7:
                                leave = true;
                                break;
                        }
                    break;
                case town:
                    switch(choice)
                        {
                            case 1:
                                Shop(player, townNum);
                                break;
                            case 2:
                                LearnMagic(player, townNum);
                                break;
                            case 3:
                                Talk(player, townNum);
                                break;
                            case 4:
                                location = map;
                                break;
                        }
                    break;
                case bossBattle
                    switch(choice)
                        {
                            case 1:
                                Fight(player, monster);
                                break;
                            case 2;
                                cout<<"Can't run from boss fight!"<<endl
                                break;
                        }
                    if(monster.Health() == 0)
                        {
                            if(nextBoss == 8)
                                win = true;
                            player.AddExp(monster.Experience());
                            location = map; 
                            nextBoss++;
                        }
                    break;
                case battle:
                    switch(choice)
                        {
                            case 1:
                                Fight(player, monster);
                                break;
                            case 2:
                                UseMagic(player, monster);
                                break;
                            case 3:
                                UseItem(player);
                                break;
                            case 4:
                                location = map;
                                break;
                        }
                    BattleStatus(player, monster);
                    if(monster.Health() = 0)
                        {
                            player.AddExp(monster.Experience());
                            location = map;
                        }
                    break;
            }
        if(player.Health() = 0)
            leave == true;
        return leave;
    }
void Move(apvector<apstring>& Map, Player& player, 
          apvector<Monster>& monsterList, apvector<Monster>& Bosses,
          State& location, Monster& monster, char& landscape,
          int nextBoss)
    {
        int x, y, randMons;
        Point Coords;
        
        __gotoxy(0,23);
        cout<<"Please choose an x coordinate on the map using"<<endl;
        cout<<"method described in the instructions:  ";
        cin>>x;
        __gotoxy(0,23);
        cout<<"                                              ";
        __gotoxy(0,24);
        cout<<"                                              ";
        __gotoxy(0,23);
        cout<<"Now, please choose a y coordinate normally:  "
        cin>>y;
        
        player.SetCoords(x,y);
        Coords = player.GetCoords();
        landscape = Map[Coords.x][Coords.y]
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
