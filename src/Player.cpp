//Mike Lukas - p2prog03- player.cpp-
//Functions and explanations for the player class.

#include <iostream>
#include "player.h"

using std::cout;
using std::cin;
using std::endl;

//Constructors---------------------------------------------------------------//

Player::Player()
    : Character(BEGINHP, BEGINAP, BEGINDP, BEGINSP, BEGINGOLD, 0),
      expToNext(100),
      lvl(1),
      Coords(STARTPOS)
    {
        //attribute variables initialized in initializer list
        cout<<"Greetings wanderer, tell me your name:  ";
        cin>>name;
        cout<<endl;

        initStartingEquipment();
    }

void Player::initStartingEquipment()
	{
		//postcondition: equipped map inited with null pointers for all equipment types.

		currentEquipped[WEAPON] = NULL;
		currentEquipped[ARMOR] = NULL;
		currentEquipped[ITEM] = NULL; //can't actually equip these but just to give it SOME default val
	}

//Public Member Functions-----------------------------------------------//

void Player::LevelUp()
    {
        //postcondition:  player's attributes are increased;
        //user chooses whether he/she wants to increase a certain
        //attack or defense attribute greater than the others, while
        //the player's HP, SP, lvl, and expToNext are changed by
        //the same rates every time.
        
        int choice;
        
        maxHP = maxHP + int(maxHP * HPRATE);
                
        if(lvl % SPRATE == 0)
            SP++;
        lvl++;
        expToNext = expToNext + int(expToNext * NEXTRATE);
        
        cout<<"Congratulations, your level is now "<<lvl<<"!"<<endl;
        cout<<"--------------------------------------"<<endl;
        
        cout<<"Increase:  1) attack"<<endl
            <<"           2) defense"<<endl
            <<"           3) even increment"<<endl;
        cout<<"Choice:  ";
        cin>>choice;
        cout<<"--------------------------------------"<<endl;
         
         switch(choice)
            {
                case 1: //Attack
                    AP = AP + int(AP * BIGRATE);
                    DP = DP + int(AP * FLATRATE);
                    break;
                case 2: //Defense
                    AP = AP + int(AP * FLATRATE);
                    DP = DP + int(AP * BIGRATE);
                    break;
                default:  //even
                    AP = AP + int(AP * FLATRATE);
                    DP = DP + int(AP * FLATRATE); 
            }
            
        }

void Player::AddExp(int pts)
    {
        //postcondition:  the player's experience points are raised by
        //the value sent to the function
        
        expPoints = expPoints + pts;
    }
void Player::AddMoney(int money)
    {
        //postcondition:  the player's gold total is raised by the value
        //sent to the function
        
        gold = gold + money;
    }
void Player::AddEquipment(const EquipmentLine& newEqLine)
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
void Player::AddSpell(const Spell* newSpell)
	{
		spells.insert(newSpell);
	}
void Player::Buy(const EquipmentLine* purchasedEqLine)
	{
		AddEquipment(*purchasedEqLine);

		gold -= (purchasedEqLine->getTotalCost());
	}
void Player::Sell(const EquipmentLine* soldEqLine)
	{
		//postcondition: sold equipment quantity is subtracted from the quantity
		//the player has, and the equipment is removed entirely if they have none left
		//after selling.  An amount of gold equal to the sale price of the
		//equipment * sold quantity is added to player's gold count.

		EquipType soldType = soldEqLine->pEquipment->getType();
		map<const Equipment*, EquipmentLine>& inventory = getInventoryFor(soldType);

		EquipmentLine& invEqline = inventory[soldEqLine->pEquipment];
		if(invEqline.pEquipment == NULL)
		{
			//bug if we got this far...
			cout<<"You can't sell what you don't have!"<<endl;
			return;
		}

		invEqline -= (*soldEqLine);
		if(invEqline.quantity <= 0)
		{
			//don't want this equipment listed anywhere anymore if we're out of it
			inventory.erase(invEqline.pEquipment);
		}

		gold += soldEqLine->getTotalSellPrice();
	}

//accessor functions-------------------------------------------------//

int Player::Level() const
    {
        //postcondition:  returns the user's level number
        return lvl;
    }

Point Player::GetCoords() const
    {
        //postcondition:  returns the player's coordinates on the map
        return Coords;
    }
    
void Player::SetCoords(int x, int y)
    {
        //postcondition:  returns a player's x and y coordinates on the map
        Coords.x = x;
        Coords.y = y;
    }
    
int Player::NumToNext() const
    {
        //postcondition:  returns the amount of experience points the user
        //needs to advance to the next level up.
        
        return expToNext;
    }
