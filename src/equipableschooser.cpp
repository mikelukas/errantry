#include "equipableschooser.h"

EquipablesChooser::EquipablesChooser(Player& player, int numWeapons, int numArmor)
	: EquipmentChooser(player.getWeaponsAndArmorAsVector()), //deleted in super-destructor
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
		<<"Current Attributes:       "<<"AP: "<<setw(4)<<player.Damage()<<" DP: "<<setw(4)<<player.Defense()<<" SP: "<<setw(4)<<player.Speed()<<endl;
}

void EquipablesChooser::displayInventoryChoices() const
{
	//postcondition: Displays weapons and armor in the player's inventory in
	//2 separate lists, one after the other respectively. Each equipment line
	//shows the change in stat(s) that would occur by equipping that equipment.
	//Numbers are displayed and increment successfully regardless of type, for
	//use by the player in selecting what he/she wishes to equip.

	const Equipment* currWeap = player.getCurrentEquipped(WEAPON);
	StatMod wStats = (currWeap != NULL) ? currWeap->getStatMod() : NO_STATMOD;

	const Equipment* currArmor = player.getCurrentEquipped(ARMOR);
	StatMod aStats = (currArmor != NULL) ? currArmor->getStatMod() : NO_STATMOD;

	int i = 0;
	cout<<"Weapons"<<endl;
	for(; i < numWeapons; i++)
	{
		const Equipment* invEq = (*invChoices)[i]->pEquipment;
		const StatMod& invStatMod = invEq->getStatMod();
		int apDiff = invStatMod.apMod - wStats.apMod;
		int dpDiff = invStatMod.dpMod - wStats.dpMod;
		int spDiff = invStatMod.spMod - wStats.spMod;

		std::ostringstream eqChoiceLabel;
		eqChoiceLabel<<i+1<<") "<<invEq->getName();
		if((*invChoices)[i]->quantity > 1) {
			eqChoiceLabel<<" (x"<<(*invChoices)[i]->quantity<<")";
		}
		cout<<std::left<<setw(26)<<eqChoiceLabel.str()<<std::right<<setw(8)<<apDiff<<setw(9)<<dpDiff<<setw(9)<<spDiff<<endl;
	}

	cout<<endl;

	cout<<"Armor"<<endl;
	for(; (i-numWeapons) < numArmor; i++)
	{
		const Equipment* invEq = (*invChoices)[i]->pEquipment;
		const StatMod& invStatMod = invEq->getStatMod();
		int apDiff = invStatMod.apMod - aStats.apMod;
		int dpDiff = invStatMod.dpMod - aStats.dpMod;
		int spDiff = invStatMod.spMod - aStats.spMod;

		std::ostringstream eqChoiceLabel;
		eqChoiceLabel<<i+1<<") "<<invEq->getName();
		if((*invChoices)[i]->quantity > 1) {
			eqChoiceLabel<<" (x"<<(*invChoices)[i]->quantity<<")";
		}
		cout<<std::left<<setw(26)<<eqChoiceLabel.str()<<std::right<<setw(8)<<apDiff<<setw(9)<<dpDiff<<setw(9)<<spDiff<<endl;
	}
	cout<<endl;
}