#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <string>

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
            int AP;             //attack power
            int DP;             //defense percentage
            int SP;             //speed points

            string name;

            int gold;
            int expPoints;      //number of expPoints character carries
                    
        public:
            Character(int, int, int, int, int, int);
            void ChangeHP(int);
            
            string ShowName() const;

            int Damage() const;
            int Defense() const;
            int Health() const;
            int MaxHealth() const;
            int Speed() const;
            int Money() const;
            int ExpPts() const;
    };

#endif
