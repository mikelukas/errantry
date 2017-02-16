#ifndef SRC_INTROMODE_H_
#define SRC_INTROMODE_H_

#include "gamemode.h"

enum IntroState {TITLE, INSTRUCTIONS, PLAYER_NAME};

/* Simple mode run at the start of that game that displays the title, and optionally
 * instructions, then advances to OverworldMode.
 */
class IntroMode : public GameMode
{
	protected:

		IntroState state;

		virtual int updateDisplay();
		void displayTitle();
		void displayInstructions();
		void displayNamePrompt();

		virtual bool processInput(int);

		bool validateChoice(char answer);

		void initPlayerName();

	public:
		IntroMode(GameData&, GameState& gameState);
		~IntroMode() { };
};

#endif
