#include "gamestate.h"
#include "shoptransactionmode.h"

using std::cin;

ShopTransactionMode::ShopTransactionMode(vector<EquipmentLine*>* equipmentChoices, GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, false),
	  equipmentChoices(equipmentChoices),
	  equipmentChoice(NULL),
	  choiceNum(-1)
{

}

ShopTransactionMode::~ShopTransactionMode()
{
	if(equipmentChoice != NULL)
	{
		clearShopChoice();
	}

	delete equipmentChoices;
}

void ShopTransactionMode::updateDisplay()
{
	//postcondition: displays equipment choice list to be bought/sold at shop,
	//and returns the index into the equipmentChoices vector the player picked,
	//or the EXIT_CHOICE value if the player wants to exit buy/sell mode at the shop.
	//Also handles asking the player how much of the equipment they chose they
	//want to buy/sell, and dynamically allocates a new EquipmentLine for the
	//choice and quantity.  This will be freed once the transaction is processed
	//after testChoice.

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
			<<CANCELED_CHOICE<<") Back"<<endl
			<<"***************"<<endl
			<<"*Gold:        *"<<endl
			<<"*  $"<<setw(10)<<gameState.getPlayer().Money()<<"*"<<endl
			<<"***************"<<endl
			<<"**********************MESSAGES**********************"<<endl;
		do
		{
			cout<<"Please choose an option:  "<<endl;
			cin>>choiceNum;

			if(choiceNum == CANCELED_CHOICE)
			{
				return;
			}
		}while(!validateChoice(choiceNum, equipmentChoices->size()));

		do
		{
			cout<<"How many '"<<(*equipmentChoices)[choiceNum-1]->pEquipment->getName()<<"' (0 to cancel)? "<<endl;
			cin>>quantity;
		}while(!validateShopChoice((*equipmentChoices)[choiceNum-1]->pEquipment, quantity));
	}while(quantity <=0);

	equipmentChoice = new EquipmentLine((*equipmentChoices)[choiceNum-1]->pEquipment, quantity);
}

bool ShopTransactionMode::processInput()
{
	//postcondition: calls subclass's implementations of processTransaction and
	//updateChoices, or exits the mode if the player chose to leave from the
	//choice list.
	//Always returns true to indicate turn should finish.

	switch(choiceNum)
	{
	case CANCELED_CHOICE:
		gameState.requestExitCurrentMode();
		break;
	default:
		processTransaction();
		updateChoices(choiceNum);
		clearShopChoice();
		break;
	}

	return true;
}

void ShopTransactionMode::clearShopChoice()
{
	delete equipmentChoice;
	equipmentChoice = NULL;
	choiceNum = -1;
}
