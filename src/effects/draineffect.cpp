#include <iostream>
#include "../character.h"
#include "draineffect.h"

using std::cout;
using std::endl;

DrainEffect::DrainEffect(Element element, Character& applier, Character& target)
	: Effect(element, applier, target)
{

}

void DrainEffect::run()
{
	//postcondition: BASE
	int netDamage = target.applyMagicalDamage(BASE_DRAIN_HP, element);
	applier.ChangeHP(netDamage); //add to applier's HP amount done in magical damage

	cout<<applier.ShowName()<<" drained "<<netDamage<<" HP from "<<target.ShowName()<<"!"<<endl;
}
