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
		name = "none";
    }
//Public Member functions--------------------------------------------//
void Character::ChangeHP(int hpChange)
    {
        //postcondition:  HP value of character altered by the value
        //sent to the function; if damage is done, a negative value
        //is added to HP, if health is gained, a positive value is
        //added to HP

        HP += hpChange;
        if(HP > maxHP)
        {
        	HP = maxHP;
        }
    }

void Character::ChangeMP(int mpChange)
    {
        //postcondition:  MP value of character altered by the value
        //sent to the function; if MP is being used, a negative value
        //should be passed in, otherwise, a positive value should be passed in

        MP += mpChange;
        if(MP > maxMP)
		{
			MP = maxMP;
		}
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

		MP += stats.mpMod;
		if(MP > maxMP)
		{
			MP = maxMP;
		}

		AP += stats.apMod;
		DP += stats.dpMod;
		MDP += stats.mdpMod;
		SP += stats.spMod;
	}

void Character::SubStats(const StatMod& stats)
	{
		HP -= stats.hpMod;
		MP -= stats.mpMod;
		AP -= stats.apMod;
		DP -= stats.dpMod;
		MDP -= stats.mdpMod;
		SP -= stats.spMod;
	}

void Character::AddEquipment(const EquipmentLine& newEqLine)
	{
		//postcondition: adds the Equipment within the incoming EquipmentLine*
		//to the player's inventory.
		//Safe for the caller to delete the EquipmentLine pointed to by the
		//incoming pointer; if the player already has the equipment, we increment
		//their count for it, and if they don't we, make a copy of the EquipmentLine
		//and store it into the inventory.

		EquipType purchaseType = newEqLine.pEquipment->getType();
		map<const Equipment*, EquipmentLine>& inventory = getInventoryFor(purchaseType);

		EquipmentLine& eqLine = inventory[newEqLine.pEquipment];
		if(eqLine.pEquipment != NULL)
		{
			eqLine += newEqLine;
		}
		else {
			inventory[newEqLine.pEquipment] = newEqLine;
		}
	}

void Character::AddSpell(const Spell* newSpell)
	{
		//postcondition: the given spell is added to the Character, and also
		//added to Character's categorized spells map (if the Character doesn't
		//already know the spell.

		spells.insert(newSpell);
		categorizedSpells[newSpell->getCategory()].insert(newSpell);
	}

vector<const Equipment*>* Character::getAllEquipment() const
	{
		//postcondition: allocates a new vector and fills it with pointers to
		//all equipment this character owns.

		vector<const Equipment*>* allEquipment = new vector<const Equipment*>();
		allEquipment->reserve(weapons.size() + armor.size() + items.size());

		for(map<const Equipment*, EquipmentLine>::const_iterator it = weapons.begin(); it != weapons.end(); it++)
		{
			allEquipment->push_back(it->first);
		}

		for(map<const Equipment*, EquipmentLine>::const_iterator it = armor.begin(); it != armor.end(); it++)
		{
			allEquipment->push_back(it->first);
		}

		for(map<const Equipment*, EquipmentLine>::const_iterator it = items.begin(); it != items.end(); it++)
		{
			allEquipment->push_back(it->first);
		}

		return allEquipment;
	}

map<const Equipment*, EquipmentLine>& Character::getInventoryFor(const EquipType equipType)
	{
		//postcondition: returns the inventory set matching the given equipment type,
		//or the items list if the EquipType is not recognized (if this happens then
		//it should be a bug.

		switch(equipType)
		{
		case WEAPON:
			return weapons;
			break;
		case ARMOR:
			return armor;
			break;
		case ITEM:
			return items;
			break;

		default:
			return items;
			break;
		}
	}

bool Character::hasSpell(const Spell* spell) const
	{
		return (spells.find(spell) != spells.end());
	}

bool Character::hasSpells() const
	{
		return spells.size() > 0;
	}

vector<const Spell*>* Character::getSpells() const
	{
		//postcondition: allocates a new vector of all spells the Character knows.

		vector<const Spell*>* spellsVector = new vector<const Spell*>();
		for(set<const Spell*>::const_iterator it = spells.begin(); it != spells.end(); it++)
		{
			spellsVector->push_back((*it));
		}
		return spellsVector;
	}

const set<const Spell*>& Character::getSpellsForCategory(SpellCategory category)
	{
		return categorizedSpells[category];
	}

int Character::applyPhysicalDamage(int rawDamage)
	{
		//postcondition: rawDamage is modified based on this character's DP,
		//then applied to this character.  The net damage after modification is
		//returned.

		int netDamage = rawDamage - Defense();
	    if(netDamage < 0)
	    {
	    	netDamage = 0;
	    }

	    ChangeHP(-1 * netDamage);

	    return netDamage;
	}

int Character::applyMagicalDamage(int rawDamage, Element element)
	{
		//postcondition: rawDamage is modified based on this character's MDP, and
		//elemental weakness, then applied to this character.  The net damage
		//after modification is returned.

		int netDamage = rawDamage - MagicDefense();
	    if(netDamage < 0)
	    {
	    	netDamage = 0;
	    }

	    ChangeHP(-1 * netDamage);

	    return netDamage;
	}
