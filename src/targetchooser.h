#ifndef SRC_TARGETCHOOSER_H_
#define SRC_TARGETCHOOSER_H_

#include "character.h"
#include "chooser.h"

class TargetChooser: public Chooser<Character>
{
	protected:

		void displayChoiceMenu() const;
		void displayChoicePrompt() const;

	public:
		TargetChooser(const vector<Character*>*);
		virtual ~TargetChooser() {}
};

#endif
