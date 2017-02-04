#ifndef _PLAYER_H
#define _PLAYER_H

//MikeLukas -p2prog03-    -player.h-
//Class definition for a player.  This class holds all the values of all the
//necessary player attributes and all of the operations that a player will
//need to do such as move up a level, access attributes, move coordinates,
//etc. 

#include <string>
#include <vector>
#include "character.h"
#include "point.h"

using std::map;
using std::set;
using std::string;
using std::vector;

const double HPRATE = .65;   //
const double MPRATE = .55;	  //
const double BIGRATE = .45;     //rates to increase attributes by at level up
const double FLATRATE = .2;      //
const double LOWRATE = .1;      //
const int    SPRATE = 10;      //
const double NEXTRATE = .85; //

//attributes a player starts with
const int BEGINHP = 25;
const int BEGINMP = 15;
const int BEGINAP = 10;
const int BEGINDP = 7;
const int BEGINMDP = 5;
const int BEGINSP = 3;
const int BEGINGOLD = 1200;

const Point STARTPOS(29, 8);

enum LvlUpOpt { EVEN, ATK, DEF, MAG_DEF };

//Player Class Definition----------------------------------------------------// 
class Player : public Character
    {
        private:
            int expToNext;      //exp. points needed to advance level
            int lvl;            //current level
            Point Coords;       //Holds the players coordinates on the map

            map<EquipType, const Equipment*> currentEquipped;

            void initStartingEquipment();

        public:
            Player();

            void setName(const string&);

            void LevelUp(LvlUpOpt);
            void AddExp(int);
            void AddMoney(int);

            Point GetCoords() const;
            void SetCoords(int, int);

            void Buy(const EquipmentLine*);
            void Buy(const SpellTemplate*);
            void Sell(const EquipmentLine*);
                        
            int Level() const;
            int NumToNext() const;

            EquipmentLine& getEquipmentLineFromInventoryFor(const Equipment*);

            vector<const SpellTemplate*>* getSpellsForLocale(SpellLocale locale) const;

            const Equipment* getCurrentEquipped(EquipType);

            void dequipCurrent(EquipType);
            void equip(const Equipment*);
    };

#endif
