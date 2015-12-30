//Mike Lukas - p2prog03-      -monster.cpp-
//Member function definitions for the monster class.  Function
//explanations also included

#include "monster.h"

//Constructors-------------------------------------------------------//

Monster::Monster()
	: HP(1),
	  maxHP(1),
	  AP(0),
	  DP(0),
	  MDP(0),
	  SP(0),
	  gold(0),
	  weakness(fire),
	  monsterName("none")
	{
		//all necessary monster attributes initialized in initializer
		//list
	}
Monster::Monster(int hpVar, int apVar, int dpVar, int mdpVar,
				 int spVar, int money, int expPts, elemType& weak, 
				 apstring& name)
	: HP(hpVar),
	  maxHP(hpVar),
	   AP(apVar),
	  DP(dpVar),
	  MDP(mdpVar),
	  SP(spVar),
	  gold(money),
	  weakness(weak)
	{
		//sets all monster attributes to specific values, specified by
		//a file.  
				
		monsterName = name;
		
		expPoints = expPts;
	}
//Public Member functions--------------------------------------------//
void Monster::ChangeHP(int hpChange)
	{
		//postcondition:  HP value of character altered by the value
		//sent to the function; if damage is done, a negative value
		//is added to HP, if health is gained, a positive value is
		//added to HP
		
		HP = HP + hpChange;
	}
//accessor functions-------------------------------------------------//

int Monster::Damage() const
	{
		//postcondition:  returns the amount of damage the player can do (AP)
		return AP;
	}

int Monster::Defense() const
	{
		//postcondition:  returns user's defense points
		return DP;
	}

int Monster::Health() const
	{
		//postcondition:  returns user's health points
		return HP;
	}

int Monster::MDefense() const
	{
		//postcondition:  returns the character's magic defense points
		return MDP;
	}

int Monster::Speed() const
	{
		//postcondition:  returns the character's speed points
		return SP;
	}

int Monster::Money() const
	{
		//postcondition:  returns amount of gold the character has
		return gold;
	}

int Monster::Weakness() const
	{
		//returns a numerical value corresponding with the monster's
		//elemental weakness
		
		return weakness;
	}
int Monster::Experience() const
	{
		//returns the number of experience points the monster gives
		
		return expPoints;
	}