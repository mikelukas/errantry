#include "monstercastspellaction.h"

MonsterCastSpellAction::MonsterCastSpellAction(Character& monster, Character& enemy)
	: CastSpellAction(monster, enemy)
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