map<const Equipment*, EquipmentLine>& Player::getInventoryFor(const EquipType equipType)
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
vector<EquipmentLine*>* Player::getWeaponsAndArmorAsVector()
	{
		//Postcondition: A vector is dynamically allocated to hold these, and
		//new EquipmentLines for each piece of equipment are also dynamically
		//allocated.  All of these allocations should be freed by the caller.

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
vector<EquipmentLine*>* Player::getItemsAsVector()
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
EquipmentLine& Player::getEquipmentLineFromInventoryFor(const Equipment* equipment)
	{
		switch(equipment->getType())
		{
		case WEAPON:
			return weapons[equipment];
			break;
		case ARMOR:
			return armor[equipment];
			break;
		case ITEM:
			return items[equipment];
			break;
		default:
			return items[equipment]; //will likely create a null equipment
			break;
		}
	}
vector<const Spell*>* Player::getSpells() const
{
	vector<const Spell*>* spellsVector = new vector<const Spell*>();
	for(set<const Spell*>::const_iterator it = spells.begin(); it != spells.end(); it++)
	{
		spellsVector->push_back((*it));
	}
	return spellsVector;
}

vector<const Spell*>* Player::getSpellsForLocale(SpellLocale locale) const
	{
		//postcondition: allocates a new vector containing only spell pointers
		//from the player's inventory that can be cast in the given locale.
		//Assumes caller will free the vector when done with it.

		vector<const Spell*>* spellsForLocale = new vector<const Spell*>();
		for(set<const Spell*>::const_iterator it = spells.begin(); it != spells.end(); it++)
		{
			set<int> eligibleLocations = (*it)->getEligibleLocations();
			if(eligibleLocations.find(locale) != eligibleLocations.end()) {
				spellsForLocale->push_back((*it));
			}
		}

		return spellsForLocale;
	}

const Equipment* Player::getCurrentEquipped(EquipType equipType)
	{
		return currentEquipped[equipType];
	}

void Player::dequipCurrent(EquipType equipType)
	{
		//postcondition: "dequips" the passed in equipment by subtracting its
		//stats from the player's current stats (since it's not equipped it doesn't
		//contribute stat gains anymore), adding the equipment back into the player's
		//inventory, and setting the currentEquipped equipment for its type back
		//to null.
		//Call before calling equip.  Called by apply() to ensure old equipment
		//is dequipped before new equipment is equipped.

		const Equipment* pCurrEquipment = getCurrentEquipped(equipType);
		if(pCurrEquipment == NULL) {
			return;
		}

		SubStats(pCurrEquipment->getStatMod());

		//Since equipping "removes" equipment from inventory, we need to put it back
		map<const Equipment*, EquipmentLine>& inv = getInventoryFor(equipType);
		EquipmentLine& invEqLine = inv[pCurrEquipment];
		if(invEqLine.pEquipment == NULL)
		{
			//if we had removed the last one when we currentEquipped the item, a blank EquipmentLine will have been re-instantiated by looking it up in the map, and needs populated
			invEqLine.pEquipment = pCurrEquipment;
		}
		invEqLine.quantity++;

		currentEquipped[equipType] =  NULL;
	}
void Player::equip(const Equipment* equipment)
	{
		//precondition: assumes equipment is in Player's inventory (should've
		//been validated by useEquipment()).
		//postcondition: "equips" the passed-in equipment by setting it as the
		//currentEquipped equipment for its type on the player, adding its stats
		//to the player's current stats.
		//
		//DO NOT use this method to perform the menu action of equipping - instead
		//use useEquipment(), which handles dequipping whatever the player has currently
		//equipped prior to calling this method before equipping the new equipment.
		//Not dequipping would cause the player to lose the current equipment,
		//rather than placing it back in their inventory, and also cause them
		//to build stats permanently by buying and equipping successful equipment
		//of the same type.

		currentEquipped[equipment->getType()] = equipment;
		AddStats(equipment->getStatMod());
	}
void Player::useEquipment(const Equipment* eq, Character& onTarget)
{
	//postcondition: apply() is called on the target, and the incoming equipment
	//is decremented from the quantity in the player's inventory.
	//If this reduces the quantity to 0, the entry for that equipment in the
	//player's inventory is removed entirely.

	//Sanity check that this method is actually being called with something the player has
	map<const Equipment*, EquipmentLine>& inv = getInventoryFor(eq->getType());
	EquipmentLine& invEqLine = inv[eq];
	if(invEqLine.pEquipment == NULL)
	{
		inv.erase(eq);//have to do this since inv[eq] will create a new line.
		cout<<"Attempted to use equipment you don't have in your inventory: "<<eq->getName()<<endl;
		return;
	}

	onTarget.apply(eq);

	//Regardless of the Equipment type, using it removes it from Player's active inventory
	(invEqLine.quantity)--;
	if(invEqLine.quantity <= 0)
	{
		inv.erase(eq); //remove line from inventory completely
	}
}

void Player::apply(const Equipment* eq)
	{
		//postcondition: The incoming Equipment is "applied" to the player, which
		//adds the stat changes from the Equipment to the player's stats.
		//For weapons and armor any previously-equipped equipment is also
		//removed first and placed back into the player's inventory.

		switch(eq->getType())
		{
		case WEAPON:
		case ARMOR:
			dequipCurrent(eq->getType());
			equip(eq);
			break;
		case ITEM:
			AddStats(eq->getStatMod());
		}
	}
