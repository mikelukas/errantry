#ifndef SRC_INTROMODE_H_
#define SRC_INTROMODE_H_

#include "gamemode.h"

/* Simple mode run at the start of that game that displays the title, and optionally
 * instructions, then advances to OverworldMode.
 */
class IntroMode : public GameMode
{
	protected:

		bool validateChoice(char answer);

		void initPlayerName();

	public:
		IntroMode(GameData&, GameState& gameState);
		~IntroMode() { };

		void run();
};

#endif
