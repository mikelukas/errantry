#ifndef SRC_EFFECTS_PLAYERREMOVEWEAKNESSEFFECT_H_
#define SRC_EFFECTS_PLAYERREMOVEWEAKNESSEFFECT_H_

#include "removeweaknesseffect.h"

/* Prompts player to choose a weakness for the target, and removes it.*/
class PlayerRemoveWeaknessEffect : public RemoveWeaknessEffect
{
	protected:
		Element chooseWeakness();

	public:
		PlayerRemoveWeaknessEffect(const EffectParams&);
		virtual ~PlayerRemoveWeaknessEffect() {}
};

#endif
