#include <sstream>

#include "equipmode.h"
#include "gamestate.h"

EquipMode::EquipMode(GameData& gameData, GameState& gameState)
	: ApplyEquipmentMode(gameData, gameState)
{

}

void EquipMode::displayRelevantPlayerAttrs()
{
	//postcondition: Displays currently-equipped weapon and armor, or "Fists" and/or
	//"T-Shirt" respectively if there is nothing equipped for each type, then
	//displays the player's current attributes for determining how they'd change
	//after equipping something

	Player& player = gameState.getPlayer();
	const Equipment* currWeapon = player.getCurrentEquipped(WEAPON);
	const Equipment* currArmor = player.getCurrentEquipped(ARMOR);

	cout<<"Current Weapon: "<<(currWeapon != NULL ? currWeapon->getName() : "Fists")<<endl
		<<"Current Armor:  "<<(currArmor != NULL ? currArmor->getName() : "T-Shirt")<<endl
		<<endl
		<<"Current Attributes:       "<<"AP: "<<setw(4)<<player.Damage()<<" DP: "<<setw(4)<<player.Defense()<<" SP: "<<setw(4)<<player.Speed()<<endl;
}

void EquipMode::displayEquipmentList()
{
	//postcondition: Displays weapons and armor in the player's inventory in
	//2 separate lists, one after the other respectively. Each equipment line
	//shows the change in stat(s) that would occur by equipping that equipment.
	//Numbers are displayed and increment successfully regardless of type, for
	//use by the player in selecting what he/she wishes to equip.

	const Equipment* currWeap = gameState.getPlayer().getCurrentEquipped(WEAPON);
	StatMod wStats = (currWeap != NULL) ? currWeap->getStatMod() : NO_STATMOD;

	const Equipment* currArmor = gameState.getPlayer().getCurrentEquipped(ARMOR);
	StatMod aStats = (currArmor != NULL) ? currArmor->getStatMod() : NO_STATMOD;

	int i = 0;
	cout<<"Weapons"<<endl;
	map<const Equipment*, EquipmentLine>& invWeapons = gameState.getPlayer().getInventoryFor(WEAPON);
	for(; i < invWeapons.size(); i++)
	{
		const Equipment* invEq = (*invEquipment)[i]->pEquipment;
		const StatMod& invStatMod = invEq->getStatMod();
		int apDiff = invStatMod.apMod - wStats.apMod;
		int dpDiff = invStatMod.dpMod - wStats.dpMod;
		int spDiff = invStatMod.spMod - wStats.spMod;

		std::ostringstream eqChoiceLabel;
		eqChoiceLabel<<i+1<<") "<<invEq->getName();
		if((*invEquipment)[i]->quantity > 1) {
			eqChoiceLabel<<" (x"<<(*invEquipment)[i]->quantity<<")";
		}
		cout<<std::left<<setw(26)<<eqChoiceLabel.str()<<std::right<<setw(8)<<apDiff<<setw(9)<<dpDiff<<setw(9)<<spDiff<<endl;
	}

	cout<<endl
		<<"Armor"<<endl;
	map<const Equipment*, EquipmentLine>& invArmor = gameState.getPlayer().getInventoryFor(ARMOR);
	for(; (i-invWeapons.size()) < invArmor.size(); i++)
	{
		const Equipment* invEq = (*invEquipment)[i]->pEquipment;
		const StatMod& invStatMod = invEq->getStatMod();
		int apDiff = invStatMod.apMod - aStats.apMod;
		int dpDiff = invStatMod.dpMod - aStats.dpMod;
		int spDiff = invStatMod.spMod - aStats.spMod;

		std::ostringstream eqChoiceLabel;
		eqChoiceLabel<<i+1<<") "<<invEq->getName();
		if((*invEquipment)[i]->quantity > 1) {
			eqChoiceLabel<<" (x"<<(*invEquipment)[i]->quantity<<")";
		}
		cout<<std::left<<setw(26)<<eqChoiceLabel.str()<<std::right<<setw(8)<<apDiff<<setw(9)<<dpDiff<<setw(9)<<spDiff<<endl;
	}
	cout<<endl;
}

void EquipMode::updateEquipmentChoices()
{
	//postcondition: populates invEquipment with dynamically allocated vector of
	//equipment.  invEquipment will be freed by cleanupEquipmentChoices()

	invEquipment = gameState.getPlayer().getWeaponsAndArmorAsVector();
}
