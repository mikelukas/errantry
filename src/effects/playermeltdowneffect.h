#ifndef SRC_EFFECTS_PLAYERMELTDOWNEFFECT_H_
#define SRC_EFFECTS_PLAYERMELTDOWNEFFECT_H_

#include "meltdowneffect.h"

/* Prompts player to choose equipment from their inventory to melt down into
 * magic damage.
 */
class PlayerMeltdownEffect : public MeltdownEffect
{
	protected:
		EquipmentLine* chooseEquipment() const;

		bool validateQuantityChoice(int, int) const;
	public:
		PlayerMeltdownEffect(Element, Character&, Character&);
		virtual ~PlayerMeltdownEffect() {}
};

#endif
