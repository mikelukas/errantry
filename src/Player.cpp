//Mike Lukas - p2prog03- Member function definition for player class-
//Function explanations also included.

#include <iostream>
#include <ctype.h>
#include "player.h"

using std::cout;
using std::cin;

//Constructors---------------------------------------------------------------//

Player::Player()
    : HP(BEGINHP),
      maxHP(BEGINHP),
      MP(BEGINMP),
      maxMP(BEGINMP),
      AP(BEGINAP),
      DP(BEGINDP),
      MDP(BEGINMDP),
      SP(BEGINSP),
      gold(BEGINGOLD),
      spellCount(0),
      weapCount(0),
      armCount(0),
      itemCount(0),
      expPoints(0),
      expToNext(100),
      lvl(1)
     
    {
        //attribute variables initialized in initializer list
        int lcv;
        
        Coords.x = 0;
        Coords.y = 0;
        eArmor.name = "none";
        eWeapon.name = "none";
        Spells.resize(MAXEQUIPMENT);
        for(lcv = 0; lcv<MAXEQUIPMENT; lcv++)
            {
                Spells[lcv].MAP = 0;
                Spells[lcv].cost = 0;
                Spells[lcv].name = "none";
                Spells[lcv].element = none;
            }
        InitializeInventory(Weapons, weapon);
        InitializeInventory(Armor, armor);
        InitializeInventory(Items, item);
        cout<<"Greetings wanderer, tell me your name:  ";
        cin>>playerName;
        cout<<endl;
    }
Player::Player(int hpVar, int mpVar, int apVar, int dpVar, int mdpVar, 
               int spVar, int money, int level)
    : HP(hpVar),
      maxHP(hpVar),
      MP(mpVar),
      maxMP(mpVar),
      AP(apVar),
      DP(dpVar),
      MDP(mdpVar),
      SP(spVar),
      gold(money)
    {
        //postcondition:  Player statistics are initialized to the specific
        //values sent to the function
                
        spellCount = 0;
        weapCount = 0;
        armCount = 0;
        itemCount = 0;
        lvl = level;
        
        cout<<"Greetings wanderer, tell me your name:  ";
        cin>>playerName;
        cout<<endl;
    }
//Public Member Functions-----------------------------------------------//

void Player::AddSpell(SpellType& newSpell)
    {
        //postcondition:  newSpell added to the list of spells held 
        //in 'Spells'
        
        Spells[spellCount] = newSpell;
        spellCount++;
    }
void Player::AddEquip(apvector<EquipType>& EquipList, EquipType& newItem)
    {
        //postcondition:  newItem added to the equipment list sent to
        //the function ('EquipList')
        
        int index = 0;
        int amtItems = GetItemCount(newItem);
        bool found = FindItem(EquipList, newItem.name, index, amtItems);        
        
        if(found == true)
            EquipList[index].quantity++;
        else
            {
                EquipList[amtItems] = newItem;      
                ChangeCount(newItem, 'U');
            }
    }
void Player::RemoveEquip(apvector<EquipType>& EquipList, EquipType& oldItem)
    {
        //Postcondition:  item is removed from the equipment list sent to 
        //the function ('EquipList')
        
        int index = 0;
        int numItems = GetItemCount(oldItem);
        bool found = FindItem(EquipList, oldItem.name, index, numItems);
     
        if(found == true)
            {
                if(oldItem.quantity > 0)
                    EquipList[index].quantity--;        
                else
                    {
                        EquipList[index].statUp = 0;
                        EquipList[index].cost = 0;
                        EquipList[index].quantity = 0;
                        EquipList[index].name = "none";
                        EquipList[index].type = oldItem.type;
                        ChangeCount(oldItem, 'D');
                    }
            }
        else
            cout<<"You don't have that item to remove."<<endl;
                            
    }
