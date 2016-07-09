#include "castablespell.h"
#include "character.h"
#include "effectfactory.h"

CastableSpell::CastableSpell(const SpellTemplate* spellDefinition, Character& caster, Character& target)
	: SpellTemplate(*spellDefinition),
	  caster(caster),
	  target(target),
	  initializedEffects()
{

}

CastableSpell::~CastableSpell()
{
	//postcondition: will attempt to delete initialized effects, just in case
	//this spell was created and setup(), but not cast

	clearInitializedEffects();
}

bool CastableSpell::setup()
{
	//postcondition: returns true if initializedEffects is populated with
	//concrete Effects to be applied when cast() is called, or false if one or
	//more effects could not be setup after being constructed.

	for(vector<int>::const_iterator it = effectIds.begin(); it != effectIds.end(); it++)
	{
		Effect* effectToRun = EffectFactory::getInstance()->createEffect((*it), getElement(), caster, target);
		if(effectToRun == NULL)
		{
			continue; //if we hit this, the spell references Effects that don't exist
		}

		if(!effectToRun->setup())
		{
			clearInitializedEffects();
			return false;
		}

		initializedEffects.push_back(effectToRun);
	}

	return true;
}

void CastableSpell::cast()
{
	//postcondition: //The caster's MP is then reduced by the mpCost of the spell,
	//and the effect function of each effect referenced by this spell is called,
	//in order (dat file specifies order), with the caster and target.

	caster.ChangeMP(-getMpCost());

	for(vector<Effect*>::const_iterator it = initializedEffects.begin(); it != initializedEffects.end(); it++)
	{
		(*it)->run();
	}

	clearInitializedEffects();
}

void CastableSpell::clearInitializedEffects()
{
	//postcondition: deletes all the Effects within initializedEffects, then
	//clears the vector

	for(int i = 0; i < initializedEffects.size(); i++)
	{
		delete initializedEffects[i];
	}

	initializedEffects.clear();
}
