#ifndef _PLAYER_H
#define _PLAYER_H

//MikeLukas -p2prog03-    -player.h-
//Class definition for a player.  This class holds all the values of all the
//necessary player attributes and all of the operations that a player will
//need to do such as move up a level, access attributes, move coordinates,
//etc. 

#include <map>
#include <string>
#include <vector>
#include "character.h"
#include "equipment.h"
#include "point.h"

using std::map;
using std::string;
using std::vector;

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
const int BEGINGOLD = 1200;

const Point STARTPOS(29, 8);

//Player Class Definition----------------------------------------------------// 
class Player : public Character
    {
        private:
            int expToNext;      //exp. points needed to advance level
            int lvl;            //current level
            Point Coords;       //Holds the players coordinates on the map
            

            //Inventory; maps for fast lookup of quantity
            map<const Equipment*, EquipmentLine> weapons;
            map<const Equipment*, EquipmentLine> armor;
            map<const Equipment*, EquipmentLine> items;

            map<EquipType, const Equipment*> currentEquipped;

            void initStartingEquipment();

			void dequipCurrent(EquipType);
			void equip(const Equipment*);

        public:
            Player();

            void LevelUp();
            void AddExp(int);
            void AddMoney(int);
            Point GetCoords() const;
            void SetCoords(int, int);

            void Buy(const EquipmentLine*);
            void Sell(const EquipmentLine*);
                        
            int Level() const;
            int NumToNext() const;

            map<const Equipment*, EquipmentLine>& getInventoryFor(const EquipType);
            vector<EquipmentLine*>* getWeaponsAndArmorAsVector();
            vector<EquipmentLine*>* getItemsAsVector();
            EquipmentLine& getEquipmentLineFromInventoryFor(const Equipment*);

            const Equipment* getCurrentEquipped(EquipType);

            void useEquipment(const Equipment*, Character&);
            void apply(const Equipment*);
    };

#endif
