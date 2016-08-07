#include "effecttype.h"

const string getAdjectiveFor(EffectType type)
{
	//postcondition: returns a adjective string used to describe things affected
	//by the EffectType.
	//Not every Effect has an adjective; if an Effect does not, the empty string
	//is returned.

	switch(type)
	{
	case TEMPERED:
		return "stronger";
	case WEAKENED:
		return "weaker";
	case HARDENED:
		return "firmer";
	case FRAIL:
		return "frailer";
	case BLESSED:
		return "protected";
	case CURSED:
		return "unprotected";
	case HYPER:
		return "faster";
	case SLOWED:
		return "slower";
	case STUNNED:
		return "stunned";
	default:
		return "";
	}
}
