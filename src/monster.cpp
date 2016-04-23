//Mike Lukas - p2prog03-      -monster.cpp-
//Member function definitions for the monster class.  Function
//explanations also included

#include "monster.h"

//Constructors-------------------------------------------------------//

Monster::Monster()
    : mHP(1),
      mmaxHP(1),
      AP(0),
      DP(0),
      SP(0),
      monsterName("none")
    {
        //all necessary monster attributes initialized in initializer
        //list
    }
//Public Member functions--------------------------------------------//
void Monster::SetAttributes(int hpVar, int apVar, int dpVar, int spVar, int goldVar, int expVar,
                         string& name)
    {
        mHP = hpVar;
        mmaxHP = hpVar;
        AP = apVar;
        DP = dpVar;
        SP = spVar;
        gold = goldVar;
        expPoints = expVar;
        monsterName = name;
    }
void Monster::ChangeHP(int hpChange)
    {
        //postcondition:  HP value of character altered by the value
        //sent to the function; if damage is done, a negative value
        //is added to HP, if health is gained, a positive value is
        //added to HP
        
        mHP = mHP + hpChange;
    }
//accessor functions-------------------------------------------------//

string Monster::ShowName() const
    {
        //postcondition:  returns the monster's name
        return monsterName;
    }
    
int Monster::Damage() const
    {
        //postcondition:  returns the amount of damage the monster can do (AP)
        return AP;
    }

int Monster::Defense() const
    {
        //postcondition:  returns monster's defense points
        return DP;
    }

int Monster::mHealth() const
    {
        //postcondition:  returns monster's health points
        return mHP;
    }

int Monster::mMaxHealth() const
    {
        //postcondition:  returns monster's maximum health points
        return mmaxHP;
    }
int Monster::Speed() const
    {
        //postcondition:  returns the monster's speed points
        return SP;
    }
int Monster::Money() const
	{
		//postcondition: returns the amount of gold the monster is carrying
		return gold;
	}
int Monster::Experience() const
    {
        //returns the number of experience points the monster gives
        
        return expPoints;
    }
