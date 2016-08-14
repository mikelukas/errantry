#include <stddef.h>
#include "character.h"
#include "effectfactory.h"
#include "effects/channeleffect.h"
#include "effects/curestatuseseffect.h"
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
#include "statuses/blindstatus.h"
#include "statuses/doomedstatus.h"
#include "statuses/mutestatus.h"
#include "statuses/poisonstatus.h"
#include "statuses/regenstatus.h"
#include "statuses/statusconstants.h"
#include "statuses/stunstatuseffect.h"
#include "statuses/tempstatmodstatuseffect.h"
#include "util/mathutils.h"

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
	statusesByType[TEMPERED] = new StatusTemplate("Tempered", TEMPERED, 10, BATTLE_ONLY);
	statusesByType[WEAKENED] = new StatusTemplate("Weakened", WEAKENED, 10, BATTLE_ONLY);
	statusesByType[HARDENED] = new StatusTemplate("Hardened", HARDENED, 10, BATTLE_ONLY);
	statusesByType[FRAIL] = new StatusTemplate("Frail", FRAIL, 10, BATTLE_ONLY);
	statusesByType[BLESSED] = new StatusTemplate("Blessed", BLESSED, 10, BATTLE_ONLY);
	statusesByType[CURSED] = new StatusTemplate("Cursed", CURSED, 10, BATTLE_ONLY);
	statusesByType[HYPER] = new StatusTemplate("Hyper", HYPER, 10, BATTLE_ONLY);
	statusesByType[SLOWED] = new StatusTemplate("Slowed", SLOWED, 10, BATTLE_ONLY);
	statusesByType[STUNNED] = new StatusTemplate("Stunned", STUNNED, 2, BATTLE_ONLY);
	statusesByType[FOCUSED] = new StatusTemplate("Focused", FOCUSED, 10, BATTLE_ONLY);
	statusesByType[UNFOCUSED] = new StatusTemplate("Unfocused", UNFOCUSED, 10, BATTLE_ONLY);
	statusesByType[POISON] = new StatusTemplate("Poison", POISON, 10, GLOBAL);
	statusesByType[REGEN] = new StatusTemplate("Regen", REGEN, 10, BATTLE_ONLY);
	statusesByType[DOOMED] = new StatusTemplate("Doomed", DOOMED, 10, BATTLE_ONLY);
	statusesByType[BLIND] = new StatusTemplate("Blind", BLIND, 10, GLOBAL);
	statusesByType[MUTE] = new StatusTemplate("Mute", MUTE, 10, GLOBAL);
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
		return new CureStatusesEffect(POISON, effectParams);
	case CURE_BLIND:
		return new CureStatusesEffect(BLIND, effectParams);
	case CURE_MUTE:
		return new CureStatusesEffect(MUTE, effectParams);
	case PURIFY: {
		vector<EffectType>* statusesToCure = new vector<EffectType>();
		statusesToCure->push_back(POISON);
		statusesToCure->push_back(BLIND);
		statusesToCure->push_back(MUTE);
		return new CureStatusesEffect(statusesToCure, effectParams);
	}

	//Status Effects
	case TEMPERED: {
		StatMod statMod;
		statMod.apMod = max(1, roundDouble(((double) effectParams.target.getBaseAP()) * MOD_SCALING_FACTOR));
		return new TempStatModStatusEffect(statMod, WEAKENED, *(statusesByType[effectId]), effectParams);
	}
	case WEAKENED: {
		StatMod statMod;
		statMod.apMod = -1 * max(1, roundDouble(((double) effectParams.target.getBaseAP()) * MOD_SCALING_FACTOR));
		return new TempStatModStatusEffect(statMod, TEMPERED, *(statusesByType[effectId]), effectParams);
	}
	case HARDENED: {
		StatMod statMod;
		statMod.dpMod = max(1, roundDouble(((double) effectParams.target.getBaseDP()) * MOD_SCALING_FACTOR));
		return new TempStatModStatusEffect(statMod, FRAIL, *(statusesByType[effectId]), effectParams);
	}
	case FRAIL: {
		StatMod statMod;
		statMod.dpMod = -1 * max(1, roundDouble(((double) effectParams.target.getBaseDP()) * MOD_SCALING_FACTOR));
		return new TempStatModStatusEffect(statMod, HARDENED, *(statusesByType[effectId]), effectParams);
	}
	case BLESSED: {
		StatMod statMod;
		statMod.mdpMod = max(1, roundDouble(((double) effectParams.target.getBaseMDP()) * MOD_SCALING_FACTOR));
		return new TempStatModStatusEffect(statMod, CURSED, *(statusesByType[effectId]), effectParams);
	}
	case CURSED: {
		StatMod statMod;
		statMod.mdpMod = -1 * max(1, roundDouble(((double) effectParams.target.getBaseMDP()) * MOD_SCALING_FACTOR));
		return new TempStatModStatusEffect(statMod, BLESSED, *(statusesByType[effectId]), effectParams);
	}
	case HYPER: {
		StatMod statMod;
		statMod.spMod = max(1, roundDouble(((double) effectParams.target.getBaseSP()) * SP_UPSCALING_FACTOR));
		return new TempStatModStatusEffect(statMod, SLOWED, *(statusesByType[effectId]), effectParams);
	}
	case SLOWED: {
		StatMod statMod;
		statMod.spMod = -1 * roundInt(((double) effectParams.target.getBaseSP()) * SP_DOWNSCALING_FACTOR); //no max() because speed shouldn't be allowed to be reduced to 0 from Slowed status
		return new TempStatModStatusEffect(statMod, HYPER, *(statusesByType[effectId]), effectParams);
	}
	case STUNNED:
		return new StunStatusEffect(*(statusesByType[effectId]), effectParams);
	case FOCUSED:
		return new HasOppositeStatusEffect(UNFOCUSED, *(statusesByType[effectId]), effectParams);
	case UNFOCUSED:
		return new HasOppositeStatusEffect(FOCUSED, *(statusesByType[effectId]), effectParams);
	case POISON:
		return new PoisonStatus(*(statusesByType[effectId]), effectParams);
	case REGEN:
		return new RegenStatus(*(statusesByType[effectId]), effectParams);
	case DOOMED:
		return new DoomedStatus(*(statusesByType[effectId]), effectParams);
	case BLIND:
		return new BlindStatus(*(statusesByType[effectId]), effectParams);
	case MUTE:
		return new MuteStatus(*(statusesByType[effectId]), effectParams);

	default:
		return NULL;
	}
}
