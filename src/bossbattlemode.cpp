/*
 * bossbattlemode.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: mlukas
 */

#include "bossbattlemode.h"

BossBattleMode::BossBattleMode(Monster& bossMonster, GameData& gameData, GameState& gameState)
	: BattleMode(bossMonster, gameData, gameState)
{

}

void BossBattleMode::runFromBattle()
{
	cout<<"Can't run from boss fight!"<<endl;
}

void BossBattleMode::onBattleWon()
{
	//postcondition: in addition to normal resolution of battle, advance to next
	//boss on the list or enter Win Mode if all bosses are dead.

	BattleMode::onBattleWon();
	gameState.advanceToNextBoss();
}
