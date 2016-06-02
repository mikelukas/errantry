#include "targetchooser.h"

TargetChooser::TargetChooser(const vector<Character*>* eligibleTargets)
	: Chooser(eligibleTargets)
{

}

void TargetChooser::displayChoiceMenu() const
{
	//postcondition:
	cout<<"**********************MESSAGES**********************"<<endl;
	for(int i=0; i < eligibleChoices->size(); i++)
	{
		cout<<i+1<<")"<<(*eligibleChoices)[i]->ShowName()<<endl;
	}
	cout<<CANCELED_CHOICE<<")Back"<<endl;
	cout<<endl;
}

void TargetChooser::displayChoicePrompt() const
{
	cout<<"Choose a target:  ";
}
