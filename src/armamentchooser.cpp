#include "armamentchooser.h"

ArmamentChooser::ArmamentChooser(Character& character, int numWeapons, int numArmor)
	: InventoryChooser<EquipmentLine>(character.getWeaponsAndArmorAsVector()), //deleted in super-destructor
	  numWeapons(numWeapons),
	  numArmor(numArmor)
{
	// TODO Auto-generated constructor stub

}

void ArmamentChooser::displayInventoryChoices() const
{
	//postcondition: Displays weapons and armor in the character's inventory in
	//2 separate lists, one after the other respectively.
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
