#include "castablespell.h"
#include "castspellmode.h"
#include "gamestate.h"

CastSpellMode::CastSpellMode(GameData& gameData, GameState& gameState)
	: MenuMode(gameData, gameState)
{
	vector<const SpellTemplate*>* playerFieldSpells = gameState.getPlayer().getSpellsForLocale(FIELD);

	//Separate out spells that aren't castable in the field, so that player can view all spells from this mode, but only cast castable ones
	const set<const SpellTemplate*>& allPlayerSpells = gameState.getPlayer().getSpells();
	vector<const SpellTemplate*>* playerBattleOnlySpells = new vector<const SpellTemplate*>();
	for(set<const SpellTemplate*>::const_iterator it = allPlayerSpells.begin(); it != allPlayerSpells.end(); it++)
	{
		const set<int> eligibleLocations = (*it)->getEligibleLocations();
		if(eligibleLocations.find(FIELD) == eligibleLocations.end())
		{
			playerBattleOnlySpells->push_back((*it));
		}
	}
	spellChooser = new CastSpellChooser(playerFieldSpells, playerBattleOnlySpells, gameState.getPlayer());
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

	const SpellTemplate* spellTemplate = spellChooser->getChoice();
	CastableSpell spell(spellTemplate, gameState.getPlayer(), gameState.getPlayer());
	if(!spell.setup())
	{
		return;
	}

	spell.cast();
}
