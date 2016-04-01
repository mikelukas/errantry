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
