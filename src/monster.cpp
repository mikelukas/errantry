//Mike Lukas - p2prog03-      -monster.cpp-
//Member function definitions for the monster class.  Function
//explanations also included

#include <limits>
#include "monster.h"
#include "randombattlestrategy.h"

using std::numeric_limits;
using std::streamsize;

//Constructors-------------------------------------------------------//

Monster::Monster()
    : Character(1, 0, 0, 0, 0, 0, 0, 0)
    {
        name = "none";
        battleStrategy = new RandomBattleStrategy();
    }

Monster::Monster(const Monster& monster)
	: Character(monster),
	  weaponIds(monster.weaponIds),
	  armorIds(monster.armorIds),
	  itemIds(monster.itemIds),
	  spellIds(monster.spellIds),
	  battleStrategy(monster.battleStrategy->clone())
	{
		//postcondition: performs a deep copy of monster; BattleStrategy* is cloned.

	}

Monster::~Monster()
	{
		delete battleStrategy;
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

vector<int> Monster::getSpellIds() const
{
	return spellIds;
}

BattleStrategy* Monster::getBattleStrategy() const
{
	return battleStrategy;
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
        is>>monster.MP;
        monster.maxMP = monster.MP;
        is>>monster.AP;
        is>>monster.DP;
        is>>monster.MDP;
        is>>monster.SP;
        is>>monster.gold;
        is>>monster.expPoints;
        is.ignore(numeric_limits<streamsize>::max(), '\n');

        //init inventory from stream (1 line of ids for each equipment type
        getIdLine(is, monster.weaponIds);
        getIdLine(is, monster.armorIds);
        getIdLine(is, monster.itemIds);
        getIdLine(is, monster.spellIds);

        return is;
    }
