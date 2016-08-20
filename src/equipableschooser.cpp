#include "equipableschooser.h"
#include "statsdisplayer.h"

EquipablesChooser::EquipablesChooser(Player& player)
	: ArmamentChooser(player),
	  player(player)
{

}

void EquipablesChooser::displayRelevantStats() const
{
	//postcondition: Uses stats displayer to show attributes relevant for
	//making equipment decisions (current stats, current equipped Equipment, and
	//current Status immunities).

	StatsDisplayer::equipDisplayFor(player);
}

void EquipablesChooser::displayChoice(int choiceNum, EquipmentLine* invEqLine) const
{
	//postcondition: Each equipment line shows the change in stat(s) that would
	//occur by equipping that equipment.

	const Equipment* invEq = invEqLine->pEquipment;

	//slightly less efficient to look up curr equipment every loop iteration, since for a given loop will be the same, but trade-off is consolidating common code.
	const Equipment* currEquipped = player.getCurrentEquipped(invEq->getType());
	StatMod currEqStats = (currEquipped != NULL) ? currEquipped->getStatMod() : NO_STATMOD;

	const StatMod& invStatMod = invEq->getStatMod();
	int apDiff = invStatMod.apMod - currEqStats.apMod;
	int dpDiff = invStatMod.dpMod - currEqStats.dpMod;
	int mdpDiff = invStatMod.mdpMod - currEqStats.mdpMod;
	int spDiff = invStatMod.spMod - currEqStats.spMod;

	std::ostringstream eqChoiceLabel;
	eqChoiceLabel<<choiceNum+1<<") "<<invEq->getName();
	if(invEqLine->quantity > 1) {
		eqChoiceLabel<<" (x"<<invEqLine->quantity<<")";
	}
	cout<<std::left<<setw(23)<<eqChoiceLabel.str()<<std::right<<setw(8)<<apDiff<<setw(8)<<dpDiff<<setw(8)<<mdpDiff<<setw(8)<<spDiff<<endl;
}
