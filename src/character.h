#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <string>
#include "equipment.h"

using std::string;

//Mike Lukas -p2prog03-         - character.h - 
//Class definition for a character.  This class holds all of the basic
//values a character will need; health points, magic points, attack
//points, defense points, magic defense points, speed points, and 
//money.  
    
class Character
    {
        protected:
            int HP;             //current hit points (life)
            int maxHP;          //maximum hit points
            int MP;				//current magic points (needed to cast spells)
            int maxMP;			//maximum magic points
            int AP;             //attack power
            int DP;             //defense percentage
            int MDP;			//magic defense percentage
            int SP;             //speed points

            string name;

            int gold;
            int expPoints;      //number of expPoints character carries
                    
            void AddStats(const StatMod&);
			void SubStats(const StatMod&);

        public:
            Character(int, int, int, int, int, int, int, int);
            virtual ~Character() {};

            void ChangeHP(int);
            void ChangeMP(int);
            
            string ShowName() const;

            int Damage() const;
            int Defense() const;
            int MagicDefense() const;
            int Health() const;
            int MaxHealth() const;
            int getMP() const;
            int MaxMP() const;
            int Speed() const;
            int Money() const;
            int ExpPts() const;

            virtual void apply(const Equipment*) = 0;
    };

#endif
