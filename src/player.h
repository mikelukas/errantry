#ifndef _PLAYER_H
#define _PLAYER_H

//MikeLukas -p2prog03-    -player.h-
//Class definition for a player.  This class holds all the values of all the
//necessary player attributes and all of the operations that a player will
//need to do such as move up a level, access attributes, move coordinates,
//etc. 

#include <string>
#include <unordered_map>
#include "equipment.h"
#include "point.h"

using std::string;
using std::unordered_map;

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
const int BEGINGOLD = 0;

const Point STARTPOS(29, 8);

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
                        
            string playerName;
            
            int expPoints;      //current experience points
            int expToNext;      //exp. points needed to advance level
            int lvl;            //current level
            Point Coords;       //Holds the players coordinates on the map
            
            //Inventory; maps for fast lookup of quantity
            unordered_map<const Equipment*, EquipmentLine> weapons;
            unordered_map<const Equipment*, EquipmentLine> armor;
            unordered_map<const Equipment*, EquipmentLine> items;

            unordered_map<const Equipment*, EquipmentLine>& getInventoryFor(const EquipType);

        public:
            Player();
            Player(int, int, int, int, int, int);

            void LevelUp();
            void AddExp(int);
            void AddMoney(int);
            Point GetCoords() const;
            void SetCoords(int, int);
            void ChangeHP(int);

            void Buy(const EquipmentLine*);
                        
            string ShowName() const;
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

#endif
