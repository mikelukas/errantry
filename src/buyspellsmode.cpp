#include "buyspellsmode.h"
#include "gamestate.h"

BuySpellsMode::BuySpellsMode(const Town& currentTown, GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState)
{
	//This vector will be freed in spellChooser's destructor
	vector<const Spell*>* shopSpells = gameData.getSpellsForIds(currentTown.getShopSpellIds());

	spellChooser = new BuySpellChooser(shopSpells, gameState.getPlayer());
}

BuySpellsMode::~BuySpellsMode()
{
	//Destroys the spell chooser used for this mode - doing this will clean up
	//the spells vector instantiated in the constructor.

	delete spellChooser;
}

int BuySpellsMode::displayMenu()
{
	//postcondition: SpellChooser is used to display the Spells the player can
	//purchase, and the player is prompted to either purchase or leave the shop

	spellChooser->display();
	return spellChooser->getChoice();
}

void BuySpellsMode::testChoice(int choiceNum)
{
	//postcondition: if the player chose to leave the shop, an exit mode request
	//is made to the GameState, otherwise the purchase is completed.

	switch(choiceNum)
	{
	case EXIT_CHOICE:
		gameState.requestExitCurrentMode();
		break;

	default:
		processTransaction(spellChooser->getChosenSpell());
		break;
	}
}

void BuySpellsMode::processTransaction(const Spell* purchasedSpell)
{
	//postcondition: the chosen spell is added to the player's inventory and the
	//purchase price is deducted from his/her gold.
	//A message stating what spell the player learned is displayed.

	gameState.getPlayer().Buy(purchasedSpell);
	cout<<"Learned '"<<purchasedSpell->getName() + "'!";
}
