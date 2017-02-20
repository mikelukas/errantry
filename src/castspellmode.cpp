#include "castablespell.h"
#include "castspellmode.h"
#include "gamestate.h"

CastSpellMode::CastSpellMode(GameData& gameData, GameState& gameState)
	: GameMode(gameData, gameState, true)
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

void CastSpellMode::updateDisplay()
{
	//postcondition: invokes chooser to display list of spells player can cast,
	//returns the numerical choice they selected

	spellChooser->run();
}

bool CastSpellMode::processInput()
{
	//postcondition: if the player chose to exit, an exit is requested, otherwise
	//cast() is called on the chosen spell with the player as both the caster
	//and the target.
	//returns false if spell setup() fails and aborts casting to let player loop
	//back and choose another spell without consuming a turn, true otherwise.

	if(spellChooser->canceled())
	{
		gameState.requestExitCurrentMode();
		return true;
	}

	const SpellTemplate* spellTemplate = spellChooser->getChoice();
	CastableSpell spell(spellTemplate, gameState.getPlayer(), gameState.getPlayer());
	if(!spell.setup())
	{
		return false;
	}

	spell.cast();
	return true;
}
