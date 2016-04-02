#include "gamestate.h"
#include "shopsellmode.h"

ShopSellMode::ShopSellMode(vector<EquipmentLine*>* equipmentChoices, GameData& gameData, GameState& gameState)
	: ShopTransactionMode(equipmentChoices, gameData, gameState)
{

}

void ShopSellMode::displayShopChoice(const EquipmentLine* eqLine) const
{
	//postcondition: displays 1 line of equipment to be sold.  Does not append newline.

	cout<<"$"<<eqLine->pEquipment->getCost()<<" - "<<std::left<<setw(19)<<eqLine->pEquipment->getName()<<" x"<<eqLine->quantity;
}

bool ShopSellMode::validateShopChoice(const Equipment* equipment, int quantity) const
{
	//postcondition: returns false and shows an error message if the player tried
	//to sell more than they have of something, or somehow tried to sell something
	//they don't have. returns true otherwise

	EquipmentLine& eqLine = gameState.getPlayer().getEquipmentLineFromInventoryFor(equipment);
	if(eqLine.pEquipment == NULL)
	{
		//Bug if this happens, since the mode should only have been created with stuff the player has
		cout<<"You don't actually have "<<equipment->getName()<<" in your inventory... how'd you get as far as trying to sell it?"<<endl;
		return false;
	}

	if(quantity > eqLine.quantity)
	{
		cout<<"You can't sell more than you have ("<<eqLine.quantity<<")!"<<endl;
		return false;
	}

	return true;
}

void ShopSellMode::processTransaction()
{
	//postcondition: sell is called on the player object with the chosen EquipmentLine,
	//and a message is displayed telling the player what they just bought and for how much.

	gameState.getPlayer().Sell(equipmentChoice);
	cout<<"Sold "<<equipmentChoice->quantity<<" "<<equipmentChoice->pEquipment->getName()<<" for $"<<equipmentChoice->getTotalSellPrice()<<"."<<endl;
}

void ShopSellMode::updateChoices(int choiceIndex)
{
	//postcondition: the equipment the player purchased is subtracted from the
	//copy of the inventory in this shop, and removed from the choices list if
	//they sold anything (worst case O(n)... need to probably not use a vector for storage?)

	EquipmentLine* invLine = (*equipmentChoices)[choiceIndex-1]; //-1 b/c shop choices start numbering at 1
	(*invLine) -= (*equipmentChoice);
	if(invLine->quantity <= 0)
	{
		equipmentChoices->erase(equipmentChoices->begin()+(choiceIndex-1));
	}
}
