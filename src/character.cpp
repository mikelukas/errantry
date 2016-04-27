#include "character.h"

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
