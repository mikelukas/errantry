#include "gamemode.h"
#include "gamestate.h"
#include "generalstoremainmode.h"
#include "shopbuymode.h"

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
	//TODO: implement
	cout<<"Just sellin' at the "<<currentTown.getName()<<" General Store!"<<endl;
}
