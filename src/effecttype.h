#ifndef SRC_EFFECTTYPE_H_
#define SRC_EFFECTTYPE_H_

#include <string>

using std::string;

/* Maps an integer id to an enum value name, to make adding effects a little easier*/
enum EffectType
{
	ELEMENTAL_DAMAGE = 0,
	HEAL = 1,
	PLAYER_ADD_WEAKNESS = 2,
	PLAYER_REMOVE_WEAKNESS = 3,
	MP_DAMAGE = 4,
	DRAIN = 5,
	CHANNEL = 6,
	PLAYER_MELTDOWN = 7,

	//Monster-only effects
	MONSTER_ADD_WEAKNESS = 8,
	MONSTER_REMOVE_WEAKNESS = 9,
	MONSTER_MELTDOWN = 10,

	//Status cures
	CURE_POISON = 50,
	CURE_BLIND = 51,
	CURE_MUTE = 52,
	PURIFY = 53,

	//StatusEffects
	TEMPERED = 100,
	WEAKENED = 101,
	HARDENED = 102,
	FRAIL = 103,
	BLESSED = 104,
	CURSED = 105,
	HYPER = 106,
	SLOWED = 107,
	STUNNED = 108,
	FOCUSED = 109,
	UNFOCUSED = 110,
	POISON = 111,
	REGEN = 112,
	DOOMED = 113,
	BLIND = 114,
	MUTE = 115,
};

const string getDisplayNameFor(EffectType);
const string getAdjectiveFor(EffectType);

#endif
