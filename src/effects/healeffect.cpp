#include <iostream>
#include "../character.h"
#include "healeffect.h"

using std::cout;
using std::endl;

HealEffect::HealEffect(Element element, Character& applier, Character& target)
	: Effect(element, applier, target)
{

}

void HealEffect::run()
{
	//postcondition: BASE_HEAL_HP is added to target's HP.

	target.ChangeHP(BASE_HEAL_HP);

	cout<<target.ShowName()<<" healed "<<BASE_HEAL_HP<<" HP!"<<endl;
}
