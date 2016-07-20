#ifndef SRC_EFFECTFACTORY_H_
#define SRC_EFFECTFACTORY_H_

#include <map>
#include "effects/effect.h"
#include "statuses/statustemplate.h"
#include "effecttype.h"

using std::map;

/* Singleton class for building Effects used by spells, given an effect id.
 *
 * The factory should be retrieved with getInstance(), then createEffect() can
 * be called to instantiate the appropriate Effect for a given effect id.
 */
class EffectFactory
{
	protected:
		static EffectFactory* instance;

		map<EffectType, const StatusTemplate*> statusesByType; //initialized in constructor
		EffectFactory();

	public:
		static const EffectFactory* getInstance();
		virtual ~EffectFactory();

		Effect* createEffect(int, const EffectParams&) const;
		Effect* createEffect(EffectType, const EffectParams&) const;
};

#endif
