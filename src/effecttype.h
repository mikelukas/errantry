#ifndef SRC_EFFECTTYPE_H_
#define SRC_EFFECTTYPE_H_

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

	//StatusEffects
	POISON = 100,
};

#endif
