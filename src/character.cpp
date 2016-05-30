#include "character.h"

//Constructors-------------------------------------------------------//
Character::Character(int hpVar, int mpVar, int apVar, int dpVar, int mdpVar, int spVar, int money, int expPoints)
	: HP(hpVar),
	  maxHP(hpVar),
	  MP(mpVar),
	  maxMP(mpVar),
	  AP(apVar),
      DP(dpVar),
	  MDP(mdpVar),
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

        HP += hpChange;
    }

void Character::ChangeMP(int mpChange)
    {
        //postcondition:  MP value of character altered by the value
        //sent to the function; if MP is being used, a negative value
        //should be passed in, otherwise, a positive value should be passed in

        MP += mpChange;
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

int Character::MagicDefense() const
    {
        //postcondition:  returns character's magic defense points
        return MDP;
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

int Character::getMP() const
    {
        //postcondition:  returns character's magic points
        return MP;
    }

int Character::MaxMP() const
    {
        //postcondition:  returns character's maximum magic points
        return maxMP;
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
