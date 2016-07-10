#ifndef SRC_EFFECTS_PLAYERADDWEAKNESSEFFECT_H_
#define SRC_EFFECTS_PLAYERADDWEAKNESSEFFECT_H_

#include "addweaknesseffect.h"

/* Prompts player to choose a weakness for the target, and applies it.*/
class PlayerAddWeaknessEffect: public AddWeaknessEffect
{
	protected:

		virtual Element chooseWeakness();

	public:
		PlayerAddWeaknessEffect(Element, Character&, Character&);
		virtual ~PlayerAddWeaknessEffect() {}
};

#endif
