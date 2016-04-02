#include "armorymainmode.h"
#include "gamestate.h"
#include "shopbuymode.h"
#include "shopsellmode.h"

ArmoryMainMode::ArmoryMainMode(const Town& town, GameData& gameData, GameState& gameState)
	: ShopMainMode(town, gameData, gameState)
{

}

void ArmoryMainMode::enterBuyMode()
{
	//postcondition: Enters ShopBuyMode with current town's weapon and armor list.
	//Dynamically allocates EquipmentLines for each piece, and also allocates a
	//vector to hold them, all of which will be cleaned up in ShopTransactionMode's
	//destructor.

	const vector<Equipment*> allWeapons = gameData.getWeapons();
	const vector<Equipment*> allArmor = gameData.getArmor();

	const vector<int> shopWeaponIds = currentTown.getShopEquipmentIds(WEAPON);
	const vector<int> shopArmorIds = currentTown.getShopEquipmentIds(ARMOR);

	vector<EquipmentLine*>* equipmentChoices = new vector<EquipmentLine*>; //will be deleted by ShopTransactionMode

	for(int i = 0; i < shopWeaponIds.size(); i++)
	{
		EquipmentLine* eqLine = new EquipmentLine(allWeapons[shopWeaponIds[i]], INF_QUANTITY);
		equipmentChoices->push_back(eqLine);
	}

	for(int i = 0; i < shopArmorIds.size(); i++)
	{
		EquipmentLine* eqLine = new EquipmentLine(allArmor[shopArmorIds[i]], INF_QUANTITY);
		equipmentChoices->push_back(eqLine);
	}

	GameMode* shopBuyMode = new ShopBuyMode(equipmentChoices, gameData, gameState);
	gameState.enterMode(shopBuyMode);
}

void ArmoryMainMode::enterSellMode()
{
	//postcondition: Enter ShopSellMode with weapons and armor from player's inventory.
	//A vector is dynamically allocated to hold these, and new EquipmentLines for each
	//piece of equipment are also dynamically allocated.  All of these allocations
	//are freed in ShopTransactionMode's destructor when exiting the mode.

	map<const Equipment*, EquipmentLine>& invWeapons = gameState.getPlayer().getInventoryFor(WEAPON);
	map<const Equipment*, EquipmentLine>& invArmor = gameState.getPlayer().getInventoryFor(ARMOR);

	vector<EquipmentLine*>* equipmentChoices = new vector<EquipmentLine*>; //will be deleted by ShopTransactionMode

	for(map<const Equipment*,EquipmentLine>::iterator it=invWeapons.begin(); it!=invWeapons.end(); it++)
	{
		EquipmentLine* eqLine = new EquipmentLine(it->second);
		equipmentChoices->push_back(eqLine);
	}

	for(map<const Equipment*,EquipmentLine>::iterator it=invArmor.begin(); it!=invArmor.end(); it++)
	{
		EquipmentLine* eqLine = new EquipmentLine(it->second);
		equipmentChoices->push_back(eqLine);
	}

	GameMode* shopBuyMode = new ShopSellMode(equipmentChoices, gameData, gameState);
	gameState.enterMode(shopBuyMode);
}
