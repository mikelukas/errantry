#include <iostream>
#include "../character.h"
#include "channeleffect.h"

using std::cout;
using std::cin;
using std::endl;

ChannelEffect::ChannelEffect(const EffectParams& effectParams)
	: Effect(effectParams),
	  hpToChannel(0)
{

}

bool ChannelEffect::setup()
{
	//postcondition: prompts applier to choose HP to convert into magical damage,
	//and sets that amount into hpToChannel for when the effect is run.
	//returns true if the applier chose an amount > 0
	//returns false otherwise, allowing effect to be aborted.

	cout<<"Enter amount of your HP to convert into "<<getDisplayNameFor(element)<<" damage (up to "<<applier.Health()-1<<", 0 aborts): ";
	do
	{
		cin>>hpToChannel;
	}while(!validateChannelDamage(hpToChannel));

	return (hpToChannel > 0);
}

bool ChannelEffect::validateChannelDamage(int inputDamage)
{
	//postcondition: returns true if input damage is >= 0 and < applier's health
	//returns false otherwise.

	if(inputDamage < 0)
	{
		cout<<"Can't channel a negative amount of HP!"<<endl;
		return false;
	}

	if(inputDamage >= applier.Health())
	{
		cout<<"Are you crazy?! Channeling all of your HP would kill you!"<<endl;
		return false;
	}

	return true;
}

void ChannelEffect::apply()
{
	//postcondition: reduces applier's HP by amount they chose to convert in setup(),
	//and applies it as magical damage of this effect's element to the target,
	//showing how much damage was done after MDP adjustment.

	applier.ChangeHP(-1*hpToChannel);
	int netDamage = target.applyMagicalDamage(hpToChannel, fire);
	cout<<applier.ShowName()<<" channeled "<<hpToChannel<<" HP into "<<netDamage<<" "<<getDisplayNameFor(element)<<" damage to "<<target.ShowName()<<"!"<<endl;
}
