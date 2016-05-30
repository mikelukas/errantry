#include "buyspellchooser.h"

BuySpellChooser::BuySpellChooser(const Player& player)
	: SpellChooser(player)
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
