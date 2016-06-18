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

	cout<<caster.ShowName() + " cast '" + spellChoice->getName() + "' on " + spellTarget->ShowName() + "."<<endl;
	spellChoice->cast(caster, *spellTarget);
}
