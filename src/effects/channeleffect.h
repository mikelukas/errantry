#ifndef SRC_EFFECTS_CHANNELEFFECT_H_
#define SRC_EFFECTS_CHANNELEFFECT_H_

#include "effect.h"

/* Applier chooses some amount of HP to loose, which will be converted into
 * raw (i.e. subject to MDP adjustment) magical damage applied to the target.
 */
class ChannelEffect: public Effect
{
	protected:
		int hpToChannel;

		bool validateChannelDamage(int);

		virtual void runTurnEffect();

	public:
		ChannelEffect(const EffectParams&);
		virtual ~ChannelEffect() {}

		virtual bool setup();
};

#endif
