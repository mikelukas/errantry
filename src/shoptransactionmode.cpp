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
