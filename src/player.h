#ifndef _PLAYER_H
#define _PLAYER_H

//MikeLukas -p2prog03-    -player.h-
//Class definition for a player.  This class holds all the values of all the
//necessary player attributes and all of the operations that a player will
//need to do such as move up a level, access attributes, move coordinates,
//etc. 

#include "apstring.h"
#include "point.h"

const double HPRATE = .65;   //
const double BIGRATE = .45;      //rates to increase attributes by
const double FLATRATE = .2;      //
const int    SPRATE = 10;       //
const double NEXTRATE = .85; //

//attributes a player starts with
const int BEGINHP = 50;
const int BEGINAP = 15;
const int BEGINDP = 20;
const int BEGINSP = 3;
const int BEGINGOLD = 0;

//Player Class Definition----------------------------------------------------// 
class Player
    {
        private:
            int HP;             //current hit points (life)
            int maxHP;          //maximum hit points
            int AP;             //attack power
            int DP;             //defense percentage
            int SP;             //speed points
            int gold;

            apstring playerName;
            int expPoints;      //current experience points
            int expToNext;      //exp. points needed to advance level
            int lvl;            //current level
            Point Coords;       //Holds the players coordinates on the map
            
        public:
            Player();
            Player(int, int, int, int, int, int);

            void LevelUp();
            void AddExp(int);
            void AddMoney(int);
            Point GetCoords() const;
            void SetCoords(int, int);
            void MoveCoords(int, int);
            void ChangeHP(int);

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

//free function prototypes---------------------------------------------------// 

bool Validate(char answer);
bool Validate(int answer, int numChoices);
