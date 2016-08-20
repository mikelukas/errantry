#include "effecttype.h"

const string getDisplayNameFor(EffectType type)
{
	//postcondition: returns a string to display for the name of the EffectType

	switch(type){
	//1-use effects
	case ELEMENTAL_DAMAGE:
		return "Elemental Damage";
	case HEAL:
		return "Heal";
	case PLAYER_ADD_WEAKNESS:
	case MONSTER_ADD_WEAKNESS:
		return "Add Weakness";
	case PLAYER_REMOVE_WEAKNESS:
	case MONSTER_REMOVE_WEAKNESS:
		return "Remove Weakness";
	case MP_DAMAGE:
		return "MP Damage";
	case DRAIN:
		return "Drain HP";
	case CHANNEL:
		return "Channel";
	case PLAYER_MELTDOWN:
	case MONSTER_MELTDOWN:
		return "Meltdown";

	//Status cures
	case CURE_POISON:
		return "Cure Poison";
	case CURE_BLIND:
		return "Cure Blind";
	case CURE_MUTE:
		return "Cure Mute";
	case PURIFY:
		return "Purify";

	//StatusEffects
	case TEMPERED:
		return "Tempered";
	case WEAKENED:
		return "Weakened";
	case HARDENED:
		return "Hardened";
	case FRAIL:
		return "Frail";
	case BLESSED:
		return "Blessed";
	case CURSED:
		return "Curse";
	case HYPER:
		return "Hyper";
	case SLOWED:
		return "Slow";
	case STUNNED:
		return "Stun";
	case FOCUSED:
		return "Focus";
	case UNFOCUSED:
		return "Unfocus";
	case POISON:
		return "Poison";
	case REGEN:
		return "Regen";
	case DOOMED:
		return "Doom";
	case BLIND:
		return "Blind";
	case MUTE:
		return "Mute";
	default:
		return "";
	}
}

const string getAdjectiveFor(EffectType type)
{
	//postcondition: returns a adjective string used to describe things affected
	//by the EffectType.
	//Not every Effect has an adjective; if an Effect does not, the empty string
	//is returned.

	switch(type)
	{
	case TEMPERED:
		return "stronger";
	case WEAKENED:
		return "weaker";
	case HARDENED:
		return "firmer";
	case FRAIL:
		return "frailer";
	case BLESSED:
		return "protected";
	case CURSED:
		return "unprotected";
	case HYPER:
		return "faster";
	case SLOWED:
		return "slower";
	case STUNNED:
		return "stunned";
	case FOCUSED:
		return "focused";
	case UNFOCUSED:
		return "unfocused";
	default:
		return "";
	}
}
