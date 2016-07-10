#ifndef SRC_EFFECTFACTORY_H_
#define SRC_EFFECTFACTORY_H_

#include "effects/effect.h"

/* Maps an integer id to an enum value name, to make adding effects a little easier*/
enum EffectName
{
	ELEMENTAL_DAMAGE = 0,
	HEAL = 1,
	PLAYER_ADD_WEAKNESS = 2,

	//Monster-only effects
	MONSTER_ADD_WEAKNESS = 8,
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

		EffectFactory();

	public:
		static const EffectFactory* getInstance();
		virtual ~EffectFactory() {}

		Effect* createEffect(int, Element, Character&, Character&) const;
		Effect* createEffect(EffectName, Element, Character&, Character&) const;
};

#endif
