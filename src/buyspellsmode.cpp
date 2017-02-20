#include "logging/log.h"
#include "buyspellsmode.h"
#include "gamestate.h"

BuySpellsMode::BuySpellsMode(const Town& currentTown, GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, false)
{
	//This vector will be freed in spellChooser's destructor
	vector<const SpellTemplate*>* shopSpells = gameData.getSpellsForIds(currentTown.getShopSpellIds());

	spellChooser = new BuySpellChooser(shopSpells, gameState.getPlayer());
}

BuySpellsMode::~BuySpellsMode()
{
	//Destroys the spell chooser used for this mode - doing this will clean up
	//the spells vector instantiated in the constructor.

	delete spellChooser;
}

void BuySpellsMode::updateDisplay()
{
	//postcondition: SpellChooser is used to display the Spells the player can
	//purchase, and the player is prompted to either purchase or leave the shop

	spellChooser->run();
}

bool BuySpellsMode::processInput()
{
	//postcondition: if the player chose to leave the shop, an exit mode request
	//is made to the GameState, otherwise the purchase is completed.
	//Always returns true to indicate turn should finish.

	if(spellChooser->canceled())
	{
		gameState.requestExitCurrentMode();
	}
	else
	{
		processTransaction(spellChooser->getChoice());
	}

	return true;
}

void BuySpellsMode::processTransaction(const SpellTemplate* purchasedSpell)
{
	//postcondition: the chosen spell is added to the player's inventory and the
	//purchase price is deducted from his/her gold.
	//A message stating what spell the player learned is displayed.

	gameState.getPlayer().Buy(purchasedSpell);

	std::stringstream learnedMsg;
	learnedMsg<<"Learned '"<<purchasedSpell->getName() + "'!";
	log(learnedMsg.str());
}
