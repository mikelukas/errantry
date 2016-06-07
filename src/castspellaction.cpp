#include "castspellaction.h"

CastSpellAction::CastSpellAction(Character& caster, Character& enemy)
	: caster(caster),
	  enemy(enemy),
	  spellChoice(NULL),
	  spellTarget(NULL)
{

}

void CastSpellAction::execute()
{
	//postcondition: cast is called on the chosen spell with the passed-in caster
	//and chosen target as args.

	if(spellChoice == NULL || spellTarget == NULL)
	{
		return;
	}

	spellChoice->cast(caster, *spellTarget);
}