void Player::OverwriteSpell(SpellType& newSpell)
    {
        //postcondition:  newSpell replaces a user selected spell
        //(oldSpell) in the list of spells held in 'Spells'
        
        int index = 0;
        bool found;
        char response;
        apstring oldSpell;
                
        cout<<"Which spell do you want to overwrite?  ";
        cin>>oldSpell;
        do
         {
            cout<<"Are you sure you want to overwrite this spell?(y/n)  ";
            cin>>response;                  
         }while(Validate(response));
            
        if(response == 'y' || response == 'Y')
            {
                 found = FindSpell(Spells, oldSpell, index, spellCount);
                 
                 if(found == true)
                    {
                        Spells[index] = newSpell;
                        cout<<oldSpell<<" was erased and you learned "
                            <<newSpell.name<<endl;
                    }
                 else
                    cout<<"You don't have that spell."<<endl;
            }
        else
            {
                cout<<oldSpell<<" will not be overwritten"<<endl;
            }
    }
void Player::OverwriteEquip(apvector<EquipType>& EquipList, EquipType& newItem)
    {
        //postcondition:  newItem replaces a user selected item
        //(oldItem) in the list of equipment sent to 'EquipList'
        int index = 0;
        int numItems = GetItemCount(newItem);
        bool found;
        char response;
        apstring oldItem;
                
        cout<<"Which piece of equipment do you want to replace?  ";
        cin>>oldItem;
        do
         {
            cout<<"Are you sure you want to replace this item?(y/n)  ";
            cin>>response;                  
         }while(Validate(response));
            
        if(response == 'y' || response == 'Y')
            {
                
                 found = FindItem(EquipList, oldItem, index, 
                                             numItems);
                 if(found == true)
                    {
                        EquipList[index] = newItem;
                        cout<<oldItem<<" was replaced and you received "
                            <<newItem.name<<endl;
                    }
                 else
                    cout<<"You don't have that item."<<endl;
            }
        else
            {
                cout<<oldItem<<" will not be replaced"<<endl;
            }
    }

void Player::LevelUp()
    {
        //postcondition:  player's attributes are increased;
        //user chooses whether he/she wants to increase a certain
        //attack or defense attribute greater than the others, while
        //the player's HP, MP, SP, lvl, and expToNext are changed by
        //the same rates every time.
        
        int lcv, choice;
        
        HP = HP + int(HP * HPRATE);
        MP = MP + int(MP * MPRATE);
        if(lvl % SPRATE == 0)
            SP++;
        lvl++;
        expToNext = expToNext + int(expToNext * NEXTRATE);
        
        cout<<"Congratulations, your level is now "<<lvl<<"!"<<endl;
        cout<<"--------------------------------------"<<endl;
        
        do
         {
            cout<<"Increase:  1) attack"<<endl
                <<"           2) defense"<<endl
                <<"           3) magic attack power"<<endl
                <<"           4) magic defense"<<endl;
            cout<<"Choice:  ";
            cin>>choice;
            cout<<"--------------------------------------"<<endl;
         }while(Validate(choice, 4));
         
         switch(choice)
            {
                case 1: //Attack
                    AP = AP + int(AP * BIGRATE);
                    DP = DP + int(AP * FLATRATE);
                    for(lcv = 0; lcv<spellCount; lcv++)
                        {
                            Spells[lcv].MAP = Spells[lcv].MAP
                                        + int(Spells[lcv].MAP * FLATRATE);
                        }
                    MDP = MDP + int(MDP * FLATRATE);
                    break;
                case 2: //Defense
                    AP = AP + int(AP * FLATRATE);
                    DP = DP + int(AP * BIGRATE);
                    for(lcv = 0; lcv<spellCount; lcv++)
                        {
                            Spells[lcv].MAP = Spells[lcv].MAP
                                        + int(Spells[lcv].MAP * FLATRATE);
                        }
                    MDP = MDP + int(MDP * FLATRATE);
                    break;
                case 3: //MagicAttack
                    AP = AP + int(AP * FLATRATE);
                    DP = DP + int(AP * FLATRATE);
                    for(lcv = 0; lcv<spellCount; lcv++)
                        {
                            Spells[lcv].MAP = Spells[lcv].MAP
                                        + int(Spells[lcv].MAP * BIGRATE);
                        }
                    MDP = MDP + int(MDP * FLATRATE);
                    break;
                case 4:  //MagicDefense
                    AP = AP + int(AP * FLATRATE);
                    DP = DP + int(AP * FLATRATE);
                    for(lcv = 0; lcv<spellCount; lcv++)
                        {
                            Spells[lcv].MAP = Spells[lcv].MAP
                                        + int(Spells[lcv].MAP * FLATRATE);
                        }
                    MDP = MDP + int(MDP * BIGRATE);
                    break;
            }
            
        }

