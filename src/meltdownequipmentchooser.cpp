#include "meltdownequipmentchooser.h"

MeltdownEquipmentChooser::MeltdownEquipmentChooser(Character& character)
	: ArmamentChooser(character)
{

}

void MeltdownEquipmentChooser::displayRelevantStats() const
{
	cout<<std::left<<setw(23)<<"Equipment"<<"Meltdown Damage"<<endl;
}

void MeltdownEquipmentChooser::displayChoice(int choiceNum, EquipmentLine* invEqLine) const
{
	//postcondition: display equipment name and how much raw fire damage it will
	//cause if melted down.

	const Equipment* invEq = invEqLine->pEquipment;

	std::ostringstream eqChoiceLabel;
	eqChoiceLabel<<choiceNum+1<<") "<<invEq->getName();
	if(invEqLine->quantity > 1) {
		eqChoiceLabel<<" (x"<<invEqLine->quantity<<")";
	}
	cout<<std::left<<setw(23)<<eqChoiceLabel.str()<<std::right<<setw(15)<<invEq->getStatMod().getMeltdownDamage()<<endl;
}
