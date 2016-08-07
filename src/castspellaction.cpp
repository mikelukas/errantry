#include <stack>
#include "castspellaction.h"

using std::stack;

CastSpellAction::CastSpellAction(Character& caster, Character& enemy)
	: BattleAction(caster),
	  caster(caster),
	  enemy(enemy),
	  spellChoice(NULL),
	  spellTarget(NULL),
	  castableSpell(NULL)
{

}

CastSpellAction::~CastSpellAction()
{
	if(castableSpell != NULL)
	{
		delete castableSpell;
	}
}

void CastSpellAction::setup()
{
	//postcondition: castableSpell is set with a spell to cast during execute,
	//or this action is aborted because spell choosing was canceled.
	//Handles returning to spell choosing if a spell is chosen but target choosing
	//is canceled or spell setup is aborted.

	while(!isAborted() && castableSpell == NULL)
	{
		if(!setupSpellChoice())
		{
			continue;
		}

		if(!setupTargetChoice())
		{
			continue;
		}

		if(!setupCastableSpell())
		{
			continue;
		}
	}
}

bool CastSpellAction::setupCastableSpell()
{
	castableSpell = new CastableSpell(spellChoice, caster, *spellTarget); //freed here or after casting by destructor
	if(!castableSpell->setup())
	{
		delete castableSpell;
		castableSpell = NULL;
		return false;
	}

	return true;
}

void CastSpellAction::doAction()
{
	//postcondition: cast is called on the chosen spell with the passed-in caster
	//and chosen target as args.

	if(castableSpell == NULL)
	{
		return;
	}

	cout<<caster.ShowName() + " cast '" + castableSpell->getName() + "' on " + spellTarget->ShowName() + "."<<endl;
	castableSpell->cast();
}
