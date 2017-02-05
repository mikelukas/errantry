#include "logging/log.h"
#include "bossbattlemode.h"
#include "gamestate.h"
#include "winmode.h"

BossBattleMode::BossBattleMode(Monster bossMonster, GameData& gameData, GameState& gameState)
	: BattleMode(bossMonster, gameData, gameState)
{

}

void BossBattleMode::runFromBattle()
{
	log("Can't run from boss fight!");
}

void BossBattleMode::onBattleWon()
{
	//postcondition: in addition to normal resolution of battle, advance to next
	//boss on the list or enter Win Mode if all bosses are dead.

	BattleMode::onBattleWon();
	if(gameState.getCurrentBoss() >= 7)
	{
		GameMode* win = new WinMode(gameData, gameState);
		gameState.requestEnterMode(win);
	}
	gameState.advanceToNextBoss();
}
