//Mike Lukas - p2prog03-      -Errantry.cpp-

#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include "apstring.h"
#include "apvector.h"
#include "chtypes.h"

const int MAXMONSTERS = 20;
const int MAXSIZE = 50;
const Point STARTPOS = {29, 8};
 
enum State {overworld, town, battle};

bool GetMap(apvector<apstring>& Map);
bool GetMonsters(apvector<Monster>& monsters);
bool MainGame(Player& player, apvector<apstring>& Map,
              apvector<Monster>& monsters, Point& startPos);
void DisplayMenu(apvector<apstring>& Map, char& choice, 
                 State& location);
void PrintMap(const apvector<apstring> &Map);
void GameOver(bool win);

int main()
    {
        bool mapFound, monsFound, win;
        Player player;
        Point startPos;
        apvector<Monster> monsters(MAXMONSTERS);
        apvector<apstring> Map(MAXSIZE);
        
        mapFound = GetMap(Map);
        
        if(mapFound != false)
            {
                GetMonsters(monsters);
                if(monsFound != false)
                    {
                        cout<<"Monsters found!";
                        win = MainGame(player, monsters, STARTPOS);
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
              apvector<Monster>& monsters, Point& StartPos)
    {
        int choice, townNum = 0;
        bool win = false, dead = false, leave = false;
        State location = overworld;
        
        while(dead == false && leave == false && win == false);
            {
                DisplayMenu(Map, choice, location);
                leave = TestChoice(player, choice, location, win
                                   townNum);
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
bool TestChoice(Player& player, Monster& monster, char choice,
                State& location, bool win, int& townNum)
    {
        bool leave = false;
        
        switch(location)
            {
                case map:
                    switch(choice)
                        {
                            case 1:
                                Move(player, location);
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
                    if(monster.Health() == 0)
                        
                                                
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
