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

	public:
		ChannelEffect(Element, Character&, Character&);
		virtual ~ChannelEffect() {}

		virtual bool setup();
		virtual void run();
};

#endif
