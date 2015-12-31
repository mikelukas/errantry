#ifndef _CHTYPES_H
#define _CHTYPES_H

//MikeLukas -p2prog03-    -chtypes.h-
//This header holds two class definitions, one for the monster class,
//and one for the player class.

//Class definition for a player.  This class holds all the values of all the
//necessary player attributes and all of the operations that a player will
//need to do such as equip an unequip items, add items to their inventory, 
//remove items from their inventory, buy and sell items, swap items or spells
//if there inventory is full, and move up a level. 

#include "apvector.h"
#include "apstring.h"

const int    MAXEQUIPMENT = 5;
const double HPRATE = .65;   //
const double MPRATE = .55;      //
const double BIGRATE = .45;      //rates to increase attributes by
const double FLATRATE = .2;      //
const int    SPRATE = 10;       //
const double NEXTRATE = .85; //

//attributes a player starts with
const int BEGINHP = 50;
const int BEGINMP = 30;
const int BEGINAP = 15;
const int BEGINDP = 20;
const int BEGINMDP = 20;
const int BEGINSP = 3;
const int BEGINGOLD = 0;

enum type {weapon, armor, item};
enum elemType {fire, air, earth, water, none};

//Structs to hold item and spell data----------------------------------------//
struct SpellType
    {
        int MAP;            //attack power of spell
        int cost;           //cost in MP
        apstring name;      //name of spell
        elemType element;   //basic elemental type of spell
    };
    
struct EquipType
    {
        int statUp;     //how much additional AP/DP/HP/MP given by item
        int cost;   //price the item sells for
        int quantity;
        type type;
        apstring name;
    };

struct Point
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
            int MP;             //magic points (energy for spells)
            int maxMP;          //maximum magic points 
            int AP;             //attack power
            int DP;             //defense percentage
            int MDP;            //magic defense percentage
            int SP;             //speed points
            int gold;
            
            apstring playerName;            
            int spellCount;     //number of spells player has
            int weapCount;      //number of weapons player has
            int armCount;       //amount of armor player has
            int itemCount;      //number of items player has
            int expPoints;      //current experience points
            int expToNext;      //exp. points needed to advance level
            int lvl;            //current level
            Point Coords;       //Holds the players coordinates on the map
            EquipType eArmor;   //holds currently equipped armor
            EquipType eWeapon;  //holds currently equipped weapon
            apvector<SpellType> Spells;
            apvector<EquipType> Weapons;
            apvector<EquipType> Armor;
            apvector<EquipType> Items;
            
            int GetItemCount(EquipType&) const;
            bool FindItem(apvector<EquipType>&, apstring&, int&, int) const;
            bool FindSpell(apvector<SpellType>&, apstring&, int&, int) const;
            void InitializeInventory(apvector<EquipType>&, type equipType);
        public:
            Player();
            Player(int, int, int,int, int, int, int, int);
                        
            void AddSpell(SpellType&);
            void AddEquip(apvector<EquipType>&, EquipType&);
            void RemoveEquip(apvector<EquipType>&, EquipType&);
            void OverwriteSpell(SpellType&);            
            void OverwriteEquip(apvector<EquipType>&, EquipType&);
            void LevelUp();             
            
            void ChangeCount(EquipType&, char); 
            void EquipItem(EquipType&);
            void Unequip(EquipType&);
            void BuyItem(apvector<EquipType>&, EquipType&, int);
            void SellItem(apvector<EquipType>&, EquipType&);
            void AddExp(int);
            void AddMoney(int);
            Point GetCoords() const;
            void SetCoords(int, int);
            void MoveCoords(int, int);
            void ChangeHP(int);
            void ChangeMP(int);
            
            int Damage() const;
            int Defense() const;
            int Health() const;
            int MEnergy() const;
            int MDefense() const;
            int Speed() const;
            int Money() const;
            int MDamage(SpellType&);
            int Level() const;
            int NumExpPts() const;      
            int NumToNext() const;
    };

//free function prototypes-------------------------------------------// 

bool Validate(char answer);
bool Validate(int answer, int numChoices);

//----------Monster Class--------------------------------------------//
//Class definition for a monster.  This class holds all the values of all the
//necessary player attributes and all of the operations that a player will
//need to do such as equip an unequip items, add items to their inventory, 
//remove items from their inventory, buy and sell items, swap items or spells
//if there inventory is full, and move up a level.
    
class Monster
    {
        private:
            int HP;             //current hit points (life)
            int maxHP;          //maximum hit points
            int AP;             //attack power
            int DP;             //defense percentage
            int MDP;            //magic defense percentage
            int SP;             //speed points
            int gold;
            int expPoints;          //number of expPoints player gets 
                                    //from beating monster
            elemType weakness;      //holds numerical elemental weakness of
                                    //monster, based on the type held by
                                    //a spell
            apstring monsterName;
                        
        
        public:
            Monster();
            Monster(int, int, int, int, int, int, int, elemType&,
                    apstring&);
            void ChangeHP(int);
                    
            int Damage() const;
            int Defense() const;
            int Health() const;
            int MDefense() const;
            int Speed() const;
            int Money() const;
            int Weakness() const;
            int Experience() const;
    };

#endif
