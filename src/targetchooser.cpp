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
		displayChoice(i, (*eligibleChoices)[i]);
	}
	cout<<CANCELED_CHOICE<<")Back"<<endl;
	cout<<endl;
}

void TargetChooser::displayChoicePrompt() const
{
	cout<<"Choose a target:  ";
}

void TargetChooser::displayChoice(int choiceNum, Character* targetChoice) const
{
	cout<<choiceNum+1<<")"<<targetChoice->ShowName()<<endl;
}
