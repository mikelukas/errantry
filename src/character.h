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
//Constructors-------------------------------------------------------// 
Character::Character()
    : HP(1),
      maxHP(1),
      AP(0),
      DP(0),
      SP(0),
      gold(0)
    {
        //attribute variables initialized in intializer list
    }
Character::Character(int hpVar, int apVar, int dpVar, int spVar, int money)
    { 
        //postcondition:  a character's attributes have been set to
        //the attributes given
        
        HP= hpVar;
        maxHP = hpVar;
        AP = apVar;
        DP = dpVar;
        SP = spVar;
        gold = money;
    }
//Public Member functions--------------------------------------------//
void Character::ChangeHP(int hpChange)
    {
        //postcondition:  HP value of character altered by the value
        //sent to the function; if damage is done, a negative value
        //is added to HP, if health is gained, a positive value is
        //added to HP
        
        HP = HP + hpChange;
    }

//accessor functions-------------------------------------------------//

int Character::Damage() const
    {
        //postcondition:  returns the amount of damage the player can do (AP)
        return AP;
    }

int Character::Defense() const
    {
        //postcondition:  returns user's defense points
        return DP;
    }

int Character::Health() const
    {
        //postcondition:  returns user's health points
        return HP;
    }

int Character::Speed() const
    {
        //postcondition:  returns the character's speed points
        return SP;
    }

int Character::Money() const
    {
        //postcondition:  returns amount of gold the character has
        return gold;
    }
#endif
