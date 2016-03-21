#include "armorymainmode.h"
#include "gamestate.h"

ArmoryMainMode::ArmoryMainMode(const Town& town, GameData& gameData, GameState& gameState)
	: ShopMainMode(town, gameData, gameState)
{

}

void ArmoryMainMode::enterBuyMode()
{
	//TODO: implement actual state change
	cout<<"Just buyin' at the "<<currentTown.getName()<<" Armory!"<<endl;
	gameState.exitCurrentMode();
}

void ArmoryMainMode::enterSellMode()
{
	//TODO: implement actual state change
	cout<<"Just sellin' at the "<<currentTown.getName()<<" Armory!"<<endl;
	gameState.exitCurrentMode();
}
