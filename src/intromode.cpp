#include <iostream>
#include "logging/log.h"
#include "gamestate.h"
#include "intromode.h"
#include "overworldmode.h"

using std::cin;
using std::cout;
using std::endl;

IntroMode::IntroMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, false),
	  state(TITLE)
{

}

int IntroMode::updateDisplay()
{
	//postcondition: depending on the state we're in, display the title,
	//instructions, or a prompt for the player to enter their name

	switch(state)
	{
	case TITLE:
		displayTitle();
		break;
	case INSTRUCTIONS:
		displayInstructions();
		break;
	case PLAYER_NAME:
		displayNamePrompt();
		break;
	default:
		log("WARNING: Invalid IntroMode state encountered!"); //Bug if we have reached this point, this mode should only be able to set state to one of the valid enum values
	}

	return 1; //return value of this method is unused
}

void IntroMode::displayTitle()
{
	//postconditions: title screen is displayed to the player, with a prompt for instructions

	cout<<"#/////**/----/**/////**/\**\\\\\**\----\**\\\\\#"<<endl
		<<"|                                              |"<<endl
		<<"|                                              |"<<endl
		<<"|                  Errantry                    |"<<endl
		<<"|                by Mike Lukas                 |"<<endl
		<<"|                                              |"<<endl
		<<"|                                              |"<<endl
		<<"#\\\\\**\----\**\\\\\**\/**/////**/----/**/////#"<<endl
		<<"Would you like to view the instructions?(y/n) ";
}

void IntroMode::displayInstructions()
{
	//postcondition: Backstory and instructions to the player are displayed

	cout<<"The world you have just set foot in has become one of chaos."<<endl
		<<"Monsters ravish the land destroying all that once was beautiful"
  <<endl<<"to the people.  An errant warrior from another continent, it is"<<endl
		<<"your job to defeat these monsters and their evil controllers"<<endl
		<<"hiding in various caves around the continent.  Only after all"<<endl
		<<"7 have been defeated, can the monsters be vanquished and peace"<<endl
		<<"be restored."<<endl
		<<"Your position on the continent is marked by an X on the map."<<endl
		<<"You begin on the right side.  As you progress to the other"<<endl
		<<"side of the continent, beware, for the monsters become stronger."<<endl
		<<"The various C's along the map mark the entrances to caves."<<endl
		<<"By moving to the caves, you can fight the evil controllers" <<endl
		<<"of the monsters.  While you move around the map, you may encouner"<<endl
		<<"monsters.  By defeating these monsters, you can increase your"<<endl
		<<"experience points.  When you gain enough, you will advance 1"<<endl
		<<"level.  Every level advance allows you to increase your attributes"<<endl
		<<"and become stronger.  If you are defeated by a monster in battle,"<<endl
		<<"you lose the game.  You may view your statistics at any time"<<endl
		<<"by choosing that option on the map menu.  Build your levels"<<endl
		<<"so that you are stronger and can fight monsters and controllers"<<endl
		<<"better!  Good luck and enjoy Errantry!"<<endl;
	cout<<"Type x and press enter to start the game:  ";
}

void IntroMode::displayNamePrompt()
{
	//postcondition: player is prompted to enter their name

	cout<<"Greetings wanderer, tell me your name:  ";
}

bool IntroMode::processInput(int choice)
{
	//postcondition: await input appropriate for the particular state this mode
	//is in, and act upon what is entered

	char answer;

	switch(state)
	{
	case TITLE: {
		do{
			cin>>answer;
		} while(!validateChoice(answer));

		state = ((answer == 'Y' || answer == 'y') ? INSTRUCTIONS : PLAYER_NAME);
		return true;
	}
	case INSTRUCTIONS: {
		cin>>answer;
		state = PLAYER_NAME;
		return true;
	}
	case PLAYER_NAME: { //Waits for player to type their name, sets the Player object's name with it, and requests we enter OverworldMode
		string name;
		cin>>name;
		cout<<endl;
		gameState.getPlayer().setName(name);

		//Request we enter Overworld mode now that everything is set up
		GameMode* overworld  = new OverworldMode(gameData, gameState);
		gameState.requestEnterMode(overworld);

		state = TITLE; //put state back into TITLE mode display, in case we were to ever re-enter this mode somehow
		return true;
	}
	default:
		return true;
	}

}

bool IntroMode::validateChoice(char answer)
{
	//postcondition:  determines if response entered by user is
	//a valid response character and returns true if so, false
	//if not.
	if(answer == 'Y' || answer == 'y' || answer == 'n' || answer == 'N')
		return true;
	else
		log("Invalid Response");
	return false;
}

void IntroMode::initPlayerName()
{
	//postcondition: player is prompted to enter their name, and what they type
	//is set as the Player object's name.

	string name;
    cout<<"Greetings wanderer, tell me your name:  ";
    cin>>name;
    cout<<endl;

    gameState.getPlayer().setName(name);
}
