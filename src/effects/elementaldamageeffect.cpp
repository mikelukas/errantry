#include <iostream>
#include "../character.h"
#include "elementaldamageeffect.h"

using std::cout;
using std::endl;

ElementalDamageEffect::ElementalDamageEffect(const EffectParams& effectParams)
	: Effect(effectParams)
{

}

void ElementalDamageEffect::apply()
{
	//postcondition: BASE_ELEMENTAL_DAMAGE magic damage, of an elemental type
	//matching this EFfect's element is applied to the target, with message
	//informing the user what the net damage was along with the elemental type

	int netDamage = target.applyMagicalDamage(BASE_ELEMENTAL_DAMAGE, element);

	cout<<applier.ShowName()<<" did "<<netDamage<<" "<<getDisplayNameFor(element)<<" damage to "<<target.ShowName()<<"!"<<endl;
}
