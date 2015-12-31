#ifndef _CHTYPES_H
#define _CHTYPES_H

//MikeLukas -p2prog03-    -chtypes1.h-
//This header holds two class definitions, one for the monster class,
//and one for the player class.

//Class definition for a player.  This class holds all the values of all the
//necessary player attributes and all of the operations that a player will
//need to do such as move up a level, access attributes, move coordinates,
//etc. 

#include "apstring.h"

const double HPRATE = .65;   //
const double BIGRATE = .45;     //rates to increase attributes by at level up
const double FLATRATE = .2;      //
const int    SPRATE = 10;       //
const double NEXTRATE = .85; //

//attributes a player starts with
const int BEGINHP = 25;
const int BEGINAP = 10;
const int BEGINDP = 7;
const int BEGINSP = 3;

struct Point //holds x y coordinates on the map
    {
        int x;
        int y;
    };

//Player Class Definition--------------------------------------------// 
class Player
    {
        private:
            int HP;             //current hit points (life)
            int maxHP;          //maximum hit points
            int AP;             //attack power
            int DP;             //defense power
            int SP;             //speed points
                        
            apstring playerName;            
            
            int expPoints;      //current experience points
            int expToNext;      //exp. points needed to advance level
            int lvl;            //current level
            Point Coords;       //Holds the players coordinates on the map
            
        public:
            Player();
            Player(int, int, int, int, int);
                        
            void LevelUp();             
            void AddExp(int);
            Point GetCoords() const;
            void SetCoords(int, int);
            void ChangeHP(int);
                        
            apstring ShowName() const;
            int Damage() const;
            int Defense() const;
            int Health() const;
            int MaxHealth() const;
            int Speed() const;
            int Money() const;
            int Level() const;
            int NumExpPts() const;      
            int NumToNext() const;
    };

//free function prototypes-------------------------------------------// 

bool Validate(char answer);
bool Validate(int answer, int numChoices);

//----------Monster Class--------------------------------------------//
//Class definition for a monster.  This class holds all the attributes
//and operations a monster will need, such as HP changing and accessing
//various attributes of the monster from in the program
    
class Monster
    {
        private:
            int mHP;                //current hit points (life)
            int mmaxHP;         //maximum hit points
            int AP;             //attack power
            int DP;             //defense percentage
            int SP;             //speed points
            int expPoints;          //number of expPoints player gets 
                                    //from beating monster
            apstring monsterName;
                        
        
        public:
            Monster();
            void SetAttributes(int, int, int, int, int, apstring&);
            void ChangeHP(int);
                    
            apstring ShowName() const;
            int Damage() const;
            int Defense() const;
            int mHealth() const;
            int mMaxHealth() const;
            int Speed() const;
            int Experience() const;
    };

#endif