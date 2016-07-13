#ifndef SRC_EFFECTS_MELTDOWNEFFECT_H_
#define SRC_EFFECTS_MELTDOWNEFFECT_H_

#include "effect.h"
#include "../equipment.h"

/* Abstract base class for Effect that converts 1 or more equipment of a given
 * time into raw magic damage applied to the target */
class MeltdownEffect: public Effect
{
protected:

	EquipmentLine* meltdownChoice;

	virtual EquipmentLine* chooseEquipment() const = 0;

public:
	MeltdownEffect(const EffectParams&);
	virtual ~MeltdownEffect();

	virtual bool setup();
	virtual void run();
};

#endif
