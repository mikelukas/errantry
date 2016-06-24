#include "equipableschooser.h"

EquipablesChooser::EquipablesChooser(Player& player, int numWeapons, int numArmor)
	: InventoryChooser<EquipmentLine>(player.getWeaponsAndArmorAsVector()), //deleted in super-destructor
	  player(player),
	  numWeapons(numWeapons),
	  numArmor(numArmor)
{

}

void EquipablesChooser::displayRelevantStats() const
{
	//postcondition: Displays currently-equipped weapon and armor, or "Fists" and/or
	//"T-Shirt" respectively if there is nothing equipped for each type, then
	//displays the player's current attributes for determining how they'd change
	//after equipping something

	const Equipment* currWeapon = player.getCurrentEquipped(WEAPON);
	const Equipment* currArmor = player.getCurrentEquipped(ARMOR);

	cout<<"Current Weapon: "<<(currWeapon != NULL ? currWeapon->getName() : "Fists")<<endl
		<<"Current Armor:  "<<(currArmor != NULL ? currArmor->getName() : "T-Shirt")<<endl
		<<endl
		<<"Current Attributes     "<<"AP: "<<setw(4)<<player.Damage()<<" DP: "<<setw(3)<<player.Defense()<<" MDP:"<<setw(3)<<player.MagicDefense()<<" SP: "<<setw(3)<<player.Speed()<<endl;
}

void EquipablesChooser::displayInventoryChoices() const
{
	//postcondition: Displays weapons and armor in the player's inventory in
	//2 separate lists, one after the other respectively. Each equipment line
	//shows the change in stat(s) that would occur by equipping that equipment.
	//Numbers are displayed and increment successfully regardless of type, for
	//use by the player in selecting what he/she wishes to equip.

	int i = 0;
	cout<<"Weapons"<<endl;
	for(; i < numWeapons; i++)
	{
		displayChoice(i, (*eligibleChoices)[i]);
	}

	cout<<endl;

	cout<<"Armor"<<endl;
	for(; (i-numWeapons) < numArmor; i++)
	{
		displayChoice(i, (*eligibleChoices)[i]);
	}
	cout<<endl;
}

void EquipablesChooser::displayChoice(int choiceNum, EquipmentLine* invEqLine) const
{
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
