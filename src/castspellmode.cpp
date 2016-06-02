#include "castspellmode.h"
#include "gamestate.h"

CastSpellMode::CastSpellMode(GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState)
{
	vector<const Spell*>* playerFieldSpells = gameState.getPlayer().getSpellsForLocale(FIELD);
	spellChooser = new CastSpellChooser(playerFieldSpells, gameState.getPlayer());
}

CastSpellMode::~CastSpellMode()
{
	if(spellChooser != NULL)
	{
		delete spellChooser;
	}
}

int CastSpellMode::displayMenu()
{
	//postcondition: invokes chooser to display list of spells player can cast,
	//returns the numerical choice they selected

	spellChooser->run();
	return spellChooser->getChoiceNum();
}

void CastSpellMode::testChoice(int choiceNum)
{
	//postcondition: if the player chose to exit, an exit is requested, otherwise
	//cast() is called on the chosen spell with the player as both the caster
	//and the target.

	if(spellChooser->canceled())
	{
		gameState.requestExitCurrentMode();
		return;
	}

	const Spell* spell = spellChooser->getChoice();
	spell->cast(gameState.getPlayer(), gameState.getPlayer());
}
