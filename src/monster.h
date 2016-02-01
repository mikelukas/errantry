#ifndef _MONSTER_H
#define _MONSTER_H

//Mike Lukas -p2prog03-             - monster.h -
//Class definition for a monster.  This class holds all the values of all the
//necessary player attributes and all of the operations that a player will
//need to do such as equip an unequip items, add items to their inventory, 
//remove items from their inventory, buy and sell items, swap items or spells
//if there inventory is full, and move up a level.

#include "spell.h"
#include "apstring.h"
    
class Monster
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
            int expPoints;          //number of expPoints player gets 
                                    //from beating monster
            elemType weakness;      //holds numerical elemental weakness of
                                    //monster, based on the type held by
                                    //a spell
            apstring monsterName;
            SpellType Spell;
            
        
        public:
            Monster();
            Monster(int, int, int, int, int, int, int, int, elemType&,
                    apstring&, SpellType&);
            void ChangeHP(int);
            void ChangeMP(int);
            
            int Damage() const;
            int Defense() const;
            int Health() const;
            int MEnergy() const;
            int MDefense() const;
            int Speed() const;
            int Money() const;
            int MDamage() const;
            int Weakness() const;
    };

#endif
