#include "gamemode.h"
#include "gamestate.h"
#include "generalstoremainmode.h"
#include "shopbuymode.h"
#include "shopsellmode.h"

GeneralStoreMainMode::GeneralStoreMainMode(const Town& town, GameData& gameData, GameState& gameState)
	: ShopMainMode(town, gameData, gameState)
{

}

void GeneralStoreMainMode::enterBuyMode()
{
	//postcondition: Enters ShopBuyMode with current town's item list.
	//Dynamically allocates EquipmentLines for each item, and also allocates a
	//vector to hold them, all of which will be cleaned up in ShopTransactionMode's
	//destructor.

	const vector<Equipment*> allItems = gameData.getItems();
	const vector<int> shopItemIds = currentTown.getShopEquipmentIds(ITEM);

	vector<EquipmentLine*>* equipmentChoices = new vector<EquipmentLine*>; //will be deleted by ShopTransactionMode

	for(int i = 0; i < shopItemIds.size(); i++)
	{
		EquipmentLine* eqLine = new EquipmentLine(allItems[shopItemIds[i]], INF_QUANTITY);
		equipmentChoices->push_back(eqLine);
	}

	GameMode* shopBuyMode = new ShopBuyMode(equipmentChoices, gameData, gameState);
	gameState.enterMode(shopBuyMode);
}

void GeneralStoreMainMode::enterSellMode()
{
	//postcondition: Enter ShopSellMode with items from player's inventory.
	//A vector is dynamically allocated to hold these, and new EquipmentLines for each
	//piece of equipment are also dynamically allocated.  All of these allocations
	//are freed in ShopTransactionMode's destructor when exiting the mode.

	map<const Equipment*, EquipmentLine>& invItems = gameState.getPlayer().getInventoryFor(ITEM);

	vector<EquipmentLine*>* equipmentChoices = new vector<EquipmentLine*>; //will be deleted by ShopTransactionMode

	for(map<const Equipment*,EquipmentLine>::iterator it=invItems.begin(); it!=invItems.end(); it++)
	{
		EquipmentLine* eqLine = new EquipmentLine(it->second);
		equipmentChoices->push_back(eqLine);
	}

	GameMode* shopBuyMode = new ShopSellMode(equipmentChoices, gameData, gameState);
	gameState.enterMode(shopBuyMode);
}
