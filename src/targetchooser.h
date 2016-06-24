#ifndef SRC_TARGETCHOOSER_H_
#define SRC_TARGETCHOOSER_H_

#include "character.h"
#include "chooser.h"

/* Displays a list of targets for the player to choose from and can return
 * the Character object mapping to that target
 */
class TargetChooser: public Chooser<Character>
{
	protected:

		void displayChoiceMenu() const;
		void displayChoice(int, Character*) const;
		void displayChoicePrompt() const;

	public:
		TargetChooser(const vector<Character*>*);
		virtual ~TargetChooser() {}
};

#endif
