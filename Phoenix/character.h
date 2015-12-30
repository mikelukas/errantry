#ifndef _CHARACTER_H
#define _CHARACTER_H

//Mike Lukas -p2prog03-			- character.h - 
//Class definition for a character.  This class holds all of the basic
//values a character will need; health points, magic points, attack
//points, defense points, magic defense points, speed points, and 
//money.  

#include "apstring.h"

enum elemType {fire, air, earth, water, none};

struct SpellType
	{
		int MAP; 			//attack power of spell
		int cost;			//cost in MP
		apstring name; 		//name of spell
		elemType element; 	//basic elemental type of spell
	};
	
class Character
	{
		protected:
			int HP;				//current hit points (life)
			int maxHP;			//maximum hit points
			int MP;				//magic points (energy for spells)
			int maxMP;			//maximum magic points 
			int AP; 			//attack power
			int DP;				//defense percentage
			int MDP;			//magic defense percentage
			int SP;				//speed points
			int gold;
					
		public:
			Character();
			Character(int, int, int, int, int, int, int);
			void ChangeHP(int);
			void ChangeMP(int);
			
			int Damage() const;
			int Defense() const;
			int Health() const;
			int MEnergy() const;
			int MDefense() const;
			int Speed() const;
			int Money() const;	
	};
//Constructors-------------------------------------------------------//	
Character::Character()
	: HP(1),
	  maxHP(1),
	  MP(0),
	  maxMP(0),
	  AP(0),
	  DP(0),
	  MDP(0),
	  SP(0),
	  gold(0)
	{
		//attribute variables initialized in intializer list
	}
Character::Character(int hpVar, int mpVar, int apVar, int dpVar,
					 int mdpVar, int spVar, int money)
	{ 
	 	//postcondition:  a character's attributes have been set to
	 	//the attributes given
	 	
	 	HP= hpVar;
	 	maxHP = hpVar;
	 	MP = mpVar;
	 	maxMP = mpVar;
	 	AP = apVar;
	 	DP = dpVar;
	 	MDP = mdpVar;
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
void Character::ChangeMP(int mpChange)
	{
		//postcondition:  MP value of character altered by the value
		//sent to the function; if a spell is used, a negative value
		//is added to MP, if MP is gained, a positive value is
		//added to MP
		
		MP = MP + mpChange;
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

int Character::MEnergy() const
	{
		//postcondition:  returns the character's magic points
		return MP;
	}

int Character::MDefense() const
	{
		//postcondition:  returns the character's magic defense points
		return MDP;
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