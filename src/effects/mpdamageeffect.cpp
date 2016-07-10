#include <iostream>
#include "../character.h"
#include "mpdamageeffect.h"

using std::cout;
using std::endl;

MpDamageEffect::MpDamageEffect(Element element, Character& applier, Character& target)
	: Effect(element, applier, target)
{

}

void MpDamageEffect::run()
{
	//postcondition: target's MP is reduced by BASE_MP_DROP and a message is
	//displayed about how much.

	target.ChangeMP(-1*BASE_MP_DROP);

	cout<<target.ShowName()<<" lost "<<BASE_MP_DROP<<" MP!"<<endl;
}
