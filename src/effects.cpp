#include <iostream>
#include "character.h"
#include "effects.h"
#include "elementchooser.h"
#include "meltdownequipmentchooser.h"

using std::cout;
using std::cin;
using std::endl;

void elementalDamage(Character& appliedBy, Character& target, int rawDamage, Element element)
{
	int netDamage = target.applyMagicalDamage(rawDamage, element);

	cout<<appliedBy.ShowName()<<" did "<<netDamage<<" "<<getDisplayNameFor(element)<<" damage to "<<target.ShowName()<<"!"<<endl;
}

void fireDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, fire);
}

void waterDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, water);
}

void airDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, air);
}

void earthDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, earth);
}

void nonElementalMagicDamageFunc(Character& appliedBy, Character& target)
{
	elementalDamage(appliedBy, target, BASE_ELEMENTAL_DAMAGE, none);
}

void healFunc(Character& appliedby, Character& target)
{
	target.ChangeHP(25);
}

void fearFunc(Character& appliedby, Character& target)
{
	//postcondition: caster is prompted to choose an Element, and target is made
	//weak to that element.

	ElementChooser elementChooser(target);
	elementChooser.run();

	const Element* elementChoice = elementChooser.getChoice();

	target.addWeakness(*elementChoice);

	cout<<target.ShowName()<<" is now weak to "<<getDisplayNameFor(*elementChoice)<<"."<<endl;
}

void enervateFunc(Character& appliedBy, Character& target)
{
	target.ChangeMP(-1*BASE_MP_DROP);

	cout<<target.ShowName()<<" lost "<<BASE_MP_DROP<<" MP!"<<endl;
}

void drainFunc(Character& appliedBy, Character& target)
{
	int netDamage = target.applyMagicalDamage(BASE_DRAIN_HP, water);
	appliedBy.ChangeHP(netDamage); //add to applier's HP amount done in magical damage

	cout<<appliedBy.ShowName()<<" drained "<<netDamage<<" HP from "<<target.ShowName()<<"!"<<endl;
}

void channelFunc(Character& appliedBy, Character& target)
{
	int baseChannelDamage;
	cout<<"Enter amount of your HP to convert into Fire damage (up to "<<appliedBy.Health()-1<<"): ";
	do
	{
		cin>>baseChannelDamage;
	}while(!validateChannelDamage(appliedBy, baseChannelDamage));

	appliedBy.ChangeHP(-1*baseChannelDamage);
	int netDamage = target.applyMagicalDamage(baseChannelDamage, fire);
	cout<<appliedBy.ShowName()<<" channeled "<<baseChannelDamage<<" HP into "<<netDamage<<" "<<getDisplayNameFor(fire)<<" damage to "<<target.ShowName()<<"!"<<endl;
}

bool validateChannelDamage(Character& appliedBy, int inputDamage)
{
	if(inputDamage < 0)
	{
		cout<<"Can't channel a negative amount of HP!"<<endl;
		return false;
	}

	if(inputDamage >= appliedBy.Health())
	{
		cout<<"Channeling all of your HP would kill you!"<<endl;
		return false;
	}

	return true;
}

void meltdownFunc(Character& appliedBy, Character& target)
{
	MeltdownEquipmentChooser eqChooser(appliedBy);
	eqChooser.run();

	EquipmentLine meltdownChoice(*(eqChooser.getChoice())); //Copy what they chose so we don't change the quantity of the actual inventory equipment here.

	//Can melt down more than 1 piece of the chosen equipment, so ask player for quantity
	const int available = meltdownChoice.quantity;
	do
	{
		cout<<"How many (up to "<<available<<")? ";
		cin>>meltdownChoice.quantity;
	} while(meltdownChoice.quantity < 1 && meltdownChoice.quantity > available);

	//Remove chosen quantity of chosen equipment
	appliedBy.RemoveEquipment(&meltdownChoice);

	//Convert equipment stats to damage and deal it to the target
	int rawMeltdownDamage = meltdownChoice.quantity * (meltdownChoice.pEquipment->getStatMod().getMeltdownDamage());
	int netDamage = target.applyMagicalDamage(rawMeltdownDamage, fire);

	cout<<appliedBy.ShowName()<<" melted down "<<meltdownChoice.quantity<<" "<<meltdownChoice.pEquipment->getName()<<" into "<<netDamage<<" "<<getDisplayNameFor(fire)<<" damage to "<<target.ShowName()<<"!"<<endl;
}

vector<EffectFunction> initEffects()
{
	vector<EffectFunction> effects;
	effects.push_back(&fireDamageFunc);
	effects.push_back(&waterDamageFunc);
	effects.push_back(&airDamageFunc);
	effects.push_back(&earthDamageFunc);
	effects.push_back(&nonElementalMagicDamageFunc);
	effects.push_back(&healFunc);
	effects.push_back(&fearFunc);
	effects.push_back(&enervateFunc);
	effects.push_back(&drainFunc);
	effects.push_back(&channelFunc);
	effects.push_back(&meltdownFunc);

	return effects;
}
