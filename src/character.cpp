#include "character.h"

//Constructors-------------------------------------------------------//
Character::Character(int hpVar, int apVar, int dpVar, int spVar, int money, int expPoints)
	: HP(hpVar),
	  maxHP(hpVar),
	  AP(apVar),
      DP(dpVar),
      SP(spVar),
      gold(money),
	  expPoints(expPoints)
    {
        //postcondition:  a character's attributes have been set to
        //the attributes given
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
string Character::ShowName() const
    {
        //postcondition:  returns the name of the character
        return name;
    }

int Character::Damage() const
    {
        //postcondition:  returns the amount of damage the character can do (AP)
        return AP;
    }

int Character::Defense() const
    {
        //postcondition:  returns character's defense points
        return DP;
    }

int Character::Health() const
    {
        //postcondition:  returns character's health points
        return HP;
    }

int Character::MaxHealth() const
    {
        //postcondition:  returns character's maximum health points
        return maxHP;
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

int Character::ExpPts() const
    {
        //postcondition:  returns the character's current experience point total
        return expPoints;
    }

void Character::AddStats(const StatMod& stats)
	{
		HP += stats.hpMod;
		if(HP > maxHP)
		{
			HP = maxHP;
		}

		AP += stats.apMod;
		DP += stats.dpMod;
		SP += stats.spMod;
	}

void Character::SubStats(const StatMod& stats)
	{
		HP -= stats.hpMod;
		AP -= stats.apMod;
		DP -= stats.dpMod;
		SP -= stats.spMod;
	}
