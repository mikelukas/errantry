#include "gamestate.h"
#include "shopbuymode.h"

ShopBuyMode::ShopBuyMode(const vector<Equipment*>* equipmentChoices, GameData& gameData, GameState& gameState)
	: ShopTransactionMode(equipmentChoices, gameData, gameState)
{

}

void ShopBuyMode::displayShopChoice(const Equipment* equipment) const
{
	cout<<"$"<<equipment->getCost()<<setw(5)<<" - "<<equipment->getName();
}

bool ShopBuyMode::validateShopChoice(const Equipment* equipment, int quantity) const
{
	int totalCost = equipment->getCost() * quantity;
	if(totalCost <= gameState.getPlayer().Money())
	{
		return true;
	}

	cout<<"Not enough gold! Total cost is $"<<totalCost<<"."<<endl;
	return false;
}

void ShopBuyMode::processTransaction()
{
	//TODO: After buy() is implemented on player, call it here w/ equipmentChoice to put it in player inventory
	int totalCost = equipmentChoice->getTotalCost();
	cout<<"Bought "<<equipmentChoice->quantity<<" "<<equipmentChoice->pEquipment->getName()<<" for $"<<totalCost<<"."<<endl;
}
