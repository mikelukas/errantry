#ifndef SRC_STATUSES_STATUSEFFECT_H_
#define SRC_STATUSES_STATUSEFFECT_H_

#include "../effects/effect.h"
#include "statustemplate.h"

/* Base class for EFfects which are added to characters, allowing their effects
 * to persist across turns in mode, or even indefinitely.
 * onAdd() is called when a StatusEffect is added to a character
 * onRemove is called when a StatusEffect is removed from a character
 * onTurn() is called each turn that the player has the status, and will run
 * subclass-defined functionality, as well as decrement the effect duration
 * (not unlimited)
 *
 * Thus StatusEffects can have behavior that is run when they are added,
 * when they are removed, and each turn, if desired by subclasses, by
 * implementing onAdd(), onRemove() and runTurnEffect(), respectively.
 */
class StatusEffect: public StatusTemplate, public Effect
{
	protected:
		void setExpired();

	public:
		StatusEffect(const StatusTemplate&, const EffectParams&);
		virtual ~StatusEffect() {}

		virtual bool isExpired() const;

		virtual void onAdd() {}
		virtual void onRemove() {}

		virtual void onTurn();

		virtual void apply();
};

#endif
