#include <iostream>
#include "blindstatus.h"
#include "../character.h"

using std::cout;
using std::endl;

BlindStatus::BlindStatus(const StatusTemplate& statusTemplate, const EffectParams& params)
	: StatusEffect(statusTemplate, params)
{

}

void BlindStatus::onAdd()
{
	cout<<target.ShowName()<<" can't see!"<<endl;
}

void BlindStatus::onRemove()
{
	cout<<target.ShowName()<<" can see again."<<endl;
}
