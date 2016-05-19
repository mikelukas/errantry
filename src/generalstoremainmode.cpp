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
	gameState.requestEnterMode(shopBuyMode);
}

void GeneralStoreMainMode::enterSellMode()
{
	//postcondition:  Enter ShopSellMode with weapons and armor from player's inventory.
	//Equipment choices vector (but not EquipmentLines there-in) will be freed by ShopTransactionMode

	vector<EquipmentLine*>* equipmentChoices = gameState.getPlayer().getItemsAsVector();

	GameMode* shopBuyMode = new ShopSellMode(equipmentChoices, gameData, gameState);
	gameState.requestEnterMode(shopBuyMode);
}
