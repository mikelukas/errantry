#include <iostream>
#include <sstream>
#include "../character.h"
#include "doomedstatus.h"

using std::cout;
using std::endl;

DoomedStatus::DoomedStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{

}

void DoomedStatus::onAdd()
{
	cout<<target.ShowName()<<" is doomed!"<<endl;
}

void DoomedStatus::onRemove()
{
	//postcondition: if this status's duration hit 0, the target's HP is brought
	//to 0, otherwise, if it was removed prior to hitting 0 a message is displayed
	//stating that the target will not die.

	if(isExpired())
	{
		cout<<target.ShowName()<<" succumbs to Doom!"<<endl;
		target.ChangeHP(-(target.getEffectiveMaxHP()));
	}
	else
	{
		cout<<target.ShowName()<<" is saved from certain death!"<<endl;
	}
}

const string DoomedStatus::getName() const
{
	//postcondition: return's this status's name plus its remaining duration,
	//so it is clear how many turns the target has to live.

	std::stringstream doomSS;
	doomSS<<StatusEffect::getName()<<" "<<durationTurns;

	return doomSS.str();
}