void Player::ChangeCount(EquipType& equipItem, char changeHow)
    {
        //postcondition:  The number of items of a certain type of item
        //sent to the function is increased or decreased depending on
        //which way the user wants the count changed
        
        switch(equipItem.type)
            {
                case weapon:
                    if(changeHow == 'U')  //U for Up
                        weapCount++;
                    else
                        weapCount--;
                    break;
                case armor:
                    if(changeHow == 'U')
                        armCount++;
                    else
                        armCount--;
                    break;
                case item:
                    if(changeHow == 'U')
                        itemCount++;
                    else
                        itemCount--;
                    break;
            }
    }
void Player::EquipItem(EquipType& Item)
    {
        //postcondition:  adds a weapon's attack power to the user's attack
        //power or an armor's defense points to the user's defense points 
        //as though the player were "using" the item (equipped) and sets
        //the equipped item (eWeapon or eArmor) to whatever item that was
        //sent to the function
        
        switch(Item.type)
            {
                case weapon:
                    if(eWeapon.name != "none")
                        Unequip(eWeapon);
                    eWeapon.name = Item.name;
                    AP = AP + Item.statUp;
                    break;
                case armor:
                    if(eArmor.name != "none")
                        Unequip(eArmor);
                    eArmor.name = Item.name;
                    DP = DP + Item.statUp;
                    break;
                default:
                    cout<<"Not an equipable item!"<<endl;
                    
            }
    }
                
void Player::Unequip(EquipType& Item)
    {
        //postcondition:  subtracts the equipped item's (eWeapon or eArmor)
        //attack power or defense points from the user's total and sets 
        //the equipped item (eWeapon or eArmor) to empty.
        
        switch(Item.type)
            {
                case weapon:
                    AP = AP - Item.statUp;
                    eWeapon.statUp = 0;
                    eWeapon.cost = 0;
                    eWeapon.quantity = 0;
                    eWeapon.name = "none";
                    break;
                case armor:
                    DP = DP - Item.statUp;
                    eArmor.statUp = 0;
                    eArmor.cost = 0;
                    eArmor.quantity = 0;
                    eArmor.name = "none";
                    break;
            }
    }

void Player::BuyItem(apvector<EquipType>& EquipList, EquipType& Item, int cost)
    {
        //postcondition:  adds an item to the user's inventory and subtracts
        //cost of the item from the user's gold total as if they had "bought"
        //the item.  If they don't have enough money, then they are given a
        //message stating so, and the item is not purchased.
        
        int numItems = GetItemCount(Item);
        
        if(numItems < MAXEQUIPMENT)
            {
                if(cost <= gold)
                    {
                        gold = gold - cost;
                        AddEquip(EquipList, Item);
                    }
                else
                    cout<<"Not enough money!"<<endl;
            }
        else
            cout<<"Too much, sell an item!";
    }

