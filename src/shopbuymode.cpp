#include "gamestate.h"
#include "shopbuymode.h"

ShopBuyMode::ShopBuyMode(vector<EquipmentLine*>* equipmentChoices, GameData& gameData, GameState& gameState)
	: ShopTransactionMode(equipmentChoices, gameData, gameState)
{

}

void ShopBuyMode::displayShopChoice(const EquipmentLine* eqLine) const
{
	cout<<"$"<<eqLine->pEquipment->getCost()<<setw(5)<<" - "<<eqLine->pEquipment->getName();
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
	gameState.getPlayer().Buy(equipmentChoice);
	cout<<"Bought "<<equipmentChoice->quantity<<" "<<equipmentChoice->pEquipment->getName()<<" for $"<<equipmentChoice->getTotalCost()<<"."<<endl;
}
