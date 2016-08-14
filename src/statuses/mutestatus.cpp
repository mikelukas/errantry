#include <iostream>
#include "../character.h"
#include "mutestatus.h"

using std::cout;
using std::endl;

MuteStatus::MuteStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{

}

void MuteStatus::onAdd()
{
	cout<<target.ShowName()<<" is unable to speak!"<<endl;
}

void MuteStatus::onRemove()
{
	cout<<target.ShowName()<<" can speak again."<<endl;
}
