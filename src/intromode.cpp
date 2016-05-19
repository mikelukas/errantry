/*
 * intromode.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: mlukas
 */

#include "gamestate.h"
#include "intromode.h"
#include "overworldmode.h"

IntroMode::IntroMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState)
{

}

void IntroMode::run()
{
	char answer, start;
	do
	{
		cout<<"#/////**/----/**/////**/\**\\\\\**\----\**\\\\\#"<<endl
			<<"|                                              |"<<endl
			<<"|                                              |"<<endl
			<<"|                  Errantry                    |"<<endl
			<<"|                by Mike Lukas                 |"<<endl
			<<"|                                              |"<<endl
			<<"|                                              |"<<endl
			<<"#\\\\\**\----\**\\\\\**\/**/////**/----/**/////#"<<endl
			<<"Would you like to view the instructions?(y/n) ";
		cin>>answer;
	}while(!validateChoice(answer));

	if(answer == 'Y' || answer == 'y')
		{
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
		}
	cout<<"Type x and press enter to start the game:  ";
	cin>>start;
	cout<<"****************************************************"<<endl;

	GameMode* overworld  = new OverworldMode(gameData, gameState);
	gameState.requestEnterMode(overworld);
}

bool IntroMode::validateChoice(char answer)
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
