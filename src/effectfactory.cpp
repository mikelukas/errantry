#include <stddef.h>
#include "effectfactory.h"

EffectFactory* EffectFactory::instance = NULL; //singleton instance static initialization

EffectFactory::EffectFactory()
{

}

const EffectFactory* EffectFactory::getInstance()
{
	//postcondition: allocates a new EffectFactory instance if one does not exist,
	//and sets it as the active singleton instance.  If we've already instantiated
	//one, that instance is returned.

	if(instance == NULL)
	{
		instance = new EffectFactory();
	}
	return instance;
}

Effect* EffectFactory::createEffect(int effectNameOrdinal, Element element, Character& applier, Character& target) const
{
	//postcondition: convenience method to convert an integer ordinal for an
	//effect id to an enum value, before calling the main createEffect with that instead.

	return createEffect(static_cast<EffectName>(effectNameOrdinal), element, applier, target);
}

Effect* EffectFactory::createEffect(EffectName effectId, Element element, Character& applier, Character& target) const
{
	//postcondition: allocates a new Effect subclass matching the given id, with
	//the given parameters passed to its constructor.  Effect should be freed by
	//the caller.
	//Returns NULL if the id doesn't match any Effect subclasses.

	switch(effectId)
	{
	default:
		return NULL;
	}
}
