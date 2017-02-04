#ifndef SRC_LEVELUPCHOOSER_H_
#define SRC_LEVELUPCHOOSER_H_

#include "chooser.h"
#include "player.h"

vector<LvlUpOpt> vectorizeOptions();
const vector<const LvlUpOpt*>* buildLvlUpOptPointerVector();

const vector<LvlUpOpt> LVL_UP_OPTIONS = vectorizeOptions();

class LevelUpChooser : public Chooser<const LvlUpOpt>
{
	protected:

		virtual void displayChoiceMenu() const;
		virtual void displayChoice(int, const LvlUpOpt*) const;

	public:
		LevelUpChooser();
		virtual ~LevelUpChooser() {}
};

#endif
