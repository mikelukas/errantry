#include <algorithm>
#include <iostream>
#include <math.h> //ceil()
#include "character.h"
#include "effectfactory.h"
#include "statuses/statusconstants.h"
#include "util/mathutils.h"

using std::cout;
using std::endl;

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
	  totalStatMods(),
      gold(money),
	  expPoints(expPoints)
    {
        //postcondition:  a character's attributes have been set to
        //the attributes given
		name = "none";
    }

Character::~Character()
	{
		//de-allocate StatusEffects added to this Character that haven't been removed.
		for(map<const EffectType, StatusEffect*>::const_iterator it = statuses.begin(); it != statuses.end(); it++)
		{
			delete it->second;
		}
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

int Character::getBaseAP() const
    {
        //postcondition:  returns character's base AP value before modifications
		//from things like equipment and statuses
        return AP;
    }

int Character::getEffectiveAP() const
    {
        //postcondition:  returns character's total AP after including modifications (e.g. from equipment or statuses)
        return AP + totalStatMods.apMod;
    }

int Character::getBaseDP() const
	{
		//postcondition:  returns character's base DP value before modifications
		//from things like equipment and statuses
		return DP;
	}

int Character::getEffectiveDP() const
    {
        //postcondition:  returns character's total DP after including modifications (e.g. from equipment or statuses)
        return DP + totalStatMods.dpMod;
    }

int Character::getBaseMDP() const
	{
		//postcondition:  returns character's base MDP value before modifications
		//from things like equipment and statuses
		return MDP;
	}

int Character::getEffectiveMDP() const
    {
        //postcondition:  returns character's total MDP after including modifications (e.g. from equipment or statuses)
        return MDP + totalStatMods.mdpMod;
    }

int Character::getHP() const
    {
        //postcondition:  returns character's health points
        return HP;
    }

int Character::getBaseMaxHP() const
	{
		//postcondition:  returns character's base max HP value before modifications
		//from things like equipment and statuses
		return maxHP;
	}

int Character::getEffectiveMaxHP() const
    {
        //postcondition:  returns character's maximum HP after including modifications (e.g. from equipment or statuses)
        return maxHP + totalStatMods.maxHpMod;
    }

int Character::getMP() const
    {
        //postcondition:  returns character's magic points
        return MP;
    }

int Character::getBaseMaxMP() const
	{
		//postcondition:  returns character's base max MP value before modifications
		//from things like equipment and statuses
		return maxMP;
	}

int Character::getEffectiveMaxMP() const
    {
        //postcondition:  returns character's maximum MP after including modifications (e.g. from equipment or statuses)
        return maxMP + totalStatMods.maxMpMod;
    }

int Character::getBaseSP() const
	{
		//postcondition:  returns character's base SP value before modifications
		//from things like equipment and statuses
		return SP;
	}

int Character::getEffectiveSP() const
    {
        //postcondition:  returns the character's SP after including modifications (e.g. from equipment or statuses)
        return SP + totalStatMods.spMod;
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

bool Character::isWeakAgainst(Element element) const
	{
		return weaknesses.count(element) > 0;
	}

const set<Element>& Character::getWeaknesses() const
	{
		return weaknesses;
	}

void Character::AddStats(const StatMod& stats)
	{
		//postcondition: incoming stats are added to the total stat modifications
		//applied to this Character's stats when they are checked.
		//Current HP and MP values (not max values) will not be increased beyond
		//the effective maximum)

		totalStatMods += stats;
		totalStatMods.hpMod = 0; //doesn't make sense to have current HP have persistent modification (only base max HP)
		totalStatMods.mpMod = 0; //doesn't make sense to have current MP have persistent modification (only base max MP)

		HP += stats.hpMod;
		if(HP > getEffectiveMaxHP())
		{
			HP = getEffectiveMaxHP();
		}

		MP += stats.mpMod;
		if(MP > getEffectiveMaxMP())
		{
			MP = getEffectiveMaxMP();
		}
	}

void Character::SubStats(const StatMod& stats)
	{
		//postcondition: incoming stats are subtracted from the total stat modifications
		//applied to this Character's stats when they are checked.

		totalStatMods -= stats;
		totalStatMods.hpMod = 0; //doesn't make sense to have current HP have persistent modification (only base max HP)
		totalStatMods.mpMod = 0; //doesn't make sense to have current MP have persistent modification (only base max MP)

		HP -= stats.hpMod;
		if(HP > getEffectiveMaxHP()) //if something increased max HP, and that inrease is lost, need to ensure HP goes back to new max
		{
			HP = getEffectiveMaxHP();
		}

		MP -= stats.mpMod;
		if(MP > getEffectiveMaxMP())
		{
			MP = getEffectiveMaxMP();
		}
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

bool Character::RemoveEquipment(const Equipment* eq)
{
	//postcondition: specified Equipment amount is reduced by 1 in the Character's
	//inventory, and removed entirely if they have none left after reducing
	//the quantity.
	//returns true if equipment was able to be removed, false if somehow the
	//caller tried to remove equipment this Character does not have.

	const EquipmentLine eqLine(eq);
	return RemoveEquipment(&eqLine);
}

bool Character::RemoveEquipment(const EquipmentLine* removedEqLine)
{
	//postcondition: specified equipmentline's quantity is subtracted from the
	//character's, and the equipment is removed entirely if they have none left
	//after it is removed.
	//returns true if equipment was able to be removed, false if somehow the
	//caller tried to remove equipment this Character does not have.

	EquipType eqType = removedEqLine->pEquipment->getType();
	map<const Equipment*, EquipmentLine>& inventory = getInventoryFor(eqType);

	EquipmentLine& invEqline = inventory[removedEqLine->pEquipment];
	if(invEqline.pEquipment == NULL)
	{
		//bug if we got this far...
		cout<<"Tried to remove equipment "<<ShowName()<<" doesn't have..."<<endl;
		return false;
	}

	invEqline -= (*removedEqLine);
	if(invEqline.quantity <= 0)
	{
		//don't want this equipment listed anywhere anymore if we're out of it
		inventory.erase(invEqline.pEquipment);
	}

	return true;
}

void Character::AddSpell(const SpellTemplate* newSpell)
	{
		//postcondition: the given spell is added to the Character, and also
		//added to Character's categorized spells map (if the Character doesn't
		//already know the spell.  The Character's weaknesses are recalculated
		//since they are based on the Elements of all spells the character knows.

		spells.insert(newSpell);
		categorizedSpells[newSpell->getCategory()].insert(newSpell);
		recalculateWeakness();
	}

void Character::addWeakness(Element element)
{
	weaknesses.insert(element);
}

void Character::removeWeakness(Element element)
{
	weaknesses.erase(element);
}

void Character::recalculateWeakness()
	{
		//postcondition: Character's weaknesses set is updated based on the
		//Elements of all Spells they have.
		//If a Character has more Elements of one type than its opposite, the
		//character will be weak to its opposite; e.g. if the character has
		//3 Fire spells, and 2 Water spells, the character will be weak to Water.

		int numPairs = (ELEMENTS.size()-1)/2; //-1 b/c none doesn't have an opposite, and div by 2 b/c every element is paired with its opposite
		int* elementPairAffinities = new int[numPairs]; //The index of a pair is the int val of the 1st element in that pair (see Element enum for pairings)
		std::fill(elementPairAffinities, elementPairAffinities + numPairs, 0);

		//First go through every spell's Element, and score it based on if it's the first element in its pair or 2nd
		for(set<const SpellTemplate*>::const_iterator it = spells.begin(); it != spells.end(); it++)
		{
			Element spellElement = (*it)->getElement();
			if(spellElement == none)
			{
				continue; //can't be weak against 'none', so skip this spell
			}

			//add 1 to element's pair if it is the first element in the pair, subtract 1 if it's the 2nd
			if(spellElement % 2 == 0)
			{
				elementPairAffinities[spellElement/2]++;
			}
			else
			{
				elementPairAffinities[spellElement/2]--;
			}
		}

		//For each pair, determine if there are more spells of the first element in the pair or 2nd, and set the weakness to be opposite
		weaknesses.clear();
		for(int i = 0; i < numPairs; i++)
		{
			int pairAffinity = elementPairAffinities[i];
			if(pairAffinity == 0)
			{
				continue;
			}

			Element pairElement = static_cast<Element>(2*i);
			if(pairAffinity > 0)
			{
				//More spells' Elements are of the 1st Element in this pair.
				weaknesses.insert(getOppositeOf(pairElement));
			}
			else if(pairAffinity < 0)
			{
				//More spells' Elements are of the 2nd Element in this pair
				weaknesses.insert(pairElement);
			}
		}

		delete elementPairAffinities;
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

vector<EquipmentLine*>* Character::getWeaponsAndArmorAsVector()
	{
		//Postcondition: A vector is dynamically allocated to hold pointers to
		//every weapon and armor equipment line in the character's inventory.
		//Vector should be freed by the caller.

		map<const Equipment*, EquipmentLine>& invWeapons = getInventoryFor(WEAPON);
		map<const Equipment*, EquipmentLine>& invArmor = getInventoryFor(ARMOR);

		vector<EquipmentLine*>* equipmentChoices = new vector<EquipmentLine*>;

		for(map<const Equipment*,EquipmentLine>::iterator it=invWeapons.begin(); it!=invWeapons.end(); it++)
		{
			equipmentChoices->push_back(&(it->second));
		}

		for(map<const Equipment*,EquipmentLine>::iterator it=invArmor.begin(); it!=invArmor.end(); it++)
		{
			equipmentChoices->push_back(&(it->second));
		}

		return equipmentChoices;
	}

vector<EquipmentLine*>* Character::getItemsAsVector()
	{
		//Postcondition: A vector is dynamically allocated to hold all items in
		//the player's inventory, and new EquipmentLines for each piece of item
		//are also dynamically allocated.  All of these allocations should be
		//freed by the caller.

		map<const Equipment*, EquipmentLine>& invItems = getInventoryFor(ITEM);

		vector<EquipmentLine*>* equipmentChoices = new vector<EquipmentLine*>;

		for(map<const Equipment*,EquipmentLine>::iterator it=invItems.begin(); it!=invItems.end(); it++)
		{
			equipmentChoices->push_back(&(it->second));
		}

		return equipmentChoices;
	}

int Character::getEffectiveMpCostFor(const SpellTemplate* spell) const
	{
		//postcondition: returns the actual MP cost for the given spell after
		//adjusting for statuses this Character has which can affect it.

		int netMpCost = spell->getMpCost();
		if(hasStatus(FOCUSED))
		{
			netMpCost = max(1, roundInt(((double)netMpCost) * MP_COST_DOWNSCALING_FACTOR));
		}
		else if(hasStatus(UNFOCUSED))
		{
			netMpCost *= MP_COST_UPSCALING_FACTOR;
		}

		return netMpCost;
	}

bool Character::hasEnoughMpFor(const SpellTemplate* spell) const
	{
		//postcondition: returns true if the Character has enough MP to cast the
		//given spell, taking adjustments from StatusEffects into account.

		return getEffectiveMpCostFor(spell) <= getMP();
	}

bool Character::hasSpell(const SpellTemplate* spell) const
	{
		return (spells.find(spell) != spells.end());
	}

bool Character::hasSpells() const
	{
		return spells.size() > 0;
	}

const set<const SpellTemplate*>& Character::getSpells() const
	{
		return spells;
	}

const set<const SpellTemplate*>& Character::getSpellsForCategory(SpellCategory category)
	{
		return categorizedSpells[category];
	}

const set<const SpellTemplate*>* Character::getSpellsForCategories(const set<SpellCategory>& categories)
	{
		//postcondition: allocates a new set of spells that match any of the
		//specified categories.

		set<const SpellTemplate*>* spellsForCategories = new set<const SpellTemplate*>(); //freed by caller
		for(set<SpellCategory>::const_iterator it = categories.begin(); it != categories.end(); it++)
		{
			const set<const SpellTemplate*>& spellsForCategory = getSpellsForCategory((*it));
			spellsForCategories->insert(spellsForCategory.begin(), spellsForCategory.end());
		}

		return spellsForCategories;
	}

const set<pair<Element, int>, bool(*)(const pair<Element, int>&, const pair<Element, int>&)>* Character::getSpellElementCounts(const set<SpellCategory>& categories)
	{
		//postcondition: allocates a set of Elements with their counts, sorted
		//in ascending order by how many spells of that element the character has.

		vector<int> elementsToCounts(ELEMENTS.size()-1, 0);

		//Count the amount of each element in all of the Character's spells
		const set<const SpellTemplate*>* monsterSpells = getSpellsForCategories(categories);
		for(set<const SpellTemplate*>::const_iterator it = monsterSpells->begin(); it != monsterSpells->end(); it++)
		{
			Element element = (*it)->getElement();
			if(element == none)
			{
				continue;
			}

			elementsToCounts[element]++;
		}

		delete monsterSpells;

		//Populate a sorted set with pairs of Elements with their counts
		bool(*sort_func)(const pair<Element, int>&, const pair<Element, int>&) = elementCountSort; //from element.h
		set<pair<Element, int>, bool(*)(const pair<Element, int>&, const pair<Element, int>&)>* sortedElementCounts = new set<pair<Element, int>, bool(*)(const pair<Element, int>&, const pair<Element, int>&)>(sort_func); //up to caller to free
		for(int i=0; i < elementsToCounts.size(); i++)
		{
			Element el = static_cast<Element>(i);

			sortedElementCounts->insert(std::make_pair(el, elementsToCounts[el]));
		}

		return sortedElementCounts;
	}

int Character::applyPhysicalDamage(int rawDamage)
	{
		//postcondition: rawDamage is modified based on this character's DP,
		//then applied to this character.  The net damage after modification is
		//returned.

		int netDamage = rawDamage - getEffectiveDP();
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
		//elemental weakness, then applied to this character.
		//If character is weak toward the incoming element, then only half of
		//their MDP is used (rounding up).  Otherwise the base MDP value is used.
		//The net damage after modification is returned.

		int adjustedMDP = isWeakAgainst(element)? ceil(.5*((float)getEffectiveMDP())) : getEffectiveMDP();

		int netDamage = rawDamage - adjustedMDP;
	    if(netDamage < 0)
	    {
	    	netDamage = 0;
	    }

	    ChangeHP(-1 * netDamage);

	    return netDamage;
	}

void Character::useItem(const Equipment* item, Character& onTarget)
	{
		//postcondition: The incoming item is used on by this character on the
		//given target, by adding the item's stat changes to the target's stats,
		//adding any immunities conferred by the item as permanent immunities,
		//and applying any effects from the item on the target.
		//The item's quantity in the character's inventory is reduced by 1
		//(before use).  This method is aborted before any item effects are
		//applied if the item can't be subtracted from the Character's inventory.

		if(!RemoveEquipment(item))
		{
			return; //Abort using item if it can't be removed from inventory; must be a bug where Character is trying to use something they dont' have
		}

		AddStats(item->getStatMod());
		addPermImmunitiesFrom(item);
		applyEquipmentEffects(item, onTarget);
	}

void Character::applyEquipmentEffects(const Equipment* eq, Character& onTarget)
	{
		//postcondition: creates effects for each effect ID held by eq and
		//applies them to onTarget with this Character as the applier.  Any
		//effects that fail during setup are skipped.

		EffectParams effectParams(eq->getElement(), *this, onTarget);
		const vector<int>& effectIds = eq->getEffectIds();
		for(int i=0; i < effectIds.size(); i++)
		{
			Effect* effect = EffectFactory::getInstance()->createEffect(effectIds[i], effectParams);
			if(!effect->setup())
			{
				continue; //XXX just skip effects we can't set up; shouldn't be defining items with effects that require more choices
			}

			effect->apply();
		}
	}

bool Character::addStatus(StatusEffect* status)
	{
		//postcondition: if the character does not already have the given status,
		//and is not immune to it, it is added to its status maps, and onAdd()
		//is invoked on the status to run any initial/setup effects, in that
		//order.
		//returns true if the status was added, false otherwise, so it can be
		//deleted by the caller if applicable.

		if(isImmuneTo(status->getType()))
		{
			cout<<ShowName()<<" is immune to "<<status->getName()<<"!"<<endl;
			return false;
		}

		if(statuses.count(status->getType()) > 0)
		{
			return false; //can't add the same status more than once.
		}

		//Add status to both lookup maps
		statuses[status->getType()] = status;
		statusesByContext[status->getEligibleContext()].insert(status);

		status->onAdd();
		return true;
	}

void Character::removeStatus(const EffectType statusType)
	{
		//postcondition: if the character the given status, it is removed from
		//its statuses map, then the statusByContext map, then onRemove() is invoked
		//on the status to run any cleanup effects, and the status is deallocated,
		//in that order.

		map<const EffectType,StatusEffect*>::iterator statusIt = statuses.find(statusType);
		if(statusIt == statuses.end())
		{
			return; //can't remove a status player doesn't have
		}

		StatusEffect* status = statusIt->second;

		statuses.erase(statusIt);
		statusesByContext[status->getEligibleContext()].erase(status);

		status->onRemove();
		delete status;
	}

void Character::removeStatusesFor(const Context context)
	{
		//postcondition: all statuses the Character has for the given context are
		//removed from statuses, one at a time, calling onRemove() on each after it is
		//is removed and then deallocating it, followed by clearing the set of
		//StatusEffects in the statusesByContext map for that Context, in that order.

		//Remove every status for the given context from the statuses map first
		set<StatusEffect*> toRemove = statusesByContext[context];
		for(set<StatusEffect*>::iterator it = toRemove.begin(); it != toRemove.end(); it++)
		{
			statuses.erase((*it)->getType());
			(*it)->onRemove();
			delete (*it);
		}

		//Empty the vector of statuses for that context next
		toRemove.clear();
	}

void Character::processStatusEffects()
	{
		//postcondition: calls onTurn() on every status the Character has,
		//and removes statuses that become expired after doing so.

		vector<StatusEffect*> expiredStatuses;

		//Call onTurn() on every status, track if status is expired after doing so (don't want to remove while iterating
		for(map<const EffectType, StatusEffect*>::iterator it = statuses.begin(); it != statuses.end(); it++)
		{
			StatusEffect* status = it->second;

			status->onTurn();
			if(status->isExpired())
			{
				expiredStatuses.push_back(status);
			}
		}

		//Remove all expired statuses
		for(int i=0; i < expiredStatuses.size(); i++)
		{
			removeStatus(expiredStatuses[i]->getType());
		}
	}

bool Character::hasStatus(const EffectType statusType) const
	{
		//postcondition: returns true if the Character currently has a status matching
		//the given type, false otherwise.

		return statuses.count(statusType) > 0;
	}

bool Character::hasStatuses() const
	{
		//postcondition: returns true if Character has any statuses, false otherwise

		return !statuses.empty();
	}

vector<StatusEffect*>* Character::getAllStatuses() const
	{
		//postcondition: allocates a new vector containing pointers to all StatusEffects*
		//the Character currently has.

		vector<StatusEffect*>* statusVector = new vector<StatusEffect*>(); //freed by caller
		for(map<const EffectType, StatusEffect*>::const_iterator it = statuses.begin(); it != statuses.end(); it++)
		{
			statusVector->push_back(it->second);
		}

		return statusVector;
	}

bool Character::isImmuneTo(const EffectType status) const
	{
		//postcondition: returns true if the Character is immune to the incoming
		//status, either temporarily or permanently.

		return (tempStatusImmunities.count(status) > 0) || (permStatusImmunities.count(status) > 0);
	}

bool Character::hasImmunities() const
	{
		//postcondition: returns true if Character is immune, either temporarily
		//or permanently to at least 1 StatusEffect

		return (tempStatusImmunities.size() > 0) || (permStatusImmunities.size() > 0);
	}

const set<EffectType>* Character::getAllImmunities() const
	{
		//postcondition: returns all temporary and permanent EFfectTypes that
		//this Character is immune to, in an dynamically allocated set. It is
		//up to the caller to delete the set.

		set<EffectType>* immunities = new set<EffectType>();
		for(map<const EffectType, set<const Equipment*> >::const_iterator it = tempStatusImmunities.begin(); it != tempStatusImmunities.end(); it++)
		{
			immunities->insert(it->first);
		}
		immunities->insert(permStatusImmunities.begin(), permStatusImmunities.end());

		return immunities;
	}

void Character::addTempImmunitiesFrom(const Equipment* equipment)
	{
		//postcondition: adds all immunities conferred by equipment as temporary
		//immunities for this Character

		const set<int> immunityStatusIds = equipment->getEffectImmunityIds();
		for(set<int>::const_iterator it = immunityStatusIds.begin(); it != immunityStatusIds.end(); it++)
		{
			EffectType status = static_cast<EffectType>(*it);
			addTempImmunityTo(status, equipment);
		}
	}

void Character::addTempImmunityTo(const EffectType status, const Equipment* fromEquipment)
	{
		//postcondition: adds an immunity to status, referencing fromEquipoment
		//as the equipment that is providing it, for use when removing.

		tempStatusImmunities[status].insert(fromEquipment);
		removeStatus(status);
	}

void Character::removeTempImmunitiesFor(const Equipment* equipment)
	{
		//postcondition: removes all immunities conferred by equipment from
		//this Character.

		const set<int> immunityStatusIds = equipment->getEffectImmunityIds();
		for(set<int>::const_iterator it = immunityStatusIds.begin(); it != immunityStatusIds.end(); it++)
		{
			EffectType status = static_cast<EffectType>(*it);
			removeTempImmunityTo(status, equipment);
		}
	}

void Character::removeTempImmunityTo(const EffectType status, const Equipment* fromEquipment)
	{
		//postcondition: removes fromEquipment as a reference to the immunity for
		//status, and if status is not referenced as an immunity by any other
		//equipped equipment, the status immunity is removed

		if(tempStatusImmunities.count(status) <= 0)
		{
			return;
		}

		set<const Equipment*>& eqRefs = tempStatusImmunities[status];
		eqRefs.erase(fromEquipment);

		if(eqRefs.empty())
		{
			tempStatusImmunities.erase(status);
		}
	}

void Character::addPermImmunitiesFrom(const Equipment* equipment)
	{
		//postcondition: adds all immunities conferred by equipment as temporary
		//immunities for this Character

		const set<int> immunityStatusIds = equipment->getEffectImmunityIds();
		for(set<int>::const_iterator it = immunityStatusIds.begin(); it != immunityStatusIds.end(); it++)
		{
			EffectType status = static_cast<EffectType>(*it);
			addPermImmunityTo(status);
		}
	}

void Character::addPermImmunityTo(const EffectType immunity)
	{
		//postcondition: the incoming immunity is added to the set of permanent
		//status immunities for the Character.

		permStatusImmunities.insert(immunity);
		removeStatus(immunity);
	}

void Character::removePermImmunitiesFor(const Equipment* equipment)
	{
		//postcondition: removes all immunities conferred by equipment from
		//this Character.

		const set<int> immunityStatusIds = equipment->getEffectImmunityIds();
		for(set<int>::const_iterator it = immunityStatusIds.begin(); it != immunityStatusIds.end(); it++)
		{
			EffectType status = static_cast<EffectType>(*it);
			removePermImmunityTo(status);
		}
	}

void Character::removePermImmunityTo(const EffectType immunity)
	{
		//postcondition: the incoming immunity is removed from the set of permanent
		//status immunities for the Character.

		permStatusImmunities.erase(immunity);
	}
