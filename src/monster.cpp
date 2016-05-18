//Mike Lukas - p2prog03-      -monster.cpp-
//Member function definitions for the monster class.  Function
//explanations also included

#include <limits>
#include "monster.h"

using std::numeric_limits;
using std::streamsize;

//Constructors-------------------------------------------------------//

Monster::Monster()
    : Character(1, 0, 0, 0, 0, 0)
    {
        name = "none";
    }

vector<int> Monster::getEquipmentIds(EquipType equipType) const
	{
		//postcondition: returns a copy of the Monster's equipment id vector
		//matching the requested EquipType

		switch(equipType)
		{
		case WEAPON:
			return weaponIds;
			break;
		case ARMOR:
			return armorIds;
			break;
		case ITEM:
			return itemIds;
			break;
		default:
			return vector<int>();
			break;
		}
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

istream& operator>> (istream& is, Monster& monster)
	{
		getline(is, monster.name);

		//Init monster stats from stream
        is>>monster.HP;
        monster.maxHP = monster.HP;
        is>>monster.AP;
        is>>monster.DP;
        is>>monster.SP;
        is>>monster.gold;
        is>>monster.expPoints;
        is.ignore(numeric_limits<streamsize>::max(), '\n');

        //init inventory from stream (1 line of ids for each equipment type
        readEquipmentIdLine(is, monster.weaponIds);
        readEquipmentIdLine(is, monster.armorIds);
        readEquipmentIdLine(is, monster.itemIds);

        return is;
    }
