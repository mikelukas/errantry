#include "effect.h"

EffectParams::EffectParams(Element element, Character& applier, Character& target)
	: element(element),
	  applier(applier),
	  target(target)
{

}

Effect::Effect(const EffectParams& effectParams)
	: element(effectParams.element),
	  applier(effectParams.applier),
	  target(effectParams.target)
{


}
