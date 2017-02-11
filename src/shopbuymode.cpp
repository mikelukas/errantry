#include <sstream>
#include "logging/log.h"
#include "gamestate.h"
#include "shopbuymode.h"

ShopBuyMode::ShopBuyMode(vector<EquipmentLine*>* equipmentChoices, GameData& gameData, GameState& gameState)
	: ShopTransactionMode(equipmentChoices, gameData, gameState)
{

}

ShopBuyMode::~ShopBuyMode()
{
	if(equipmentChoices == NULL)
	{
		return;
	}

	//for BuyModes, all EquipmentLine* in choices vector were dynamically allocated,
	//since they are created from the shops' inventories which have unlimited amounts
	//TODO: to avoid having to de-allocate here, shop inventory could be Eq lines, rather than just Equipment.  would need to encapsulate decrementing quantity so decrementing from infinity could be enforced
	while(!equipmentChoices->empty())
	{
		delete (equipmentChoices->back());
		equipmentChoices->pop_back();
	}
}

void ShopBuyMode::displayShopChoice(const EquipmentLine* eqLine) const
{
	//postcondition: displays 1 line of equipment able to be bought.  Does not append newline.

	cout<<"$"<<eqLine->pEquipment->getCost()<<setw(5)<<" - "<<eqLine->pEquipment->getName();
}

bool ShopBuyMode::validateShopChoice(const Equipment* equipment, int quantity) const
{
	//postcondition: returns false and shows an error message if the player tried
	//to buy more than they can afford

	int totalCost = equipment->getCost() * quantity;
	if(totalCost <= gameState.getPlayer().Money())
	{
		return true;
	}

	std::stringstream noGoldMsg;
	noGoldMsg<<"Not enough gold! Total cost is $"<<totalCost<<".";
	log(noGoldMsg.str());
	return false;
}

void ShopBuyMode::processTransaction()
{
	//postcondition: buy is called on the player object with the chosen EquipmentLine,
	//and a message is displayed telling the player what they just bought and for how much.

	gameState.getPlayer().Buy(equipmentChoice);

	std::stringstream purchaseMsg;
	purchaseMsg<<"Bought "<<equipmentChoice->quantity<<" "<<equipmentChoice->pEquipment->getName()<<" for $"<<equipmentChoice->getTotalCost()<<".";
	log(purchaseMsg.str());
}
