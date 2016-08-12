#include <iostream>
#include "castablespell.h"
#include "character.h"
#include "effectfactory.h"
#include "statuses/statusconstants.h"
#include "util/mathutils.h"

using std::cout;
using std::endl;

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

	deallocInitializedEffects();
}

bool CastableSpell::setup()
{
	//postcondition: returns true if initializedEffects is populated with
	//concrete Effects to be applied when cast() is called, or false if one or
	//more effects could not be setup after being constructed.

	if(!initializedEffects.empty())
	{
		//A bug if this is reached; protects against calling setup() multiple times and adding a bunch of duplicate effects. Whatever is calling setup() 2+ times should be fixed
		cout<<"WARNING: This spell is already initialized - was setup() called twice before casting?"<<endl;
		deallocInitializedEffects();
	}

	if(!caster.hasEnoughMpFor(this))
	{
		cout<<caster.ShowName()<<" does not have enough MP to cast '"<<getName()<<"'!"<<endl;
		return false;
	}

	const EffectParams effectParams(getElement(), caster, target);
	for(vector<int>::const_iterator it = effectIds.begin(); it != effectIds.end(); it++)
	{
		Effect* effectToRun = EffectFactory::getInstance()->createEffect((*it), effectParams);
		if(effectToRun == NULL)
		{
			cout<<"WARNING: spell references effects that do not exist."<<endl;
			continue; //if we hit this, the spell references Effects that don't exist, which is probably a bug
		}

		if(!effectToRun->setup())
		{
			deallocInitializedEffects();
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

	//caster could've gotten a status that prevents casting after setup() was called
	if(!caster.hasEnoughMpFor(this))
	{
		deallocInitializedEffects();
		return;
	}

	caster.ChangeMP(-(caster.getEffectiveMpCostFor(this)));

	for(vector<Effect*>::const_iterator it = initializedEffects.begin(); it != initializedEffects.end(); it++)
	{
		(*it)->apply();
		if((*it)->isExpired())
		{
			delete (*it);
		}
	}

	//Can dispose of our pointers to Effects, since they have either been deleted or assigned to another owner, which will force setup() to be called again on this spell if casting it again is desired
	initializedEffects.clear();
}

void CastableSpell::deallocInitializedEffects()
{
	//postcondition: deletes all the Effects within initializedEffects, then
	//clears the vector

	for(int i = 0; i < initializedEffects.size(); i++)
	{
		delete initializedEffects[i];
	}

	initializedEffects.clear();
}
