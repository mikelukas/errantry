#include "inventorychooser.h"

template <typename T>
InventoryChooser<T>::InventoryChooser(const vector<T*>* invChoices)
	: Chooser<T>(invChoices)
{

}

template <typename T>
void InventoryChooser<T>::displayChoiceMenu() const
{
	//postcondition: the player's current attributes relative to the type of
	//equipment they can apply in this mode are displayed, followed by eligible
	//equipment choices they can apply to themselves in this mode.

	cout<<"****************************************************"<<endl;
	displayRelevantStats();
	cout<<"----------------------------------------------------"<<endl;
	displayInventoryChoices();
	if(this->isCancelAllowed())
	{
		cout<<CANCELED_CHOICE<<") Back"<<endl;
	}
	displayPostChoiceListInfo();
	cout<<"**********************MESSAGES**********************"<<endl;
}
