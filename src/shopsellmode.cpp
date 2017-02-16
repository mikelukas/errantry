#include <sstream>
#include "logging/log.h"
#include "gamestate.h"
#include "shopsellmode.h"

ShopSellMode::ShopSellMode(vector<EquipmentLine*>* equipmentChoices, GameData& gameData, GameState& gameState)
	: ShopTransactionMode(equipmentChoices, gameData, gameState)
{

}

void ShopSellMode::displayShopChoice(const EquipmentLine* eqLine) const
{
	//postcondition: displays 1 line of equipment to be sold.  Does not append newline.

	cout<<"$"<<eqLine->pEquipment->getSellPrice()<<" - "<<std::left<<setw(19)<<eqLine->pEquipment->getName()<<" x"<<eqLine->quantity;
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
		std::stringstream sellBugMsg;
		sellBugMsg<<"WARNING: You don't actually have "<<equipment->getName()<<" in your inventory... how'd you get as far as trying to sell it?";
		log(sellBugMsg.str());
		return false;
	}

	if(quantity > eqLine.quantity)
	{
		std::stringstream tooMuchMsg;
		tooMuchMsg<<"You can't sell more than you have ("<<eqLine.quantity<<")!";
		log(tooMuchMsg.str());
		return false;
	}

	return true;
}

void ShopSellMode::processTransaction()
{
	//postcondition: sell is called on the player object with the chosen EquipmentLine,
	//and a message is displayed telling the player what they just sold and for how much.

	gameState.getPlayer().Sell(equipmentChoice);

	std::stringstream sellMsg;
	sellMsg<<"Sold "<<equipmentChoice->quantity<<" "<<equipmentChoice->pEquipment->getName()<<" for $"<<equipmentChoice->getTotalSellPrice()<<".";
	log(sellMsg.str());
}

void ShopSellMode::updateChoices(int choiceIndex)
{
	//postcondition: the equipment the player purchased is removed from the
	//choices vector if they sold anything (worst case O(n)... need to probably not
	//use a vector for storage?).
	//NOTE: Don't need to also update quantity of the line in the choice vector
	//since it's pointing to the same line that is in the player's inventory.

	EquipmentLine* invLine = (*equipmentChoices)[choiceIndex-1]; //-1 b/c shop choices start numbering at 1
	if(invLine->quantity <= 0)
	{
		equipmentChoices->erase(equipmentChoices->begin()+(choiceIndex-1));
	}
}
