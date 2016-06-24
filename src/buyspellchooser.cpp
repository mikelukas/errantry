#include "buyspellchooser.h"

BuySpellChooser::BuySpellChooser(vector<const Spell*>* spellChoices, const Player& player)
	: SpellChooser(spellChoices, player)
{

}

void BuySpellChooser::displayInventoryChoices() const
{
	cout<<std::right<<setw(9)<<"Price"<<setw(8)<<"Name"<<setw(18)<<"Element"<<setw(10)<<"MP"<<endl;
	SpellChooser::displayInventoryChoices();
}

void BuySpellChooser::displaySpellLine(const Spell* spell) const
{
	cout<<"$"<<std::left<<setw(5)<<spell->getPurchasePrice()<<" - "<<setw(15)<<spell->getName()<<setw(14)<<getDisplayNameFor(spell->getElement())<<" "<<setw(3)<<spell->getMpCost()<<endl;
}

void BuySpellChooser::displayPostChoiceListInfo() const
{
	cout<<"***************"<<endl
		<<"*Gold:        *"<<endl
		<<"*  $"<<setw(10)<<player.Money()<<"*"<<endl
		<<"***************"<<endl;
}

bool BuySpellChooser::validate() const
{
	//First make sure player chose a valid choice number
	if(!Chooser::validate())
	{
		return false;
	}

	const Spell* chosenSpell = getChoice();

	//Check that they have enough gold to buy the spell
	if(chosenSpell->getPurchasePrice() > player.Money())
	{
		cout<<"Not enough gold! Price is $"<<chosenSpell->getPurchasePrice()<<"."<<endl;
		return false;
	}

	//Ensure they're not buying something they already have
	if(chosenSpell != NULL && player.hasSpell(chosenSpell))
	{
		cout<<"You already know '"<<chosenSpell->getName()<<"'!"<<endl;
		return false;
	}

	return true;
}