void Player::SellItem(apvector<EquipType>& EquipList, EquipType& Item)
    {
        //postcondition:  subtracts an item from the user's inventory and
        //adds half of the item's cost back to the user's gold total as if
        //they "sold" the item used.  If an item is selected to sell that
        //the user doesn't have, they are told that they do not have the item
        //and nothing is changed.
                
        int index = 0;
        int numItems = GetItemCount(Item);
        bool found = FindItem(EquipList, Item.name, index, numItems);
        
        if(found == true)
            {
                if(Item.quantity == 1)
                    {
                        RemoveEquip(EquipList, Item);
                        ChangeCount(Item, 'D');
                    }
                else
                    Item.quantity--;
                gold = gold + (Item.cost/2);
                                
            }
        else
            cout<<"That item is not in your inventory"<<endl;
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
void Player::MoveCoords(int x, int y)
    {
        //postcondition:  changes the player's position on the map to the
        //coordinates sent
        
        Coords.x = x;
        Coords.y = y;
    }
void Player::ChangeHP(int hpChange)
    {
        //postcondition:  HP value of character altered by the value
        //sent to the function; if damage is done, a negative value
        //is added to HP, if health is gained, a positive value is
        //added to HP
        
        HP = HP + hpChange;
    }
void Player::ChangeMP(int mpChange)
    {
        //postcondition:  MP value of character altered by the value
        //sent to the function; if a spell is used, a negative value
        //is added to MP, if MP is gained, a positive value is
        //added to MP
        
        MP = MP + mpChange;
    }
//accessor functions-------------------------------------------------//

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

int Player::MEnergy() const
    {
        //postcondition:  returns the character's magic points
        return MP;
    }

int Player::MDefense() const
    {
        //postcondition:  returns the character's magic defense points
        return MDP;
    }

int Player::Speed() const
    {
        //postcondition:  returns the character's speed points
        return SP;
    }

int Player::Money() const
    {
        //postcondition:  returns amount of gold the character has
        return gold;
    }
int Player::MDamage(SpellType& spell)
    {
        //postcondition:  returns the magic attack points for a 
        //certain spell 
        
        int index = 0;
        bool found = FindSpell(Spells, spell.name, index, spellCount);
        
        if(found == true)
            {
                return spell.MAP;
            }
        else
            cout<<"You don't have that spell"<<endl;
        return 0;
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

//Private Member Functions---------------------------------------------------//

int Player::GetItemCount(EquipType& equipItem) const
    {
        //postcondition:  The number of items of a certain type of item sent
        //to the function is returned
        
        switch(equipItem.type)
            {
                case weapon:
                    return weapCount;
                    break;
                case armor:
                    return armCount;
                    break;
                case item:
                    return itemCount;
                    break;
            }
    }
    
bool Player::FindItem(apvector<EquipType>& EquipList, apstring& itemName,
                      int& index, int numItems) const
    { 
        //postcondition:  when given a certain list and item, this function
        //returns if the user has that item and if so, what number that item
        //is on the list given
        
        int lcv = -1;
        bool found = false;
        tolower(itemName[0]);
        
        do
         {
            lcv++;
            tolower(EquipList[lcv].name[0]);
                    
            if(itemName == EquipList[lcv].name)
                found = true;
            
            toupper(EquipList[lcv].name[0]);
                    
         }while(lcv<numItems && found == false);
         
         toupper(itemName[0]);
         index = lcv;
         return found;
    }
bool Player::FindSpell(apvector<SpellType>& spellList, apstring& itemName,
                       int& index, int numItems) const
    { 
        //postcondition:  when given a certain list and item, this function
        //returns if the user has that item and if so, what number that item
        //is on the list given
        
        int lcv = -1;
        bool found = false;
        tolower(itemName[0]);
        
        do
         {
            lcv++;
            tolower(spellList[lcv].name[0]);
                    
            if(itemName == spellList[lcv].name)
                found = true;
            
            toupper(spellList[lcv].name[0]);
         }while(lcv<numItems && found == false);
         
         toupper(itemName[0]);
         index = lcv;
         return found;
    }
void Player::InitializeInventory(apvector<EquipType>& EquipList, type equipType)
    {
        int lcv;
        
        EquipList.resize(MAXEQUIPMENT);
        for(lcv = 0; lcv< MAXEQUIPMENT; lcv++)
            {
                EquipList[lcv].statUp = 0;
                EquipList[lcv].cost = 0;
                EquipList[lcv].quantity = 0;
                EquipList[lcv].type = equipType;
                EquipList[lcv].name = "none";
            }
    }
//free functions-------------------------------------------------------------//

bool Validate(char answer)
    {
        //postcondition:  determines if response entered by user is
        //a valid response character and returns true if so, false
        //if not.
        if(answer == 'Y' || answer == 'y' || answer == 'n' || answer == 'N')
            return true;
        else
            cout<<"Invalid Response"<<endl;
        return false;
    }
bool Validate(int answer, int numChoices)
    {
        //postcondition:  determines if response entered by user is
        //a valid response number and returns true if so, false
        //if not.
        if(answer != 1 && answer<=numChoices)
            return true;
        else
            cout<<"Invalid Response"<<endl;
        return false;
    }

#endif
