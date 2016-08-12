#include "monstercastspellaction.h"

#include "util/randutils.h"

MonsterCastSpellAction::MonsterCastSpellAction(Character& monster, Character& enemy)
	: CastSpellAction(monster, enemy)
{
	categoryToTarget[ATTACK] = &enemy;
	categoryToTarget[HEALING] = &monster;
	categoryToTarget[OFFENSIVE_ASSIST] = &enemy;
	categoryToTarget[DEFENSIVE_ASSIST] = &monster;
}

bool MonsterCastSpellAction::setupSpellChoice()
{
	//postcondition: if the monster has any spells to cast, and has MP, a spell
	//is set, with an appropriate target.  The spell chosen depends on the monster's
	//HP and a random factor for assist spells.

	//If monster has no MP left, don't even bother trying to choose a spell
	if(caster.getMP() <= 0)
	{
		setAborted(true);
		return false;
	}

	vector<SpellCategory> spellSearchPriority;

	bool attemptAssist = (getRandIntBetween(0,1) == 1);
	if(caster.getHP() < ((float)(caster.getEffectiveMaxHP()))*HP_PERCENT_TO_PRIORITIZE_HEAL)
	{
		spellSearchPriority.push_back(HEALING);
		spellSearchPriority.push_back(DEFENSIVE_ASSIST);
	}
	else if(attemptAssist)
	{
		if(caster.getHP() >= ((float)(caster.getEffectiveMaxHP()))*HP_PERCENT_TO_PRIORITIZE_OFFENSIVE_ASSIST)
		{
			spellSearchPriority.push_back(OFFENSIVE_ASSIST);
			spellSearchPriority.push_back(DEFENSIVE_ASSIST);
		}
		else if(caster.getHP() >= ((float)(caster.getEffectiveMaxHP()))*HP_PERCENT_TO_PRIORITIZE_DEFENSIVE_ASSIST)
		{
			spellSearchPriority.push_back(DEFENSIVE_ASSIST);
			spellSearchPriority.push_back(OFFENSIVE_ASSIST);
		}
	}

	spellSearchPriority.push_back(ATTACK);

	spellChoice = lookupSpellIn(spellSearchPriority);
	if(spellChoice == NULL)
	{
		//nothing Monster can cast at this point, so abort to let Monster choose another action
		setAborted(true);
		return false;
	}

	return true;
}

const SpellTemplate* MonsterCastSpellAction::lookupSpellIn(const vector<SpellCategory>& categories) const
{
	//postcondition: returns the first spell found in the first category in
	//categories with spells.

	for(int i = 0; i < NUM_SPELL_CATEGORIES; i++)
	{
		const SpellTemplate* spell = lookupSpellInCategory(categories[i]);
		if(spell != NULL)
		{
			return spell;
		}
	}

	return NULL;
}

const SpellTemplate* MonsterCastSpellAction::lookupSpellInCategory(SpellCategory category) const
{
	//postcondition: returns pointer to first available spell the monster has MP
	//to cast has in the given category, or NULL if the monster doesn't have
	//spells they can cast in that category.

	const set<const SpellTemplate*>& spellsForCategory = caster.getSpellsForCategory(category);
	if(spellsForCategory.empty())
	{
		//Monster doesn't have any spells in given category
		return NULL;
	}

	const SpellTemplate* chosenSpell = NULL;

	//Randomly choose from the spells in the given category until a spell the monster has MP to cast is found
	vector<const SpellTemplate*>* shuffledSpells = shuffleSetIntoVector(spellsForCategory);
	for(vector<const SpellTemplate*>::const_iterator it = shuffledSpells->begin(); it != shuffledSpells->end(); it++)
	{
		if(caster.hasEnoughMpFor((*it)))
		{
			chosenSpell = (*it);
			break;
		}
	}
	delete shuffledSpells;

	return chosenSpell;
}

bool MonsterCastSpellAction::setupTargetChoice()
{
	spellTarget = categoryToTarget[spellChoice->getCategory()];
	return true;
}
