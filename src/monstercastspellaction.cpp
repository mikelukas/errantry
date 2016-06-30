#include "monstercastspellaction.h"
#include "randutils.h"

MonsterCastSpellAction::MonsterCastSpellAction(Character& monster, Character& enemy)
	: CastSpellAction(monster, enemy)
{
	categoryToTarget[ATTACK] = &enemy;
	categoryToTarget[HEALING] = &monster;
	categoryToTarget[OFFENSIVE_ASSIST] = &enemy;
	categoryToTarget[DEFENSIVE_ASSIST] = &monster;
}

void MonsterCastSpellAction::setup()
{
	//postcondition: if the monster has any spells to cast, and has MP, a spell
	//is set, with an appropriate target.  The spell chosen depends on the monster's
	//HP and a random factor for assist spells.

	//If monster has no MP left, don't even bother trying to choose a spell
	if(caster.getMP() <= 0)
	{
		setAborted(true);
		return;
	}

	vector<SpellCategory> spellSearchPriority;

	bool attemptAssist = (getRandIntBetween(0,1) == 1);
	if(caster.Health() < ((float)(caster.MaxHealth()))*HP_PERCENT_TO_PRIORITIZE_HEAL)
	{
		spellSearchPriority.push_back(HEALING);
		spellSearchPriority.push_back(DEFENSIVE_ASSIST);
	}
	else if(attemptAssist)
	{
		if(caster.Health() >= ((float)(caster.MaxHealth()))*HP_PERCENT_TO_PRIORITIZE_OFFENSIVE_ASSIST)
		{
			spellSearchPriority.push_back(OFFENSIVE_ASSIST);
			spellSearchPriority.push_back(DEFENSIVE_ASSIST);
		}
		else if(caster.Health() >= ((float)(caster.MaxHealth()))*HP_PERCENT_TO_PRIORITIZE_DEFENSIVE_ASSIST)
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
		return;
	}

	spellTarget = categoryToTarget[spellChoice->getCategory()];
}

const Spell* MonsterCastSpellAction::lookupSpellIn(const vector<SpellCategory>& categories) const
{
	//postcondition: returns the first spell found in the first category in
	//categories with spells.

	for(int i = 0; i < NUM_SPELL_CATEGORIES; i++)
	{
		const Spell* spell = lookupSpellInCategory(categories[i]);
		if(spell != NULL)
		{
			return spell;
		}
	}

	return NULL;
}

const Spell* MonsterCastSpellAction::lookupSpellInCategory(SpellCategory category) const
{
	//postcondition: returns pointer to first available spell the monster has MP
	//to cast has in the given category, or NULL if the monster doesn't have
	//spells they can cast in that category.

	const set<const Spell*>& spellsForCategory = caster.getSpellsForCategory(category);
	if(spellsForCategory.empty())
	{
		//Monster doesn't have any spells in given category
		return NULL;
	}

	//Find the first spell monster can cast
	for(set<const Spell*>::const_iterator it = spellsForCategory.begin(); it != spellsForCategory.end(); it++)
	{
		if((*it)->getMpCost() <= caster.getMP())
		{
			return (*it);
		}
	}

	//If we make it this far, Monster can't CAST any of the spells it has in the given category
	return NULL;
}
