//Mike Lukas - p2prog03- player.cpp-
//Functions and explanations for the player class.

#include <iostream.h>
#include "chtypes1.h"

//Constructors---------------------------------------------------------------//

Player::Player()
    : HP(BEGINHP),
      maxHP(BEGINHP),
      AP(BEGINAP),
      DP(BEGINDP),
      SP(BEGINSP),
      expPoints(0),
      expToNext(100),
      lvl(1)
     
    {
        //attribute variables initialized in initializer list
        
        Coords.x = 0;
        Coords.y = 0;
        
        cout<<"Greetings wanderer, tell me your name:  ";
        cin>>playerName;
        cout<<endl;
    }
Player::Player(int hpVar, int apVar, int dpVar,
               int spVar, int level)
    : HP(hpVar),
      maxHP(hpVar),
      AP(apVar),
      DP(dpVar),
      SP(spVar)
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
        
        HP = HP + int(HP * HPRATE);
        maxHP = HP;
                
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

void Player::ChangeHP(int hpChange)
    {
        //postcondition:  HP value of character altered by the value
        //sent to the function; if damage is done, a negative value
        //is added to HP, if health is gained, a positive value is
        //added to HP
        
        HP = HP + hpChange;
    }

//accessor functions-------------------------------------------------//

apstring Player::ShowName() const
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
        if(answer >0 && answer<=numChoices)
            return true;
        else
            cout<<"Invalid Response"<<endl;
        return false;
    }