//Mike Lukas - p2prog03-      -Errantry2.cpp-
//This program is game called Errantry which is fantasy adventure game.
//In it, the user may travel around a map and fight monsters.  The goal
//is to defeat all 7 of the boss monsters which are found only in caves
//on the map.  While the user is moving, he/she may encounter and fight
//monsters.  If the player defeats the monster, he/she will gain 
//experience points, which when enough are earned, promote the player 
//by one level and increase his/her attributes.  It is to the player's
//advantage to move around a lot and gain experience, because by 
//increase his/her attributes, the player has a better chance of defeating
//the bosses which are stronger than the regular enemies.  The output from
//this program includes the map the user travels on and his/her position
//on it or a battle display with player and enemy information displayed,
//a menu of actions the user may take while on the map, a menu of actions
//the user may take while in battle, and other comments regarding 
//experienced being earned and levels being increased.  Also, it will
//display an ending message when the game is lost or won, as well as
//instructions in the beginning.  

#include "logging/consoleappender.h"
#include "logging/log.h"
#include "gamedata.h"
#include "gamestate.h"
#include "intromode.h"
 
void MainGame(GameData& gameData, GameState& gameState);

int main()
    {
		Log::init(new ConsoleAppender());

        GameData gameData;
        GameState gameState;

        if(!gameData.loadSuccessful())
        	{
        		log("ERROR:  Could not read one or more data files!");
        		return 1;
        	}

		MainGame(gameData, gameState);

        return 0;
    }

void MainGame(GameData& gameData, GameState& gameState)
    {
        //This function controls the main game.  It displays the
        //appropriate menus for the game's state(battle or map (overworld))
        //and also indirectly carries out all of the actions a user may
        //perform by calling the functions that perform those actions.
        
		GameMode* startingMode = new IntroMode(gameData, gameState);
	    gameState.requestEnterMode(startingMode);
	    gameState.handleEnterModeRequest();

        while(!gameState.isGameOver())
            {
        		gameState.getCurrentMode()->processStatusEffects();
        		gameState.getCurrentMode()->run();

        		gameState.handleExitModeRequest();
        		gameState.handleEnterModeRequest();
            }
    }
