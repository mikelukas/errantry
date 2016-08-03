#include <stddef.h>
#include "effectfactory.h"
#include "effects/channeleffect.h"
#include "effects/curepoisoneffect.h"
#include "effects/draineffect.h"
#include "effects/elementaldamageeffect.h"
#include "effects/healeffect.h"
#include "effects/monsteraddweaknesseffect.h"
#include "effects/monsterremoveweaknesseffect.h"
#include "effects/monstermeltdowneffect.h"
#include "effects/mpdamageeffect.h"
#include "effects/playeraddweaknesseffect.h"
#include "effects/playerremoveweaknesseffect.h"
#include "effects/playermeltdowneffect.h"
#include "statuses/poisonstatus.h"

EffectFactory* EffectFactory::instance = NULL; //singleton instance static initialization

EffectFactory* EffectFactory::getInstance()
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

EffectFactory::EffectFactory()
{
	statusesByType[POISON] = new StatusTemplate("Poison", POISON, 10, GLOBAL);
}

EffectFactory::~EffectFactory()
{
	//Delete all StatusTemplates and remove their entries from hte map
	for(map<EffectType, const StatusTemplate*>::iterator it = statusesByType.begin(); it != statusesByType.end(); it++)
	{
		delete (it->second);
		statusesByType.erase(it->first);
	}
}

Effect* EffectFactory::createEffect(int effectNameOrdinal, const EffectParams& effectParams)
{
	//postcondition: convenience method to convert an integer ordinal for an
	//effect id to an enum value, before calling the main createEffect with that instead.

	return createEffect(static_cast<EffectType>(effectNameOrdinal), effectParams);
}

Effect* EffectFactory::createEffect(EffectType effectId, const EffectParams& effectParams)
{
	//postcondition: allocates a new Effect subclass matching the given id, with
	//the given parameters passed to its constructor.  Effect should be freed by
	//the caller.
	//Returns NULL if the id doesn't match any Effect subclasses.

	switch(effectId)
	{
	case ELEMENTAL_DAMAGE:
		return new ElementalDamageEffect(effectParams);
	case HEAL:
		return new HealEffect(effectParams);
	case PLAYER_ADD_WEAKNESS:
		return new PlayerAddWeaknessEffect(effectParams);
	case PLAYER_REMOVE_WEAKNESS:
		return new PlayerRemoveWeaknessEffect(effectParams);
	case MP_DAMAGE:
		return new MpDamageEffect(effectParams);
	case DRAIN:
		return new DrainEffect(effectParams);
	case CHANNEL:
		return new ChannelEffect(effectParams);
	case PLAYER_MELTDOWN:
		return new PlayerMeltdownEffect(effectParams);

	//Monster-only Effects
	case MONSTER_ADD_WEAKNESS:
		return new MonsterAddWeaknessEffect(effectParams);
	case MONSTER_REMOVE_WEAKNESS:
		return new MonsterRemoveWeaknessEffect(effectParams);
	case MONSTER_MELTDOWN:
		return new MonsterMeltdownEffect(effectParams);

	//Status cures
	case CURE_POISON:
		return new CurePoisonEffect(effectParams);

	//Status Effects
	case POISON:
		return new PoisonStatus(*(statusesByType[effectId]), effectParams);

	default:
		return NULL;
	}
}
