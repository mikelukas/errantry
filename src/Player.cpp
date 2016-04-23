//Mike Lukas - p2prog03- player.cpp-
//Functions and explanations for the player class.

#include <iostream>
#include "player.h"

using std::cout;
using std::cin;
using std::endl;

//Constructors---------------------------------------------------------------//

Player::Player()
    : HP(BEGINHP),
      maxHP(BEGINHP),
      AP(BEGINAP),
      DP(BEGINDP),
      SP(BEGINSP),
      gold(BEGINGOLD),
      expPoints(0),
      expToNext(100),
      lvl(1),
      Coords(STARTPOS)
    {
        //attribute variables initialized in initializer list
        cout<<"Greetings wanderer, tell me your name:  ";
        cin>>playerName;
        cout<<endl;

        initStartingEquipment();
    }
Player::Player(int hpVar, int apVar, int dpVar,
               int spVar, int money, int level)
    : HP(hpVar),
      maxHP(hpVar),
      AP(apVar),
      DP(dpVar),
      SP(spVar),
      gold(money)
    {
        //postcondition:  Player statistics are initialized to the specific
        //values sent to the function
                
        lvl = level;
        
        cout<<"Greetings wanderer, tell me your name:  ";
        cin>>playerName;
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
void Player::ChangeHP(int hpChange)
    {
        //postcondition:  HP value of character altered by the value
        //sent to the function; if damage is done, a negative value
        //is added to HP, if health is gained, a positive value is
        //added to HP
        
        HP = HP + hpChange;
    }
void Player::Buy(const EquipmentLine* purchasedEqLine)
	{
		EquipType purchaseType = purchasedEqLine->pEquipment->getType();
		map<const Equipment*, EquipmentLine>& inventory = getInventoryFor(purchaseType);

		EquipmentLine& eqLine = inventory[purchasedEqLine->pEquipment];
		if(eqLine.pEquipment != NULL)
		{
			eqLine += (*purchasedEqLine);
		}
		else {
			inventory[purchasedEqLine->pEquipment] = (*purchasedEqLine);
		}

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

string Player::ShowName() const
    {
        //postcondition:  returns the name of the player
        return playerName;
    }
int Player::Damage() const
    {
        //postcondition:  returns the amount of damage the player can do (AP)
        return AP;
    }

int Player::Defense() const
    {
        //postcondition:  returns user's defense points
        return DP;
    }

int Player::Health() const
    {
        //postcondition:  returns user's health points
        return HP;
    }
    
int Player::MaxHealth() const
    {
        //postcondition:  returns user's maximum health points
        return maxHP;
    }
    
int Player::Speed() const
    {
        //postcondition:  returns the character's speed points
        return SP;
    }
int Player::Money() const
    {
        //postcondition:  returns the amount of gold the character is carrying
        return gold;
    }
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
                    
int Player::NumExpPts() const
    {
        //postcondition:  returns the user's current experience point total
        return expPoints;
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
			EquipmentLine* eqLine = new EquipmentLine(it->second);
			equipmentChoices->push_back(eqLine);
		}

		for(map<const Equipment*,EquipmentLine>::iterator it=invArmor.begin(); it!=invArmor.end(); it++)
		{
			EquipmentLine* eqLine = new EquipmentLine(it->second);
			equipmentChoices->push_back(eqLine);
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
const Equipment* Player::getCurrentEquipped(EquipType equipType)
	{
		return currentEquipped[equipType];
	}
void Player::AddStats(const StatMod& stats)
	{
		HP += stats.hpMod;
		AP += stats.apMod;
		DP += stats.dpMod;
		SP += stats.spMod;
	}
void Player::SubStats(const StatMod& stats)
	{
		HP -= stats.hpMod;
		AP -= stats.apMod;
		DP -= stats.dpMod;
		SP -= stats.spMod;
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
		//postcondition: "equips" the passed in equipment by setting it as the
		//currentEquipped equipment for its type on the player, adding its stats
		//to the player's current stats, and subtracting 1 from its quantity in
		//the player's unequipped inventory (since equipped equipment isn't allowed
		//to be sold)
		//DO NOT use this method to perform the menu action of equipping - instead
		//use apply(), which handles dequipping whatever the player has currently
		//equipped prior to calling this method before equipping the new equipment.
		//Not dequipping would cause the player to lose the current equipment,
		//rather than placing it back in their inventory, and also cause them
		//to build stats permanently by buying and equipping successful equipment
		//of the same type.

		map<const Equipment*, EquipmentLine>& inv = getInventoryFor(equipment->getType());
		EquipmentLine& invEqLine = inv[equipment];
		if(invEqLine.pEquipment == NULL)
		{
			cout<<"Attempted to equip something you don't have in your inventory: "<<equipment->getName()<<"! Don't cheat!";
			return;
		}

		currentEquipped[equipment->getType()] = equipment;
		AddStats(equipment->getStatMod());

		//Equipping something removes it from your inventory
		invEqLine.quantity--;
		if(invEqLine.quantity <= 0)
		{
			inv.erase(equipment); //remove line from inventory completely
		}
	}

void Player::apply(EquipmentLine* invEqLine)
	{
		//postcondition: The incoming EquipmentLine is "applied" to the player.
		//For weapons and armor this means it is moved out of the player's inventory
		//and set as their current equipment, with stat gains applied.  Any
		//previously-equipped equipment is removed first and placed back into the
		//player's inventory.
		//For items, this means the effect of the item is applied to the player
		//and the item's quantity is decreased.

		switch(invEqLine->pEquipment->getType())
		{
		case WEAPON:
		case ARMOR:
			dequipCurrent(invEqLine->pEquipment->getType());
			equip(invEqLine->pEquipment);
			break;
		case ITEM:
			AddStats(invEqLine->pEquipment->getStatMod());

			//assumes eqLine came from your inventory
			(invEqLine->quantity)--;
			if(invEqLine->quantity <= 0)
			{
				map<const Equipment*, EquipmentLine>& inv = getInventoryFor(invEqLine->pEquipment->getType());
				inv.erase(invEqLine->pEquipment); //remove line from inventory completely
			}
		}
	}
