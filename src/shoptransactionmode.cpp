#include "gamestate.h"
#include "shoptransactionmode.h"

ShopTransactionMode::ShopTransactionMode(vector<EquipmentLine*>* equipmentChoices, GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState),
	  equipmentChoices(equipmentChoices),
	  equipmentChoice(NULL)
{

}

ShopTransactionMode::~ShopTransactionMode()
{
	if(equipmentChoice != NULL)
	{
		clearShopChoice();
	}

	//all EquipmentLine* in choices vector were also dynamically allocated prior to creating this mode
	while(!equipmentChoices->empty())
	{
		delete (equipmentChoices->back());
		equipmentChoices->pop_back();
	}
	delete equipmentChoices;
}

int ShopTransactionMode::displayMenu()
{
	//postcondition: displays equipment choice list to be bought/sold at shop,
	//and returns the index into the equipmentChoices vector the player picked,
	//or the EXIT_CHOICE value if the player wants to exit buy/sell mode at the shop.
	//Also handles asking the player how much of the equipment they chose they
	//want to buy/sell, and dynamically allocates a new EquipmentLine for the
	//choice and quantity.  This will be freed once the transaction is processed
	//after testChoice.

	int choice;
	int quantity=0;

	do {
		cout<<"****************************************************"<<endl;
		for(int i = 0; i < equipmentChoices->size(); i++)
			{
				cout<<i+1<<") ";
				displayShopChoice((*equipmentChoices)[i]);
				cout<<endl;
			}
		cout<<endl
			<<EXIT_CHOICE<<") Back"<<endl
			<<"***************"<<endl
			<<"*Gold:        *"<<endl
			<<"*  $"<<setw(10)<<gameState.getPlayer().Money()<<"*"<<endl
			<<"***************"<<endl
			<<"**********************MESSAGES**********************"<<endl;
		do
		{
			cout<<"Please choose an option:  "<<endl;
			cin>>choice;

			if(choice == EXIT_CHOICE)
			{
				return choice;
			}
		}while(!validateChoice(choice, equipmentChoices->size()));

		do
		{
			cout<<"How many '"<<(*equipmentChoices)[choice-1]->pEquipment->getName()<<"' (0 to cancel)? "<<endl;
			cin>>quantity;
		}while(!validateShopChoice((*equipmentChoices)[choice-1]->pEquipment, quantity));
	}while(quantity <=0);

	equipmentChoice = new EquipmentLine((*equipmentChoices)[choice-1]->pEquipment, quantity);
	return choice;
}

void ShopTransactionMode::testChoice(int choice)
{
	//postcondition: calls subclass's implementations of processTransaction and
	//updateChoices, or exits the mode if the player chose to leave from the
	//choice list.

	switch(choice)
	{
	case EXIT_CHOICE:
		gameState.exitCurrentMode();
		break;
	default:
		processTransaction();
		updateChoices(choice);
		clearShopChoice();
		break;
	}
}

void ShopTransactionMode::clearShopChoice()
{
	delete equipmentChoice;
	equipmentChoice = NULL;
}
