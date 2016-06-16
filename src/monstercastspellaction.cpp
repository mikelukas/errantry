#include "monstercastspellaction.h"

MonsterCastSpellAction::MonsterCastSpellAction(GameData& gameData, Monster& monster, Character& enemy)
	: CastSpellAction(monster, enemy),
	  gameData(gameData)
{

}

void MonsterCastSpellAction::setup()
{
	//If monster has no MP left, don't even bother trying to choose a spell
	if(caster.getMP() <= 0)
	{
		setAborted(true);
		return;
	}

	//Prioritize healing if monster's HP is below half
	if(caster.Health() < ((float)(caster.MaxHealth()))*HP_PERCENT_TO_PRIORITIZE_HEAL)
	{
		spellChoice = lookupSpellInCategory(HEALING);
		if(spellChoice != NULL)
		{
			spellTarget = &caster;
			return;
		}
	}

	spellChoice = lookupSpellInCategory(ATTACK);
	if(spellChoice == NULL)
	{
		//nothing Monster can cast at this point, so abort to let Monster choose another action
		setAborted(true);
		return;
	}

	spellTarget = &enemy;
}

const Spell* MonsterCastSpellAction::lookupSpellInCategory(SpellCategory category)
{
	//postcondition: returns pointer to first available spell the monster has MP
	//to cast has in the given category, or NULL if the monster doesn't have
	//spells they can cast in that category.

	const vector<int>& spellIdsForCategory = gameData.getSpellIdsForCategory(category);
	if(spellIdsForCategory.empty())
	{
		//Shouldn't happen except for bug; if there are no spells in a category, that category shouldn't be programmed into the game.
		return NULL;
	}

	Monster& monster = static_cast<Monster&>(caster); //XXX hate casting, but need to change the way Monsters are loaded to be able to give Characters ability to have spell* vectors, to avoid the cast
	vector<int> monsterSpellIds = monster.getSpellIds();
	if(monsterSpellIds.empty())
	{
		//Shouldn't happen except for bug; if monster doesn't have spells BattleStrategy shouldn't've made this action in the first place
		return NULL;
	}

	//Find the first spell the monster has in the given category
	for(int catSpellsInd = 0; catSpellsInd < spellIdsForCategory.size(); catSpellsInd++)
	{
		for(int monsterSpellsInd = 0; monsterSpellsInd < monsterSpellIds.size(); monsterSpellsInd++)
		{
			if(spellIdsForCategory[catSpellsInd] == monsterSpellIds[monsterSpellsInd])
			{
				const Spell* chosenSpell = gameData.getSpells()[monsterSpellIds[monsterSpellsInd]];
				if(chosenSpell->getMpCost() <= caster.getMP())
				{
					return chosenSpell;
				}
			}
		}
	}

	//If we make it this far, Monster doesn't have any spells in given category
	return NULL;
}
