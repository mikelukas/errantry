#ifndef SRC_EFFECTS_EFFECT_H_
#define SRC_EFFECTS_EFFECT_H_

#include "../element.h"

class Character;  //Forward declaration since Spell and Character are interdependent, and Spell Depends on Effects

struct EffectParams
{
	Element element;    //Used for things such as applying magic damage

	Character& applier; //Character causing the effect
	Character& target;  //Character receiving the effect (can be same as applier)

	EffectParams(Element, Character&, Character&);
};

/* Abstract base class for Effects - scripted actions to run on a target, which
 * can be referenced by things like spells.  Effects have an associated Element
 * to use when applicable, which can be provided by the code creating the Effect.
 * Concrete Effects should be constructed with the EffectFactory, by providing
 * the id of the effect to create.
 * To use an Effect after it is created, call setup() first, then run(). setup()
 * will return true if the Effect can be run, or false if something during
 * initialization has caused the Effect to not be runnable (e.g. a player choice
 * was required and they canceled).
 */
class Effect
{
	protected:

		Element element;    //Used for things such as applying magic damage

		Character& applier; //Character causing the effect
		Character& target;  //Character receiving the effect (can be same as applier)

	public:
		Effect(const EffectParams&);
		virtual ~Effect() {}

		virtual bool setup() { return true; }
		virtual void run() = 0;
};

#endif
