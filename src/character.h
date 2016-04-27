#ifndef _CHARACTER_H
#define _CHARACTER_H

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
            int gold;
                    
        public:
            Character();
            Character(int, int, int, int, int);
            void ChangeHP(int);
            
            int Damage() const;
            int Defense() const;
            int Health() const;
            int Speed() const;
            int Money() const;  
    };

#endif
