#include "levelupchooser.h"

LevelUpChooser::LevelUpChooser()
	: Chooser<const LvlUpOpt>(buildLvlUpOptPointerVector())
{
	cancelAllowed = false;

}

vector<LvlUpOpt> vectorizeOptions()
{
	//postcondition: returns all enum values of LvlUpOpt in a vector, in the same
	//order as they appear in the enum.

	vector<LvlUpOpt> options;
	options.push_back(EVEN);
	options.push_back(ATK);
	options.push_back(DEF);
	options.push_back(MAG_DEF);

	return options;
}

const vector<const LvlUpOpt*>* buildLvlUpOptPointerVector()
{
	//postcondition: allocates a new vector of pointers to LvlUpOpts in the
	//LVL_UP_OPTIONS vector (mainly to comply w/ Chooser interface).

	vector<const LvlUpOpt*>* lvlUpOptPtrs = new vector<const LvlUpOpt*>();
	for (int i = 0; i < LVL_UP_OPTIONS.size(); i++)
	{
		lvlUpOptPtrs->push_back(&(LVL_UP_OPTIONS[i]));
	}

	return lvlUpOptPtrs;
}

void LevelUpChooser::displayChoiceMenu() const
{
	cout << "--------------------------------------" << endl;
	cout << "Increase:" << endl;
	//postcondition: displays a list of elements and choice numbers.
	for (int i = 0; i < eligibleChoices->size(); i++)
	{
		displayChoice(i, (*eligibleChoices)[i]);
	}
	cout << "--------------------------------------" << endl;
	cout << endl;
}

void LevelUpChooser::displayChoice(int choiceNum, const LvlUpOpt* opt) const
{
	cout << choiceNum+1 << ") ";
	switch (*opt)
	{
	case ATK:
		cout << "Attack";
		break;
	case DEF:
		cout << "Defense";
		break;
	case MAG_DEF:
		cout << "Magic Defense";
		break;
	default:
		cout << "Even";
		break;
	}
	cout << endl;
}