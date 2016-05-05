//Mike Lukas - p2prog03-      -monster.cpp-
//Member function definitions for the monster class.  Function
//explanations also included

#include "monster.h"

//Constructors-------------------------------------------------------//

Monster::Monster()
    : Character(1, 0, 0, 0, 0, 0)
    {
        name = "none";
    }
//Public Member functions--------------------------------------------//
void Monster::SetAttributes(int hpVar, int apVar, int dpVar, int spVar, int goldVar, int expVar,
                         string& name)
    {
        HP = hpVar;
        maxHP = hpVar;
        AP = apVar;
        DP = dpVar;
        SP = spVar;
        gold = goldVar;
        expPoints = expVar;
        this->name = name;
    }

void Monster::apply(const Equipment* eq)
	{
		//postcondition: The incoming Equipment is "applied" to the player, which
		//adds the stat changes from the Equipment to the player's stats.
		//For weapons and armor any previously-equipped equipment is also
		//removed first and placed back into the player's inventory.

		switch(eq->getType())
		{
		case ITEM:
			AddStats(eq->getStatMod());
			break;
		default:
			return;
		}
	}
