#include "armorymainmode.h"
#include "gamestate.h"
#include "shopbuymode.h"

ArmoryMainMode::ArmoryMainMode(const Town& town, GameData& gameData, GameState& gameState)
	: ShopMainMode(town, gameData, gameState)
{

}

void ArmoryMainMode::enterBuyMode()
{
	const vector<Equipment*> allWeapons = gameData.getWeapons();
	const vector<Equipment*> allArmor = gameData.getArmor();

	const vector<int> shopWeaponIds = currentTown.getShopEquipmentIds(WEAPON);
	const vector<int> shopArmorIds = currentTown.getShopEquipmentIds(ARMOR);

	vector<Equipment*>* equipmentChoices = new vector<Equipment*>;

	for(int i = 0; i < shopWeaponIds.size(); i++)
	{
		Equipment* eq = allWeapons[shopWeaponIds[i]];
		equipmentChoices->push_back(eq);
	}

	for(int i = 0; i < shopArmorIds.size(); i++)
	{
		equipmentChoices->push_back(allArmor[shopArmorIds[i]]);
	}

	GameMode* shopBuyMode = new ShopBuyMode(equipmentChoices, gameData, gameState);
	gameState.enterMode(shopBuyMode);
}

void ArmoryMainMode::enterSellMode()
{
	//TODO: implement actual state change
	cout<<"Just sellin' at the "<<currentTown.getName()<<" Armory!"<<endl;
	gameState.exitCurrentMode();
}
