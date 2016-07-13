#ifndef SRC_EFFECTFACTORY_H_
#define SRC_EFFECTFACTORY_H_

#include "effects/effect.h"

/* Maps an integer id to an enum value name, to make adding effects a little easier*/
enum EffectName
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
};

/* Singleton class for building Effects used by spells, given an effect id.
 *
 * The factory should be retrieved with getInstance(), then createEffect() can
 * be called to instantiate the appropriate Effect for a given effect id.
 */
class EffectFactory
{
	protected:
		static EffectFactory* instance;

		EffectFactory() {};

	public:
		static const EffectFactory* getInstance();
		virtual ~EffectFactory() {}

		Effect* createEffect(int, const EffectParams&) const;
		Effect* createEffect(EffectName, const EffectParams&) const;
};

#endif
