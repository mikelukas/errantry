#include <sstream>
#include "logging/log.h"
#include "armorymainmode.h"
#include "gamestate.h"
#include "generalstoremainmode.h"
#include "townmode.h"
#include "buyspellsmode.h"

TownMode::TownMode(const Town& town, GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, true),
	  currentTown(town)
{

}

void TownMode::updateDisplay()
{
	//postcondition: Displays town menu options to user, and returns their choice.

	cout<<"*********Choices*********"<<endl;
	cout<<"*1)Talk                 *"<<endl;
	cout<<"*2)Go to Armory         *"<<endl;
	cout<<"*3)Go to General Store  *"<<endl;
	cout<<"*4)Magic Lessons        *"<<endl;
	cout<<"*5)Leave Town           *"<<endl;
	cout<<"*************************"<<endl;
}

bool TownMode::processInput()
{
	//postcondition: prompts for and processes the player's menu choice

	int choice = 0;

	do
	{
		cout<<"Please choose an option:  ";
		cin>>choice;
	}while(!validateChoice(choice, 5));

	switch(choice)
		{
			case 1:
				talk();
				break;
			case 2:
				enterArmory();
				break;
			case 3:
				enterGenStore();
				break;
			case 4:
				enterMagicShop();
				break;

			case 5: //Leave Town
				gameState.requestExitCurrentMode();
				break;
		}

	return true;
}

void TownMode::talk() const
{
	//postcondition: prints out what people are saying at the current town.

	char junkCh;

	cout<<"****************************************************"<<endl;
	cout<<currentTown.getConversation();
	cout<<"**********************MESSAGES**********************"<<endl;
	cout<<"Press X and enter when done:  ";
	cin>>junkCh;
	cout<<endl<<endl;
}

void TownMode::enterArmory()
{
	//postcondition: enters ArmoryMainMode if the town has weapons and armor to sell,
	//otherwise just displays message and remains in town mode.

	bool hasInventory = (!currentTown.getShopEquipmentIds(WEAPON).empty()
						|| !currentTown.getShopEquipmentIds(ARMOR).empty());

	if(!hasInventory)
	{
		std::stringstream closedMsg;
		closedMsg<<ARMORY_CLOSED_MSG<<currentTown.getName()<<".";
		log(closedMsg.str());
		return;
	}

	GameMode* mode = new ArmoryMainMode(currentTown, gameData, gameState);
	gameState.requestEnterMode(mode);
}

void TownMode::enterGenStore()
{
	//postcondition: enters GeneralStoreMainMode if the town has items to sell,
	//otherwise just displays message and remains in town mode.

	bool hasInventory = !currentTown.getShopEquipmentIds(ITEM).empty();
	if(!hasInventory)
	{
		std::stringstream closedMsg;
		closedMsg<<GENSTORE_CLOSED_MSG<<currentTown.getName()<<".";
		log(closedMsg.str());
		return;
	}

	GameMode* genStore = new GeneralStoreMainMode(currentTown, gameData, gameState);
	gameState.requestEnterMode(genStore);
}

void TownMode::enterMagicShop()
{
	//postcondition: Enters BuySpellsMode if the town has magic to sell,
	//otherwise just displays a message and remains in town mode.

	bool hasSpells = !currentTown.getShopSpellIds().empty();
	if(!hasSpells)
	{
		std::stringstream closedMsg;
		closedMsg<<MAGICSHOP_CLOSED_MSG<<currentTown.getName()<<".";
		log(closedMsg.str());
		return;
	}

	GameMode* magicShop = new BuySpellsMode(currentTown, gameData, gameState);
	gameState.requestEnterMode(magicShop);
}
